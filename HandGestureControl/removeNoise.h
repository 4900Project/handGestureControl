#include "Colors.h"
#include <opencv2/opencv.hpp> //Contains: VideoCapture


using namespace cv; // In std: VideoCapture,


class remove_Noise
{
public: void noise(Mat &threshNoise);
		void noise(Mat &threshNoise, Colors theColor);

};