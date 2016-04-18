#include "timer_1.h"
#include <time.h>
#include <string>
#include <vector>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"

using namespace cv;
using namespace std;
using namespace cvflann;


timer_1::timer_1()
{
}


timer_1::~timer_1()
{
}

void timer_1::start_1()
{
	int64 startTime_1 = getTickCount();
}

void timer_1::stop_1()
{
	int64 stopTime_1 = getTickCount();
	value_1 = value_1 + ((double)stopTime_1 - startTime_1) / getTickFrequency();

}

void timer_1::reset_1()
{
	value_1 = 0;
}


double timer_1::getStop_1()
{
	return value_1;
}