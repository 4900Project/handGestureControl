//Detect and track a single color
//Open a RGB, HSV, and Threshold window
//Treshold window gives binary black(=0) and white(=1)
//Open up Trackbar to change HSV values to isolate selected color
//Isolating color will help give us values for computation

#define _CRT_SECURE_NO_DEPRECATE

#include <sstream>
#include <iostream>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <opencv2/opencv.hpp> //Contains: VideoCapture
#include <string>
#include "removeNoise.h"
#include "trackColor.h"
#include "Colors.h"
#include "handDistance.h"
#include "Coordinates.h"
#include "HandGestureLibrary.h"
#include "ContourTimer.h"
#include "timer_0.h"
#include "timer_1.h"
#include <vector>
#include <time.h>

using namespace cv; // In std: VideoCapture,
using namespace std; // In std: <string>, 

//INITALIZE 

//window width and height
const int Width = 640;
const int Height = 480;

//Names of the windows that will pop up and trackbar
const string windowNameOriginal = "Original Window";
const string windowNameHSV = "HSV Window";
const string windowNameThreshold = "Threshold Window";
const string windowNameTrackbars = "HSV Trackbars";
const string windowNameMorphTrans = "Morphological Transformations";
const string windowNameGaussThresh = "Gaussian Blur of Threshold";

//HSV trackbar min and max values
int H_min = 0;
int H_max = 256;
int S_min = 0;
int S_max = 256;
int V_min = 0;
int V_max = 256;

//min and max area of object being detected
//objects smaller than 25x25 pixels will be considered noise
//objects bigger than 3/4 of the screen probably just mean the HSV values need to be adjusted to make filter better
const int objectArea_min = 15 * 15;
const int objectArea_max = Width*Height*(3 / 4);



//FUNCTIONS

//call this function when track position is changed
void rangeControl(int, void*)
{}

//function to create Trackbar window
void Trackbars()
{
	char trackbarLabels[25]; //var for trackbar labels, max 25 characters in length

	// make the trackbar window
	namedWindow(windowNameTrackbars, 0);  // Userdata=0, otherwise autosize

	// now create trackbars for the window created
	//&var means you are passing address of variable (pointer)
	//createTrackbar(trackbarname, winname, value, count, OnChange)
	//trackbarname: name of the created trackbar
	//winname: name of parent window for trackbar
	//value: optional pointer to an integer variable whose value reflects the position of the slider
	//       slider position defined by variable
	//count: max position of slider
	//OnChange: Pointer to function to be called every time slider changes position
	createTrackbar("Hue Min", windowNameTrackbars, &H_min, H_max, rangeControl);
	createTrackbar("Hue Max", windowNameTrackbars, &H_max, H_max, rangeControl);
	createTrackbar("Sat Min", windowNameTrackbars, &S_min, S_max, rangeControl);
	createTrackbar("Sat Max", windowNameTrackbars, &S_max, S_max, rangeControl);
	createTrackbar("Value Min", windowNameTrackbars, &V_min, S_max, rangeControl);
	createTrackbar("Value Max", windowNameTrackbars, &V_max, S_max, rangeControl);

	// sprintf part of C library and sets labels for the trackbars
	//variable, label, value
	sprintf(trackbarLabels, "Hue Min", H_min);
	sprintf(trackbarLabels, "Hue Max", H_max);
	sprintf(trackbarLabels, "Sat Min", S_min);
	sprintf(trackbarLabels, "Sat Max", S_max);
	sprintf(trackbarLabels, "Value Min", V_min);
	sprintf(trackbarLabels, "Value Max", V_max);
	
}

int main()
{

	//int argc, char** argv
	bool calibrationMode = false;
	
	timer_0 reset0;
	timer_1 reset1;

	reset0.reset_0();
	reset1.reset_1();

	//Store Original frames in matrix
	Mat framesOriginal;

	//Store HSV frames
	Mat framesHSV;

	//Store Threshold  
	Mat framesThresh;
	Mat framesThreshRED, framesThreshORANGE, framesThreshYELLOW, framesThreshGREEN, framesThreshBLUE;

	//Store Gaussien Threshold frames
	Mat framesGauss;

	//create Videocapture variable for webcam
	VideoCapture capture;

	//Open Trackbars
	if (calibrationMode)
	{
		Trackbars();
	}
	//Open up the default camera at location 0, location 1 would be...
	capture.open(0);

	//VideoCapture frame dimensions
	capture.set(CAP_PROP_FRAME_WIDTH, Width);
	capture.set(CAP_PROP_FRAME_HEIGHT, Height);


		//Copy frames into matrix
		while (true)
		{
			//use this frame from initalizing gestures
			//if it's in this square for Z seconds then start recognition
			//reads video frame by frame
			capture.read(framesOriginal);
			//RGB to HSV
			cvtColor(framesOriginal, framesHSV, COLOR_BGR2HSV);
			double getSTOP, returnTime0;
			Colors red("red"), blue("blue"), green("green"), yellow("yellow"), orange("orange");
			remove_Noise remove;
			track trackColor;
			Coordinates get_Coords;
			HandGestureLibrary start;
			timer_1 findTimerValue;


			if (calibrationMode == true)
			{//in calibration mode we track objects based on JSV slider values
				cvtColor(framesOriginal, framesHSV, COLOR_BGR2HSV);

				//HSV to Threshold
				inRange(framesHSV, Scalar(H_min, S_min, V_min), Scalar(H_max, S_max, V_max), framesThresh);

				remove_Noise remove;
				remove.noise(framesThresh);

				track trackColor;
				trackColor.track_Color(framesThresh, framesHSV, framesOriginal, objectArea_min, objectArea_max);

				imshow(windowNameThreshold, framesThresh);


			}
			else
			{
				//first find the reds
				cvtColor(framesOriginal, framesHSV, COLOR_BGR2HSV);
				//inRange(framesHSV, red.getminHSV(), red.getmaxHSV(), framesThresh);
				//remove.noise(framesThresh);
				//trackColor.track_Color(red, framesThresh, framesHSV, framesOriginal, windowNameGaussThresh, objectArea_min, objectArea_max);

				inRange(framesHSV, red.getminHSV(), red.getmaxHSV(), framesThreshRED);
				inRange(framesHSV, orange.getminHSV(), orange.getmaxHSV(), framesThreshORANGE);
				inRange(framesHSV, yellow.getminHSV(), yellow.getmaxHSV(), framesThreshYELLOW);
				inRange(framesHSV, green.getminHSV(), green.getmaxHSV(), framesThreshGREEN);
				inRange(framesHSV, blue.getminHSV(), blue.getmaxHSV(), framesThreshBLUE);

				remove.noise(framesThreshRED, red);
				remove.noise(framesThreshORANGE);
				remove.noise(framesThreshYELLOW);
				remove.noise(framesThreshGREEN);
				remove.noise(framesThreshBLUE);

				//get_Coords.X_Coord(red, orange, framesThreshRED, framesThreshORANGE, framesOriginal, windowNameGaussThresh, objectArea_min, objectArea_max);
				//get_Coords.X_Coord(red, yellow, framesThreshRED, framesThreshYELLOW, framesOriginal, windowNameGaussThresh, objectArea_min, objectArea_max);
				get_Coords.X_Coord(red, green, framesThreshRED, framesThreshGREEN, framesOriginal, windowNameGaussThresh, objectArea_min, objectArea_max);
				//get_Coords.X_Coord(red, blue, framesThreshRED, framesThreshBLUE, framesOriginal, windowNameGaussThresh, objectArea_min, objectArea_max);

			//	returnTime0=findTimerValue.returnTime_0();
				start.StartGestures(red, green, framesThreshRED, framesThreshGREEN, framesOriginal, windowNameGaussThresh, objectArea_min, objectArea_max);
				//findTimerValue.stop_1();
				//getSTOP = findTimerValue.getStop_0();
				//stringstream ss_timer;
				//string finalTimer;
				//ss_timer << getSTOP;
				//finalTimer = ss_timer.str();

				//putText(framesOriginal, finalTimer, Point(30, 230), 1, 1, Scalar(255, 0, 43), 2);

				//could set a timer out here and then let use it as input for StartGestures

				//then find the blues
				//cvtColor(framesOriginal, framesHSV, COLOR_BGR2HSV);
				//inRange(framesHSV, blue.getminHSV(), blue.getmaxHSV(), framesThresh);
				//remove.noise(framesThresh);
				//trackColor.track_Color(blue, framesThresh, framesHSV, framesOriginal, windowNameGaussThresh, objectArea_min, objectArea_max);
				//get_Coords.X_Coord(red, blue, framesThresh, framesHSV, framesOriginal, windowNameGaussThresh, objectArea_min, objectArea_max);


				//then the greens
				//cvtColor(framesOriginal, framesHSV, COLOR_BGR2HSV);
				//inRange(framesHSV, green.getminHSV(), green.getmaxHSV(), framesThresh);
				//remove.noise(framesThresh);
				//trackColor.track_Color(green, framesThresh, framesHSV, framesOriginal, windowNameGaussThresh, objectArea_min, objectArea_max);


				//then the yellows
				//cvtColor(framesOriginal, framesHSV, COLOR_BGR2HSV);
				//inRange(framesHSV, yellow.getminHSV(), yellow.getmaxHSV(), framesThresh);
				//remove.noise(framesThresh);
				//trackColor.track_Color(yellow, framesThresh, framesHSV, framesOriginal, windowNameGaussThresh, objectArea_min, objectArea_max);


				//then the oranges
				//cvtColor(framesOriginal, framesHSV, COLOR_BGR2HSV);
				//inRange(framesHSV, orange.getminHSV(), orange.getmaxHSV(), framesThresh);
				//remove.noise(framesThresh);
				//trackColor.track_Color(orange, framesThresh, framesHSV, framesOriginal, windowNameGaussThresh, objectArea_min, objectArea_max);

				//get_Coords.X_Coord(red, blue, framesThresh, framesHSV, framesOriginal, windowNameGaussThresh, objectArea_min, objectArea_max);


			}

			// pop up the windows
			imshow(windowNameOriginal, framesOriginal);
			findTimerValue.stop_1();
			getSTOP = findTimerValue.getStop_1();
			stringstream ss_timer;
			string finalTimer;
			ss_timer << getSTOP;
			finalTimer = ss_timer.str();
			putText(framesOriginal, finalTimer, Point(30, 230), 1, 1, Scalar(255, 0, 43), 2);
			//holdTime0.holdTime_0(getSTOP);
			waitKey(30);
		}
	
return 0;
}