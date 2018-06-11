#include "Preprocessing.h"
#include <iostream>
#include <math.h>
#include <ctime>

using namespace cv;
using namespace std;

Preprocessing::Preprocessing()
{
}


Preprocessing::~Preprocessing()
{
}

void Preprocessing::Sharpen(const Mat& img, Mat& result)
{
	result.create(img.size(), img.type());

	for (int row = 1; row < img.rows - 1; row++)
	{

		const uchar* previous = img.ptr<const uchar>(row - 1);

		const uchar* current = img.ptr<const uchar>(row);

		const uchar* next = img.ptr<const uchar>(row + 1);
		uchar *output = result.ptr<uchar>(row);
		int ch = img.channels();
		int starts = ch;
		int ends = (img.cols - 1) * ch;
		for (int col = starts; col < ends; col++)
		{

			*output++ = saturate_cast<uchar>(5 * current[col] - current[col - ch] - current[col + ch] - previous[col] - next[col]);
		}
	}

	result.row(0).setTo(Scalar::all(0));
	result.row(result.rows - 1).setTo(Scalar::all(0));
	result.col(0).setTo(Scalar::all(0));
	result.col(result.cols - 1).setTo(Scalar::all(0));
}

void Preprocessing::Enhance(Mat* src)
{
	detailEnhance(src[0], src[0]);
}

void Preprocessing::Equal(Mat* src, int i)
{
	std::vector<Mat> channels;

	Mat img_hist_equalized;
	cvtColor(src[0], img_hist_equalized, CV_BGR2HSV); //change the color image from BGR to YCrCb format

	split(img_hist_equalized, channels); //split the image into channels

	equalizeHist(channels[2], channels[2]); //equalize histogram on the 1st channel (Y)


	merge(channels, img_hist_equalized); //merge 3 channels including the modified 1st channel into one image

	cvtColor(img_hist_equalized, src[0], CV_HSV2BGR);

	img_hist_equalized.release();

}

void Preprocessing::Erosion2(Mat* src_)
{
	//Mat erosion_dst;

	int erosion_size = 1;
	Mat element = getStructuringElement(cv::MORPH_ELLIPSE,
		cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		cv::Point(erosion_size, erosion_size));


	erode(src_[0], src_[0]/* erosion_dst*/, element);

	element.release();
	//return src_[0];
}
void Preprocessing::Dilation2(Mat* src_)
{
	int erosion_size = 1;
	Mat element = getStructuringElement(cv::MORPH_ELLIPSE,
		cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		cv::Point(erosion_size, erosion_size));

	dilate(src_[0], src_[0], element);
	element.release();
}

//void Preprocessing::Dilation3(Mat* src_)
//{
//	int erosion_size = 1;
//	Mat element = getStructuringElement(cv::MORPH_,
//		cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
//		cv::Point(erosion_size, erosion_size));
//
//	dilate(src_[0], src_[0], element);
//	element.release();
//}

void Preprocessing::BlackWhite(Mat* big, int dist, int step)
{
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);
	

	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;
			int middle = (big_[dopp_big] + big_[dopp_big + 1] + big_[dopp_big + 2]) / 3;
			int dif1 = abs(big_[dopp_big] - big_[dopp_big + 1]);
			int dif2 = abs(big_[dopp_big] - big_[dopp_big + 2]);
			int dif3 = abs(big_[dopp_big+1] - big_[dopp_big + 2]);
			bool fg = dif1 < dist && dif2 < dist && dif3 < dist;

			if (fg /*&& (middle<step || middle>255-step)*/)
			{
				/*big_[dopp_big] = 255;
				big_[dopp_big+1] = 0;
				big_[dopp_big+2] = 0;*/
			}
			else
			{
				big_[dopp_big] = 255;
				big_[dopp_big + 1] = 255;
				big_[dopp_big + 2] = 255;
			}
		}

	}
}

void Preprocessing::SearhTicket(Mat* big)
{
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);
	int r = 0;
	int g = 0; 
	int b = 0;

	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;
		int max = 0;
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;
			int middle = (big_[dopp_big] + big_[dopp_big + 1] + big_[dopp_big + 2]) / 3;
			if (middle > max)
			{
				max = middle;
				r = big_[dopp_big + 2];
				g = big_[dopp_big + 1];
				b = big_[dopp_big ];
			}

		}
		int max2 = max / 2;
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;
			int middle = (big_[dopp_big] + big_[dopp_big + 1] + big_[dopp_big + 2]) / 3;
			
			if (middle < max2)
			{
				big_[dopp_big] = 0;// b;
				big_[dopp_big + 1] = 0;// g;
				big_[dopp_big + 2] = 0;// r;

			}
		}

	}
}

void Preprocessing::SearchTicket2(Mat* big)
{
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);
	int r = 0;
	int g = 0;
	int b = 0;
	double* diap = new double[26];
	int perc = 30.0*big[0].cols / 100.0;
	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;
		
		for (int k = 0; k < 26; k++)
			diap[k] = 0;
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;
			int middle = (big_[dopp_big] + big_[dopp_big + 1] + big_[dopp_big + 2]) / 3;
			middle = middle/10;
			if (middle>13)
				diap[middle]++;
		}
		int sum = 0;
		int border = 0;
		int from = 255;
		for (int l = 25; l > 0; l--)
		{
			sum += diap[l];
			border = l*10;
			double res = diap[l] / (diap[l - 1] + 1);
			double res1 = diap[l-1] / (diap[l] + 1);
			r = border;
			g = border;
			b = border;
			if (res1 > 2.0)
				from = l * 10;
			if (res > 2 && sum>perc)
				break;
		}

		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;
			int middle = (big_[dopp_big] + big_[dopp_big + 1] + big_[dopp_big + 2]) / 3;
			/*double dif1 = abs(big_[dopp_big] - big_[dopp_big + 1]);
			double dif2 = abs(big_[dopp_big] - big_[dopp_big + 2]);
			double dif3 = abs(big_[dopp_big + 1] - big_[dopp_big + 2]);
			bool fg = dif1 < dist && dif2 < dist && dif3 < dist;*/
			if ((middle < border && middle<from) || middle<128)
			{
				big_[dopp_big] = 0;// b;
				big_[dopp_big + 1] = 0;// g;
				big_[dopp_big + 2] = 0;// r;

			}
			else
			{
				big_[dopp_big] = r;// b;
				big_[dopp_big + 1] = g;// g;
				big_[dopp_big + 2] = b;// r;
			}
		}

	}
};

void Preprocessing::SearchTicket3(Mat* big)
{
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);
	int r = 0;
	int g = 0;
	int b = 0;
	double* diap = new double[26];
	int perc = 20.0*big[0].cols*big[0].rows / 100.0;

	for (int k = 0; k < 26; k++)
		diap[k] = 0;
	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;

		
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;
			int middle = (big_[dopp_big] + big_[dopp_big + 1] + big_[dopp_big + 2]) / 3;
			middle = middle / 10;
			diap[middle]++;
		}
	}
		int sum = 0;
		int border = 0;
		for (int l = 25; l > 0; l--)
		{
			sum += diap[l];
			border = l * 10;
			double res =1.0* diap[l] / (diap[l - 1] + 1);
			if (res > 2 && sum>perc)
				break;
		}
		for (int i = 0; i < big[0].rows; i++)
		{
			int dop_big = stride_big * i;
			for (int j = 0; j < big[0].cols; j++)
			{
				int dopp_big = dop_big + j * 3;
				int middle = (big_[dopp_big] + big_[dopp_big + 1] + big_[dopp_big + 2]) / 3;

				if (middle < border)
				{
					big_[dopp_big] = 0;// b;
					big_[dopp_big + 1] = 0;// g;
					big_[dopp_big + 2] = 0;// r;

				}
			}
		}

};


void Preprocessing::ColorRemove(Mat* big)
{
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);


	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;
			int middle = (big_[dopp_big] + big_[dopp_big + 1] + big_[dopp_big + 2]) / 3;
			double dif1 = 1.0*(big_[dopp_big]+1)/(big_[dopp_big+1]+1);
			double dif2 = 1.0*(big_[dopp_big+1]+1) / (big_[dopp_big]+ 1);
			dif1 = min(dif1, dif2);
			double dif3 = 1.0*(big_[dopp_big] + 1) / (big_[dopp_big + 2] + 1);
			double dif4 = 1.0*(big_[dopp_big + 2] + 1) / (big_[dopp_big] + 1);
			dif3 = min(dif3, dif4);
			dif1 = min(dif1, dif3);
			double dif5 = 1.0*(big_[dopp_big+1] + 1) / (big_[dopp_big + 2] + 1);
			double dif6 = 1.0*(big_[dopp_big + 2] + 1) / (big_[dopp_big+1] + 1);
			dif5 = min(dif5, dif6);
			dif1 = min(dif1, dif5);

			double val = 255.0*dif1;

			big_[dopp_big] = val;
			big_[dopp_big + 1] = val;
			big_[dopp_big + 2] = val;
			
		}

	}
}

void Preprocessing::Benk2(Mat* bmp)
{
	Mat src_gray;
	Mat grad;
	//char* window_name = "..";
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	int c;

	GaussianBlur(bmp[0], bmp[0], Size(3, 3), 0, 0, BORDER_DEFAULT);
	int lp = bmp[0].type();
	if (lp != 0)
		cvtColor(bmp[0], src_gray, CV_BGR2GRAY);

	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;



	Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	cvtColor(grad, bmp[0], COLOR_GRAY2BGR);
	src_gray.release();
	grad.release();
	grad_x.release();
	grad_y.release();
	abs_grad_x.release();
	abs_grad_y.release();
}

void Preprocessing::Sobel_(Mat* bmp)
{
	Mat src_gray;
	Mat grad;
	//char* window_name = "..";
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	int c;

	
	//GaussianBlur(bmp[0], bmp[0], Size(3, 3), 0, 0, BORDER_DEFAULT);

	int lp = bmp[0].type();
	if (lp != 0)
		cvtColor(bmp[0], src_gray, CV_BGR2GRAY);

	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;


	//Scharr(src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT);
	Sobel(src_gray, grad_x, ddepth, 1, 0, 1, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	//Scharr(src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT);
	Sobel(src_gray, grad_y, ddepth, 0, 1, 1, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	//addWeighted(grad_x, 0.5, grad_y, 0.5, 0, grad);

	cvtColor(grad, bmp[0], COLOR_GRAY2BGR);
	lp = bmp[0].type();

	

	src_gray.release();
	grad.release();
	grad_x.release();
	grad_y.release();
	abs_grad_x.release();
	abs_grad_y.release();
}

void Preprocessing::Threshold(Mat* bmp)
{
	int min = 130;
	int max = 255;
	int lp = bmp[0].type();
	if (lp != 0)
		cvtColor(bmp[0], bmp[0], COLOR_BGR2GRAY);
	int f = bmp[0].type();
	threshold(bmp[0], bmp[0], min, max, THRESH_BINARY);
	cvtColor(bmp[0], bmp[0], COLOR_GRAY2BGR);
	rectangle(bmp[0], Rect(0, 0, bmp[0].cols, bmp[0].rows), Scalar(0, 0, 0));
}

void Preprocessing::GreyScale(Mat* bmp)
{
	cvtColor(bmp[0], bmp[0], COLOR_BGR2GRAY);
}

void Preprocessing::Transpose_(Mat* bmp)
{
	transpose(bmp[0], bmp[0]);
}


void Preprocessing::Bilateral(Mat* bmp)
{
	Mat dst;
	//
	GaussianBlur(bmp[0], dst, Size(51, 51), 0, 0);
	//medianBlur(bmp[0], dst, 11);
	//bilateralFilter(bmp[0], dst, 50, 100, 100);
	//}
	dst.copyTo(bmp[0]);
}

Mat Preprocessing::FewBlobsTop(Mat bmp, double from, double till)
{

	int width = bmp.cols;
	int height = bmp.rows;
	//double r = perc;
	//double comp_ar = 1.0*perc *width*height / 100.0;


	Mat src_gray;
	int lp = bmp.type();
	if (lp != 0)
		cvtColor(bmp, src_gray, COLOR_BGR2GRAY);

	int countB = 0;
	Blob_* blobs = BlobCounter_::GetBlobs(src_gray, true, true, countB);

	double ar = 0;
	int cnt = -1;
	int lim = countB;
	int new_count = 0;
	for (int i = 0; i < lim; i++)
	{
		if (blobs[i].area > from && blobs[i].area < till)
		{
			new_count++;
		}
	}
	Blob_* few_blobs = new Blob_[new_count];
	int counter = 0;
	for (int i = 0; i < lim; i++)
	{
		if (blobs[i].area > from && blobs[i].area < till)
		{
			few_blobs[counter++] = blobs[i];
		}
	}

	Mat res_mat(bmp.rows, bmp.cols, CV_8UC1, Scalar(0));
	res_mat = BlobsBuild_::PutBlobsBlackWhite(res_mat, few_blobs, counter, 1);
	cvtColor(res_mat, bmp, COLOR_GRAY2BGR);
	return bmp;
}
int Preprocessing::FewBlobsTop2(Mat* bmp)
{
	int from = 100;
	int till = 4000;
	int width = bmp[0].cols;
	int height = bmp[0].rows;
	//double r = perc;
	//double comp_ar = 1.0*perc *width*height / 100.0;
	int* diap = new int[4];
	for (int i = 0; i < 4; i++)
		diap[i] = 0;
	Mat src_gray;
	int lp = bmp[0].type();
	if (lp != 0)
		cvtColor(bmp[0], src_gray, COLOR_BGR2GRAY);

	int countB = 0;
	Blob_* blobs = BlobCounter_::GetBlobs(src_gray, true, true, countB);

	double ar = 0;
	int cnt = -1;
	int lim = countB;
	int new_count = 0;
	for (int i = 0; i < lim; i++)
	{
		double area = blobs[i].area;
		double dif = abs(blobs[i].image.cols - blobs[i].image.rows);
		bool tmp = true;//dif < 20;
		if (area > 100 && area <= 1000 && tmp)
			diap[0]++;
		if (area > 1000 && area <= 2000 && tmp)
			diap[1]++;
		if (area > 2000 && area <= 3000 && tmp)
			diap[2]++;
		if (area > 3000 && area <= 4000 && tmp)
			diap[3]++;
	}
	int max_ = 0;
	int index = -1;
	for (int i = 0; i < 4; i++)
	{
		if (diap[i] > max_)
		{
			max_ = diap[i];
			index = i;
		}
	}

	switch (index)
	{
	case -1:
		return 0;
		break;
	case 0:
		from = 100;
		till = 1000;
		break;
	case 1:
		from = 1000;
		till = 2000;
		break;
	case 2:
		from = 2000;
		till = 3000;
		break;
	case 3:
		from = 3000;
		till = 4000;
		break;
	}

	Blob_* few_blobs = new Blob_[diap[index]];
	int counter = 0;
	for (int i = 0; i < lim; i++)
	{
		double area = blobs[i].area;
		//double dif = abs(blobs[i].image.cols - blobs[i].image.rows);
		bool tmp = true;// dif < 20;
		if (area > from && area <= till && tmp)
		if (area > from && blobs[i].area < till)
		{
			few_blobs[counter++] = blobs[i];
		}
	}

	Mat res_mat(bmp[0].rows, bmp[0].cols, CV_8UC1, Scalar(0));
	res_mat = BlobsBuild_::PutBlobsBlackWhite(res_mat, few_blobs, counter, 1);
	cvtColor(res_mat, bmp[0], COLOR_GRAY2BGR);
	
	src_gray.release();
	res_mat.release();
	
	delete[] blobs;
	delete[] few_blobs;
	return counter;
}
void Preprocessing::Invert(Mat* bmp)
{
	Mat tmp;
	bitwise_not(bmp[0], tmp);
	tmp.copyTo(bmp[0]);
	tmp.release();
}

void Preprocessing::Blur(Mat* bmp)
{
	cv::GaussianBlur(bmp[0], bmp[0], cv::Size(5, 5), 0, 0, BORDER_DEFAULT);
}

void Preprocessing::SearchTicket4(Mat* big)
{
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);
	int r = 0;
	int g = 0;
	int b = 0;
	double* diap = new double[26];
	int perc = 20.0*big[0].cols*big[0].rows / 100.0;

	for (int k = 0; k < 26; k++)
		diap[k] = 0;
	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;


		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;
			int middle = (big_[dopp_big] + big_[dopp_big + 1] + big_[dopp_big + 2]) / 3;
			middle = middle / 10;
			diap[middle]++;
		}
	}
	int sum = 0;
	int border = 0;
	for (int l = 25; l > 10; l--)
	{
		sum += diap[l];
		border = l * 10;
		double res = 1.0* diap[l] / (diap[l - 1] + 1);
		if (res > 1.8 && sum>perc)
			break;
	}
	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;
			int middle = (big_[dopp_big] + big_[dopp_big + 1] + big_[dopp_big + 2]) / 3;

			if (middle < border)
			{
				//big_[dopp_big] = 0;// b;
				//big_[dopp_big + 1] = 0;// g;
				//big_[dopp_big + 2] = 0;// r;

			}
			else
			{
				big_[dopp_big] = 255;// b;
				big_[dopp_big + 1] = 255;// g;
				big_[dopp_big + 2] = 255;// r;
			}
		}
	}

};


void Preprocessing::SearchTicket4_bottom(Mat* big)
{
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);
	int r = 0;
	int g = 0;
	int b = 0;
	double* diap = new double[26];
	int perc = 20.0*big[0].cols*big[0].rows / 100.0;

	for (int k = 0; k < 26; k++)
		diap[k] = 0;
	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;


		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;
			int middle = (big_[dopp_big] + big_[dopp_big + 1] + big_[dopp_big + 2]) / 3;
			middle = middle / 10;
			diap[middle]++;
		}
	}
	int sum = 0;
	int border = 0;
	for (int l = 0; l <25; l++)
	{
		//sum += diap[l];
		border = (l) * 10;
		double res = 1.0* diap[l+1] / (diap[l] + 1);
		if (res < 1.0 )
			break;
	}
	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;
			int middle = (big_[dopp_big] + big_[dopp_big + 1] + big_[dopp_big + 2]) / 3;

			if (middle < border)
			{
				big_[dopp_big] = 0;// b;
				big_[dopp_big + 1] = 0;// g;
				big_[dopp_big + 2] = 0;// r;

			}
			else
			{
				//big_[dopp_big] = 255;// b;
				//big_[dopp_big + 1] = 255;// g;
				//big_[dopp_big + 2] = 255;// r;
			}
		}
	}

};


bool Preprocessing::TicketYesNo_0_old(Mat* _src, int& counter)
{
	Erosion2(_src);
	Preprocessing::SearchTicket4_bottom(_src);
	SearchTicket4(_src);
	Invert(_src);
	Threshold(_src);
	//SisThreshold(src);
	counter = FewBlobsTop2(_src);
	if (counter > 80)
	return true;
	else
	return false;
};


bool Preprocessing::TicketYesNo_0(Mat* _src, int& counter)
{
	Mat* sr = new Mat[1];
	_src[0].copyTo(sr[0]);

	Preprocessing::Erosion2(_src);
	Preprocessing::Benk2(_src);
	for (int i = 0; i < 5; i++)
		Preprocessing::Blur(_src);

	Preprocessing::Df2(sr, _src);
	Preprocessing::Invert(_src);
	Preprocessing::SisThreshold(_src);
	Preprocessing::BlackFrame(_src);
	Preprocessing::RemoveBigSmallBlobs3(_src);
	//imwrite("c:\\0000000aaa.jpg", _src[0]);
	counter = 150;





	//Erosion2(src);
	//Preprocessing::SearchTicket4_bottom(src);
	//SearchTicket4(src);
	//Invert(src);
	//Threshold(src);
	////SisThreshold(src);
	//counter = FewBlobsTop2(src);
	//if (counter > 80)
		return true;
	/*else
		return false;*/
};

void Preprocessing::Rotation_0(Mat* src)
{
	
	Mat tmp1;
	/*if (src[0].cols>src[0].rows)
		Preprocessing::Rotate(&src[0], -90.);*/
	src[0].copyTo(tmp1);
	//Preprocessing::ReSize3(&tmp1, tmp1.cols / 2, tmp1.rows / 2);
	int counter = 0;
	Preprocessing::TicketYesNo(&tmp1, counter);
	if (Preprocessing::BlackLines90(&tmp1))
	{
		Preprocessing::Rotate(&src[0], -90.);
		Preprocessing::Rotate(&tmp1, -90.);
	}

	double max = 0.0;
	double min = 1000000.0;

	double angle = 0.0;


	for (double i = -10.0; i < 10.0; i += 1.0)
	{
		Mat tmp;
		tmp1.copyTo(tmp);
		Preprocessing::Rotate(&tmp, i);
		double res=Preprocessing::BlackLines(&tmp);
		tmp.release();
		if (res > max)
		{
			angle = i;
			max = res;
		}

		/*if (res < min)
		{
			angle = i;
			min = res;
		}*/

	}
	Preprocessing::Rotate(src, angle);
};


double Preprocessing::Rotation(Mat* src)
{

	Mat tmp1;
	double ret = 0.0;
	src[0].copyTo(tmp1);

	int counter = 0;
	Preprocessing::TicketYesNo_0(&tmp1, counter);
	if (Preprocessing::BlackLines90(&tmp1))
	{
		ret -= 90.0;
		Preprocessing::Rotate(&src[0], -90.);
		Preprocessing::Rotate(&tmp1, -90.);
	}

	double maxi = 0.0;
	double angle = 0.0;


	for (double i = -30.0; i < 30.0; i += 2.0)
	{
		Mat tmp;
		tmp1.copyTo(tmp);
		Preprocessing::Rotate(&tmp, i);
		double res = Preprocessing::BlackLines(&tmp);
		tmp.release();
		if (res > maxi)
		{
			angle = i;
			maxi = res;
		}
	}
	maxi = 0.0;
	double angle_ = 0.0;
	for (double i = angle-2.0; i < angle+2.0; i += 0.5)
	{
		Mat tmp;
		tmp1.copyTo(tmp);
		Preprocessing::Rotate(&tmp, i);
		double res = Preprocessing::BlackLines(&tmp);
		tmp.release();
		if (res > maxi)
		{
			angle_ = i;
			maxi = res;
		}
	}
	Preprocessing::Rotate(src, angle_);
	ret += angle_;
	tmp1.release();
	return ret;
};

double Preprocessing::RotationW(Mat* src)
{

	Mat tmp1;
	double ret = 0.0;
	src[0].copyTo(tmp1);

	int counter = 0;
	Preprocessing::TicketYesNo_0(&tmp1, counter);
	if (Preprocessing::BlackLines90(&tmp1))
	{
		ret -= 90.0;
		Preprocessing::Rotate(&src[0], -90.);
		Preprocessing::Rotate(&tmp1, -90.);
	}

	double maxi = 0.0;
	double angle = 0.0;


	for (double i = -30.0; i < 30.0; i += 2.0)
	{
		Mat tmp;
		tmp1.copyTo(tmp);
		Preprocessing::Rotate(&tmp, i);
		double res = Preprocessing::BlackLines(&tmp);
		tmp.release();
		if (res > maxi)
		{
			angle = i;
			maxi = res;
		}
	}
	maxi = 0.0;
	double angle_ = 0.0;
	for (double i = angle - 2.0; i < angle + 2.0; i += 0.5)
	{
		Mat tmp;
		tmp1.copyTo(tmp);
		Preprocessing::Rotate(&tmp, i);
		double res = Preprocessing::BlackLines(&tmp);
		tmp.release();
		if (res > maxi)
		{
			angle_ = i;
			maxi = res;
		}
	}
	Preprocessing::Rotate(&tmp1, angle_);
	ret += angle_;
	src[0].release();
	tmp1.copyTo(src[0]);
	tmp1.release();
	return ret;
};

//bool Preprocessing::RotationW2(Mat* src, int& code, double& angle)
//{
//
//	Mat tmp1;
//	double ret = 0.0;
//	src[0].copyTo(tmp1);
//
//	int counter = 0;
//	Preprocessing::TicketYesNo_0(&tmp1, counter);
//	if (counter < 100)
//	{
//		code = 1000 + counter;
//		return false;
//	}
//
//	if (Preprocessing::BlackLines90(&tmp1))
//	{
//		ret -= 90.0;
//		Preprocessing::Rotate(&src[0], -90.);
//		Preprocessing::Rotate(&tmp1, -90.);
//	}
//
//	double maxi = 0.0;
//	//double angle = 0.0;
//
//
//	for (double i = -30.0; i < 30.0; i += 2.0)
//	{
//		Mat tmp;
//		tmp1.copyTo(tmp);
//		Preprocessing::Rotate(&tmp, i);
//		double res = Preprocessing::BlackLines(&tmp);
//		tmp.release();
//		if (res > maxi)
//		{
//			angle = i;
//			maxi = res;
//		}
//		
//	}
//	maxi = 0.0;
//	double angle_ = 0.0;
//	for (double i = angle - 2.0; i < angle + 2.0; i += 0.5)
//	{
//		Mat tmp;
//		tmp1.copyTo(tmp);
//		Preprocessing::Rotate(&tmp, i);
//		double res = Preprocessing::BlackLines(&tmp);
//		tmp.release();
//		if (res > maxi)
//		{
//			angle_ = i;
//			maxi = res;
//		}
//		
//	}
//
//	if (maxi < 20)
//	{
//		code = 2000 + maxi;
//		return false;
//	}
//
//	Preprocessing::Rotate(&tmp1, angle_);
//	double re = Preprocessing::GreenPercent(&tmp1);
//	/*if (re > 20)
//	{
//	code = 3000 + re;
//	return false;
//	}*/
//	angle = ret + angle_;
//	src[0].release();
//	tmp1.copyTo(src[0]);
//	tmp1.release();
//	//angle = ret;
//	return true;
//};

bool Preprocessing::RotationW3(Mat* src, int& code, double& angle)
{

	Mat tmp1;
	Mat tmp2;
	double ret = 0.0;
	src[0].copyTo(tmp1);
	src[0].copyTo(tmp2);

	int counter = 0;
	int counter1 = 0;
	
	Preprocessing::TicketYesNo_0_old(&tmp1, counter);
	Preprocessing::TicketYesNo_0(&tmp2, counter1);

	double r1 = IsItScan(&tmp1);
	double r2 = IsItScan(&tmp2);

	if (r2 > r1)
	{
		tmp1.release();
		tmp2.copyTo(tmp1);
		counter = counter1;

	}


	if (counter < 100)
	{
		code = 1000 + counter;
		return false;
	}

	if (Preprocessing::BlackLines90(&tmp1))
	{
		ret -= 90.0;
		Preprocessing::Rotate(&src[0], -90.);
		Preprocessing::Rotate(&tmp1, -90.);
	}

	double maxi = 0.0;
	//double angle = 0.0;


	for (double i = -30.0; i < 30.0; i += 2.0)
	{
		Mat tmp;
		tmp1.copyTo(tmp);
		Preprocessing::Rotate(&tmp, i);
		double res = Preprocessing::BlackLines(&tmp);
		tmp.release();
		if (res > maxi)
		{
			angle = i;
			maxi = res;
		}
	}
	maxi = 0.0;
	double angle_ = 0.0;
	for (double i = angle - 2.0; i < angle + 2.0; i += 0.5)
	{
		Mat tmp;
		tmp1.copyTo(tmp);
		Preprocessing::Rotate(&tmp, i);
		double res = Preprocessing::BlackLines(&tmp);
		tmp.release();
		if (res > maxi)
		{
			angle_ = i;
			maxi = res;
		}
	}

	if (maxi < 20)
	{
		code = 2000 + maxi;
		return false;
	}

	Preprocessing::Rotate(&tmp1, angle_);
	double re = Preprocessing::GreenPercent(&tmp1);
	/*if (re > 20)
	{
	code = 3000 + re;
	return false;
	}*/
	angle = ret + angle_;
	src[0].release();
	tmp1.copyTo(src[0]);
	tmp1.release();
	tmp2.release();
	//angle = ret;
	return true;
};

void Preprocessing::ReSize3(Mat* bmp, int width, int height)
{
	//Mat ret;
	cv::Size new_size = cv::Size(width, height);
	cv::resize(bmp[0], bmp[0], new_size);
	//bmp[0].release();
	//return ret;
};

void Preprocessing::Rotate(Mat* src, double angle)
{
	Point2f c(src[0].cols / 2.0, src[0].rows / 2.0);
	Mat r = getRotationMatrix2D(c, (double)angle, 1.0);
	Rect x = RotatedRect(c, src[0].size(), angle).boundingRect();
	r.at<double>(0, 2) += x.width / 2.0 - c.x;
	r.at<double>(1, 2) += x.height / 2.0 - c.y;
	////warpAffine(src[0], src[0], r, x.size());

	//Mat tmp;
	//warpAffine(src[0], tmp, r, x.size(), INTER_CUBIC, BORDER_CONSTANT, Scalar(0,255,0));
	warpAffine(src[0], src[0], r, x.size(), INTER_CUBIC, BORDER_CONSTANT, Scalar(0, 255, 0));
	/*src[0].release();
	tmp.copyTo(src[0]);
	tmp.release();*/
	r.release();

}



double Preprocessing::BlackLines(Mat* big)
{
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);
	double counter = 0;
	
	int minX =100000;
	int maxX = 0;
	int minY = 100000;
	int maxY = 0;
	int spec_counter_x = 0;
	int spec_counter_y = 0;
	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;
		spec_counter_x = 0;
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;

			if (big_[dopp_big] > 10)
			{
				spec_counter_x++;
			}
		}
		if (spec_counter_x > 20)
		{
			minY = i;
			break;
		}
	}

	for (int i = big[0].rows-1; i >0; i--)
	{
		int dop_big = stride_big * i;
		spec_counter_x = 0;
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;

			if (big_[dopp_big] > 10)
			{
				spec_counter_x++;
			}
		}
		if (spec_counter_x > 20)
		{
			maxY = i;
			break;
		}
	}
	
	for (int j = 0; j < big[0].cols; j++)
	{
		spec_counter_x = 0;
		for (int i = 0; i < big[0].rows; i++)
		{
			int dop_big = stride_big * i;
			int dopp_big = dop_big + j * 3;

			if (big_[dopp_big] > 10)
			{
				spec_counter_x++;
			}
		}
		if (spec_counter_x > 20)
		{
			minX = j;
			break;
		}

	}

	for (int j = big[0].cols-1; j >0; j--)
	{
		spec_counter_x = 0;
		for (int i = 0; i < big[0].rows; i++)
		{
			int dop_big = stride_big * i;
			int dopp_big = dop_big + j * 3;

			if (big_[dopp_big] > 10)
			{
				spec_counter_x++;
			}
		}
		if (spec_counter_x > 20)
		{
			maxX = j;
			break;
		}
	}

	bool idn = false;
	int counter_bl = 0;
	for (int i = minY; i < maxY; i++)
	{
		int dop_big = stride_big * i;
		bool black = true;
		
		
		for (int j = minX; j < maxX; j++)
		{
			int dopp_big = dop_big + j * 3;

			if (big_[dopp_big] > 10)
			{
				idn = true;
				black = false;
				break;
			}
		}
		if (black && idn)
		{
			counter++;
			counter_bl++;
			if (counter_bl > 5)
			{
				idn = false;
				counter_bl = 0;
			}
		}
	}
	/*counter = counter / (maxY - minY + 1);
	return counter;*/
	return counter;
}




bool Preprocessing::BlackLines90(Mat* big)
{
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);
	double counter = 0;

	int minX = 100000;
	int maxX = 0;
	int minY = 100000;
	int maxY = 0;
	int spec_counter_x = 0;
	int spec_counter_y = 0;
	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;
		spec_counter_x = 0;
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;

			if (big_[dopp_big] > 10)
			{
				spec_counter_x++;
			}
		}
		if (spec_counter_x > 20)
		{
			minY = i;
			break;
		}
	}

	for (int i = big[0].rows - 1; i >0; i--)
	{
		int dop_big = stride_big * i;
		spec_counter_x = 0;
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;

			if (big_[dopp_big] > 10)
			{
				spec_counter_x++;
			}
		}
		if (spec_counter_x > 20)
		{
			maxY = i;
			break;
		}
	}

	for (int j = 0; j < big[0].cols; j++)
	{
		spec_counter_x = 0;
		for (int i = 0; i < big[0].rows; i++)
		{
			int dop_big = stride_big * i;
			int dopp_big = dop_big + j * 3;

			if (big_[dopp_big] > 10)
			{
				spec_counter_x++;
			}
		}
		if (spec_counter_x > 20)
		{
			minX = j;
			break;
		}

	}

	for (int j = big[0].cols - 1; j >0; j--)
	{
		spec_counter_x = 0;
		for (int i = 0; i < big[0].rows; i++)
		{
			int dop_big = stride_big * i;
			int dopp_big = dop_big + j * 3;

			if (big_[dopp_big] > 10)
			{
				spec_counter_x++;
			}
		}
		if (spec_counter_x > 20)
		{
			maxX = j;
			break;
		}
	}

	if ((maxY - minY) > (maxX - minX))
		return false;
	else
		return true;

}

void Preprocessing::Cutting2(Mat* big)
{
	Mat* src = new Mat();
	big[0].copyTo(src[0]);
	double ang=Preprocessing::RotationW(big);
	Preprocessing::Rotate(src, ang);
	//return;
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);
	double counter = 0;

	int minX = 100000;
	int maxX = 0;
	int minY = 100000;
	int maxY = 0;
	int spec_counter_x = 0;
	int spec_counter_y = 0;
	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;
		spec_counter_x = 0;
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;

			if (big_[dopp_big] > 10)
			{
				spec_counter_x++;
			}
		}
		if (spec_counter_x > 20)
		{
			minY = i;
			break;
		}
	}

	for (int i = big[0].rows - 1; i >0; i--)
	{
		int dop_big = stride_big * i;
		spec_counter_x = 0;
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;

			if (big_[dopp_big] > 10)
			{
				spec_counter_x++;
			}
		}
		if (spec_counter_x > 20)
		{
			maxY = i;
			break;
		}
	}

	for (int j = 0; j < big[0].cols; j++)
	{
		spec_counter_x = 0;
		for (int i = 0; i < big[0].rows; i++)
		{
			int dop_big = stride_big * i;
			int dopp_big = dop_big + j * 3;

			if (big_[dopp_big] > 10)
			{
				spec_counter_x++;
			}
		}
		if (spec_counter_x > 20)
		{
			minX = j;
			break;
		}

	}

	for (int j = big[0].cols - 1; j >0; j--)
	{
		spec_counter_x = 0;
		for (int i = 0; i < big[0].rows; i++)
		{
			int dop_big = stride_big * i;
			int dopp_big = dop_big + j * 3;

			if (big_[dopp_big] > 10)
			{
				spec_counter_x++;
			}
		}
		if (spec_counter_x > 20)
		{
			maxX = j;
			break;
		}
	}

	bool idn = false;
	int counter_bl = 0;
	Point* diap = new Point[big[0].rows];
	for (int i = 0; i < big[0].rows; i++)
	{
		diap[i].x = -1;
		diap[i].y = -1;
	}

	int counter_diap = 0;
	bool flag_diap = false;
	for (int i = minY; i < maxY; i++)
	{
		int dop_big = stride_big * i;
		bool black = true;
		for (int j = minX; j < maxX; j++)
		{
			int dopp_big = dop_big + j * 3;

			if (big_[dopp_big] > 10)
			{
				if (flag_diap)
				{
					
					for (int k = minX; k < maxX; k++)
					{
						int dopp_big = dop_big + k * 3;
						if (big_[dopp_big] > 10)
						{
							if (diap[counter_diap].x == -1)
								diap[counter_diap].x = k;
							diap[counter_diap].y = k;
						}
					}
					counter_diap++;
					flag_diap = false;
				}
				
				idn = true;
				black = false;
				break;
			}

		}
		if (black && idn)
		{
			counter++;
			counter_bl++;
			flag_diap = true;
			if (i + 5 < maxY)
				i += 5;
			if (counter_bl > 5)
			{
				idn = false;
				counter_bl = 0;
			}
		}
	}
	
	Point beg(0,0);
	Point end(0, 0);
	beg.y = minY;
	end.y = maxY;

	beg.x = minX;
	end.x = maxX;

	//double summ_left = 0.;
	//double summ_right = 0.;
	//int spec_counter = 0;
	//for (int i = 0; i < counter_diap; i++)
	//{
	//	if (diap[i].y - diap[i].x>200)
	//	{
	//		summ_left += diap[i].x;
	//		summ_right += diap[i].y;
	//		spec_counter++;
	//	}
	//}

	//beg.x = summ_left / (spec_counter+1)-50;
	//end.x = summ_right / (spec_counter + 1) + 50;

	Preprocessing::ChangeFrame(src, beg, end);
	big[0].release();
	src[0].copyTo(big[0]);
	src[0].release();
}


void Preprocessing::Cutting3(Mat* big)
{
	Mat* src = new Mat();
	big[0].copyTo(src[0]);
	double ang = Preprocessing::RotationW(big);
	Preprocessing::Rotate(src, ang);
	//return;
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);
	double counter = 0;

	int minX = 100000;
	int maxX = 0;
	int minY = 100000;
	int maxY = 0;
	int spec_counter_x = 0;
	int spec_counter_y = 0;

	int* left = new int[big[0].rows];
	int* right = new int[big[0].rows];

	for (int i = 0; i < big[0].rows; i++)
	{

		left[i] = -1;
		right[i] = -1;
	}


	int* top = new int[big[0].cols];
	int* bottom = new int[big[0].cols];

	for (int i = 0; i < big[0].cols; i++)
	{

		top[i] = -1;
		bottom[i] = -1;
	}

	for (int j = 0; j < big[0].cols; j++)
	{
		spec_counter_x = 0;
		for (int i = 0; i < big[0].rows; i++)
		{
			int dop_big = stride_big * i;
			int dopp_big = dop_big + j * 3;

			if (big_[dopp_big] > 10)
			{
				top[j]=i;
				break;
			}
		}
	}

	for (int j = 0; j < big[0].cols; j++)
	{
		spec_counter_x = 0;
		for (int i = big[0].rows-1; i >=0; i--)
		{
			int dop_big = stride_big * i;
			int dopp_big = dop_big + j * 3;

			if (big_[dopp_big] > 10)
			{
				bottom[j] = i;
				break;
			}
		}
	}



	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;
		spec_counter_x = 0;
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;

			if (big_[dopp_big] > 10)
			{
				left[i] = j;
				break;
			}
		}

	}
	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;
		spec_counter_x = 0;
		for (int j = big[0].cols-1; j >=0; j--)
		{
			int dopp_big = dop_big + j * 3;

			if (big_[dopp_big] > 10)
			{
				right[i] = j;
				break;
			}
		}

	}

	counter = 1;
	double left_sum = 0.;
	double right_sum = 0.;

	for (int i = 0; i < big[0].rows; i++)
	{
		if (right[i] - left[i]>100)
		{
			left_sum += left[i];
			right_sum += right[i];
			counter++;
		}
	}

	left_sum /= counter;
	right_sum /= counter;

	int mini = 10000000;
	int maxi = -1;

	for (int i = 0; i < big[0].cols; i++)
	{
		if (top[i] < mini && top[i]>-1)
			mini = top[i];

		if (bottom[i] >maxi && bottom[i]>-1)
			maxi = bottom[i];

	}

	Point beg(0, 0);
	Point end(0, 0);
	beg.y = mini;
	end.y = maxi;

	beg.x = left_sum;
	end.x = right_sum+100;

	Preprocessing::ChangeFrame(src, beg, end);
	big[0].release();
	src[0].copyTo(big[0]);
	src[0].release();
}



void Preprocessing::Cutting4(Mat* big)
{
	Mat* src = new Mat();
	big[0].copyTo(src[0]);
	double ang = Preprocessing::RotationW(big);
	Preprocessing::Rotate(src, ang);
	//return;
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);


	Point beg(0, 0);
	Point end(0, 0);

	double* left = new double[big[0].cols];
	double* top = new double[big[0].rows];

	for (int i = 0; i < big[0].cols; i++)
		left[i] = 0;

	for (int i = 0; i < big[0].rows; i++)
		top[i] = 0;


	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;

		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;

			left[j] += big_[dopp_big];
			top[i] += big_[dopp_big];
			
		}

	}

	double val = 255 * 200 * big[0].rows/4500;

	double val1 = 255 * 50 * big[0].cols / 4500;

	for (int i = 0; i < big[0].cols; i++)
	{
		if (left[i] > val)
		{
			beg.x = i;
			break;
		}
	}

	for (int i = big[0].cols-1; i >=0; i--)
	{
		if (left[i] > val)
		{
			end.x = i;
			break;
		}
	}

	for (int i = 0; i < big[0].rows; i++)
	{
		if (top[i] > val1)
		{
			beg.y = i;
			break;
		}
	}

	for (int i = big[0].rows-1; i >=0; i--)
	{
		if (top[i] > val1)
		{
			end.y = i;
			break;
		}
	}

	double adds = 100 * big[0].cols / 3500.;
	
	if (beg.x - adds>0)
		beg.x -= adds;

	if (end.x + adds<big[0].cols - 1)
		end.x += adds;

	if (beg.y - 50>0)
		beg.y -= 50;

	if (end.y + 50<big[0].rows - 1)
		end.y += 50;

	/*if (beg.y>100)
		beg.y = 0;

	if (end.y<big[0].rows-100)
		end.y = big[0].rows - 1;*/

	beg.y = 0;
	end.y = big[0].rows - 1;


	Preprocessing::ChangeFrame(src, beg, end);
	big[0].release();
	src[0].copyTo(big[0]);
	src[0].release();
}


bool Preprocessing::RotateAndCut(Mat* big, int& counter)
{
	Mat* src = new Mat();
	big[0].copyTo(src[0]);
	double ang = 0.0;
	/*Mat big1;
	Mat big2;
	big[0].copyTo(big1);
	big[0].copyTo(big2);
	big[0].release();*/
	int cnt1 = 0;
	int cnt2 = 0;
	bool res = Preprocessing::RotationW3(big, cnt1, ang);
	/*res = Preprocessing::RotationW2(&big2, cnt2, ang);*/

	/*if (cnt1 > cnt2)
		big1.copyTo(big[0]);
	else
		big2.copyTo(big[0]);

	big1.release();
	big2.release();*/


	//imwrite("c:\\0000000aaa.jpg", big[0]);
	if (!res)
		return res;
	int parts = 3;
	int step = big[0].rows / parts - 5;
	int mini_beg = 1000000;
	int maxi_end = 0;

	//imwrite("c:\\0000000aaa.jpg", big[0]);

	for (int i = 0; i < big[0].rows - step; i += step)
	{
		Point beg(0, i);
		int istep = i + step;
		/*if (istep >= big[0].rows - 1)
		istep = big[0].rows - 1;*/
		Point end(big[0].cols, istep);
		Mat tmp = Preprocessing::ChangeFrame3(big, beg, end);
		Point rez = Preprocessing::Coord(&tmp);
		tmp.release();
		if (rez.x < mini_beg && rez.x>-1)
			mini_beg = rez.x;
		if (rez.y > maxi_end && rez.y >-1)
			maxi_end = rez.y;
	}


	double length = maxi_end - mini_beg;
	if (length <= 0)
	{
		counter = 4000;

		big[0].release();
		src[0].copyTo(big[0]);
		src[0].release();

		return false;
	}

	Preprocessing::Rotate(src, ang);

	int adds_left = 10. * length / 100.0;

	int adds_right = 10. * length / 100.0;



	if (mini_beg - adds_left>0)
		mini_beg -= adds_left;

	if (maxi_end + adds_right<big[0].cols - 1)
		maxi_end += adds_right;

	/*if (beg.y - 50>0)
	beg.y -= 50;*/

	/*if (end.y + 50<big[0].rows - 1)
	end.y += 50;*/

	/*if (beg.y>100)
	beg.y = 0;

	if (end.y<big[0].rows-100)
	end.y = big[0].rows - 1;*/
	Point beg(mini_beg, 0);
	Point end(maxi_end, big[0].rows - 1);
	beg.y = 0;
	end.y = src[0].rows - 1;


	Preprocessing::ChangeFrame(src, beg, end);
	big[0].release();
	src[0].copyTo(big[0]);
	src[0].release();

	return true;
}



Point Preprocessing::Coord(Mat* big)
{
	//imwrite("c:\\0000000aaa.jpg", big[0]);
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);


	Point beg(-1, -1);
	Point end(-1, -1);

	double* left = new double[big[0].cols];
	double* top = new double[big[0].rows];

	for (int i = 0; i < big[0].cols; i++)
		left[i] = 0;

	for (int i = 0; i < big[0].rows; i++)
		top[i] = 0;


	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;

		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;

			left[j] += big_[dopp_big];
			top[i] += big_[dopp_big];

		}

	}

	double maxi = 0.;
	int step = 1;

	for (int i = 0; i < big[0].cols - step; i++)
	{
		if (left[i + step] - left[i] > maxi)
		{
			maxi = (left[i + step] - left[i])*5.;
			beg.x = i + step;

		}
	}
	maxi = 0.;
	for (int i = big[0].cols - 1; i >= beg.x + 200; i--)
	{
		if (left[i - step] - left[i] > maxi)
		{
			maxi = (left[i - step] - left[i])*5.;
			end.x = i - step;

		}
	}
	Point ret(beg.x, end.x);
	return ret;
	
}

//bool Preprocessing::RotateAndCut2(Mat* big, int& counter)
//{
//	Mat* src = new Mat();
//	big[0].copyTo(src[0]);
//	double ang = 0.0;
//	bool res = Preprocessing::RotationW2(big, counter, ang);
//	if (!res)
//		return res;
//	int parts = 3;
//	int step = big[0].rows / parts-5;
//	int mini_beg = 1000000;
//	int maxi_end = 0;
//
//	imwrite("c:\\0000000aaa.jpg", big[0]);
//
//	for (int i = 0; i < big[0].rows-step; i += step)
//	{
//		Point beg(0,i);
//		int istep = i + step;
//		/*if (istep >= big[0].rows - 1)
//			istep = big[0].rows - 1;*/
//		Point end(big[0].cols, istep);
//		Mat tmp = Preprocessing::ChangeFrame3(big, beg, end);
//		Point rez = Preprocessing::Coord(&tmp);
//		tmp.release();
//		if (rez.x < mini_beg && rez.x>-1)
//			mini_beg = rez.x;
//		if (rez.y > maxi_end && rez.y >-1)
//			maxi_end = rez.y;
//	}
//
//	/*double ang = Preprocessing::RotationW(big);*/
//
//
//	//return true;
//	
//
//	//double val = 255 * 200 * big[0].rows / 4500;
//
//	//double val1 = 255 * 50 * big[0].cols / 4500;
//
//
//	//***************************************************************************
//
//	double length = maxi_end - mini_beg;
//	if (length <= 0)
//	{
//		counter = 4000;
//
//		big[0].release();
//		src[0].copyTo(big[0]);
//		src[0].release();
//
//		return false;
//	}
//	//**************************************************************************
//	Preprocessing::Rotate(src, ang);
//
//	int adds_left = 10. * length / 100.0;
//
//	int adds_right = 10. * length / 100.0;
//
//
//
//	if (mini_beg - adds_left>0)
//		mini_beg -= adds_left;
//
//	if (maxi_end + adds_right<big[0].cols - 1)
//		maxi_end += adds_right;
//
//	/*if (beg.y - 50>0)
//	beg.y -= 50;*/
//
//	/*if (end.y + 50<big[0].rows - 1)
//	end.y += 50;*/
//
//	/*if (beg.y>100)
//	beg.y = 0;
//
//	if (end.y<big[0].rows-100)
//	end.y = big[0].rows - 1;*/
//	Point beg(mini_beg,0);
//	Point end(maxi_end, big[0].rows - 1);
//	beg.y = 0;
//	end.y = src[0].rows - 1;
//
//	
//	Preprocessing::ChangeFrame(src, beg, end);
//	big[0].release();
//	src[0].copyTo(big[0]);
//	src[0].release();
//
//	return true;
//}


void Preprocessing::WF0(Mat* src)
{
	/*int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);


	Point beg(0, 0);
	Point end(0, 0);

	double* left = new double[big[0].cols];
	double* top = new double[big[0].rows];

	for (int i = 0; i < big[0].cols; i++)
		left[i] = 0;

	for (int i = 0; i < big[0].rows; i++)
		top[i] = 0;


	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;

		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;

			left[j] += big_[dopp_big];
			top[i] += big_[dopp_big];

		}

	}


	double maxi = 0.;

	for (int i = 0; i < big[0].cols - 5; i++)
	{
		if (left[i + 5] - left[i] > maxi)
		{
			maxi = left[i + 5] - left[i];
			beg.x = i + 5;
			break;
		}
	}
	maxi = 0.;
	for (int i = big[0].cols - 1; i >= 5; i--)
	{
		if (left[i - 5] - left[i] > maxi)
		{
			maxi = left[i - 5] - left[i];
			end.x = i - 5;
			break;
		}
	}

	beg.y = 0;
	end.y = big[0].rows - 1;


	Preprocessing::ChangeFrame(src, beg, end);*/
}


void Preprocessing::ChangeFrame(Mat* src, Point beg, Point end)
{
	cv::Size sz(end.x-beg.x, end.y-beg.y);
	Mat out(sz, src[0].type(), cv::Scalar::all(0));
	Rect source = cv::Rect(beg, end);
	Rect target = cv::Rect(0, 0, end.x - beg.x, end.y - beg.y);
	src[0](source).copyTo(out(target));
	src[0].release();
	out.copyTo(src[0]);
}

Mat Preprocessing::ChangeFrame2(Mat* src, Point beg, Point end)
{
	cv::Size sz(end.x - beg.x, end.y - beg.y);
	Mat out(sz, src[0].type(), cv::Scalar::all(0));
	Rect source = cv::Rect(beg, end);
	Rect target = cv::Rect(0, 0, end.x - beg.x, end.y - beg.y);
	src[0](source).copyTo(out(target));
	return out;
}


double Preprocessing::GreenPercent(Mat* big)
{
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);
	long counter = 0;

	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;
		
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;
			bool val= big_[dopp_big]==0 && big_[dopp_big + 1]==255 && big_[dopp_big + 2]==0;
			if (val)
				counter++;

		}

	}

	double res = counter/(big[0].rows*big[0].cols / 100.0);
	return res;
}

void Preprocessing::DemountMount2(Mat* big)
{
	/*Preprocessing::GrayScale3Ch(big);
	Preprocessing::Contrast(big, 100);
	Preprocessing::Contrast(big, 100);
	//Preprocessing::Contrast(big, 100);
	Preprocessing::Invert(big);

	return;*/

	int byX = big[0].cols / 100;
	int byY = big[0].rows / 50;
	
	Mat* set = new Mat[byX*byY];
	Preprocessing::Demount(big, set, byX, byY);
	int counter = 0;
	
	for (int i = 0; i < byY; i++)
	{
		for (int j = 0; j < byX; j++)
		{
			counter = 0;
			//Preprocessing::TicketYesNo_0(&set[i*byX + j], counter);
			//Preprocessing::Threshold(&set[i*byX + j]);
			//Preprocessing::Invert(&set[i*byX + j]);
			/*Preprocessing::SearchTicket4_bottom(&set[i*byX + j]);
			Preprocessing::SearchTicket4(&set[i*byX + j]);*/
			//Preprocessing::Contrast(&set[i*byX + j],100);
			//Preprocessing::BackgroundRemoval(&set[i*byX + j]);
			//Preprocessing::Enhance(&set[i*byX + j]);
			Preprocessing::GrayScale3Ch(&set[i*byX + j]);
			Preprocessing::Contrast(&set[i*byX + j], 100);
			Preprocessing::Contrast(&set[i*byX + j], 100);
			//Preprocessing::Contrast(&set[i*byX + j], 100);
			Preprocessing::Invert(&set[i*byX + j]);
			Preprocessing::SearchTicket4_bottom(&set[i*byX + j]);
			Preprocessing::SearchTicket4(&set[i*byX + j]);

			

		//	Preprocessing::Equal(&set[i*byX + j], 0);
		}
	}

	Mat res1 = Preprocessing::Mount(set, byX, byY);
	

	res1.copyTo(big[0]);

	

	/*Preprocessing::SearchTicket4_bottom(big);
	Preprocessing::SearchTicket4(big);*/
	//Preprocessing::RemoveBigSmallBlobs(big);

	for (int i = 0; i < byY; i++)
		for (int j = 0; j < byX; j++)
			set[i*byX + j].release();
	res1.release();
	

}


bool Preprocessing::PrePro(Mat* big, int& counter)
{
	bool res = RotateAndCut(big, counter);
	if (!res) return res;
	Mat* src = new Mat();
	big[0].copyTo(src[0]);
	SisThreshold(big);
	Invert(big);
	BlackFrame(big);
	RemoveBigSmallBlobs(big);
	Point ret = TopBottom(big);
	if (ret.x - 10 > 0)
		ret.x -= 10;
	if (ret.y + 10 < big[0].rows)
		ret.y += 10;

	Point beg(0, ret.x);
	Point end(src[0].cols, ret.y);
	ChangeFrame(src, beg, end);
	big[0].release();
	src[0].copyTo(big[0]);
	src[0].release();
	return res;
}


bool Preprocessing::PrePro2(Mat* big, int& counter)
{
	bool res = RotateAndCut(big, counter);
	if (!res) return res;
	Mat* src = new Mat();
	big[0].copyTo(src[0]);
	SisThreshold(big);
	Invert(big);
	BlackFrame(big);
	RemoveBigSmallBlobs(big);
	Point ret = TopBottom(big);
	if (ret.x - 10 > 0)
		ret.x -= 10;
	if (ret.y + 10 < big[0].rows)
		ret.y += 10;

	Point beg(0, ret.x);
	Point end(src[0].cols, ret.y);
	ChangeFrame(src, beg, end);
	big[0].release();
	src[0].copyTo(big[0]);
	src[0].release();
	return res;
}


bool Preprocessing::TicketYesNo1(Mat* big, int& counter )
{
	bool res = PrePro(big, counter);
	if (!res) return res;

	int byX = 5;
	int byY = big[0].rows / 100;

	Mat* set_res = new Mat[byX*byY];
	Mat* set_src = new Mat[byX*byY];

	Preprocessing::Demount(big, set_res, byX, byY);

	for (int i = 0; i < byY; i++)
	{
		for (int j = 0; j < byX; j++)
		{
			Preprocessing::SisThreshold(&set_res[i*byX + j]);
		}
	}

	Mat res1 = Preprocessing::Mount(set_res, byX, byY);


	res1.copyTo(big[0]);

	Invert(big);
	BlackFrame(big);
	RemoveBigSmallBlobs2(big);
	

	for (int i = 0; i < byY; i++)
		for (int j = 0; j < byX; j++)
		{
			set_src[i*byX + j].release();
			set_res[i*byX + j].release();
		}
	res1.release();

	return res;
}

//bool Preprocessing::TicketYesNo1(Mat* big, int& counter)
//{
//
//	bool res = RotateAndCut(big, counter);
//	//return res;
//	if (!res) return res;
//	Mat* src = new Mat();
//	big[0].copyTo(src[0]);
//
//	SisThreshold(big);
//	Invert(big);
//	BlackFrame(big);
//	RemoveBigSmallBlobs(big);
//	Point ret = TopBottom(big);
//
//	Point beg(0, ret.x);
//	Point end(src[0].cols, ret.y);
//	ChangeFrame(src, beg, end);
//	
//	big[0].release();
//	src[0].copyTo(big[0]);
//
//	//return res;
//
//	int byX = 1;
//	int byY = big[0].rows / 150;
//
//	/*int byX = big[0].cols / 50;
//	int byY = big[0].rows / 50;*/
//
//	Mat* set_res = new Mat[byX*byY];
//	Mat* set_src = new Mat[byX*byY];
//
//	Preprocessing::Demount(big, set_res, byX, byY);
//	Preprocessing::Demount(src, set_src, byX, byY);
//	//int counter = 0;
//
//	for (int i = 0; i < byY; i++)
//	{
//		for (int j = 0; j < byX; j++)
//		{
//			//Preprocessing::SisThreshold(&set_res[i*byX + j]);
//			Preprocessing::Sobel_(&set_res[i*byX + j]);
//			Preprocessing::Df2(&set_src[i*byX + j], &set_res[i*byX + j]);
//		}
//	}
//
//	Mat res1 = Preprocessing::Mount(set_res, byX, byY);
//	Mat src1 = Preprocessing::Mount(set_src, byX, byY);
//
//
//	res1.copyTo(big[0]);
//	src1.copyTo(src[0]);
//
//	Invert(big);
//	SisThreshold(big);
//
//	RemoveBigSmallBlobs(big);
//	BlackFrame(big);
//	
//	
//
//	for (int i = 0; i < byY; i++)
//		for (int j = 0; j < byX; j++)
//		{
//			set_src[i*byX + j].release();
//			set_res[i*byX + j].release();
//		}
//	res1.release();
//	src1.release();
//	return res;
//}


bool Preprocessing::TicketYesNo(Mat* big, int& counter)
{

	bool res = PrePro(big, counter);
	if (!res) return res;
	Mat* src = new Mat();
	big[0].copyTo(src[0]);
	Preprocessing::Sobel_(big);
	Preprocessing::Df2(src, big);
	Invert(big);
	SisThreshold(big);
	BlackFrame(big);
	RemoveBigSmallBlobs(big);
	src[0].release();
	return res;
}

bool Preprocessing::TicketYesNo2(Mat* big, int& counter)
{
	bool res = PrePro(big, counter);
	if (!res) return res;
	GrayScale3Ch(big);
	Contrast(big, 100);
	Invert(big);
	SisThreshold(big);
	BlackFrame(big);
	RemoveBigSmallBlobs(big);

	return res;
}


void Preprocessing::BlackFrame(Mat* big)
{
	int thickness = 2;
	int lineType = 8;
	rectangle(big[0], Point(0, 0), Point(big[0].cols, big[0].rows),
		Scalar(0, 0, 0),
		thickness,
		lineType);
}



void Preprocessing::Demount(Mat* big, Mat* set,int byX, int byY)
{

	int width = 1.0 * big[0].cols / byX;
	int height = 1.0 * big[0].rows / byY;
	cv::Size sz(width,height);
	Mat out(sz, big[0].type(), cv::Scalar::all(0));
	int y = 0;
	for (int i = 0; i < byY; i++)
	{
		int x = 0;
		for (int j = 0; j < byX; j++)
		{
			Rect source = cv::Rect(x, y, width, height);
			Rect target = cv::Rect(0, 0, width, height);
			big[0](source).copyTo(out(target));
			out.copyTo(set[i*byX +j]);
			x += width;
		}
		y += height;
	}
	out.release();
}

Mat Preprocessing::Mount(Mat* set, int byX, int byY)
{
	int width = set[0].cols;
	int height = set[0].rows;
	cv::Size sz(width*byX, height*byY);
	Mat ret(sz, set[0].type(), cv::Scalar::all(0));
	int y = 0;
	for (int i = 0; i < byY; i++)
	{
		int x = 0;
		for (int j = 0; j < byX; j++)
		{
			Rect source = cv::Rect(0, 0, width, height);
			Rect target = cv::Rect(x, y, width, height);
			set[i*byX + j](source).copyTo(ret(target));
			/*imwrite("c:\\0000000aaa.jpg", set[i, j]);
			imwrite("c:\\0000000bbb.jpg", ret);*/
			x += width;
		}
		y += height;
	}

	
	return ret;
}

void Preprocessing::BackgroundRemoval(Mat* big)
{
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);
	double counter = 0;
	double all = big[0].rows*big[0].cols;

	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;
			double middle = (big_[dopp_big] + big_[dopp_big + 1] + big_[dopp_big + 2]) / 3;

			counter += middle;


		}

	}
	counter /= all;
	counter /= 1.2;
	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;
			double middle = (big_[dopp_big] + big_[dopp_big + 1] + big_[dopp_big + 2]) / 3;
			if (middle < counter)
			{
				big_[dopp_big] = 0;
				big_[dopp_big+1] = 0;
				big_[dopp_big+2] = 0;
			}
			else
			{
				big_[dopp_big] = 255;
				big_[dopp_big + 1] = 255;
				big_[dopp_big + 2] = 255;
			}

		}

	}

}

void Preprocessing::GrayScale3Ch(Mat* big)
{
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);

	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;
			double middle = (big_[dopp_big] + big_[dopp_big + 1] + big_[dopp_big + 2]) / 3;

			big_[dopp_big] = middle;
			big_[dopp_big + 1] = middle;
			big_[dopp_big + 2] = middle;

		}

	}
}

void Preprocessing::ContrastBrightness(Mat* src, double contrast, double brightness) // contrast [1.0-3.0]; brightness [0-100]
{
	Mat new_image = Mat::zeros(src[0].size(), src[0].type());



	/// Do the operation new_image(i,j) = alpha*image(i,j) + beta
	for (int y = 0; y < src[0].rows; y++)
	{
		for (int x = 0; x < src[0].cols; x++)
		{
			for (int c = 0; c < 3; c++) {
				new_image.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(contrast*(src[0].at<Vec3b>(y, x)[c]) + brightness);
			}
		}
	}
	src[0].release();
	new_image.copyTo(src[0]);
	new_image.release();
}

void Preprocessing::Contrast(Mat* src, int nContrast /*-100 100*/)
{


	double contrast = (100.0 + nContrast) / 100.0;

	contrast *= contrast;



	int stride_big = src[0].step;
	unsigned char *big_ = (unsigned char*)(src[0].data);

	double value = 0.0;
	for (int y = 0; y<src[0].rows; y++)
	{
		int dop_big = stride_big * y;
		for (int x = 0; x < src[0].cols; x++)
		{
			int dopp_big = dop_big + x * 3;
			value = big_[dopp_big + 2] / 255.0;
			value -= 0.5;
			value *= contrast;
			value += 0.5;
			value *= 255;
			if (value < 0) value = 0;
			if (value > 255) value = 255;
			big_[dopp_big + 2] = value;

			value = big_[dopp_big] / 255.0;
			value -= 0.5;
			value *= contrast;
			value += 0.5;
			value *= 255;
			if (value < 0) value = 0;
			if (value > 255) value = 255;
			big_[dopp_big] = value;

			value = big_[dopp_big + 1] / 255.0;
			value -= 0.5;
			value *= contrast;
			value += 0.5;
			value *= 255;
			if (value < 0) value = 0;
			if (value > 255) value = 255;
			big_[dopp_big + 1] = value;
		}
	}

}

int Preprocessing::RemoveBigSmallBlobs3(Mat* bmp)
{
	double from = 500;
	double till = 4000;
	int width = bmp[0].cols;
	int height = bmp[0].rows;

	double onePerc = width*height / 100.0;
	till = 0.5 * onePerc;
	from = 0.001*onePerc;

	Mat src_gray;
	int lp = bmp[0].type();
	if (lp != 0)
		cvtColor(bmp[0], src_gray, COLOR_BGR2GRAY);

	int countB = 0;
	Blob_* blobs = BlobCounter_::GetBlobs(src_gray, true, true, countB);
	BlobsCorrection(blobs, countB, &src_gray);

	till = 0.;
	for (int i = 0; i < countB; i++)
	{
		//till += (blobs[i].image.cols* blobs[i].image.rows);
		till += (blobs[i].image.rows);
		from += (blobs[i].image.rows);
	}
	/*till /= (countB + 50 * countB/100);
	from /= (countB - 50 * countB / 100);*/

	till = till / countB;
	till += (50 * till / 100);
	from = from / countB;
	from -= (50 * from / 100);

	Blob_* few_blobs = new Blob_[countB];
	int counter = 0;
	for (int i = 0; i < countB; i++)
	{
		double area = blobs[i].area;
		bool tmp = true;// dif < 20;
		double prop = 1.* blobs[i].image.rows / blobs[i].image.cols;
		bool cond1 = !(prop > 5 && blobs[i].image.rows > 20);
		//if (area > from && area <= till && tmp)
		if (blobs[i].image.rows > from && blobs[i].image.rows < till && blobs[i].image.cols<bmp[0].cols / 2 && cond1)
			{
				few_blobs[counter++] = blobs[i];
			}
	}

	Mat res_mat(bmp[0].rows, bmp[0].cols, CV_8UC1, Scalar(0));
	res_mat = BlobsBuild_::PutBlobsBlackWhite(res_mat, few_blobs, counter, 1);
	cvtColor(res_mat, bmp[0], COLOR_GRAY2BGR);
	return counter;
}


int Preprocessing::RemoveBigSmallBlobs4(Mat* bmp)
{
	double from = 500;
	double till = 4000;
	int width = bmp[0].cols;
	int height = bmp[0].rows;

	double onePerc = width*height / 100.0;
	till = 1. * onePerc;
	from = 0.001*onePerc;

	Mat src_gray;
	int lp = bmp[0].type();
	if (lp != 0)
		cvtColor(bmp[0], src_gray, COLOR_BGR2GRAY);

	int countB = 0;
	Blob_* blobs = BlobCounter_::GetBlobs(src_gray, true, true, countB);
	BlobsCorrection(blobs, countB, &src_gray);

	till = 0.;
	for (int i = 0; i < countB; i++)
	{
		till +=  blobs[i].image.rows;
		from += blobs[i].image.rows;
	}
	till = till/countB;
	till += (50 * till / 100);
	from = from / countB;
	from -= (50 * from / 100);



	Blob_* few_blobs = new Blob_[countB];
	int counter = 0;
	for (int i = 0; i < countB; i++)
	{
		double height = blobs[i].image.rows;
		bool tmp = true;// dif < 20;
		double prop = 1.* blobs[i].image.rows / blobs[i].image.cols;
		bool cond1 = !(prop > 5 && blobs[i].image.rows > 20);
		//if (height > from && height <= till && tmp)
			if (height > from && height < till /*&& blobs[i].image.cols<bmp[0].cols / 2 && cond1*/)
			{
				few_blobs[counter++] = blobs[i];
			}
	}

	Mat res_mat(bmp[0].rows, bmp[0].cols, CV_8UC1, Scalar(0));
	res_mat = BlobsBuild_::PutBlobsBlackWhite(res_mat, few_blobs, counter, 1);
	cvtColor(res_mat, bmp[0], COLOR_GRAY2BGR);
	return counter;
}

int Preprocessing::RemoveBigSmallBlobs(Mat* bmp)
{
	double from = 100;
	double till = 4000;
	int width = bmp[0].cols;
	int height = bmp[0].rows;

	double onePerc = width*height / 100.0;
	till = 3. * onePerc;
	from = 0.001*onePerc;

	Mat src_gray;
	int lp = bmp[0].type();
	if (lp != 0)
		cvtColor(bmp[0], src_gray, COLOR_BGR2GRAY);

	int countB = 0;
	Blob_* blobs = BlobCounter_::GetBlobs(src_gray, true, true, countB);
	BlobsCorrection(blobs, countB, &src_gray);

	Blob_* few_blobs = new Blob_[countB];
	int counter = 0;
	for (int i = 0; i < countB; i++)
	{
		double area = blobs[i].area;
		bool tmp = true;// dif < 20;
		double prop = 1.* blobs[i].image.rows / blobs[i].image.cols;
		bool cond1 = !(prop > 5 && blobs[i].image.rows > 20);
		if (area > from && area <= till && tmp)
			if (area > from && blobs[i].area < till && blobs[i].image.cols<bmp[0].cols / 2 && cond1)
			{
				few_blobs[counter++] = blobs[i];
			}
	}

	Mat res_mat(bmp[0].rows, bmp[0].cols, CV_8UC1, Scalar(0));
	res_mat = BlobsBuild_::PutBlobsBlackWhite(res_mat, few_blobs, counter, 1);
	cvtColor(res_mat, bmp[0], COLOR_GRAY2BGR);
	return counter;
}


int Preprocessing::RemoveBigSmallBlobs2(Mat* bmp)
{
	double from = 100;
	double till = 4000;
	int width = bmp[0].cols;
	int height = bmp[0].rows;

	double onePerc = width*height / 100.0;
	till = 0.05 * onePerc;
	from = 0.001*onePerc;

	Mat src_gray;
	int lp = bmp[0].type();
	if (lp != 0)
		cvtColor(bmp[0], src_gray, COLOR_BGR2GRAY);

	int countB = 0;
	Blob_* blobs = BlobCounter_::GetBlobs(src_gray, true, true, countB);


	Blob_* few_blobs = new Blob_[countB];
	int counter = 0;
	for (int i = 0; i < countB; i++)
	{
		double area = blobs[i].area;
		bool tmp = true;// dif < 20;
		double prop = 1.* blobs[i].image.rows / blobs[i].image.cols;
		bool cond1 = !(prop > 5 && blobs[i].image.rows > 20);
		if (area > from && area <= till && tmp)
			if (area > from && blobs[i].area < till && blobs[i].image.cols<bmp[0].cols / 2 && cond1)
			{
				few_blobs[counter++] = blobs[i];
			}
	}

	Mat res_mat(bmp[0].rows, bmp[0].cols, CV_8UC1, Scalar(0));
	res_mat = BlobsBuild_::PutBlobsBlackWhite(res_mat, few_blobs, counter, 1);
	cvtColor(res_mat, bmp[0], COLOR_GRAY2BGR);
	return counter;
}


void Preprocessing::Sobel2(Mat* bmp)
{
	Mat tmp;
	cvSobel(bmp, &tmp, 1, 1, 3);
	tmp.copyTo(bmp[0]);
	tmp.release();
}

void Preprocessing::Df2(Mat* src, Mat* bmp)
{
	int lp1 = src[0].type();
	int lp = bmp[0].type();
	if (lp == 0)
	{
		Mat tmp;
		cvtColor(bmp[0], tmp, COLOR_GRAY2BGR);
		tmp.copyTo(bmp[0]);
		tmp.release();

	}

	int stride = bmp[0].step;

	unsigned char *src_ = (unsigned char*)(src[0].data);
	unsigned char *bmp_ = (unsigned char*)(bmp[0].data);
	for (int i = 0; i < bmp[0].rows; i++)
	{
		int dop = stride * i;
		//int dop3 = stride3 * i;


		for (int j = 0; j < bmp[0].cols; j++)
		{
			int dopp = dop + j * 3;

			int v1 = (int)src_[dopp] - (int)bmp_[dopp];
			int v2 = (int)src_[dopp + 1] - (int)bmp_[dopp + 1];
			int v3 = (int)src_[dopp + 2] - (int)bmp_[dopp + 2];
			bmp_[dopp] = (v1 < 0) ? (unsigned char)-v1 : (unsigned char)v1;
			bmp_[dopp + 1] = (v2 < 0) ? (unsigned char)-v2 : (unsigned char)v2;
			bmp_[dopp + 2] = (v3 < 0) ? (unsigned char)-v3 : (unsigned char)v3;
		}


	}

}

void Preprocessing::Canny_(Mat* bmp)
{
	Mat gray, edge, draw;
	cvtColor(bmp[0], gray, CV_BGR2GRAY);

	Canny(gray, edge, 50, 150, 3);

	bmp[0].release();
	edge.convertTo(draw, CV_8U);
	draw.copyTo(bmp[0]);
	edge.release();
	gray.release();
	draw.release();
	
}

void Preprocessing::Laplacian_(Mat* bmp)
{
	Mat gray, dst, abs_dst;
	GaussianBlur(bmp[0], bmp[0], Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(bmp[0], gray, CV_RGB2GRAY);

	/// Apply Laplace function
	Laplacian(gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);
	bmp[0].release();
	abs_dst.copyTo(bmp[0]);
	gray.release();
	dst.release();
	abs_dst.release();

}

void Preprocessing::SisThreshold(Mat* src_)
{

	int lp = src_[0].type();
	if (lp != 0)
		cvtColor(src_[0], src_[0], CV_BGR2GRAY);

	int width = src_[0].cols;
	int height = src_[0].rows;


	bool disposeSource = false;
	int threshold;

	Mat dstImg = Mat::zeros(src_[0].size(), CV_8UC1);



	int stride = src_[0].step;


	int widthM1 = width - 1;
	int heightM1 = height - 1;
	double ex, ey, weight, weightTotal = 0, total = 0;


	unsigned char* src = (unsigned char *)src_[0].data;// + stride;
	unsigned char* dst = (unsigned char *)dstImg.data;

	for (int y = 1; y < heightM1; y++)
	{
		int dop = y*stride;

		for (int x = 1; x < widthM1; x++)
		{
			int dopp = dop + x;
			ex = src[dopp + 1] - src[dopp - 1];
			ey = src[dopp + stride] - src[dopp - stride];
			weight = (ex > ey) ? ex : ey;
			weightTotal += weight;
			total += weight * (src[dopp]);
		}

	}


	threshold = (weightTotal == 0) ? (unsigned char)0 : (unsigned char)(total / weightTotal);


	//threshold = 120;


	for (int y = 0; y < height; y++)
	{
		int dop = stride*y;
		for (int x = 0; x < width; x++)
		{
			int dopp = dop + x;
			dst[dopp] = (unsigned char)((src[dopp] <= threshold) ? 0 : 255);
		}

	}

	cvtColor(dstImg, src_[0], COLOR_GRAY2BGR);
	//dstImg.copyTo(src_[0]);
	dstImg.release();
	//return dstImg;
	//return src_;

}

Point Preprocessing::TopBottom(Mat* bmp)
{
	//int lp1 = src[0].type();
	int lp = bmp[0].type();
	//if (lp != 0)
	//{
	//	Mat tmp;
	//	cvtColor(bmp[0], tmp, COLOR_GRAY2BGR);
	//	tmp.copyTo(bmp[0]);
	//	tmp.release();

	//}

	int from = 0;
	int till = bmp[0].rows-1;

	if (lp != 0)
	{
		Mat tmp;
		cvtColor(bmp[0], tmp, CV_BGR2GRAY);
		tmp.copyTo(bmp[0]);
		tmp.release();
	}

	int stride = bmp[0].step;
	int val = 50;
	//unsigned char *src_ = (unsigned char*)(src[0].data);
	unsigned char *bmp_ = (unsigned char*)(bmp[0].data);
	for (int i = 0; i < bmp[0].rows; i++)
	{
		int dop = stride * i;
		//int dop3 = stride3 * i;

		int counter = 0;
		for (int j = 0; j < bmp[0].cols; j++)
		{
			int dopp = dop + j;
			counter += bmp_[dopp];
		}
		if (counter > val)
		{
			from = i;
			break;
		}

	}
	
	for (int i = bmp[0].rows-1; i >=0; i--)
	{
		int dop = stride * i;
		//int dop3 = stride3 * i;

		int counter = 0;
		for (int j = 0; j < bmp[0].cols; j++)
		{
			int dopp = dop + j;
			counter += bmp_[dopp];
		}
		if (counter > val)
		{
			till = i;
			break;
		}

	}
	Point ret(from,till);
	
	return ret;
	

}

void Preprocessing::Marking(Mat* bmp)
{
	int width = bmp[0].cols;
	int height = bmp[0].rows;
	Mat src_gray;
	int lp = bmp[0].type();
	if (lp != 0)
		cvtColor(bmp[0], src_gray, COLOR_BGR2GRAY);

	int countB = 0;
	Blob_* blobs = BlobCounter_::GetBlobs(src_gray, true, true, countB);
	
	for (int i = 0; i < countB; i++)
	{
		ColorFrame(bmp, blobs[i].location, blobs[i].image.cols, blobs[i].image.rows);
	}
}

Blob_* Preprocessing::Marking2(Mat* bmp, int& counter)
{
    int width = bmp[0].cols;
	int height = bmp[0].rows;
	Mat src_gray;
	int lp = bmp[0].type();
	if (lp != 0)
		cvtColor(bmp[0], src_gray, COLOR_BGR2GRAY);
	else
		bmp[0].copyTo(src_gray);
	Blob_* blobs = BlobCounter_::GetBlobs(src_gray, true, true, counter);

	/*for (int i = 0; i < counter; i++)
	{
		ColorFrame(bmp, blobs[i].location, blobs[i].image.cols, blobs[i].image.rows);
	}*/
	BlobsCorrection(blobs, counter, &src_gray);
	CodeCorrection(blobs, counter);
	return blobs;
}

void Preprocessing::CodeCorrection(Blob_* blobs, int counter)
{
	/*for (int i = 0; i < counter; i++)
	{
		Mat tmp;
		blobs[i].image.copyTo(tmp);
		blobs[i].code = GetCode(&tmp, 4, 5);
	}*/
}

void Preprocessing::CodeCorrection3(Blob_* blobs, int counter, double ht, double wt)
{
	double one_ht = ht / 100.;
	double one_wt = wt / 100.;
	for (int i = 0; i < counter; i++)
	{
		Mat tmp;
		blobs[i].image.copyTo(tmp);
		double pr_ht = tmp.rows / one_ht;
		double pr_wt = tmp.cols / one_wt;


		//morfology_::CalcPerimeterAreaRight(&blobs[i], tmp);

		/*double grav_x = blobs[i].xC / (tmp.cols / 100.);
		double grav_y = blobs[i].yC / (tmp.rows / 100.);*/

		blobs[i].code = GetCode3(&tmp, 4, 5, pr_ht, pr_wt, 0, 0);
		tmp.release();
	}
}

void Preprocessing::ColorFrame(Mat* big, Point beg, int width, int height)
{
	int thickness = 1;
	int lineType = 8;
	rectangle(big[0], beg, Point(beg.x+width, beg.y+height),
		Scalar(0, 255, 0),
		thickness,
		lineType);
}

void Preprocessing::MarkingSelected(Mat* big, Point beg, int width, int height)
{
	int thickness = 5;
	int lineType = 8;
	rectangle(big[0], beg, Point(beg.x + width, beg.y + height),
		Scalar(0, 0, 255),
		thickness,
		lineType);
}

void Preprocessing::onMouse(int event, int x, int y, int flags, void* param)
{

	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		cv::Point *point = reinterpret_cast<cv::Point*>(param);
		point[0].x = x;
		point[0].y = y;
		break;

	}
}

int Preprocessing::FindBlob(int x, int y, Blob_* blobs, int counter)
{
	int ret = -1;
	for (int i = 0; i < counter; i++)
	{
		
		if (x >= blobs[i].location.x && x <= blobs[i].location.x + blobs[i].image.cols && y >= blobs[i].location.y && y <= blobs[i].location.y + blobs[i].image.rows)
		{
			ret = i;
			break;
		}
	}
	return ret;
}

void Preprocessing::BlobsCorrection(Blob_* blobs, int count_blobs, Mat* big)
{
	
	int w = big[0].cols;
	int h = big[0].rows;
	for (int i = 0; i < count_blobs; i++)
	{
		int width = blobs[i].image.cols;
		int height = blobs[i].image.rows;

		if (width > 0 && height > 0)
		{


			Point beg = blobs[i].location;





			int beg_x = beg.x + width;
			int beg_y = beg.y + height;



			if (beg_x >= big[0].cols - 1)
				beg_x = big[0].cols - 1;
			if (beg_y >= big[0].rows - 1)
				beg_y = big[0].rows - 1;

			Point end(beg_x, beg_y);

			int e1 = beg.x;
			int e2 = beg.y;

			int e3 = end.x;
			int e4 = end.y;

			blobs[i].image.release();
			blobs[i].image = ChangeFrame3(big, beg, end);
			if (i == count_blobs - 2)
			{
				int rr = 56;

			}
			//BlobsCorrectionPixels(&blobs[i].image);
		}
	}
}

void Preprocessing::BlobsCorrectionPixels(Mat* src)
{
	int  width = src[0].cols;
	int height = src[0].rows;
	if (width < 15 || height < 25)
		return;
	Point beg(0, 0);
	Point end(src[0].cols - 1, src[0].rows - 1);
	int stride = src[0].step;
	int val = 3;
	unsigned char *src_ = (unsigned char*)(src[0].data);

	int i = 0;
	int dop = stride * i;

	int counter = 0;
	for (int j = 0; j < src[0].cols; j++)
	{
		int dopp = dop + j;
		if (src_[dopp]>200)
			counter++;
	}
	if (counter < val)
		beg.y++;

	i = src[0].rows - 1;
	dop = stride * i;

	counter = 0;
	for (int j = 0; j < src[0].cols; j++)
	{
		int dopp = dop + j;
		if (src_[dopp]>200)
			counter++;
	}
	if (counter < val)
		end.y--;



	counter = 0;
	int j = 0;
	for (int i = 0; i < src[0].rows; i++)
	{
		int dop = stride * i;
		int dopp = dop + j;
		if (src_[dopp]>200)
			counter++;
	}
	if (counter < val)
		beg.x++;

	counter = 0;
	j = src[0].cols - 1;
	for (int i = 0; i < src[0].rows; i++)
	{
		int dop = stride * i;
		int dopp = dop + j;
		if (src_[dopp]>200)
			counter++;
	}
	if (counter < val)
		end.x--;


	src[0] = ChangeFrame3(src, beg, end);

	ReSize3(src, width, height);
}

void Preprocessing::BlobsCorrectionReSize(Blob_* blobs, int count_blobs, Mat* big)
{
	for (int i = 0; i < count_blobs; i++)
	{
		int width = blobs[i].image.cols;
		int height = blobs[i].image.rows;
		Point beg = blobs[i].location;
		Point end(beg.x + width, beg.y + height);

		blobs[i].image.release();
		blobs[i].image = ChangeFrame3(big, beg, end);
		
	}
}

Mat Preprocessing::ChangeFrame3(Mat* big, Point beg, Point end)
{
	cv::Size sz(end.x - beg.x, end.y - beg.y);
	Mat out(sz, big[0].type(), cv::Scalar::all(0));
	Rect source = cv::Rect(beg, end);
	Rect target = cv::Rect(0, 0, end.x - beg.x, end.y - beg.y);
	big[0](source).copyTo(out(target));
	return out;
}

std::string Preprocessing::GetCode2(Mat* src, int sx, int sy)
{
	int x = 100;
	int y = 150;
	
	Mat tmp;
	src[0].copyTo(tmp);
	/*int lp = tmp.type();
	if (lp != 0)
		cvtColor(tmp, tmp, CV_BGR2GRAY);*/
	Preprocessing::ReSize3(&tmp, x, y);
	Preprocessing::SisThreshold(&tmp);
	

	double* hor = new double[sx];
	double* ver = new double[sy];
	double* sq = new double[sx*sy];


	int step_x = x / sx;
	int step_y = y / sy;


	for (int i = 0; i < sx; i++)
		hor[i] = 0;

	for (int i = 0; i < sy; i++)
		ver[i] = 0;

	for (int i = 0; i < sx*sy; i++)
		sq[i] = 0;
	
	int stride = tmp.step;
	unsigned char *src_ = (unsigned char*)(tmp.data);
	long counter = 0;

	for (int i = 0; i < y; i++)
	{
		int dop = stride * i;

		for (int j = 0; j < x; j++)
		{
			int dopp = dop + j*3;
			if (src_[dopp]>250)
			{
				int ind_x = j / step_x;
				int ind_y = i / step_y;
				
				hor[ind_x]++;
				ver[ind_y]++;
				sq[ind_y*sx + ind_x]++;
			}


		}

	}
	tmp.release();
	String ret = "";
	double perc_vert = 1.0 * y * x / sx /100;
	double perc_hor = 1.0 * x * y/ sy / 100;
	double perc_sq = 1.0 * x/sx * y/sy / 100;

	for (int i = 0; i < sx; i++)
	{
		double tmp = hor[i] / perc_hor;
		if (tmp <= 33)
			ret = ret + '0';
		if (tmp > 33 && tmp<=66)
			ret = ret + '1';
		if (tmp > 66 )
			ret = ret + '2';
	}
	ret = ret+ ' ';

	for (int i = 0; i < sy; i++)
	{
		double tmp = ver[i] / perc_vert;
		if (tmp <= 33)
			ret = ret + '0';
		if (tmp > 33 && tmp <= 66)
			ret = ret + '1';
		if (tmp > 66)
			ret = ret + '2';
	}

	ret = ret + ' ';

	for (int i = 0; i < sy*sx; i++)
	{
		double tmp = sq[i] / perc_sq;
		if (tmp <= 33)
			ret = ret + '0';
		if (tmp > 33 && tmp <= 66)
			ret = ret + '1';
		if (tmp > 66)
			ret = ret + '2';
	}

	/*for (int i = 0; i < sx; i++)
	{
		double tmp = hor[i] / perc_hor;
		if (tmp <= 25)
			ret = ret + '0';
		if (tmp > 25 && tmp <= 50)
			ret = ret + '1';
		if (tmp > 50 && tmp <= 75)
			ret = ret + '2';
		if (tmp > 75)
			ret = ret + '3';
	}
	ret = ret + ' ';

	for (int i = 0; i < sy; i++)
	{
		double tmp = ver[i] / perc_vert;
		if (tmp <= 25)
			ret = ret + '0';
		if (tmp > 25 && tmp <= 50)
			ret = ret + '1';
		if (tmp > 50 && tmp <= 75)
			ret = ret + '2';
		if (tmp > 75)
			ret = ret + '3';
	}*/

	ret = ret + ' ';
	ret = ret + '?';

	return ret;
}

std::string Preprocessing::GetCode3(Mat* src, int sx, int sy, double ht, double wt, double grav_x, double grav_y)
{
	int x = 100;
	int y = 150;

	Mat tmp;
	src[0].copyTo(tmp);
	/*int lp = tmp.type();
	if (lp != 0)
	cvtColor(tmp, tmp, CV_BGR2GRAY);*/
	Preprocessing::ReSize3(&tmp, x, y);
	Preprocessing::SisThreshold(&tmp);


	double* hor = new double[sx];
	double* ver = new double[sy];
	double* sq = new double[sx*sy];


	int step_x = x / sx;
	int step_y = y / sy;


	for (int i = 0; i < sx; i++)
		hor[i] = 0;

	for (int i = 0; i < sy; i++)
		ver[i] = 0;

	for (int i = 0; i < sx*sy; i++)
		sq[i] = 0;
	double sum_i = 0;
	double sum_j = 0;
	int number_w = 0;
	int stride = tmp.step;
	unsigned char *src_ = (unsigned char*)(tmp.data);
	long counter = 0;
	double all = 0.;
	for (int i = 0; i < y; i++)
	{
		int dop = stride * i;

		for (int j = 0; j < x; j++)
		{
			int dopp = dop + j * 3;
			if (src_[dopp]>0/*250*/)
			{
				sum_i += i;
				sum_j += j;
				number_w++;
				
				int ind_x = j / step_x;
				int ind_y = i / step_y;

				hor[ind_x]++;
				ver[ind_y]++;
				sq[ind_y*sx + ind_x]++;
				all++;
			}


		}

	}


	

	sum_i /= number_w;
	sum_j /= number_w;


	double grav_x = sum_j / (x / 100.);
	double grav_y = sum_i / (y / 100.);


	tmp.release();
	String ret = "";


	double perc_vert = all / 100.;
	double perc_hor = all/ 100.;
	double perc_sq = all / 100.;

	for (int i = 0; i < sx; i++)
	{
		double tmp = hor[i] / perc_hor;
		
		if (tmp <= 3)
			ret = ret + '0';
		if (tmp > 3 && tmp <= 6)
			ret = ret + '1';
		if (tmp > 6 && tmp <= 9)
			ret = ret + '2';
		if (tmp > 9 && tmp <= 12)
			ret = ret + '3';
		if (tmp > 12 && tmp <= 15)
			ret = ret + '4';
		if (tmp > 15 && tmp <= 20)
			ret = ret + '5';
		if (tmp > 20 && tmp <= 25)
			ret = ret + '6';
		if (tmp > 25 && tmp <= 30)
			ret = ret + '7';
		if (tmp > 30 && tmp <= 35)
			ret = ret + '8';
		if (tmp > 35 && tmp <= 100)
			ret = ret + '9';
		
	}
	ret = ret + ' ';

	for (int i = 0; i < sy; i++)
	{
		double tmp = ver[i] / perc_hor;
		if (tmp <= 3)
			ret = ret + '0';
		if (tmp > 3 && tmp <= 6)
			ret = ret + '1';
		if (tmp > 6 && tmp <= 9)
			ret = ret + '2';
		if (tmp > 9 && tmp <= 12)
			ret = ret + '3';
		if (tmp > 12 && tmp <= 15)
			ret = ret + '4';
		if (tmp > 15 && tmp <= 20)
			ret = ret + '5';
		if (tmp > 20 && tmp <= 25)
			ret = ret + '6';
		if (tmp > 25 && tmp <= 30)
			ret = ret + '7';
		if (tmp > 30 && tmp <= 35)
			ret = ret + '8';
		if (tmp > 35 && tmp <= 100)
			ret = ret + '9';
	}

	ret = ret + ' ';

	for (int i = 0; i < sy*sx; i++)
	{
		double tmp = sq[i] / perc_hor;
		if (tmp <= 1.5)
			ret = ret + '0';
		if (tmp > 1.5 && tmp <= 3.)
			ret = ret + '1';
		if (tmp > 3. && tmp <= 4.5)
			ret = ret + '2';
		if (tmp > 4.5 && tmp <= 6.)
			ret = ret + '3';
		if (tmp > 6. && tmp <= 7.5)
			ret = ret + '4';
		if (tmp > 7.5 && tmp <= 9.)
			ret = ret + '5';
		if (tmp > 9. && tmp <= 10.5)
			ret = ret + '6';
		if (tmp > 10.5 && tmp <= 12.)
			ret = ret + '7';
		if (tmp > 12. && tmp <= 13.5)
			ret = ret + '8';
		if (tmp > 13.5 && tmp <= 100.)
			ret = ret + '9';
	}


	ret = ret + ' ';
	
	for (int i = 0; i < 2; i++)
	{
		double tmp = ht;
		if (tmp <= 20.)
			ret = ret + '0';
		if (tmp > 20. && tmp <= 30.)
			ret = ret + '1';
		if (tmp > 30. && tmp <= 40.)
			ret = ret + '2';
		if (tmp > 40. && tmp <= 50.)
			ret = ret + '3';
		if (tmp > 50. && tmp <= 60.)
			ret = ret + '4';
		if (tmp > 60. && tmp <= 70.)
			ret = ret + '5';
		if (tmp > 70. && tmp <= 80.)
			ret = ret + '6';
		if (tmp > 80. && tmp <= 90.)
			ret = ret + '7';
		if (tmp > 90. && tmp <= 100.)
			ret = ret + '8';
		if (tmp > 100. )
			ret = ret + '9';
	}

	ret = ret + ' ';

	for (int i = 0; i < 2; i++)
	{
		double tmp = wt;
		if (tmp <= 20.)
			ret = ret + '0';
		if (tmp > 20. && tmp <= 30.)
			ret = ret + '1';
		if (tmp > 30. && tmp <= 40.)
			ret = ret + '2';
		if (tmp > 40. && tmp <= 50.)
			ret = ret + '3';
		if (tmp > 50. && tmp <= 60.)
			ret = ret + '4';
		if (tmp > 60. && tmp <= 70.)
			ret = ret + '5';
		if (tmp > 70. && tmp <= 80.)
			ret = ret + '6';
		if (tmp > 80. && tmp <= 90.)
			ret = ret + '7';
		if (tmp > 90. && tmp <= 100.)
			ret = ret + '8';
		if (tmp > 100.)
			ret = ret + '9';
	}

	ret = ret + ' ';

	for (int i = 0; i < 2; i++)
	{
		double tmp = grav_x;
		if (tmp <= 10.)
			ret = ret + '0';
		if (tmp > 10. && tmp <= 20.)
			ret = ret + '1';
		if (tmp > 20. && tmp <= 30.)
			ret = ret + '2';
		if (tmp > 30. && tmp <= 40.)
			ret = ret + '3';
		if (tmp > 40. && tmp <= 50.)
			ret = ret + '4';
		if (tmp > 50. && tmp <= 60.)
			ret = ret + '5';
		if (tmp > 60. && tmp <= 70.)
			ret = ret + '6';
		if (tmp > 70. && tmp <= 80.)
			ret = ret + '7';
		if (tmp > 80. && tmp <= 90.)
			ret = ret + '8';
		if (tmp > 90.)
			ret = ret + '9';
	}

	ret = ret + ' ';

	for (int i = 0; i < 2; i++)
	{
		double tmp = grav_y;
		if (tmp <= 10.)
			ret = ret + '0';
		if (tmp > 10. && tmp <= 20.)
			ret = ret + '1';
		if (tmp > 20. && tmp <= 30.)
			ret = ret + '2';
		if (tmp > 30. && tmp <= 40.)
			ret = ret + '3';
		if (tmp > 40. && tmp <= 50.)
			ret = ret + '4';
		if (tmp > 50. && tmp <= 60.)
			ret = ret + '5';
		if (tmp > 60. && tmp <= 70.)
			ret = ret + '6';
		if (tmp > 70. && tmp <= 80.)
			ret = ret + '7';
		if (tmp > 80. && tmp <= 90.)
			ret = ret + '8';
		if (tmp > 90.)
			ret = ret + '9';
	}


	ret = ret + ' ';
	ret = ret + '?';

	return ret;
}

void Preprocessing::VertStich(Mat* big, int dist)
{
	//int dist = 7;
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);

	for (int i = 0; i < big[0].cols; i++)
	{
		int i3 = i *1;
		for (int j = dist; j < big[0].rows - dist; j++)
		{
			for (int k = 1; k < dist; k++)
			{
				int dop_big = stride_big * j;
				int dopp_big = dop_big + i3;

				int dop_big_pl = stride_big * (j + k);
				int dopp_big_pl = dop_big_pl + i3;

				int dop_big_min = stride_big * (j - k);
				int dopp_big_min = dop_big_min + i3;

				if (big_[dopp_big] == 0 && big_[dopp_big_min] == 255 && big_[dopp_big_pl] == 255)
				{

					for (int jj = j - k; jj < j + k - 1; jj++)
					{
						int dop_big1 = stride_big * jj;
						int dopp_big1 = dop_big1 + i3;
						big_[dopp_big1] = 255;
					}
					//break;
				}
			}

		}

	}
}

void Preprocessing::HorStich(Mat* big, int dist)
{
	//dist = dist * 2;
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);

	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;
		
		for (int j = dist; j < big[0].cols - dist; j++)
		{
			int dopp_big = dop_big + j*3;
			for (int k = 1; k < dist; k++)
			{
				int dop_big_pl = dop_big + (j + k)*3;
				int dop_big_min = dop_big + (j - k)*3;

				if (big_[dopp_big] == 0 && big_[dop_big_pl] == 255 && big_[dop_big_min] == 255)
				{

					for (int jj = j - k; jj < j + k - 1; jj++)
					{
						int dop_big1 = dop_big + jj*3;
						
						big_[dop_big1+2] = 255;
					}
					//break;
				}
			}

		}
	}
}
void Preprocessing::MSER_Test(Mat* src)
{
	Ptr<MSER> ms = MSER::create();
	vector<vector<Point>> regions;
	vector<cv::Rect> mser_bbox;
	ms->detectRegions(src[0], regions, mser_bbox);

	for (int i = 0; i < regions.size(); i++)
	{
		rectangle(src[0], mser_bbox[i], CV_RGB(0, 255, 0));
	}




}


double Preprocessing::IsItScan(Mat* big)
{
	int stride_big = big[0].step;
	unsigned char *big_ = (unsigned char*)(big[0].data);
	double val = 0;
	for (int i = 0; i < big[0].rows; i++)
	{
		int dop_big = stride_big * i;
		for (int j = 0; j < big[0].cols; j++)
		{
			int dopp_big = dop_big + j * 3;

			val += (big_[dopp_big] + big_[dopp_big+1] + big_[dopp_big+2] );

		}

	}

	val /= 3 * big[0].rows*big[0].cols;
	return val;
}