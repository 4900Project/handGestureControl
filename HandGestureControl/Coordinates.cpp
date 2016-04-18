#include "DrawCenters.h"
#include "trackColor.h"
#include "Colors.h"
#include "Coordinates.h"
#include "handDistance.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <opencv2/opencv.hpp> //Contains: VideoCapture
using namespace cv; // In std: VideoCapture
using namespace std;


Coordinates::Coordinates()
{
}


Coordinates::~Coordinates()
{
}


void Coordinates::X_Coord(Colors firstColor, Colors secondColor, Mat framesThresholdRED, Mat framesThresholdCOLOR, Mat &framesOriginal, const string &windowNameGaussThresh, const int objectArea_min, const int objectArea_max)
{
	vector <Colors> reds, blues;


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

	findContours(thresholdImageRED, contoursRED, hierarchyRED, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	findContours(thresholdImageCOLOR, contoursCOLOR, hierarchyCOLOR, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	drawContours(framesOriginal, contoursRED, -1, Scalar(1, 1, 2550), 1, 8, hierarchyRED);
	drawContours(framesOriginal, contoursCOLOR, -1, Scalar(1, 1, 2550), 1, 8, hierarchyCOLOR);



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

					if (areaRED > objectArea_min && areaCOLOR > objectArea_min)
					{
						Colors red, blue;

						//set red to have the values of x and y
						red.setXPos(momentRED.m10 / areaRED);			//xPos=moment.m10/area then getXPos can use that value
						red.setYPos(momentRED.m01 / areaRED);			//yPos=moment.m01/area then getYPos can use that value
						red.setType(firstColor.getType());		//
						red.setColor(firstColor.getColor());		//

						reds.push_back(red);	//push back all the reds it finds into a vector (reds)

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
					}
				}
			}

			if (objectFound == true)
			{
				handDistance find;
				find.findDistance(reds, blues, framesOriginal);
				draw center;
				center.draw_Center(reds, blues, framesOriginal);

			}


		}
	}

}






