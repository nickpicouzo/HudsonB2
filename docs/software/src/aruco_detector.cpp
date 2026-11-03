#include <iostream>
#include <vector>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect/aruco_detector.hpp>
#include <opencv2/core.hpp>


int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: aruco_detector <video_path>\n";
        return 1;
    }

    cv::VideoCapture capture(argv[1]);

    if (!capture.isOpened()) {
        std::cerr << "Could not open video.\n";
        return 1;
    }

    auto dictionary = 
        cv::aruco::getPredefinedDictionary(
            cv::aruco::DICT_4X4_50
        );

    cv::aruco::ArucoDetector detector(dictionary);

    cv::Mat frame;
    int frameCount = 0;
    int framesWithBoth = 0;
    int only0 = 0;
    int only1 = 0;
    int neither = 0; 

    while (capture.read(frame)) {

        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f>> corners;

        detector.detectMarkers(frame, corners, ids);

        bool found0 = false;
        bool found1 = false;

        for (int id : ids) {
            if (id == 0) found0 = true;
            if (id == 1) found1 = true;
        }

        if (found0 && found1) {
            ++framesWithBoth;
        }
	else if (found0) {
	    ++only0;
	}
	else if (found1) {
	    ++only1;
	}
	else {
	    ++neither;
	}

        ++frameCount;
    }

    if (frameCount != framesWithBoth + only0 + only1 + neither) {
    	std::cerr << "ERROR: Frame counts do not match\n";
    	return 1;
	}

    std::cout << "Frames processed: "
              << frameCount << '\n';

    std::cout << "Frames with both markers: "
              << framesWithBoth << '\n';	

    std::cout << "Frames with only marker 0: "
              << only0 << '\n';

    std::cout << "Frames with only marker 1: "
	      << only1 << '\n';

    std::cout << "Frames with neither markers: "
	      << neither << '\n';

    return 0;
}
