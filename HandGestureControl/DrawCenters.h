
#include <vector>
#include <iostream>
#include <sstream>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <opencv2/opencv.hpp> //Contains: VideoCapture
#include <string>
#include "Colors.h"

using namespace cv;
using namespace std;

class draw
{
public: //void draw_Center(vector<Colors> theColors, Mat &framesOriginal, int countFails);
		void draw_Center(vector<Colors> theColors, Mat &framesOriginal);
		void draw_Center(vector<Colors> firstColor, vector<Colors> secondColor, Mat &framesOriginal);

};