#pragma once

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


using namespace cv;

class Blob_ 
{
public:
	Mat	image;
	Mat	src;
	Point	location;	
	//Mat	owner;		
	double	perimetr;   
	double    area;	
	double  roundness;
	double elongation;
	double compactness;
	double xC;
	double yC;
	double rmin;
	double rmax;
	bool whiteNoBlack;
	double koefficient;
	double roughnessB;
	float degreeRoughnessB;
    double convexity;
	double convPerimeter;
	double convArea;
	double convCompactness;
    double roughnessBArea;
	int angle;
	Point bigX;
	Point bigY;
	double bigLen;
	Point smallX;
	Point smallY;
	double smallLen;
	int number;
	bool deleted;
    //     string fileName = "";
    //     string units = "";
    long quantityPointsInPerimeter;
    int beg;
    int end;
    Scalar clr;
	std::string code;
public:
	Blob_()
	{
		//image = 0;
	};
	Blob_(Point location, bool WithMorpho, bool WhiteNoBlack);
	Blob_(Mat image, Point location, bool WithMorpho, bool WhiteNoBlack);
	Blob_(Point location, Mat owner, bool WithMorpho, bool WhiteNoBlack);
	void SetBlob(Point location, bool WithMorpho, bool WhiteNoBlack);
	~Blob_();
} ;


typedef Blob_* PBlob;

