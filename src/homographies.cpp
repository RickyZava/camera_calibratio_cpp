#include "homographies.h"

cv::Mat createCoordinates(){
    cv :: Mat coordinates(gridSizeRows*gridSizeColumn, 2  , CV_32F);
    int k=0;
    for (int i = 0; i < gridSizeRows; i++) {
        for (int j = 0; j < gridSizeColumn; j++) {
      coordinates.at<float>(k,0)=j;
      coordinates.at<float>(k,1)=i;
            k++;
        }

    }
    coordinates = coordinates*checkerboardSquareSize;
    //std::cout << "Coordinates:\n" << coordinates << "\n";
    return coordinates;
}

cv::Mat homography(const cv::Mat& coordinates, const cv::Mat& corners)
{
cv::Mat A =cv::Mat::zeros(2*coordinates.rows, 9, CV_64F);
for (int i = 0; i < coordinates.rows; i++) 
{

    double x = coordinates.at<float>(i, 0);
    double y = coordinates.at<float>(i, 1);
    double u = corners.at<float>(i, 0);
    double v = corners.at<float>(i, 1);


    A.at<double>(2*i, 0) = x;
    A.at<double>(2*i, 1) = y;
    A.at<double>(2*i, 2) = 1;
    A.at<double>(2*i, 6) = -u*x;
    A.at<double>(2*i, 7) = -u*y;
    A.at<double>(2*i, 8) = -u;
    A.at<double>(2*i+1, 3) = x;
    A.at<double>(2*i+1, 4) = y;
    A.at<double>(2*i+1, 5) = 1;
    A.at<double>(2*i+1, 6) = -v*x;
    A.at<double>(2*i+1, 7) = -v*y;
    A.at<double>(2*i+1, 8) = -v;





}     // solve with SVD: h = right singular vector of the smallest singular value

    cv::Mat w, u_, vt;
    cv::SVD::compute(A, w, u_, vt);
    cv::Mat H = vt.row(vt.rows - 1).reshape(1, 3 ).clone();   // 3x3, CV_64F
    H /= H.at<double>(2, 2);                                  // scale so H(2,2) = 1
    return H;
}

