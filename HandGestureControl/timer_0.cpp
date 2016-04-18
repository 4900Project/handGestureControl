#include "timer_0.h"
#include <time.h>
#include "opencv2/core.hpp"
#include <string>
#include <vector>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core/utility.hpp"

using namespace cv;
using namespace std;
using namespace cvflann;



timer_0::timer_0()
{
}


timer_0::~timer_0()
{
}

void timer_0::start_0()
{
	int64 startTime_0 = getTickCount();
}

void timer_0::stop_0()
{
	int64 stopTime_0 = getTickCount();
	value_0 = value_0 + ((double)stopTime_0 - startTime_0) / getTickFrequency();

}

void timer_0::reset_0()
{
	value_0 = 0;
}


double timer_0::getStop_0()
{
	return value_0;
}




