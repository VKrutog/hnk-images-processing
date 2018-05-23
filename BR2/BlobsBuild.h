#pragma once

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Blob.h"


using namespace cv;

class BlobsBuild_
{
public:
	BlobsBuild_();
	~BlobsBuild_();
public:
	static Mat PutBlobsBlackWhite(Mat src, Blob_* blobs, int blobsCount, int WhiteNoBlack);
	static Mat PutBlobsBlackWhiteCentre(Mat src, Blob_* blobs, int blobsCount, int WhiteNoBlack, Point& p, bool gravy);
	static Mat BlobsBuild_::PutBlobsBlackWhite3(Mat src, Blob_* blobs, int blobsCount, int WhiteNoBlack);
	
};

