#include "trackColor.h"
#include "DrawCenters.h"
#include "Coordinates.h"
#include "Colors.h"
#include "handDistance.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <opencv2/opencv.hpp> //Contains: VideoCapture
#include <string>

using namespace cv; // In std: VideoCapture
using namespace std;

void track::track_Color(Mat framesThreshold, Mat framesHSV, Mat &framesOriginal, const int objectArea_min, const int objectArea_max)
{
	vector <Colors> reds;
	//Colors red;

	const int maxNumObjects=50;

	//use "copyTo" to copy Matrix to another Matrix variable
	Mat thresholdImage;
	framesThreshold.copyTo(thresholdImage);

	vector<Vec4i> hierarchy;  //[x1, y1, x2, y2]: 32 bits, signed, 4 elements per vector
	vector< vector<Point> > contours; //output array of arrays

	findContours(thresholdImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	double refArea = 0;
	bool objectFound = false;

	if (hierarchy.size() > 0)
	{
		int numObjects = hierarchy.size();
		
		if (numObjects < maxNumObjects)
		{
			for (int i = 0; i >= 0; i = hierarchy[i][0])
			{
				Moments moment = moments((cv::Mat)contours[i]);

				double area = moment.m00;

				if (area > objectArea_min)
				{
					Colors red;
					red.setXPos(moment.m10 / area);
					red.setYPos(moment.m01 / area);

					//x = moment.m10 / area;
					//y = moment.m01 / area;

					reds.push_back(red);


					objectFound = true;
				}
				else objectFound = false;
			}

			if (objectFound == true)
			{
				draw center;
				center.draw_Center(reds, framesOriginal);

			}
			
		}
	}

}

void track::track_Color(Colors theColors, Mat framesThreshold, Mat framesHSV, Mat &framesOriginal, const string &windowNameGaussThresh, const int objectArea_min, const int objectArea_max)
{
	vector <Colors> reds;
	

	const int maxNumObjects = 50;

	//use "copyTo" to copy Matrix to another Matrix variable
	Mat thresholdImage;
	framesThreshold.copyTo(thresholdImage);

	vector<Vec4i> hierarchy;  //[x1, y1, x2, y2]: 32 bits, signed, 4 elements per vector
	vector< vector<Point> > contours; //output array of arrays

	//findContours(thresholdImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	//apply gaussian blur to smooth edges
	GaussianBlur(thresholdImage, thresholdImage, Size(15,15), -1);

	findContours(thresholdImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	drawContours(framesOriginal, contours, -1, Scalar(1, 1, 2550), 1, 8, hierarchy);



	double refArea = 0;
	bool objectFound = false;


	if (hierarchy.size() > 0)
	{
		int numObjects = hierarchy.size();

		if (numObjects < maxNumObjects)
		{
			for (int i = 0; i >= 0; i = hierarchy[i][0])
			{
				Moments moment = moments((cv::Mat)contours[i]);

				double area = moment.m00;

				if (area > objectArea_min)
				{
					Colors red;

					//set red to have the values of x and y
					red.setXPos(moment.m10 / area);			//xPos=moment.m10/area then getXPos can use that value
					red.setYPos(moment.m01 / area);			//yPos=moment.m01/area then getYPos can use that value
					red.setType(theColors.getType());		//
					red.setColor(theColors.getColor());		//
			

					reds.push_back(red);	//push back all the reds it finds into a vector (reds)

					
					objectFound = true;
				}
				else
				{
					objectFound = false;
				}
			}
			
			if (objectFound == true)
			{
				draw center;
				center.draw_Center(reds, framesOriginal);

			}


		}
	}

}

