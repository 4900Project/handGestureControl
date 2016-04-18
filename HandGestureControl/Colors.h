#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <opencv2/opencv.hpp> //Contains: VideoCapture
#include <string>

using namespace std;
using namespace cv;

class Colors
{
public:
	Colors();
	~Colors();

	Colors(string name); //use the name that we pass through from main.cpp to here to set the type in private variables

	int getXPos();
	void setXPos(int x);	

	int getYPos();
	void setYPos(int y);

	Scalar getminHSV();
	void setminHSV(Scalar min);

	Scalar getmaxHSV();
	void setmaxHSV(Scalar max);

	string getType()
	{
		return type;
	}

	void setType(string t)
	{
		type = t;
	}

	Scalar getColor()
	{
		return displayColor;
	}

	void setColor(Scalar c)
	{
		displayColor = c;
	}


private:
	int xPos, yPos;
	string type; //what color?

	Scalar minHSV, maxHSV;
	Scalar displayColor;
	bool failHSV;
	int countFails;

};

