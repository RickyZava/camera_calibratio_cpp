#pragma once
#include <string>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "config.h"

cv::Mat createCoordinates();
cv::Mat homography(const cv::Mat& coordinates, const cv::Mat& corners);
