#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"
#include <Eigen/Dense>
#include "show.h"
#include "homographies.h"
#include "config.h"


int main() 
{


    cv::Mat allCorners(0, 2, CV_32F);
    cv::Mat homographyCollection(0, 9, CV_64F);  
    cv :: Mat coordinates;
    cv::Mat H ;
    coordinates = createCoordinates(); 

    for (int i = 0; i < numImages; i++) {
        // Point to a specific image, and use ../ to go up from the build folder
        std::string filepath = "/home/richard/camera_calibration/data/images_and_poses_for_camera_calibration/rgb_" + std::to_string(i) + ".png";
        showImage(filepath);
        cv::Mat image;
        image= cv::imread(filepath, cv::IMREAD_COLOR);
        cv::Mat image_gray;
        cv::cvtColor(image, image_gray, cv::COLOR_BGR2GRAY);
        cv::Size patternSize(gridSizeColumn, gridSizeRows);
        cv::Mat corners;

        bool patternFound = cv::findChessboardCorners(image_gray, patternSize, corners);
        if (patternFound) 
        {//std :: cerr << "Chessboard corners found in image: " << filepath << "\n";
         //showCorners(corners);
        }
        //allCorners.push_back(corners.reshape(1));

        H= homography(coordinates, corners);
        homographyCollection.push_back(H);

    }
    std::cout << "Homography Collection:\n" << homographyCollection << "\n";
    //std::cout << "Coordinates:\n" << coordinates << "\n";

    
    //std::cout << "All corners:\n" << allCorners << "\n";
  
}



   