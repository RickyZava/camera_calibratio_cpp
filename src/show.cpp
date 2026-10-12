#include "show.h"

void showCorners(const cv::Mat& corners)
{
    std:: cout << "Corners:\n" << corners << "\n";
}



void showChannels(const cv::Mat& image)
{
    cv :: Mat ch[3];
    cv :: split(image, ch); // split the image into its three channels (BGR)
    std :: cout << "R:\n" << ch[2](cv :: Rect(0,0,5,5))<< "\n";
    cv :: imshow("Red Channel", ch[2]);
}
   



void showImage(const std::string& path)
{
    std ::cout << "Attempting to load the image: " << path << "\n";
    cv :: Mat image= cv :: imread(path, cv :: IMREAD_COLOR);
   
    //showChannels(image); // Show the individual channels of the image

    if (image.empty()) {
        std :: cerr << "Error: Could not load the image.\n";
        return;
    }
    cv :: namedWindow("Loaded Image", cv :: WINDOW_NORMAL);
    cv :: imshow("Loaded Image", image);
    cv :: waitKey(0); // Wait for a key press

}
