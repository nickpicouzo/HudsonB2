# ArUco Marker Detection - Initial Bench Experiment

**Status:** Physical setup complete | Software validation pending
**Contributors:** Nicholas - physical setup and measurements; David - software and detection validation

## 1. Objective

The objective of this experiment is to establish a repeatable ArUco marker detection setup and verify whether the vision software can correctly identify the printed markers in captured images.

This experiment is the first step toward estimating the camera's position and signed lateral displacement relative to a runway centerline. 


## 2. Physical Setup

The three ArUco markers are displayed on the iPhone Duo, which is supported by a stack of books. Three tape reference markers are placed in front of the device: one centered and two offset to either side.


### Dimensioned setup

![Dimensioned physical setup](images/dimensioned_setup.png)

### Top-down layout

![Top-down schematic of the marker arrangement](images/top_down_sketch.png)

### Measured dimensions

| Parameter | Measurement | Reference |
|---|---|---|
| Screen midpoint height | 16.5 cm | Floor to screen midpoint |
| Center reference distance | 80.0 cm | Screen plane to facing edge of rear-center tape marker |
| Left reference spacing | 20.0 cm | Center midpoint to inside edge of left tape marker |
| Right reference spacing | 20.0 cm | Center midpoint to inside edge of right tape marker |

**Measurement notes:** Standard steel tape measure (Metric, 1mm resolution) 

## 3. Hardware

| Component | Configuration |
|---|---|
| Marker display | iPhone Duo |
| Camera | iPhone 15 Pro Main Camera - 24mm f1.78 |
| Processing computer | Surface Studio Laptop 2 |
| Marker dictionary | DICT_4X4_50 |
| Marker IDs | 0 and 1 | 
| Camera resolution | 2160 x 3840 |

## 4. Methodology

### 4.1 Physical Setup and Data Collection
1. iPhone Duo was propped up on books, distance from floor to display midpoint measured.
2. Measured a perpendicular distance 80 cm from the center of the display, and placed duct tape reference. Measured and placed offset references 20 cm from middle reference. 
3. Displayed the ArUco markers (0 & 1) on Duo display
4. Placed and secured the camera on the reference, recorded video for 5 seconds. 
5. Repeated step 4 with 7 videos: 
- `Center`
- `Left`
- `Right`
- `Left_Angled`
- `Right_Angled`
- `QR_Test`
- `No_Target`
### 4.2 Software Processing and Validation
6. Execute the ArUco detection program.
7. Save the returned marker IDs and detected corner coordinates.
8. Save an annotated output generated from the same input frame.
9. Compare expected and observed detections.
10. Record failures, test configuration and software revision.

## 5. Software

The ArUco marker detection program was implemented in C++17 using OpenCV 4.12.0 on Windows x64. The program processes prerecorded .MOV video files using cv::VideoCapture and identifies markers with OpenCV's cv::aruco::ArucoDetector.

Detector configuration:

Programming language: C++17
Computer vision library: OpenCV 4.12.0
ArUco dictionary: DICT_4X4_50
Target marker IDs: 0 and 1
Input: Prerecorded .MOV video
Processing: Every successfully decoded frame
Output: Total frame count and frame counts classified as BOTH, ONLY_0, ONLY_1, or NEITHER

**Source code:** arcuro_detector.cpp 

**Run command:** build\Release\aruco_detector.exe videos\<video_file>.MOV

**Software revision:** feature/aruco-detection branch, initial C++ ArUco detector implementation.

## 6. Experimental Results

### 6.1 Marker Detection Results

Eight prerecorded MOV files were processed using the ArUco detector. The program used the `DICT_4X4_50` dictionary to identify target marker IDs 0 and 1. Each successfully decoded frame was classified into one of four categories: `BOTH`, `ONLY_0`, `ONLY_1`, or `NEITHER`.

| Recording | Frames | BOTH | ONLY_0 | ONLY_1 | NEITHER |
|---|---:|---:|---:|---:|---:|
| center.MOV | 393 | 393 | 0 | 0 | 0 |
| left.MOV | 427 | 427 | 0 | 0 | 0 |
| leftAngled.MOV | 413 | 413 | 0 | 0 | 0 |
| right.MOV | 390 | 389 | 0 | 1 | 0 |
| rightAngled.MOV | 420 | 420 | 0 | 0 | 0 |
| neither.MOV | 406 | 0 | 0 | 0 | 406 |
| qrTest.MOV | 440 | 0 | 0 | 0 | 440 |
| singleID.MOV | 372 | 0 | 372 | 0 | 0 |

[Full detection results](results/frame_counts.csv)

### 6.2 Detection Performance

Across the recordings containing both markers, the detector identified both IDs in 2,042 of 2,043 frames, giving a **99.95%** both-marker detection rate.

The only incomplete two-marker detection occurred in `right.MOV`, where one frame contained marker 1 without marker 0.

The two negative-control recordings (`neither.MOV` and `qrTest.MOV`) produced no detections of target IDs 0 or 1 across 846 frames, and showed that the detector in this distinguish between true ArUco markers and plain QR codes under tested conditions.

The single-marker recording (`singleID.MOV`) correctly identified only marker 0 in all 372 frames.

### 6.3 Experimental Interpretation

The initial bench tests demonstrate consistent recognition of target IDs 0 and 1 across the recorded camera positions and orientations.

The results support progressing to marker-corner extraction, camera calibration, and geometric pose estimation.

These results verify marker visibility only. They do not demonstrate metric lateral-position estimation, yaw compensation, or latency performance.

### 6.4 Visual Evidence

Representative raw camera frames and detector-annotated images will be included in the [images](images/) directory.


## 7. Limitations

- Marker identification is not equivalent to calibrated camera pose estimation.
- Camera intrinsics and distortion must be determined for metric pose estimation.
- Dimensions and physical reference points must be verified before geometric calculations.
- Performance under different lighting, range and camera yaw is not yet established.

## 8. Next Steps

- Complete the first documented detection run.
- Save paired raw and annotated images.
- Measure and define all required marker coordinates.
- Calibrate the camera.
- Extend the experiment to camera pose and signed lateral offset estimation.
