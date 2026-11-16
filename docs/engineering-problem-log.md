# HudsonB2 — Engineering Problem & Debugging Log

**Canonical location:** `docs/engineering-problem-log.md` in the shared HudsonB2 Git repository.  
**Initialized:** 2026-11-15. **Status:** living engineering record; updates require review and version control.  
**Owners:** Nicholas (airframe/electrical/integration), David (software/perception), and the responsible agent team for each issue.

## Recording policy

Record a technical, hardware, software, integration, or workflow obstacle only when its **subjective resolution difficulty exceeds 4/10**. Consider diagnostic complexity, engineering knowledge required, troubleshooting effort, and impact on progress; difficulty is *not* a safety-severity score. Routine 1–4/10 issues may be solved without a formal entry. Reassess if an apparently simple issue becomes substantially more difficult.

- Use permanent sequential IDs `HB2-PRB-001`, `HB2-PRB-002`, etc. Before adding one, search for an existing entry; **update rather than duplicate** an issue. Allocate the next ID from the latest merged log, not from another agent's unmerged draft.
- Keep the timeline chronological. Add dated troubleshooting updates to the same entry; preserve unsuccessful attempts and evidence. Record the date first observed when known; use **date unverified** for retrospective items rather than inventing dates.
- Separate **observations**, **hypotheses**, **confirmed root causes**, **fixes/workarounds**, and **verification**. A passing software test does not prove a hardware or flight system has been validated.
- Allowed statuses: **Open**, **In progress**, **Resolved**. Mark **Resolved** only with documented verification; otherwise retain **In progress** and a specific next check.
- Link tests, issues, commits, logs, or revisioned evidence when available. If evidence remains only in a local agent workspace, mark it **not yet published to GitHub**. Avoid pasting credentials, access tokens, private URLs, unrelated private conversations, or other secrets into this public repository.
- Maintain **one** authoritative log; other agents and dashboards should reference this file rather than maintain conflicting duplicate logs. Propose changes on a branch or pull request. The named human owner reviews engineering claims.

## Index

| ID | First observed | Area | Problem | Difficulty | Owner | Status |
|---|---|---|---|---:|---|---|
| [HB2-PRB-001](#hb2-prb-001--duplicate-windows-csv-newlines) | 2026-11-09 | Analysis software | Windows CSV doubled line terminators | 6/10 | Systems / verification | Resolved |
| [HB2-PRB-002](#hb2-prb-002--duplicate-mass-allocation-ids) | 2026-11-09 | Analysis software | Duplicate IDs silently dropped allocation mass | 8/10 | Simulation / verification | Resolved |
| [HB2-PRB-003](#hb2-prb-003--vercel-access-from-school-network) | Nov 2026; exact day unverified | Infrastructure | Deployed website unreachable from school Wi-Fi | 6/10 | Workspace team | Resolved (workaround) |
| [HB2-PRB-004](#hb2-prb-004--supabase-account-invitation-flow) | Nov 2026; exact day unverified | Authentication | Invitation redirect and callback setup failures | 7/10 | Workspace team | Resolved |
| [HB2-PRB-005](#hb2-prb-005--background-sync-erasing-form-input) | Nov 2026; exact day unverified | Frontend | Auto-refresh cleared unsaved title/text | 6/10 | Workspace team | In progress |

## HB2-PRB-001 — Duplicate Windows CSV newlines

- **Problem:** A PDR-generated CSV had doubled carriage-return sequences (`CR CR LF`) on Windows, leading to apparent blank lines and unreliable CSV formatting.
- **Difficulty:** **6/10** — required byte-level diagnosis across CSV writer and Windows text newline translation; numerical parsing alone did not expose the issue.
- **Identification:** Independent PDR verification examined raw CSV bytes and reproduced 33 doubled newline sequences.
- **Root cause:** **Confirmed:** CSV writer emitted CRLF, then the Windows text-writing path translated line endings again.
- **Troubleshooting:** Reproduced the initial output; compared CSV row counts and raw bytes; traced the output path through `scripts/pdr_sensitivity.py`.
- **Resolution:** Updated the output-writing code to use explicit newline handling and regenerated the affected study artifacts.
- **Verification:** Independent check observed no `\r\r\n` sequences; final CSV had 33 physical lines (header + 32 data cases). PDR verification recorded **47 passing software tests**. This is formatting/software evidence only.
- **Lessons learned:** Test generated artifact bytes on target OS; parsing success does not guarantee valid physical serialization.
- **Status:** **Resolved**.
- **Evidence:** `docs/reviews/PDR-0001-verification.md` in Nicholas's agent workspace; **not verified on shared GitHub `main`** when this log was initialized.
- **Timeline:** 2026-11-09 — reproduced, corrected and independently rechecked.

## HB2-PRB-002 — Duplicate mass allocation IDs

- **Problem:** A Mission 004 calculation silently omitted mass because converting allocation entries to a dictionary overwrote an earlier entry with the same identifier.
- **Difficulty:** **8/10** — latent data-integrity defect in multidisciplinary mass budgets; outputs could appear plausible while being wrong.
- **Identification:** Independent verifier inserted a duplicate `fuselage_tail` ID and observed a sample total change from **1.138 kg to 0.989 kg**.
- **Root cause:** **Confirmed:** dictionary construction silently replaced an existing keyed allocation without rejecting duplicates.
- **Troubleshooting:** Constructed a duplicate-ID probe; traced how allocations were accumulated; checked identifier namespaces for shared/wing/spar/pack/configuration and output collisions.
- **Resolution:** Validation now rejects duplicate identifiers rather than silently replacing values, with a regression test for the probe.
- **Verification:** The same probe raised `ValueError: Duplicate shared identifier`; Mission 004 verification recorded **62 passing software tests** and independent replay. No physical mass budget was validated.
- **Lessons learned:** Enforce uniqueness at ingestion; preserve disjoint inclusion scopes; add adversarial tests for silent data loss in engineering accounting.
- **Status:** **Resolved**.
- **Evidence:** `docs/reviews/MISSION-004-verification.md` in Nicholas's agent workspace; **not verified on shared GitHub `main`** when this log was initialized.
- **Timeline:** 2026-11-09 — reproduced, fix implemented, regression verified.

## HB2-PRB-003 — Vercel access from school network

- **Problem:** The production workspace showed Ready in Vercel but timed out in Chrome on a school Wi-Fi connection.
- **Difficulty:** **6/10** — required separating deployment health, DNS, routing, TCP reachability, and app behavior.
- **Identification:** DNS resolved Vercel addresses; `Test-NetConnection` to port 443 failed on the school network. The same site loaded over cellular data.
- **Root cause:** **Hypothesis (not established):** institutional network policy or route/filter interference affecting the Vercel endpoint. DNS alone did not establish reachability.
- **Troubleshooting:** Compared normal/incognito browser, DNS and TCP tests, and cellular access. No Vercel app-code change was justified.
- **Resolution/workaround:** Switched the laptop to a personal hotspot, allowing access to the existing deployed website.
- **Verification:** User confirmed successful loading from the hotspot/cellular connection. School-network root cause remains unverified.
- **Lessons learned:** Isolate network path failures before redeploying working software; test from an independent network.
- **Status:** **Resolved (workaround)**. Reopen if school Wi-Fi access is required.
- **Evidence:** PowerShell connectivity screenshots and cross-network tests in the shared project conversation; not separately archived to Git.
- **Timeline:** Nov 2026 (exact day unverified) — hotspot confirmed working.

## HB2-PRB-004 — Supabase account invitation flow

- **Problem:** HudsonB2 user invitations redirected to `localhost:3000`, then account setup encountered a missing public Supabase configuration.
- **Difficulty:** **7/10** — cross-service authentication spanning Supabase Auth redirect configuration, an invite/recovery callback, static hosting, and user membership.
- **Identification:** Browser displayed localhost connection refusal; later showed a missing `config.js` publishable-key message; Supabase initially listed the account as awaiting verification.
- **Root cause:** **Confirmed configuration problems:** the default Auth Site URL pointed to an unavailable local development server, and the deployed callback initially lacked a populated public project configuration. A previously used invitation link also became unusable.
- **Troubleshooting:** Checked Site URL, deployed callback route, public configuration and Auth user state; generated new invite/recovery links instead of reusing expired ones.
- **Resolution:** Set the production HTTPS redirect, deployed a populated *public-key-only* `config.js`, and completed account setup and membership assignment.
- **Verification:** Both Nicholas and David subsequently appeared as verified authenticated users with appropriate `chief_engineer` and `software_lead` memberships; shared workspace records were visible after refresh.
- **Lessons learned:** Test complete authentication flows before inviting collaborators; correct URL, callback, key scope, and role provisioning are separate checks.
- **Status:** **Resolved**.
- **Evidence:** Supabase SQL membership confirmation and deployed-site screenshots in shared project conversation; do not store invitation token URLs.
- **Timeline:** Nov 2026 (exact day unverified) — redirected URL repaired; callback config fixed; independent users confirmed.

## HB2-PRB-005 — Background sync erasing form input

- **Problem:** A collaborator reported unsaved task/title text disappearing while typing in the shared website.
- **Difficulty:** **6/10** — intermittent UI state loss from asynchronous polling/re-render interactions.
- **Identification:** Source inspection revealed an eight-second background refresh that reconstructed the page and could replace active form inputs.
- **Root cause:** **Confirmed in source; browser reproduction not archived:** a polling-driven render could destroy unsaved form state.
- **Troubleshooting:** Compared observed form behavior to background polling logic; patched v0.2.2 to avoid rendering while a field or modal is actively being edited, including after in-flight fetches.
- **Resolution/workaround:** The v0.2.2 patch was prepared and its JavaScript syntax checked. Its production deployment and sustained-input behavior were **not independently confirmed** in the available evidence.
- **Verification still required:** On both user accounts, type in a task and proposal form for over 20 seconds; confirm no reset, save each record, refresh, and ensure persistence and correct ownership.
- **Lessons learned:** Never replace editable DOM state during background synchronization; preserve drafts independently of server polling and test slow-user interactions.
- **Status:** **In progress** pending explicit two-user regression evidence.
- **Evidence:** Workspace v0.2.2 patch and support conversation; exact deployment commit/version to be attached.
- **Timeline:** Nov 2026 (exact day unverified) — defect diagnosed and patch authored. 2026-11-15 — regression evidence still outstanding in this log.

---

## New entry template (copy when a qualifying issue occurs)

### HB2-PRB-XXX — Short problem title

- **Problem:** System, observed symptom, impact.
- **Difficulty:** **N/10** — why diagnostic complexity, effort and project impact justify logging (>4 only).
- **Identification:** How discovered, reproducible symptom and affected configuration.
- **Root cause:** **Confirmed** with evidence, or **Hypothesis** with an explicit verification plan.
- **Troubleshooting:** Date-ordered attempts, observations, failed approaches, commands or measurements.
- **Resolution/workaround:** Exact change and why it should work; write **not yet resolved** if uncertain.
- **Verification:** Test/replay/measured evidence and revision; note incomplete checks.
- **Lessons learned:** Transferable engineering and preventive practices.
- **Status:** **Open / In progress / Resolved**.
- **Owner:** Responsible human and supporting agent(s).
- **Evidence:** Relevant repository paths, commit hashes, data, or test records.
- **Timeline:** YYYY-MM-DD — observation → investigation → change → verification.
