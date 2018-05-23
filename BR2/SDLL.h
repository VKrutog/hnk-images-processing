#pragma once
#include"Point2.h"


#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

class SDLL
{
public:
	SDLL* prev ;
	SDLL* next;
	Point2 val;
	SDLL();
	~SDLL();
	SDLL(Point2 val);
	SDLL* Prev();
	SDLL* Next();
	void Delete_();
	SDLL* Prepend(SDLL* elt);
	SDLL* Append(SDLL* elt);
	int Size();
	void CopyInto(Point2* vals, int i);
};
