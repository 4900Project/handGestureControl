#pragma once
#include "Colors.h"

class handDistance
{
public:
	handDistance();
	~handDistance();

	void findDistance(vector<Colors> firstColor, vector<Colors> secondColor, Mat &framesOriginal);

};

