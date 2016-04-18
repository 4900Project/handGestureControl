#include "Colors.h"
#include "DrawCenters.h"
#include "trackColor.h"
#include "Coordinates.h"
#include "handDistance.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <opencv2/opencv.hpp> //Contains: VideoCapture


using namespace std;
using namespace cv;


Colors::Colors()
{
}


Colors::Colors(string name)
{
	setType(name);
	Colors failHSV;
	Colors countFails;

	if (name == "red")
	{
		setminHSV(Scalar(160,165,0));
		setmaxHSV(Scalar(256,256,256));

		setColor(Scalar(5, 5, 236)); //Sets text color to red
	}

	if (name == "blue")
	{
		setminHSV(Scalar(101, 225, 69));
		setmaxHSV(Scalar(142, 256, 256));

		setminHSV(Scalar(51, 0, 9));
		setmaxHSV(Scalar(135, 243, 106));

		setColor(Scalar(236, 5, 21)); //Sets text color to red
	}

	if (name == "green")
	{
		setColor(Scalar(5, 369, 13)); //Sets text color to red

		setminHSV(Scalar(66, 172, 0));
		setmaxHSV(Scalar(94, 256, 132));

		//setminHSV(Scalar(66, 172, 0));
		//setmaxHSV(Scalar(79, 256, 132));

		//setminHSV(Scalar(66, 74, 55));
		//setmaxHSV(Scalar(88, 256, 256));

		//setminHSV(Scalar(61, 185, 5));
		//setmaxHSV(Scalar(92, 256, 126));

	}

	if (name == "yellow")
	{
		setColor(Scalar(5, 236, 228)); //Sets text color to red
		
			setminHSV(Scalar(25, 35, 160));
			setmaxHSV(Scalar(33, 236, 192));

			setminHSV(Scalar(23, 46, 130));
			setmaxHSV(Scalar(31, 256, 218));

			setminHSV(Scalar(18, 46, 154));
			setmaxHSV(Scalar(31, 251, 200));

			setminHSV(Scalar(23, 135, 130));
			setmaxHSV(Scalar(43, 256, 218));

			setminHSV(Scalar(25, 40, 147));
			setmaxHSV(Scalar(48, 256, 238));

			setminHSV(Scalar(25, 112, 127));
			setmaxHSV(Scalar(48, 256, 238));

	}

	if (name == "orange")
	{
		setColor(Scalar(5, 136, 236)); //Sets text color to red

			setminHSV(Scalar(3, 173, 165));
			setmaxHSV(Scalar(21, 256, 256));

			setminHSV(Scalar(7, 201, 127));
			setmaxHSV(Scalar(18, 256, 239));

			setminHSV(Scalar(0, 129, 165));
			setmaxHSV(Scalar(21, 256, 256));

			setminHSV(Scalar(0, 193, 149));
			setmaxHSV(Scalar(25, 256, 243));

	}
}

Colors::~Colors()
{
}

int Colors::getXPos()	//within the Colors class so it can access all the variables in it
{
	return Colors::xPos;
}

void Colors::setXPos(int x)		//take the value that we pass, x, and set xPos to x
{
	Colors::xPos = x;
}

int Colors::getYPos()
{
	return Colors::yPos;
}

void Colors::setYPos(int y)
{
	Colors::yPos = y;
}

Scalar Colors::getminHSV()
{
	return Colors::minHSV;
}

Scalar Colors::getmaxHSV()
{
	return Colors::maxHSV;
}

void Colors::setminHSV(Scalar min)
{
	Colors::minHSV = min;
}

void Colors::setmaxHSV(Scalar max)
{
	Colors::maxHSV = max;
}