#include "DrawCenters.h"
#include "trackColor.h"
#include "Colors.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace cv; // In std: VideoCapture
using namespace std;

void draw::draw_Center(vector<Colors> theColors, Mat &framesOriginal)

{
	for (int i = 0;i < theColors.size(); i++)
	{

		circle(framesOriginal, Point(theColors.at(i).getXPos(), theColors.at(i).getYPos()), 10, Scalar(0, 255, 0), 2);

		string X, Y, coords, COUNTF;

		stringstream ss_X;
		ss_X << theColors.at(i).getXPos();
		X = ss_X.str();
		stringstream ss_Y;
		ss_Y << theColors.at(i).getYPos();
		Y = ss_Y.str();

		coords = X + ", " + Y;

		putText(framesOriginal, coords, Point(theColors.at(i).getXPos(), theColors.at(i).getYPos() + 30), 1, 1, Scalar(0, 255, 0), 2);
		putText(framesOriginal, theColors.at(i).getType(), Point(theColors.at(i).getXPos(), theColors.at(i).getYPos() - 30), 1, 2, theColors.at(i).getColor());
	}
}
void draw::draw_Center(vector<Colors> firstColor, vector<Colors> secondColor, Mat &framesOriginal)

{
	for (int i = 0;i < firstColor.size(); i++)
	{
		for (int j = 0;j < secondColor.size(); j++)
		{
			circle(framesOriginal, Point(firstColor.at(i).getXPos(), firstColor.at(i).getYPos()), 10, Scalar(0, 255, 0), 2);
			circle(framesOriginal, Point(secondColor.at(j).getXPos(), secondColor.at(j).getYPos()), 10, Scalar(0, 255, 0), 2);
			string X, Y, coords, COUNTF;

			stringstream ss_X;
			ss_X << firstColor.at(i).getXPos();
			X = ss_X.str();
			stringstream ss_Y;
			ss_Y << firstColor.at(i).getYPos();
			Y = ss_Y.str();

			coords = X + ", " + Y;

			putText(framesOriginal, coords, Point(firstColor.at(i).getXPos(), firstColor.at(i).getYPos() + 30), 1, 1, Scalar(0, 255, 0), 2);
			//putText(framesOriginal, theColors.at(i).getType(), Point(theColors.at(i).getXPos(), theColors.at(i).getYPos() - 30), 1, 2, theColors.at(i).getColor());
		}
	}
}