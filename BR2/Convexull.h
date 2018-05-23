#pragma once
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "MultySort.h"
#include "SDLL.h"

using namespace cv;
class Convexull_
{
public:
	Convexull_();
	~Convexull_();
	static Point2* convexhull(Point2* pts, long& count);
	static Point* Point2ToPoint(Point2* point, int count);
	static void eliminate(SDLL* start);
	
};

