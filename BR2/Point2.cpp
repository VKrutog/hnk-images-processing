#include "Point2.h"
#include <math.h>

Point2::Point2()
{
}


Point2::~Point2()
{
}

Point2::Point2(Point point)
{
	x = (double)point.x;
	y = (double)point.y;
}
Point2::Point2(double _x, double _y)
{
	x = _x; y = _y;
}
bool Point2::Equals(Point2 p2)
{
	return x == p2.x && y == p2.y;
}
bool Point2::Less(Point2 o2)
{
	
	return x < o2.x || (x == o2.x && y < o2.y);
}
double Point2::Area2(Point2 p0, Point2 p1, Point2 p2)
{
	Point2 _p0 = p0;
	Point2 _p1 = p1;
	Point2 _p2 = p2;
	
	double ret = p0.x * (p1.y - p2.y) + p1.x * (p2.y - p0.y) + p2.x * (p0.y - p1.y);
	return ret;
}

double Point2::LineW(Point2 p1, Point2 p2)
{
	return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}
