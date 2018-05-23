#pragma once
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/photo.hpp"
#include "opencv2\opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
//#include "opencv2/text.hpp"
//#include "opencv2/features.hpp"
#include "opencv2/features2d/features2d.hpp"

#include "Blob.h"
#include "BlobCounter.h"
#include "BlobsBuild.h"
#include "morfology.h"
#include "convexull.h"
#include "Point2.h"

using namespace cv;


class Preprocessing
{
public:
	Preprocessing();
	~Preprocessing();
	static void Sharpen(const Mat& img, Mat& result);
	static void Enhance(Mat* src);
	static void Equal(Mat* src, int i);
	static void Erosion2(Mat* src_);
	static void Dilation2(Mat* src_);
	static void BlackWhite(Mat* big, int dist, int step);
	static void SearhTicket(Mat* big);
	static void SearchTicket2(Mat* big);
	static void SearchTicket3(Mat* big);
	static bool TicketYesNo_0(Mat* big, int& counter);
	static bool TicketYesNo(Mat* big, int& counter);
	static void ColorRemove(Mat* big);
	static void Sobel_(Mat* bmp);
	static void Threshold(Mat* bmp);
	static void GreyScale(Mat* bmp);
	static void Transpose_(Mat* bmp);
	static Mat FewBlobsTop(Mat bmp, double from, double till);
	static void Invert(Mat* bmp);
	static void SearchTicket4(Mat* big);
	static int FewBlobsTop2(Mat* bmp);
	static void Blur(Mat* bmp);
	static void SearchTicket4_bottom(Mat* big);
	static void Rotation_0(Mat* bmp);
	static double Rotation(Mat* bmp);
	static void ReSize3(Mat* bmp, int width, int height);
	static void Rotate(Mat* src, double angle);
	static double BlackLines(Mat* big);
	static bool BlackLines90(Mat* big);
	static void Cutting(Mat* big);
	static void ChangeFrame(Mat* src, Point beg, Point end);
	static Mat ChangeFrame2(Mat* src, Point beg, Point end);
	static double RotationW(Mat* src);
	static void Cutting2(Mat* big);
	static void Cutting3(Mat* big);
	static void Cutting4(Mat* big);
	static void WF0(Mat* src);
	static bool RotationW2(Mat* src, int& code, double& angl);
	static double GreenPercent(Mat* big);
	static void DemountMount(Mat* big);
	static void Demount(Mat* big, Mat* set, int byX, int byY);
	static Mat Mount(Mat* set, int byX, int byY);
	static void BackgroundRemoval(Mat* big);
	static void ContrastBrightness(Mat* src, double contrast, double brightness);
	static void Contrast(Mat* src, int nContrast /*-100 100*/);
	static void GrayScale3Ch(Mat* big);
	static int RemoveBigSmallBlobs(Mat* bmp);
	static void Sobel2(Mat* bmp);
	static void Df2(Mat* src, Mat* bmp);
	static void Canny_(Mat* bmp);
	static void Laplacian_(Mat* bmp);
	static void DemountMount2(Mat* big);
	static void SisThreshold(Mat* srcImg);
	static Point TopBottom(Mat* bmp);
	static bool RotateAndCut(Mat* big, int& counter);
	static void BlackFrame(Mat* big);
	static bool TicketYesNo1(Mat* big, int& counter);
	static bool TicketYesNo2(Mat* big, int& counter);
	static bool PrePro(Mat* big, int& counter);
	static int RemoveBigSmallBlobs2(Mat* bmp);
	static void Marking(Mat* src);
	static void ColorFrame(Mat* big, Point beg, int width, int height);
	static Blob_* Marking2(Mat* bmp, int& counter);
	static void MarkingSelected(Mat* big, Point beg, int width, int height);
	static void onMouse(int event, int x, int y, int flags, void*);
	static int FindBlob(int x, int y, Blob_* blobs, int counter);
	static void BlobsCorrection(Blob_* blobs, int count_blobs, Mat* src);
	static Mat ChangeFrame3(Mat* big, Point beg, Point end);
	static std::string GetCode(Mat* src, int x, int y);
	static void BlobsCorrectionReSize(Blob_* blobs, int count_blobs, Mat* big);
	static void CodeCorrection(Blob_* blobs, int counter);
	static std::string GetCode2(Mat* src, int sx, int sy);
	static void BlobsCorrectionPixels(Mat* src);
	static void VertStich(Mat* big, int dist);
	static void HorStich(Mat* big, int dist);
	static void CodeCorrection(Blob_* blobs, int counter, double ht, double wt);
	static std::string GetCode3(Mat* src, int sx, int sy, double ht, double wt, double grav_x, double grav_y);
	static void CodeCorrection3(Blob_* blobs, int counter, double ht, double wt);
	static void MSER_Test(Mat* src);
	
};

