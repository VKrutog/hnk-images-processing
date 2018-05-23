#pragma once

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

class Point2
{
public:
	double x;
	double y;
	Point2();
	~Point2();
	Point2(Point point);
	Point2(double x, double y);
	bool Equals(Point2 p2);
	bool Less(Point2 o2);
	static double Area2(Point2 p0, Point2 p1, Point2 p2);
	static double LineW(Point2 p1, Point2 p2);

};

