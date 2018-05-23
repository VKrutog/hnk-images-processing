#pragma once
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Blob.h"
#include "Point2.h"
#include "Convexull.h"


using namespace cv;

class morfology_
{
public:
	morfology_();
	~morfology_();
	static void CalcPerimeterAreaRight(Blob_* blob, Mat image);
	static void SetBlob(Blob_* blob, float Perimeter, long _QuantityPointsInPerimetr, long Area, long xc, long yc);
	static Point* GetPerimetersCoord(Blob_ blob, bool WhiteNoBlack, long& count);
	static Point2* GetConvexityCoord(Blob_ blob, long& count);
	static Point2* GetPerimeterCoord(Blob_ blob, long& count);
};

