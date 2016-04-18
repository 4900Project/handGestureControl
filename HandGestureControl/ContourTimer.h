#pragma once
#include "opencv2/core/utility.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <opencv2/opencv.hpp> //Contains: VideoCapture
#include <string>
#include "Colors.h"


class ContourTimer
{
public:
	ContourTimer();
	~ContourTimer();

	void EndGesture(bool objectFound, vector<Colors> firstColor, Mat &framesOriginal);
};

