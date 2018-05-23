#pragma once

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Blob.h"

using namespace cv;

	//static int __blobs_count__;
	class BlobCounter_
	{
	public:
		
		int	objectsCount;
		int*	objectLabels;
		//static int blobs_count ;
		BlobCounter_();
		~BlobCounter_();
		void ProcessImage(Mat srcImg, bool WhiteNoBlack);
		static Rect* GetObjectRectangles(Mat srcImg, bool WhiteNoBlack);
		static Blob_* GetBlobs(Mat srcImg, bool WithMorpho, bool WhiteNoBlack, int&  countB);
	};

