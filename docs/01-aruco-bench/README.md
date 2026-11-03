# 01 · ArUco bench setup and first marker detection

**Question:** Can the detector identify the three printed markers in a saved image from our camera setup?


## 1. Physical setup

The ArUco markers are displayed on an iPhone Duo that is propped up on a stack of books. Three tape markers are placed in front of the Duo, one in front, and two off to the sides at an angle. 

<!-- After uploading your image, remove the comment markers around the next line. Adjust the extension to match the uploaded file. -->
<!-- ![Phone on books facing the three markers, with the four setup dimensions](./setup-dimensioned.png) -->

| Dimension | Value | Where the measurement starts and ends |
| --- | ---: | --- |
| Screen midpoint height | 16.5 cm | Floor vertically up to the midpoint of the phone screen. |
| Phone to rear-center marker | 80 cm | Along the floor, from directly below the phone screen to the edge of the rear-center marker facing the phone. |
| Left marker spacing | 20 cm | From the midpoint of the rear-center marker’s front edge to the inside edge of the left marker, measured laterally. |
| Right marker spacing | 20 cm | From that same midpoint to the inside edge of the right marker, along the same lateral line. |



**Before taking the setup apart:** record the phone model, active lens, measurement tool and smallest division, printed black-square side length, and the position and orientation of each marker. Record the front-to-back offset of each side marker relative to the rear-center marker; lateral spacing alone does not locate them on the floor. Keep the original, unannotated setup photo.

## 2. Method for the first run

1. Read the expected left, rear-center and right marker IDs from the print files **before** running the detector. Record which ArUco dictionary generated them.
2. Capture a still from the phone camera that sees the markers. Save the original detector input without arrows, labels or cropping. Record resolution, lens/zoom, lighting and any image transformation.
3. Run the C++ detector on that saved input using the matching dictionary. Save a separate overlay with marker outlines and IDs. Use the same frame for both pictures.
4. Compare the returned IDs with the expected ones. Note missing and unexpected IDs, even when the result looks convincing. As a separate check, cover all markers and repeat with a new input; the expected result is no IDs.

**Decision rule for this check:** the baseline frame matches only if all three expected IDs and no unexpected IDs are returned. This is a check on one frame, not a detection rate or a position estimate.

## 3. Software and reproduction

| Item | Value used for this run |
| --- | --- |

| Capture device, active lens, resolution | iPhone 15 Pro, |
| Processing machine and OS (separate from capture device) | Not recorded yet |
| C++ standard, compiler version, CMake version, OpenCV version | Not recorded yet |
| ArUco dictionary and detector settings (defaults or overrides) | Not recorded yet |
| Expected IDs: left / rear-center / right | Not recorded yet |
| Detector source at the exact Git commit | Not linked yet |
| Starting directory; exact configure, build and run commands | Not recorded yet |

## 4. Evidence and observations

<!-- After the files exist, remove the comment markers around the corresponding image lines. Copy the actual filenames exactly. -->
<!-- ![Run 001 original camera frame](./run-001-input.png) -->
<!-- ![Run 001 detector output on the same frame, with outlines and IDs](./run-001-overlay.png) -->

| Run | Condition | Expected | Observed IDs, missing IDs or unexpected IDs | Outcome |
| --- | --- | --- | --- | --- |
| 001 | Three markers visible | Exact three print IDs; record them before the run | Not recorded | Pending |
| 002 | All markers covered | No IDs | Not recorded | Pending |

**Next decision:** Once the baseline is repeatable, measure the marker corners in a common coordinate system and calibrate the camera before testing signed lateral offset. This first record does not establish accuracy or Jetson performance.
