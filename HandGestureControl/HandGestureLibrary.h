#pragma once
#include "Colors.h"

class HandGestureLibrary
{
public:
	HandGestureLibrary();
	~HandGestureLibrary();

	void StartGestures(Colors firstColor, Colors secondColor, Mat framesThresholdRED, Mat framesThresholdCOLOR, Mat &framesOriginal, const string &windowNameGaussThresh, const int objectArea_min, const int objectArea_max);
	void SwipeRight();
	void SwipeLeft();
	void Close();

};

