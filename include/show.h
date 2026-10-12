#pragma once
#include <string>
#include <opencv2/opencv.hpp>
#include <iostream>


void showImage(const std::string& path);
void showChannels(const cv::Mat& image);
void showCorners(const cv::Mat& corners);
