#include "removeNoise.h"
#include "Colors.h"
#include <opencv2/opencv.hpp> //Contains: VideoCapture

using namespace cv; // In std: VideoCapture,


void remove_Noise::noise(Mat &threshNoise)
{
	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(7, 7));
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(9, 9));

	erode(threshNoise, threshNoise, erodeElement);

	dilate(threshNoise, threshNoise, dilateElement);
	dilate(threshNoise, threshNoise, dilateElement);

}
void remove_Noise::noise(Mat &threshNoise, Colors theColor)
{
	if (theColor.getType() == "red")
	{
		Mat erodeElement = getStructuringElement(MORPH_RECT, Size(40, 40));
		Mat dilateElement = getStructuringElement(MORPH_RECT, Size(20, 20));

		erode(threshNoise, threshNoise, erodeElement);

		dilate(threshNoise, threshNoise, dilateElement);
		//dilate(threshNoise, threshNoise, dilateElement);
	}

}