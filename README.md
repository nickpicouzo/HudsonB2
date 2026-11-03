# HudsonB2
**Vision-Based Approach Alignment Aircraft**

David Gleason and I, Nicholas Picouzo, are Juniors at the University of Miami studying Mechanical Engineering with an Aerospace concentration. We're designing and building a custom 3D-printed fixed-wing aircraft to test whether on-board sensing can tell us how far the aircraft is left or right of a marked runway, even when the nose is pointed away from it.

Our first experiment is was a fixture that let us adjust the camera position independently. We then compared the software's estimate against camera positions before in-flight testing. During our first test-flights the computer vision will record estimates, not control the aircraft. 

**Current Status**

[ArUco_Bench](docs/01-aruco-bench/README.md) completed. Results show that the initial ArUco detector had a 100 percent marker detection rate, processed every frame of the video and didn't miss any markers, and was able to identify unique ArUco IDs successfully. 

The system design and component decisions are being developed for the flight-critical avionics and the experimental vision payload. Print tests using PLA Aero using Nicholas' Bambu Lab P2S. 

**Team**

Nicholas: air frame sizing and SolidWorks design, 3D-printed structures, camera fixture, electrical integration, and flight testing.

David: camera calibration, lateral-offset estimation, rejection of unreliable measurements, onboard software, and synchronized logging and replay. 

**Next Milestones**

Nicholas: Complete [Aircraft Preliminary Design Review](docs/02-aircraft-pdr/README.md) and finalize aircraft sizing based on avionics and payload weights. 

David Gleason: Adding full ArUco dictionary support to ArUco_detector and developing orientation estimation. 
