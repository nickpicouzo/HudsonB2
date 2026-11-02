#include <iostream> //access to input/output functions
#include <opencv2/opencv.hpp> //access to OpenCV's video processing

int main(int argc, char* argv[]) { //entry point of program, defines argument count and array 
    if (argc != 2) { //requires exactly one supplied video path, otherwise fail 
        std::cerr << "Usage: replay <video_path>\n";
        return 1;
    }

    cv::VideoCapture capture(argv[1]); //identifies the 1st position in array as file name, 1st not 0th

      if (!capture.isOpened()) {
        std::cerr << "Could not open video\n";
        return 1;
    }
  
    double width = capture.get(cv::CAP_PROP_FRAME_WIDTH); //requests frame width/height from metadata
    double height = capture.get(cv::CAP_PROP_FRAME_HEIGHT); // and returns double as a catch-all for VideoCapture::get()
   
    cv::Mat frame;
    int true_width = 0; //sets initial values to 0 before verifying
    int true_height = 0;
    int frameCount = 0;

    if (capture.read(frame)) {
      true_width=frame.cols; //# of pixel columns
      true_height=frame.rows; //# of pixel rows
      ++frameCount; //counts the first successful frame 
     while (capture.read(frame)) { //loops through remaining frames
        ++frameCount;
      } 
    std::cout << "Frames processed: " // prints # frames
              << frameCount << '\n';
    std::cout << "Metadata dimensions: " 
              << width << "x" << height << std::endl; // prints Metadata-sourced dimensions and drops to the next line
    std::cout << "Decoded dimensions: "  
              << true_width << "x" << true_height << std::endl; //prints decoded dimensions
    return 0;
    } 
    else {
      std::cerr<< "Error: Could not read the first frame. Possible Video Corruption." << std::endl;
      return 1;
    }
 
}
