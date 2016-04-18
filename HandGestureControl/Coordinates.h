#pragma once
#include <vector>
#include "Colors.h"

class Coordinates
{
public:
	//vector <int> colorRedXcoords, colorRedYcoords, colorBlueXcoords, colorBlueYcoords, colorGreenXcoords, colorGreenYcoords, colorOrangeXcoords, colorOrangeYcoords, colorYellowXcoords, colorYellowYcoords;

	//vector<Colors> Color;
	//bool Found;

	Coordinates();
	~Coordinates();


	void X_Coord(Colors firstColor, Colors secondColor, Mat framesThresholdRED, Mat framesThresholdBLUE, Mat &framesOriginal, const string &windowNameGaussThresh, const int objectArea_min, const int objectArea_max);

};

