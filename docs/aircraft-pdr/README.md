# Hudson B2 - Aircraft Preliminary Design Review (PDR)

**Version**: 0.1

**Date**: November 3rd, 2026

**Lead**: Nicholas Picouzo (Airframe, Mechanical Systems & Avionics Integration

**Status**: In Progress

# 1. Project Overview

The Hudson B2 is a custom 3D-printed fixed-wing unmanned aircraft designed to investigate vision-based lateral position estimation during landing approach.

The primary objective is to determine whether the on-board sensing can estimate an aircraft's signed lateral displacement from a marked runway centerline, independent of the aircraft's nose orientation.

The aircraft will carry a payload with an NVIDIA Jetson responsible for imaging, visual target detection, pose estimation, and experimental data recording.

A separate avionics bay will be responsible for controlling the aircraft under the supervision of a drone pilot. Initial flights will be conducted with manual flight control; the vision payload will not issue flight commands. 

The project combines aircraft preliminary design, additive manufacturing, electrical power distribution, embedded computing, computer vision, and experimental verification.

# 2. Purpose of the PDR

The PDR is used to establish justifications for the proposed design against mission requirements, payload constraints, aerodynamic performance, structural consideration, and electrical power requirement.

The PDR will establish preliminary design baselines for:

- `Aircraft sizing and aerodynamic geometry`

- `Airframe structural layout and manufacturing approach`

- `Aircraft mass budget and center-of-gravity envelope`

- `Flight-control avionics architecture`

- `Jetson vision payload architecture`

- `Electrical power generation, storage, regulation, and distribution`

- `Communication interfaces and subsystem integration`

- `Preliminary propulsion and control-actuation requirements`

- `Verification methods, design risks, and outstanding engineering decisions`

# 3. Mission Objectives

**Primary Objective**

Develop a fixed-wing aircraft that is capable of carrying an onboard vision system used for estimating lateral displacement relative to a runway centerline.

The vision system must distinguish lateral translation from changes in aircraft heading and provide timestamped estimates.

**Supporting Objectives**

- Design and manufactural a lightweight, structurally testable fixed-wing airframe using 3D-Printing and reinforcement where necessary.
- Integrate an NVIDIA Jetson, camera, storage, colling, and regulated power supply.
- Maintain seperation between the payload and the flight-critical avionics.
- Develop a documented and repeatable electrical and mechanical architecture.
- Verify the system on the ground before flight testing.
- Collect onboard image data, position estimates, telemetry, and diagnostic records during manual flight.
- Compare experimental performance against acceptance criteria.

# 4. Preliminary Aircraft Configuration

The initial configuration under consideration is a pusher fixed-wing aircraft.

The airframe will consist of a 3D-printed structure with a reinforced wing spar and access to electronics.

Initial aircraft sizing will follow these ranges:

| Parameter | Preliminary Range | Status |
|---|---|---|
| Configuration | Pusher | Proposed |
| Wingspan | 1.3-1.5 m | Under evaluation |
| Wing area | 0.28–0.36 m² | Under evaluation|
| Takeoff mass | 1.3-1.7 kg | Unverified |
| Primary structural material | PLA Aero | Under testing |
| Primary onboard computer | NVIDIA Jetson Orin Nano 8GB | Confirmed |
| Flight-control architecture | Independent pilot-controlled system | Required under scope|
| Vision Payload | Single-camera marker-based position estimation | Under Development |
| Flight power source | Battery-power | Architecture TBD |
| 3D Printer | Bambu Lab P2S | Confirmed |

Two wing layouts will be compared during the PDR abased on wing loading, stall-speed estimates, and manufacturing/design considerations.

# 5. System Architecture

The aircraft is divided into two primary systems.

**5.1 Flight-Critical Avionics**

The avionics are responsible for receiving pilot commands, measuring aircraft motion, executing the selected flight mode, and controlling propulsion and actuators.

Principal components are:
- Remote-control transmitter and receiver
- Flight controller and onboard inertial sensors
- GNSS
- Electronic speed controller
- Propulsion motor and propeller
- Aileron, elevator, and rudder servos
- Power supply
- Actuator power distribution

The exact components remain to be selected.

**5.2 Experimental Vision Payload**

The payload is responsible imaging, estimating lateral displacement, and recording experimental data.

Principle components are:
- NVIDIA Jetson
- Compatible camera and lens
- Camera mounting and alignment system
- Data storage
- Thermal management hardware
- Dedicated payload power branch

The flight controller will transmit telemetry to the Jetson through a one-way interface. The Jetson will not transmit any flight-control commands. 

**5.3 Electrical Power Architecture**

The PDR will investigate a primary flight battery supplying power for:
1. Propulsion
2. Flight-control avionics
3. Control-surface actuation
4. Experimental vision payload

The flight control and payload branches may share the primary battery.

A primary requirements is that a Jetson shutdown, restart, disconnection, or invalid output will not interrupt aircraft control or actuator operation. 

# 6. Preliminary Design Workstreams

## 6.1 Aircraft Sizing and Aerodynamics

**Lead**: Nicholas

Determine the preliminary aircraft geometry.

Planned analyses:
- Wing area and wingspan trade study
- Wing loading and aspect ratio
- Airfoil selection and relevant Reynolds-number conditions
- Preliminary stall-speed estimates
- Tail geometry and stability estimates
- Center-of-gravity and margin evaluation
- Control-surface sizing

## 6.2 Structural Design and Manufacturing

**Lead**: Nicholas

Develop a SolidWorks assembly for the aircraft structural and mechanical configuration.

The design will consider wing sections, spars, root joints, fuselage separation, electronics mounting and access.

PLA Aero tests are currently being conducted and evaluated prior to airframe production.

## 6.3 Mass Properties and Center of Gravity

**Lead**: Nicholas

Develop a mass budget that includes airframe, propulsion system, batteries, flight-control hardware, and the Jetson payload. 

The mass model will track both estimated and measured components weight, and placement positions

## 6.4 Avionics and Power Distribution

**Lead**: Nicholas

Define the flight-control electrical architecture.

Decisions will include:
- Flight-controller software and hardware
- Receiver and telemetry
- Battery voltage and power requirements
- Power regulation
- Servo and ESC power requirements
- Electrical fault protection
- Wiring, grounding, and connectors

## 6.5 Vision Payload Integration

**Leads**: Nicholas (hardware integration); David (Software and image-processing)

Define the electrical, mechanical, optical, and computational requirements of the payload.

Addressing:
- Camera compatibility
- Camera optical center and mounting
- Payload power consumption
- Thermal management and ventilation
- Data storage and recording performance
- Timestamp handling and telemetry
- Removable and repeatable camera installation

# Current Status

**As of November 3rd, 2026**

| Item | Status|
|---|---|
| PDR requirements and scope | Initial development |
| Aircraft sizing | Preliminary study; not finalized |
| Wing geometry | Comparison pending |
| Mass and CG budget | Initial model; measurements required |
| SolidWorks airframe assembly | Not released |
| PLA Aero material testing | Material prepped; tests started |
| Jetson Computing Hardware | Owned; software under development|
| Camera and payload hardware | Not selected |
| Flight controller and avionics | Not selected |
| Electrical Power architecture | Not yet finalized |

*Hudson B2 — Aircraft Preliminary Design Review | Version 0.1 | November 3, 2026*
