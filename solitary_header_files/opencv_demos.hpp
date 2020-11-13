//Uncomment the following line if you are compiling this code in Visual Studio
//#include "stdafx.h"
/*
brew install opencv
g++ -std=c++11 a.cpp `pkg-config --cflags --libs opencv4`; ./a.out
*/

#include <opencv2/opencv.hpp>
#include <iostream>

// using namespace std;
// using namespace cv;

int show_image(std::string filename)
{

 // Read the image file
 cv::Mat image = cv::imread(filename);

 // Check for failure
 if (image.empty()) 
 {
  std::cout << "Could not open or find the image" << std::endl;
  std::cin.get(); //wait for any key press
  return -1;
 }

 cv::String windowName = "woo"; //Name of the window

 cv::namedWindow(windowName); // Create a window

 cv::imshow(windowName, image); // Show our image inside the created window.

 cv::waitKey(0); // Wait for any keystroke in the window

 cv::destroyWindow(windowName); //destroy the created window

 return 0;
}

int opencv_main(int argc, char** argv){


  show_image("/Users/Nick2/Downloads/meme4.jpg");



  return 0;
}


