#include "DrawCenters.h"
#include "trackColor.h"
#include "Colors.h"
#include "Coordinates.h"
#include "handDistance.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <opencv2/opencv.hpp> //Contains: VideoCapture
using namespace cv; // In std: VideoCapture
using namespace std;

handDistance::handDistance()
{
}


handDistance::~handDistance()
{
}

void handDistance::findDistance(vector<Colors> firstColor, vector<Colors> secondColor, Mat &framesOriginal)
{
	int X1, X2, Y1, Y2;
	
	for (int i = 0; i < firstColor.size(); i++)
	{
		for (int j = 0;j < secondColor.size(); j++)
		{
			X1 = firstColor.at(i).getXPos();
			Y1 = firstColor.at(i).getYPos();
			X2 = secondColor.at(j).getXPos();
			Y2 = secondColor.at(j).getYPos();
			line(framesOriginal, Point(X1, Y1), Point(X2, Y2), Scalar(208, 15, 169), 3, 8);

		}

	}
}
		
		








