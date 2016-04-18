#include "ContourTimer.h"
#include "HandGestureLibrary.h"
#include "Colors.h"
#include "DrawCenters.h"
#include "trackColor.h"
#include "Coordinates.h"
#include "handDistance.h"
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




ContourTimer::ContourTimer()
{
}


ContourTimer::~ContourTimer()
{
}

void ContourTimer::EndGesture(bool objectFound, vector<Colors> firstColor, Mat &framesOriginal)
{
	timer_1 isFound_Timer;
	timer_0 notFound_Timer;

	//double printStop_1, printStop_0;

	//printStop_1 = isFound_Timer.getStop_1();
	//printStop_0 = notFound_Timer.getStop_0();

	//string STOPvalue, STARTvalue;

	//stringstream stop_value;
	//stop_value << printStop_0;
	//STOPvalue = stop_value.str();

	//stringstream start_value;
	//start_value << printStop_1;
	//STARTvalue = start_value.str();

	//putText(framesOriginal, STOPvalue, Point(30, 230), 1, 1, Scalar(0, 255, 0), 2);

	//for (int i = 0;i < firstColor.size(); i++)
	//{
		if (objectFound == true)
		{
			//isFound_Timer.stop_1();
			if (isFound_Timer.getStop_1() == 0)
			{
				//this is the firt instance a contour was found
				//
				//putText(framesOriginal, "Contour FOUND. Start timer!", Point(30, 230), 1, 1, Scalar(0, 255, 0), 2);
				//isFound_Timer.reset_1();
				isFound_Timer.start_1();
				notFound_Timer.reset_0();
			}
			//else
			//{
				//timer has already started
				//stop the timer
			//	isFound_Timer.stop_1();

				//double getSTOP_1 = isFound_Timer.getStop_1();
				//stringstream ss_timer_1;
				//string finalTimer_1;
				//ss_timer_1 << getSTOP_1;
				//finalTimer_1 = ss_timer_1.str();

				//putText(framesOriginal, finalTimer_1, Point(60, 50), 1, 3, Scalar(0, 0, 215), 1);
				
				//if (isFound_Timer.getStop_1() > 3)
			//	{
				//	putText(framesOriginal, "START DOING GESTURES", Point(60, 150), 1, 3, Scalar(0, 0, 215), 1);
				//	isFound_Timer.reset_1();
				//	notFound_Timer.reset_0();

			//	}
			//	else
				//{
				//	isFound_Timer.start_1();
					//notFound_Timer.reset_0();
				//}
			//}
		}
		else      //NO CONTOURS WERE FOUND
		{
			//double getSTOP = notFound_Timer.getStop_0();
			//stringstream ss_timer;
			//string finalTimer;
			//ss_timer << getSTOP;
			//finalTimer = ss_timer.str();

			//putText(framesOriginal, finalTimer, Point(30, 250), 1, 1, Scalar(0, 255, 0), 2);

			//if the timer for no contours is 0, then start timer
			notFound_Timer.stop_0();
			if (notFound_Timer.getStop_0() == 0)
			{
				//first instance not finding a contour has occurred
				//notFound_Timer.reset_0();
				notFound_Timer.start_0();
				//notFound_Timer.stop_0();
				//double getSTOP = notFound_Timer.getStop_0();
				//stringstream ss_timer;
				//string finalTimer;
				//ss_timer << getSTOP;
				//finalTimer = ss_timer.str();

				//putText(framesOriginal, finalTimer, Point(30, 230), 1, 1, Scalar(0, 255, 0), 2);

			}
			else     //timer has already started
			{
				//notFound_Timer.stop_0();
				//double getSTOP = notFound_Timer.getStop_0();
				//stringstream ss_timer;
				//string finalTimer;
				//ss_timer << getSTOP;
				//finalTimer = ss_timer.str();
				//notFound_Timer.getStop_0();


				//putText(framesOriginal, finalTimer, Point(30, 250), 1, 1, Scalar(255, 0, 213), 2);
				if (notFound_Timer.getStop_0() > 10)
				{
					//if it's been longer than .43 seconds since last contour was found than don't check for hand gestures and reset the timer
					putText(framesOriginal, "OVER .5 SECS SINCE LAST CONTOUR WAS FOUND", Point(30, 230), 1, 1, Scalar(0, 255, 0), 2);
					//notFound_Timer.start_0();
					notFound_Timer.reset_0();
					//isFound_Timer.reset_1();
				}
				else
				{
					notFound_Timer.start_0();
				}

			}

		}
	//}

}