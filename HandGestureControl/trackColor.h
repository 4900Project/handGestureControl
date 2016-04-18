
#include <opencv2/opencv.hpp> //Contains: VideoCapture
#include "Colors.h""

using namespace cv;

class track
{

public: 		
	
		void track_Color(Mat framesThreshold, Mat framesHSV, Mat &framesOriginal, const int objectArea_min, const int objectArea_max);
		void track_Color(Colors theColors, Mat framesThreshold, Mat framesHSV, Mat &framesOriginal, const string &windowNameGaussThresh, const int objectArea_min, const int objectArea_max);


};

