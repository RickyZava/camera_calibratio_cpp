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

void showRectangle(const std::string&  filepath_rect,const cv::Mat& H_selected)
{


    cv::Mat p0= (cv::Mat_<double>(3,1) << coordx,coordy,1.0);
   

    //std::cout << H_selected << "\n";

    cv::Mat p0Trasformed= H_selected * p0;
    p0Trasformed= p0Trasformed/p0Trasformed.at<double>(2,0);
    
    cv::Mat topRight= (cv::Mat_<double>(3,1)<< coordx+rect_width*checkerboardSquareSize,coordy,1.0);
    cv::Mat tR= H_selected*topRight;
    tR=tR/tR.at<double>(2,0);

    
    cv::Mat bottomLeft= (cv::Mat_<double>(3,1)<< coordx,coordy+rect_height*checkerboardSquareSize,1.0);
    cv::Mat bL= H_selected*bottomLeft;
    bL=bL/bL.at<double>(2,0);


    cv::Mat bottomRight= (cv::Mat_<double>(3,1)<< coordx+rect_width*checkerboardSquareSize,coordy+rect_height*checkerboardSquareSize,1.0);
    cv::Mat bR= H_selected*bottomRight;
    bR=bR/bR.at<double>(2,0);

    cv::Mat image_rect;
    image_rect= cv::imread(filepath_rect, cv::IMREAD_COLOR);



        // 1. Convert your 3x1 cv::Mat coordinates into OpenCV integer pixel points
    cv::Point pt_p0(p0Trasformed.at<double>(0, 0), p0Trasformed.at<double>(1, 0)); // Bottom Left
    cv::Point pt_tR(tR.at<double>(0, 0), tR.at<double>(1, 0));                     // Bottom Right
    cv::Point pt_bL(bL.at<double>(0, 0), bL.at<double>(1, 0));                     // Top Left
    cv::Point pt_bR(bR.at<double>(0, 0), bR.at<double>(1, 0));                     // Top Right

    // 2. Draw the 4 sides of the quadrilateral (Color: Green, Thickness: 2)
    cv::line(image_rect, pt_p0, pt_tR, cv::Scalar(0, 255, 0), 2); // Bottom edge
    cv::line(image_rect, pt_tR, pt_bR, cv::Scalar(0, 255, 0), 2); // Right edge
    cv::line(image_rect, pt_bR, pt_bL, cv::Scalar(0, 255, 0), 2); // Top edge
    cv::line(image_rect, pt_bL, pt_p0, cv::Scalar(0, 255, 0), 2); // Left edge

    // Show the image
    cv::imshow("Transformed Points", image_rect);
    cv::waitKey(0);



}

