#include "HandGestureLibrary.h"
#include "Colors.h"
#include "DrawCenters.h"
#include "trackColor.h"
#include "Coordinates.h"
#include "handDistance.h"
#include "ContourTimer.h"
#include <time.h>
#include "timer_1.h"
#include "timer_0.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <opencv2/opencv.hpp> //Contains: VideoCapture

using namespace cvflann;
using namespace std;
using namespace cv;


HandGestureLibrary::HandGestureLibrary()
{
}


HandGestureLibrary::~HandGestureLibrary()
{
}

void HandGestureLibrary::StartGestures(Colors firstColor, Colors secondColor, Mat framesThresholdRED, Mat framesThresholdCOLOR, Mat &framesOriginal, const string &windowNameGaussThresh, const int objectArea_min, const int objectArea_max)
{
	vector <Colors> reds, blues;
	vector <Colors> redStorage;
	ContourTimer contourNotFound, contourFound;
	bool wasContourFound = false;

	const int maxNumObjects = 50;

	//use "copyTo" to copy Matrix to another Matrix variable
	Mat thresholdImageRED, thresholdImageCOLOR;
	framesThresholdRED.copyTo(thresholdImageRED);
	framesThresholdCOLOR.copyTo(thresholdImageCOLOR);

	vector<Vec4i> hierarchyRED, hierarchyCOLOR;  //[x1, y1, x2, y2]: 32 bits, signed, 4 elements per vector
	vector< vector<Point> > contoursRED, contoursCOLOR; //output array of arrays

														//findContours(thresholdImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

														//apply gaussian blur to smooth edges
	GaussianBlur(thresholdImageRED, thresholdImageRED, Size(15, 15), -1);
	GaussianBlur(thresholdImageCOLOR, thresholdImageCOLOR, Size(15, 15), -1);

	// contours of RED and COLOR in the threshold image
	findContours(thresholdImageRED, contoursRED, hierarchyRED, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	findContours(thresholdImageCOLOR, contoursCOLOR, hierarchyCOLOR, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	
	rectangle(framesOriginal, Point(299, 259), Point(339, 219), Scalar(191, 0, 172), 2);
	//if found contours....
		//if timer is greater than 0 than timer has already started so keep going
		//if timer is = 0  than timer hasn't started and this is the first frame that contains contours
	//ContourTimer find;
	
	if (contoursRED.size() > 0)
	{
		wasContourFound = true;
	}
	else
	{
		wasContourFound = false;
	}
	//find.EndGesture(wasContourFound);

	if (wasContourFound == false)
	{
		putText(framesOriginal, "NO CONTOURS FOUND", Point(319, 200), 1, 1, Scalar(0, 255, 0), 2);
		bool objectFound = false;
		contourFound.EndGesture(objectFound, reds, framesOriginal);
	}

	//INSERT FUNCTION
	//if can't find any contours in the frame check how long it's been since program detected these contours
	//if it was less then 428.57 ms/3 frames ago then keep going
	//otherwise start timer over 

	//drawContours(framesOriginal, contoursRED, -1, Scalar(1, 1, 2550), 1, 8, hierarchyRED);
	//drawContours(framesOriginal, contoursCOLOR, -1, Scalar(1, 1, 2550), 1, 8, hierarchyCOLOR);



	double refArea = 0;
	bool objectFound = false;










	if (hierarchyRED.size() > 0 && hierarchyCOLOR.size() > 0)
	{
		int numObjectsRED = hierarchyRED.size();
		int numObjectsCOLOR = hierarchyCOLOR.size();

		if (numObjectsRED < maxNumObjects && numObjectsCOLOR < maxNumObjects)
		{
			for (int i = 0; i >= 0; i = hierarchyRED[i][0])
			{
				for (int j = 0; j >= 0; j = hierarchyCOLOR[j][0])
				{
					Moments momentRED = moments((cv::Mat)contoursRED[i]);
					Moments momentCOLOR = moments((cv::Mat)contoursCOLOR[j]);

					double areaRED = momentRED.m00;
					double areaCOLOR = momentCOLOR.m00;


					//IF area of RED and other COLOR is within range then get positions
					if (areaRED > objectArea_min && areaCOLOR > objectArea_min)
					{
						

						Colors red, blue;

						//set red to have the values of x and y
						red.setXPos(momentRED.m10 / areaRED);			//xPos=moment.m10/area then getXPos can use that value
						red.setYPos(momentRED.m01 / areaRED);			//yPos=moment.m01/area then getYPos can use that value
						red.setType(firstColor.getType());		//
						red.setColor(firstColor.getColor());		//

						reds.push_back(red);	//push back all the reds it finds into a vector (reds)
						//redStorage.push_back(red); //push back all reds into a vector and keep for next frame comparison
						


						blue.setXPos(momentCOLOR.m10 / areaCOLOR);			//xPos=moment.m10/area then getXPos can use that value
						blue.setYPos(momentCOLOR.m01 / areaCOLOR);			//yPos=moment.m01/area then getYPos can use that value
						blue.setType(secondColor.getType());		//
						blue.setColor(secondColor.getColor());		//

						blues.push_back(blue);	//push back all the reds it finds into a vector (reds)


						objectFound = true;
					}
					else
					{
						objectFound = false;
						//contourFound.EndGesture(objectFound, framesOriginal);
						//putText(framesOriginal, "CONTOURS NOT FOUND", Point(319, 200), 1, 1, Scalar(0, 255, 0), 2);
						//go to ContourTimer function to start timing how long it's been since last contour was found
						
					}
				}
			}

			if (objectFound == true)
			{
				Point center_Point;
				int k = 0;
				center_Point = Point(reds.at(k).getXPos(), reds.at(k).getYPos());
				Rect rect(Point(299, 259), Point(339, 219));

				if (rect.contains(center_Point))
				{
					contourFound.EndGesture(objectFound, reds, framesOriginal);
					putText(framesOriginal, "IN THE BOX", Point(reds.at(k).getXPos(), reds.at(k).getYPos() - 50), 1, 1, Scalar(0, 255, 0), 2);
				}


			}


		}
	}


	
	
}


void HandGestureLibrary::SwipeRight()
{

}
void HandGestureLibrary::SwipeLeft()
{

}
void HandGestureLibrary::Close()
{

}