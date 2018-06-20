#include "Recognition.h"
#include "Preprocessing.h"


Recognition::Recognition()
{
	edb_counter = 0;
	blobs_counter = 0;
	edb_file_names_counter = 0;
	prcd = new Mat[1];
	edb_file_name = "";
	
}


Recognition::~Recognition()
{
	
}

Blob_* Recognition::GetBlobs(int& _blob_counter)
{
	_blob_counter = blobs_counter;
	return blobs;
}

void Recognition::NewImage()
{
	if (blobs_counter > 0)
	{
		delete[] blobs;
		blobs_counter = 0;
		prcd[0].release();
		src[0].release();
	}

}

void Recognition::SetBlobSourceImage(Mat* src)
{
	Mat tmp;
	src[0].copyTo(tmp);
	int y = 0;
	Preprocessing::PrePro(&tmp, y);
	for (int i = 0; i < blobs_counter; i++)
	{
		Point begin = blobs[i].location;
		Point end(begin.x + blobs[i].image.cols, begin.y + blobs[i].image.rows);
		blobs[i].src = Preprocessing::ChangeFrame2(&tmp, begin, end);
	}
}

Mat Recognition::ReProcessing(Mat* _src)
{

	
	for (int i = 0; i < blobs_counter; i++)
	{
		Point begin = blobs[i].location;
		Point end(begin.x + blobs[i].image.cols, begin.y + blobs[i].image.rows);


			blobs[i].image.release();
			blobs[i].image = Preprocessing::ChangeFrame2(_src, begin, end);
			Preprocessing::Enhance(&blobs[i].image);
			Preprocessing::SisThreshold(&blobs[i].image);
			Preprocessing::Invert(&blobs[i].image);
			cvtColor(blobs[i].image, blobs[i].image, COLOR_BGR2GRAY);

			
		
	}
	Mat res_mat(_src[0].rows, _src[0].cols, CV_8UC1, Scalar(0));
	res_mat = BlobsBuild_::PutBlobsBlackWhite(res_mat, blobs, blobs_counter, 1);

	
	return res_mat;
}


Mat Recognition::ReProcessing2(Mat* _src)
{

	Blob_ * big_blobs = new Blob_[blobs_counter];
	Blob_ * small_blobs = new Blob_[blobs_counter];
	int counter_big_blobs = 0;
	int counter_small_blobs = 0;

	int w = _src[0].cols;
	int h = _src[0].rows;

	for (int i = 0; i < blobs_counter; i++)
	{
		int wi = blobs[i].image.cols;
		int hi = blobs[i].image.rows;
		bool cond = wi > 0 &&  hi > 0 && wi < w / 2 && hi < h / 2;

		if (cond)
		{
			Point begin = blobs[i].location;
			Point end(begin.x + blobs[i].image.cols, begin.y + blobs[i].image.rows);


			blobs[i].image.release();

			blobs[i].image = Preprocessing::ChangeFrame2(_src, begin, end);
			
			Preprocessing::Enhance(&blobs[i].image);
			Preprocessing::SisThreshold(&blobs[i].image);
			Preprocessing::Invert(&blobs[i].image);

			cvtColor(blobs[i].image, blobs[i].image, COLOR_BGR2GRAY);



			if (blobs[i].image.cols > blobs[i].image.rows)
			{
				big_blobs[counter_big_blobs] = blobs[i];
				counter_big_blobs++;
			}
			else
			{
				small_blobs[counter_small_blobs] = blobs[i];
				counter_small_blobs++;
			}
		}
	}



	Mat res_mat(_src[0].rows, _src[0].cols, CV_8UC1, Scalar(0));
	res_mat = BlobsBuild_::PutBlobsBlackWhite(res_mat, big_blobs, counter_big_blobs, 1);

	
	
	int counter = 0;
	Blob_* blobs_new = BlobCounter_::GetBlobs(res_mat, true, true, counter);

	blobs_counter = counter + counter_small_blobs;
	blobs = new Blob_[blobs_counter];

	for (int i = 0; i < counter; i++)
	{
		blobs[i] = blobs_new[i];
	}
	for (int i = 0; i < counter_small_blobs; i++)
	{
		blobs[i+counter] = small_blobs[i];
	}

	/*for (int i = 0; i < blobs_counter; i++)
	{
		Preprocessing::Dilation2(&blobs[i].image);
	}*/

	Mat res_mat2(_src[0].rows, _src[0].cols, CV_8UC1, Scalar(0));
	res_mat2 = BlobsBuild_::PutBlobsBlackWhite(res_mat2, blobs, blobs_counter, 1);

	//imwrite("c:\\0000000aaa.jpg", res_mat2);
	return res_mat2;
}



bool Recognition::TicketYesNo(Mat* src, Mat* big, int& counter)
{
	bool res = PrePro(src, big, counter);
	if (!res) return res;
	Mat sr;// = new Mat();
	sr = big[0].clone();
	Preprocessing::Sobel_(big);
	Preprocessing::Df2(&sr, big);
	Preprocessing::Invert(big);
	Preprocessing::SisThreshold(big);
	Preprocessing::BlackFrame(big);
	Preprocessing::RemoveBigSmallBlobs(big);
	sr.release();

	return res;
}



bool Recognition::TicketYesNo2(Mat* src, Mat* big, int& counter)
{

	bool res = PrePro(src, big, counter);
	if (!res) return res;
	Mat* sr = new Mat();
	big[0].copyTo(sr[0]);
	
	Preprocessing::Erosion2(big);
	Preprocessing::Benk2(big);
	for (int i = 0; i < 5; i++)
		Preprocessing::Blur(big);
	//Preprocessing::Erosion2(big);
	//Preprocessing::Benk2(big);
	
	Preprocessing::Df2(sr, big);
	Preprocessing::Invert(big);
	Preprocessing::SisThreshold(big);
	Preprocessing::BlackFrame(big);
	Preprocessing::RemoveBigSmallBlobs3(big);
	
	sr[0].release();
	return res;
}

bool Recognition::TicketYesNo3(Mat* src, Mat* big, int& counter)
{

	bool res = PrePro2(src, big, counter);
	if (!res) return res;
	Mat sr;
	sr = src[0].clone();
	//imwrite("c:\\0000000aaa.jpg", src[0]);
	Preprocessing::Erosion2(big);
	Preprocessing::Benk2(big);
	for (int i = 0; i < 5; i++)
		Preprocessing::Blur(big);
	//Preprocessing::Erosion2(big);
	//Preprocessing::Benk2(big);

	Preprocessing::Df2(&sr, big);
	Preprocessing::Invert(big);
	Preprocessing::SisThreshold(big);
	Preprocessing::BlackFrame(big);
	//imwrite("c:\\0000000aaa5.jpg", big[0]);
	//Preprocessing::RemoveBigSmallBlobs4(big);
	Preprocessing::RemoveBigSmallBlobs7(big);
	//imwrite("c:\\0000000aaa6.jpg", big[0]);
	sr.release();
	return res;
}


std::string* Recognition::SetImage(Mat* _src, int& string_counter)
{	
	NewImage();
	src = _src;
	_src[0].copyTo(prcd[0]);

	if (!TicketYesNo(prcd, src, error))
	{
		string_counter=1;
		
		std::string* ret = new std::string[1];
		ret[0]	= std::to_string(error);
		//imwrite("C:\\0.jpg", _src[0]);
		return ret;
	}

	

	cvtColor(src[0], src[0], COLOR_BGR2GRAY);

	Mat tmp0;
	src[0].copyTo(tmp0);
	/*Preprocessing::Dilation2(&tmp0);
	Preprocessing::Dilation2(&tmp0);
	Preprocessing::Dilation2(&tmp0);*/

	blobs = BlobCounter_::GetBlobs(tmp0, true, true, blobs_counter);

	tmp0.release();

	////blobs = Preprocessing::Marking2(src, blobs_counter);
	src[0].release();
	src[0]=ReProcessing(prcd);

	double av_h = 0.;
	double av_w = 0.;

	for (int i = 0; i < blobs_counter; i++)
	{
		av_h += blobs[i].image.rows;
		av_w += blobs[i].image.cols;
	}
	av_h /= blobs_counter;
	av_w /= blobs_counter;


	Preprocessing::VertStich(src, av_h/20+1);
	//Preprocessing::HorStich(src, 4/*av_w / 12 + 1*/);
	/*imwrite("c:\\022222222.jpg", src[0]);
	imwrite("c:\\033333333.jpg", _prcd[0]);*/
	//delete[] blobs;
	
	blobs = Marking2(prcd, src, blobs_counter, av_h, av_w);

	cvtColor(src[0], src[0], COLOR_GRAY2BGR);

	if (edb_file_names_counter > 1)
	{
		double min = 10000000000000000.;
		int best = -1;
		for (int i = 0; i < edb_file_names_counter; i++)
		{
			int counter_edb = 0;
			std::string* _edb = ReadEDBCompare(edb_file_names[i], counter_edb);
			double res = RecogizeCompare(counter_edb, _edb);
			if (res < min)
			{
				min = res;
				best = i;
			}
		}
		ReadEDB(edb_file_names[best]);
	}
	Recogize();
	prcd[0].release();
	return Get_Strings(string_counter);
	
}


std::string* Recognition::SetImage2(Mat* _src, int& string_counter)
{
	NewImage();
	src = _src;
	_src[0].copyTo(prcd[0]);


	if(!TicketYesNo2(prcd, src, error)) ///*******************
	{
		string_counter = 1;

		std::string* ret = new std::string[1];
		ret[0] = std::to_string(error);
		return ret;
	}

	
	cvtColor(src[0], src[0], COLOR_BGR2GRAY);

	Mat tmp0;
	src[0].copyTo(tmp0);

	
	
	blobs = BlobCounter_::GetBlobs(tmp0, true, true, blobs_counter);

	tmp0.release();

	

	double av_h = 0.;
	double av_w = 0.;

	for (int i = 0; i < blobs_counter; i++)
	{
		av_h += blobs[i].image.rows;
		av_w += blobs[i].image.cols;
	}
	av_h /= blobs_counter;
	av_w /= blobs_counter;


	Preprocessing::VertStich(src, av_h / 20 + 1);

	Mat res_mat(_src[0].rows, _src[0].cols, CV_8UC1, Scalar(0));
	res_mat = BlobsBuild_::PutBlobsBlackWhite(res_mat, blobs, blobs_counter, 1);
	//Preprocessing::RemoveBigSmallBlobs(&res_mat);
	delete[] blobs;
	blobs = BlobCounter_::GetBlobs(res_mat, true, true, blobs_counter);


	src[0].release();
	src[0] = ReProcessing2(prcd);
	//return NULL;
	Marking3(prcd, src, blobs_counter, av_h, av_w);

	cvtColor(src[0], src[0], COLOR_GRAY2BGR);

	if (edb_file_names_counter > 1)
	{
		double min = 10000000000000000.;
		int best = -1;
		for (int i = 0; i < edb_file_names_counter; i++)
		{
			int counter_edb = 0;
			std::string* _edb = ReadEDBCompare(edb_file_names[i], counter_edb);
			double res = RecogizeCompare(counter_edb, _edb);
			if (res < min)
			{
				min = res;
				best = i;
			}
		}
		ReadEDB(edb_file_names[best]);
	}
	Recogize();
	return Get_Strings(string_counter);
}


std::string* Recognition::SetImage3(Mat* _src, int& string_counter)
{
	NewImage();
	src = _src;
	_src[0].copyTo(prcd[0]);


	if (!TicketYesNo2(prcd, src, error)) ///*******************
	{
		string_counter = 1;

		std::string* ret = new std::string[1];
		ret[0] = std::to_string(error);
		return ret;
	}


	cvtColor(src[0], src[0], COLOR_BGR2GRAY);

	Mat tmp0;
	src[0].copyTo(tmp0);



	blobs = BlobCounter_::GetBlobs(tmp0, true, true, blobs_counter);

	tmp0.release();

	double av_h = 0.;
	double av_w = 0.;

	for (int i = 0; i < blobs_counter; i++)
	{
		av_h += blobs[i].image.rows;
		av_w += blobs[i].image.cols;
	}
	av_h /= blobs_counter;
	av_w /= blobs_counter;


	Preprocessing::VertStich(src, av_h / 20 + 1);

	Mat res_mat(_src[0].rows, _src[0].cols, CV_8UC1, Scalar(0));
	res_mat = BlobsBuild_::PutBlobsBlackWhite(res_mat, blobs, blobs_counter, 1);
	Mat res_mat2 = res_mat.clone();
	//Preprocessing::RemoveBigSmallBlobs(&res_mat);
	delete[] blobs;
	blobs = BlobCounter_::GetBlobs(res_mat, true, true, blobs_counter);
	src[0].release();
	src[0] = ReProcessing3(prcd);

	Preprocessing::JustCut(src, &res_mat2, prcd);

	delete[] blobs;
	blobs = BlobCounter_::GetBlobs(res_mat2, true, true, blobs_counter);
	res_mat2.release();
	res_mat.release();
	src[0].release();
	src[0] = ReProcessing3(prcd);

	//return NULL;
	Marking3(prcd, src, blobs_counter, av_h, av_w);

	cvtColor(src[0], src[0], COLOR_GRAY2BGR);

	if (edb_file_names_counter > 1)
	{
		double min = 10000000000000000.;
		int best = -1;
		for (int i = 0; i < edb_file_names_counter; i++)
		{
			int counter_edb = 0;
			std::string* _edb = ReadEDBCompare(edb_file_names[i], counter_edb);
			double res = RecogizeCompare(counter_edb, _edb);
			if (res < min)
			{
				min = res;
				best = i;
			}
		}
		ReadEDB(edb_file_names[best]);
	}
	Recogize();
	return Get_Strings(string_counter);
}





std::string* Recognition::SetImage4(Mat* _src, int& string_counter)
{
	NewImage();
	src = _src;
	prcd[0] = _src[0].clone();

	double rrr = Preprocessing::IsItScan(_src);
	bool res_bool;

	if (rrr > 220)
		res_bool = TicketYesNo(prcd, src, error);
	else
		res_bool = TicketYesNo3(prcd, src, error);

	if (!res_bool) ///*******************
	{
		string_counter = 1;

		std::string* ret = new std::string[1];
		ret[0] = std::to_string(error);
		return ret;
	}
	

	cvtColor(src[0], src[0], COLOR_BGR2GRAY);

	Mat tmp0;
	tmp0=src[0].clone();
	//imwrite("c:\\0000000aaa.jpg", tmp0);


	blobs = BlobCounter_::GetBlobs(tmp0, true, true, blobs_counter);

	tmp0.release();



	double av_h = 0.;
	double av_w = 0.;

	for (int i = 0; i < blobs_counter; i++)
	{
		av_h += blobs[i].image.rows;
		av_w += blobs[i].image.cols;
	}
	av_h /= blobs_counter;
	av_w /= blobs_counter;


	Preprocessing::VertStich(src, av_h / 20 + 1);

	Mat res_mat(_src[0].rows, _src[0].cols, CV_8UC1, Scalar(0));
	BlobsBuild_::PutBlobsBlackWhite(&res_mat, blobs, blobs_counter, 1);
	delete[] blobs;
	blobs = BlobCounter_::GetBlobs(res_mat, true, true, blobs_counter);
	res_mat.release();
	src[0].release();
	src[0] = ReProcessing4(prcd);
	Marking3(prcd, src, blobs_counter, av_h, av_w);
	cvtColor(src[0], src[0], COLOR_GRAY2BGR);

	if (edb_file_names_counter > 1)
	{
		double min = 10000000000000000.;
		int best = -1;
		for (int i = 0; i < edb_file_names_counter; i++)
		{
			int counter_edb = 0;
			std::string* _edb = ReadEDBCompare(edb_file_names[i], counter_edb);
			double res = RecogizeCompare(counter_edb, _edb);
			if (res < min)
			{
				min = res;
				best = i;
			}
		}
		ReadEDB(edb_file_names[best]);
	}
	Recogize();
	prcd[0].release();
	return Get_Strings(string_counter);
}


std::string* Recognition::SetImage(Mat* _src, int& string_counter, bool _bold)
{
	
	NewImage();
	bold = _bold;
	src = _src;
	prcd[0] = _src[0].clone();

	double rrr = Preprocessing::IsItScan(_src);
	bool res_bool;

	if (rrr > 220)
		res_bool = TicketYesNo(prcd, src, error);
	else
		res_bool = TicketYesNo3(prcd, src, error);

	if (!res_bool) ///*******************
	{
		string_counter = 1;

		std::string* ret = new std::string[1];
		ret[0] = std::to_string(error);
		return ret;
	}


	cvtColor(src[0], src[0], COLOR_BGR2GRAY);

	Mat tmp0;
	tmp0 = src[0].clone();
	//imwrite("c:\\0000000aaa.jpg", tmp0);


	blobs = BlobCounter_::GetBlobs(tmp0, true, true, blobs_counter);

	tmp0.release();



	double av_h = 0.;
	double av_w = 0.;

	for (int i = 0; i < blobs_counter; i++)
	{
		av_h += blobs[i].image.rows;
		av_w += blobs[i].image.cols;
	}
	av_h /= blobs_counter;
	av_w /= blobs_counter;


	Preprocessing::VertStich(src, av_h / 20 + 1);

	Mat res_mat(_src[0].rows, _src[0].cols, CV_8UC1, Scalar(0));
	BlobsBuild_::PutBlobsBlackWhite(&res_mat, blobs, blobs_counter, 1);
	delete[] blobs;
	blobs = BlobCounter_::GetBlobs(res_mat, true, true, blobs_counter);
	res_mat.release();
	src[0].release();
	src[0] = ReProcessing4(prcd);
	Marking3(prcd, src, blobs_counter, av_h, av_w);
	cvtColor(src[0], src[0], COLOR_GRAY2BGR);

	if (edb_file_names_counter > 1)
	{
		double min = 10000000000000000.;
		int best = -1;
		for (int i = 0; i < edb_file_names_counter; i++)
		{
			int counter_edb = 0;
			std::string* _edb = ReadEDBCompare(edb_file_names[i], counter_edb);
			double res = RecogizeCompare(counter_edb, _edb);
			if (res < min)
			{
				min = res;
				best = i;
			}
		}
		ReadEDB(edb_file_names[best]);
	}
	Recogize();
	prcd[0].release();
	return Get_Strings(string_counter);
}


std::string* Recognition::SetImage5(Mat* _src, int& string_counter)
{
	NewImage();
	src = _src;
	_src[0].copyTo(prcd[0]);

	double rrr = Preprocessing::IsItScan(_src);
	bool res_bool;

	if (rrr > 220)
		res_bool = TicketYesNo(prcd, src, error);
	else
		res_bool = TicketYesNo3(prcd, src, error);

	if (!res_bool) ///*******************
	{
		string_counter = 1;

		std::string* ret = new std::string[1];
		ret[0] = std::to_string(error);
		return ret;
	}


	cvtColor(src[0], src[0], COLOR_BGR2GRAY);

	Mat tmp0;
	src[0].copyTo(tmp0);
	//imwrite("c:\\0000000aaa.jpg", tmp0);


	blobs = BlobCounter_::GetBlobs(tmp0, true, true, blobs_counter);

	tmp0.release();



	double av_h = 0.;
	double av_w = 0.;

	for (int i = 0; i < blobs_counter; i++)
	{
		av_h += blobs[i].image.rows;
		av_w += blobs[i].image.cols;
	}
	av_h /= blobs_counter;
	av_w /= blobs_counter;


	Preprocessing::VertStich(src, av_h / 20 + 1);

	Mat res_mat(_src[0].rows, _src[0].cols, CV_8UC1, Scalar(0));
	res_mat = BlobsBuild_::PutBlobsBlackWhite(res_mat, blobs, blobs_counter, 1);
	//Preprocessing::RemoveBigSmallBlobs(&res_mat);
	delete[] blobs;
	blobs = BlobCounter_::GetBlobs(res_mat, true, true, blobs_counter);


	src[0].release();
	src[0] = ReProcessing3(prcd);
	//return NULL;
	Marking3(prcd, src, blobs_counter, av_h, av_w);

	cvtColor(src[0], src[0], COLOR_GRAY2BGR);

	if (edb_file_names_counter > 1)
	{
		double min = 10000000000000000.;
		int best = -1;
		for (int i = 0; i < edb_file_names_counter; i++)
		{
			int counter_edb = 0;
			std::string* _edb = ReadEDBCompare(edb_file_names[i], counter_edb);
			double res = RecogizeCompare(counter_edb, _edb);
			if (res < min)
			{
				min = res;
				best = i;
			}
		}
		ReadEDB(edb_file_names[best]);
	}
	Recogize();
	return Get_Strings(string_counter);
}

void Recognition::SetEDB_fileNames(std::string* _edb_file_names, int _edb_file_names_counter)
{
	edb_file_names_counter = _edb_file_names_counter;
	edb_file_names = _edb_file_names;
}


Blob_* Recognition::Marking2(Mat* _src, Mat* bmp, int& counter)
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


	
	Preprocessing::BlobsCorrection(blobs, counter, &src_gray);
	Preprocessing::CodeCorrection(blobs, counter);

	for (int i = 0; i < blobs_counter; i++)
	{
		Point begin = blobs[i].location;
		Point end(begin.x + blobs[i].image.cols, begin.y + blobs[i].image.rows);
		blobs[i].src = Preprocessing::ChangeFrame2(_src, begin, end);
		cvtColor(blobs[i].image, blobs[i].image, COLOR_GRAY2BGR);
	}

	return blobs;
}


void Recognition::CodeCorrection3(Blob_* blobs, int counter, double ht, double wt)
{
	double one_ht = ht / 100.;
	double one_wt = wt / 100.;
	int yui = counter;
	for (int i = 0; i < counter; i++)
	{
		if (i == 799)
		{
			int r = 20;
		}
		
		Mat tmp;
		tmp = blobs[i].image.clone();
		double pr_ht = tmp.rows / one_ht;
		double pr_wt = tmp.cols / one_wt;


		//morfology_::CalcPerimeterAreaRight(&blobs[i], tmp);

		
		Gravitation(&blobs[i]);
		/*Preprocessing::SisThreshold(&blobs[i].image);
		Preprocessing::Dilation2(&blobs[i].image);*/
		/*double grav_x = blobs[i].xC / (tmp.cols / 100.);
		double grav_y = blobs[i].yC / (tmp.rows / 100.);*/

		//blobs[i].code = "nn";
		blobs[i].code = GetCode3(&tmp, 4, 5, pr_ht, pr_wt, 0, 0);
		//blobs[i].code = GetCode4(&tmp, 4, 5, pr_ht, pr_wt, 0, 0);
		tmp.release();
	}
}

std::string Recognition::GetCode3(Mat* src, int sx, int sy, double ht, double wt, double grav_x, double grav_y)
{
	//if (src[0].rows < 5 || src[0].cols < 5) return NULL;
	
	int x = sx*20;
	int y = sy*30;

	Mat temp;
	src[0].copyTo(temp);
	/*int lp = tmp.type();
	if (lp != 0)
	cvtColor(tmp, tmp, CV_BGR2GRAY);*/
	//if (&tmp == NULL) return NULL;
	Preprocessing::ReSize3(&temp, x, y);
	Preprocessing::SisThreshold(&temp);


	double* hor = new double[sx];
	double* ver = new double[sy];
	double* sq = new double[sx*sy];


	double step_x = x / sx;
	double step_y = y / sy;


	for (int i = 0; i < sx; i++)
		hor[i] = 0;

	for (int i = 0; i < sy; i++)
		ver[i] = 0;

	for (int i = 0; i < sx*sy; i++)
		sq[i] = 0;
	double sum_i = 0;
	double sum_j = 0;
	int number_w = 0;
	int stride = temp.step;
	unsigned char *src_ = (unsigned char*)(temp.data);
	long counter = 0;
	double all = 0.;
	for (int i = 0; i < y; i++)
	{
		int dop = stride * i;
		/*if (i == 149)
		{
			int u = 90;
		}*/
		for (int j = 0; j < x; j++)
		{
			int dopp = dop + j *3;
			if (src_[dopp]>0/*250*/)
			{
				sum_i += i;
				sum_j += j;
				number_w++;

				int ind_x = 1.0*j / step_x;
				int ind_y = 1.0*i / step_y;

				hor[ind_x]++;
				ver[ind_y]++;
				//sq[ind_y*sx + ind_x]++;
				sq[ind_y*sx + ind_x]++;
				all++;
			}


		}

	}


	temp.release();

	sum_i /= number_w;
	sum_j /= number_w;


	double grav_x = sum_j / (x / 100.);
	double grav_y = sum_i / (y / 100.);


	//tmp.release();
	String ret = "";


	double perc_vert = all / 100.;
	double perc_hor = all / 100.;
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
		if (tmp <= 10)
			ret = ret + '0';
		if (tmp > 10 && tmp <= 14)
			ret = ret + '1';
		if (tmp > 14 && tmp <= 18)
			ret = ret + '2';
		if (tmp > 18 && tmp <= 22)
			ret = ret + '3';
		if (tmp > 22 && tmp <= 26)
			ret = ret + '4';
		if (tmp > 26 && tmp <= 30)
			ret = ret + '5';
		if (tmp > 30 && tmp <= 34)
			ret = ret + '6';
		if (tmp > 34 && tmp <= 38)
			ret = ret + '7';
		if (tmp > 38 && tmp <= 42)
			ret = ret + '8';
		if (tmp > 42 && tmp <= 100)
			ret = ret + '9';
	}

	/*ret = ret + ' ';

	{
		int i = 2;
		for (int r = 0; r < 2; r++)
		{
			double tmp = ver[i] / perc_hor;
			if (tmp <= 10)
				ret = ret + '0';
			if (tmp > 10 && tmp <= 14)
				ret = ret + '1';
			if (tmp > 14 && tmp <= 18)
				ret = ret + '2';
			if (tmp > 18 && tmp <= 22)
				ret = ret + '3';
			if (tmp > 22 && tmp <= 26)
				ret = ret + '4';
			if (tmp > 26 && tmp <= 30)
				ret = ret + '5';
			if (tmp > 30 && tmp <= 34)
				ret = ret + '6';
			if (tmp > 34 && tmp <= 38)
				ret = ret + '7';
			if (tmp > 38 && tmp <= 42)
				ret = ret + '8';
			if (tmp > 42 && tmp <= 100)
				ret = ret + '9';
		}
	}*/


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
		if (tmp > 100.)
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
	/*for (int i = 0; i < 6; i++)
	{
		double tmp = ht;
		if (tmp <= 30.)
			ret = ret + '0';
		if (tmp > 30. && tmp <= 80.)
			ret = ret + '1';
		if (tmp > 80. && tmp <= 130.)
			ret = ret + '2';
		if (tmp > 130.)
			ret = ret + '3';
		
		
		
	}


	ret = ret + ' ';

	for (int i = 0; i < 6; i++)
	{
		double tmp = wt;
		
		if (tmp <= 30.)
			ret = ret + '0';
		if (tmp > 30. && tmp <= 80.)
			ret = ret + '1';
		if (tmp > 80. && tmp <= 130.)
			ret = ret + '2';
		if (tmp > 130.)
			ret = ret + '3';
	}*/

	/*ret = ret + ' ';

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
	}*/


	ret = ret + ' ';
	ret = ret + '?';

	return ret;
}

std::string Recognition::GetCode4(Mat* src, int sx, int sy, double ht, double wt, double grav_x, double grav_y)
{
	int x = 100;
	int y = 150;

	Mat tmp;
	src[0].copyTo(tmp);


	Preprocessing::ReSize3(&tmp, x, y);
	Preprocessing::SisThreshold(&tmp);


	double sum_i = 0;
	double sum_j = 0;
	int number_w = 0;
	int stride = tmp.step;
	unsigned char *src_ = (unsigned char*)(tmp.data);

	String ret = "";

	for (int i = 0; i < y; i++)
	{
		int dop = stride * i;

		for (int j = 0; j < x; j++)
		{
			int dopp = dop + j * 3;
			if (src_[dopp]>250)
			{
				ret = ret + '1';
			}
			else
			{
				ret = ret + '0';
			}


		}

	}

	ret = ret + ' ';
	ret = ret + '?';

	return ret;
}

Blob_* Recognition::Marking2(Mat* _src, Mat* bmp, int& counter, double ht, double wt)
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

	

	Preprocessing::BlobsCorrection(blobs, counter, &src_gray);

	for (int i = 0; i < blobs_counter; i++)
	{
		Preprocessing::BlobsCorrectionPixels(&blobs[i].image);

	}

	double av_h = 0.;
	double av_w = 0.;

	for (int i = 0; i < blobs_counter; i++)
	{
		av_h += blobs[i].image.rows;
		av_w += blobs[i].image.cols;
	}
	av_h /= blobs_counter;
	av_w /= blobs_counter;


	CodeCorrection3(blobs, counter, ht, wt);


	for (int i = 0; i < blobs_counter; i++)
	{
		
		
		Point begin = blobs[i].location;
		Point end(begin.x + blobs[i].image.cols, begin.y + blobs[i].image.rows);
		
		if (begin.x < 0)
			begin.x = 0;
		if (end.x >= _src[0].cols)
			end.x = _src[0].cols - 1;

		if (begin.y < 0)
			begin.y = 0;
		if (end.y >= _src[0].rows)
			end.y = _src[0].rows - 1;

			


		blobs[i].src = Preprocessing::ChangeFrame2(_src, begin, end);
		cvtColor(blobs[i].image, blobs[i].image, COLOR_GRAY2BGR);
	}

	return blobs;
}


void Recognition::Marking3(Mat* _src, Mat* bmp, int& counter, double ht, double wt)
{
	int width = bmp[0].cols;
	int height = bmp[0].rows;
	Mat src_gray;
	int lp = bmp[0].type();
	if (lp != 0)
		cvtColor(bmp[0], src_gray, COLOR_BGR2GRAY);
	else
		src_gray = bmp[0].clone();
	

	Preprocessing::BlobsCorrection(blobs, counter, &src_gray);

	src_gray.release();

	double av_h = 0.;
	double av_w = 0.;

	for (int i = 0; i < blobs_counter; i++)
	{
		av_h += blobs[i].image.rows;
		av_w += blobs[i].image.cols;
	}
	av_h /= blobs_counter;
	av_w /= blobs_counter;


	CodeCorrection3(blobs, counter, ht, wt);


	for (int i = 0; i < blobs_counter; i++)
	{

		Point begin = blobs[i].location;
		Point end(begin.x + blobs[i].image.cols, begin.y + blobs[i].image.rows);

		if (begin.x < 0)
			begin.x = 0;
		if (end.x >= _src[0].cols)
			end.x = _src[0].cols - 1;

		if (begin.y < 0)
			begin.y = 0;
		if (end.y >= _src[0].rows)
			end.y = _src[0].rows - 1;
		blobs[i].src = Preprocessing::ChangeFrame2(_src, begin, end);
		//Mat cvt;
		cvtColor(blobs[i].image, blobs[i].image, COLOR_GRAY2BGR);
		/*blobs[i].image.release();
		blobs[i].image = cvt.clone();
		cvt.release();*/
	}

	
}

void Recognition::ReadEDB(std::string _edb_file_name)
{
	edb_file_name = _edb_file_name;
	ifstream strm(edb_file_name);
	char ss[40] = { 0 };
	strm.getline(ss, 40);
	edb_counter = atoi(ss);
	edb = new std::string[edb_counter];
	for (int i = 0; i < edb_counter; i++)
	{
		char ss[40] = { 0 };
		strm.getline(ss, 40);
		std::string tmp(ss);
		edb[i]=tmp;
	}
	strm.close();

}

std::string* Recognition::ReadEDBCompare(std::string _edb_file_name, int& edb_counter)
{
	std::string* _edb;
	ifstream strm(_edb_file_name);
	char ss[40] = { 0 };
	strm.getline(ss, 40);
	edb_counter = atoi(ss);
	_edb = new std::string[edb_counter];
	for (int i = 0; i < edb_counter; i++)
	{
		char ss[40] = { 0 };
		strm.getline(ss, 40);
		std::string tmp(ss);
		_edb[i] = tmp;
	}
	strm.close();
	return _edb;
}

void Recognition::WriteEDB(std::string _edb_file_name)
{
	edb_file_name = _edb_file_name;
	ofstream strm(edb_file_name);
	strm << edb_counter << '\n';
	for (int i = 0; i < edb_counter; i++)
	{
		strm << edb[i] << '\n';
	}
	strm.close();
}

int Recognition::DifStrings(std::string str1, std::string str2)
{
	int dif = 0;
	int sum = 0;
	for (int i = 0; i < str1.length()-1; i++)
		dif += abs(str1[i] - str2[i]);
	return dif;
}

int Recognition::BestVar(std::string str, int& dif)
{
	int min = 100000;
	int poz = -1;
	for (int i = 0; i < edb_counter; i++)
	{
		int tmp = DifStrings(str, edb[i]);
		if (tmp <= min)
		{
			min = tmp;
			poz = i;
		}
	}
	dif = min;
	return poz;
}

int Recognition::BestVarCompare(std::string str, int& dif, int edb_counter, std::string* edb)
{
	int min = 100000;
	int poz = -1;
	for (int i = 0; i < edb_counter; i++)
	{
		int tmp = DifStrings(str, edb[i]);
		if (tmp <= min)
		{
			min = tmp;
			poz = i;
		}
	}
	dif = min;
	return poz;
}
void Recognition::DRec(int number)
{
	std::string* edb1 = new std::string[edb_counter-1];
	int new_counter = 0;
	for (int i = 0; i < edb_counter; i++)
	{
		if (i != number)
			edb1[new_counter++] = edb[i];
	}
	if (edb_counter>0)
		delete[] edb;
	edb_counter--;
	edb = edb1;
	Sort();
}
void Recognition::ARec(std::string str)
{
	std::string* edb1 = new std::string[edb_counter + 1];
	int new_counter = 0;
	for (int i = 0; i < edb_counter; i++)
	{
		edb1[i] = edb[i];
	}
	if (edb_counter>0)
		delete[] edb;
	edb1[edb_counter] = str;
	edb_counter++;
	edb = edb1;
	Sort();
}

void Recognition::NewEDB()
{
	if (edb_counter > 0)
		delete[] edb;
	if (edb_file_names_counter > 0)
		delete[] edb_file_names;
	
	edb_counter = 0;
	edb_file_name = "";
	edb_file_names_counter = 0;
}

void Recognition::Sort()
{
	if (edb_counter < 2) return;
	std::string* edb1 = new std::string[edb_counter];
	int let = edb[0].length()-1;
	int poz = -1;
	int min = 255;
	int counter = 0;
	do
	{
		
		poz = -1;
		min = 255;
		for (int i = 0; i < edb_counter; i++)
		{
			if (edb[i] != "")
			{
				std::string tmp = edb[i];
				if (tmp[let] < min)
				{
					poz = i;
					min = tmp[let];
				}
			}
		}
		if (poz > -1)
		{
			edb1[counter] = edb[poz];
			counter++;
			edb[poz] = "";
		}
	} while (poz != -1);
	if (edb_counter>0)
		delete[] edb;
	edb = edb1;
}

std::string Recognition::ChangeLet(std::string str, char ch)
{
	str[str.length() - 1] = ch;
	return str;
}
void Recognition::Recogize()
{
	for (int i = 0; i < blobs_counter; i++)
	{
		int poz = -1;
		std::string tmp = blobs[i].code;
		std::string tmp1 = "";
		int res =BestVar(tmp, poz);
		if (res > -1)
		{
			tmp1 = edb[res];
			tmp[tmp.length() - 1] = tmp1[tmp1.length() - 1];
			blobs[i].code = tmp;

		}
	}
}

double Recognition::RecogizeCompare(int _edb_counter, std::string* _edb)
{
	double counter = 0.;
	for (int i = 0; i < blobs_counter; i++)
	{
		int poz = -1;
		std::string tmp = blobs[i].code;
		 BestVarCompare(tmp, poz, _edb_counter, _edb);
		 counter += poz;
	}
	return counter;
}

std::string* Recognition::Get_Strings(int& string_counter)
{

	int height = src[0].rows;
	int width = src[0].cols;

	int counter = 0;
	int old_counter = 0;
	int* rows = new int[10000];
	int rows_counter=0;
	int* numbers = new int[blobs_counter];
	int* lengths = new int[blobs_counter];

	for (int i = 0; i < blobs_counter; i++)
	{
		numbers[i] = i;
		lengths[i] = 0;
		
	}
	
	int matrx_counter = 0;

	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			matrx[i][j] = -1;
		}
	}



	matrx_counter = 0;
	int old_i = 0;
	int dest = 5;

	for (int i = 0; i < height; i+=2)
	{
		counter = 0;
		for (int j = 0; j < blobs_counter; j++)
		{
			if (numbers[j] > -1)
			{
				int y_beg = blobs[j].location.y;
				int y_end = blobs[j].location.y + blobs[j].image.rows;
				if (i > y_beg && i < y_end)
				if (i > y_beg-5 && i < y_end+5)
				{
					counter++;

				}
			}
		}
		if (counter < old_counter && counter >3)
		{
			int string_number = 0;
			for (int j = 0; j < blobs_counter; j++)
			{
				if (numbers[j] > -1)
				{
					int y_beg = blobs[j].location.y;
					int y_end = blobs[j].location.y + blobs[j].image.rows;
					if (old_i > y_beg && old_i < y_end)
					{
						matrx[matrx_counter][string_number] = j;
						string_number++;
						numbers[j] = -1;
						
					}
				}
			}
			lengths[matrx_counter] = string_number;
			matrx_counter++;
			counter = 0;
			
		}
		old_i = i;
		old_counter = counter;
	}


	for (int i = 0; i < matrx_counter; i++)
	{
		SortRow(i, lengths[i]);
		InsertSpace(i, lengths[i]);
		CorrectO(i, lengths[i]);
		//CorrectI(i, lengths[i]);
	}

	std::string* ret = new std::string[matrx_counter];
	for (int i = 0; i < matrx_counter; i++)
	{
		ret[i] = "";
		for (int j = 0; j < lengths[i]; j++)
		{
			if (matrx[i][j] != -2)
			{
				std::string tmp = blobs[matrx[i][j]].code;
				tmp = tmp[tmp.length() - 1];
				ret[i] += tmp;
			}
			else
			{
				ret[i] += " ";
			}
		}
	}
	string_counter = matrx_counter;
	return ret;
}


std::string* Recognition::Get_Strings2(int& string_counter)
{

	int height = src[0].rows;
	int width = src[0].cols;

	int counter = 0;
	int old_counter = 0;
	int* rows = new int[10000];
	int rows_counter = 0;
	int* numbers = new int[blobs_counter];
	int* lengths = new int[blobs_counter];

	for (int i = 0; i < blobs_counter; i++)
	{
		numbers[i] = i;
		lengths[i] = 0;

	}

	int matrx_counter = 0;

	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 1000; j++)
		{
			matrx[i][j] = -1;
		}
	}



	matrx_counter = 0;
	int old_i = 0;
	int dest = 5;

	for (int i = 0; i < height; i += 2)
	{
		counter = 0;
		for (int j = 0; j < blobs_counter; j++)
		{
			if (numbers[j] > -1)
			{
				int y_beg = blobs[j].location.y;
				int y_end = blobs[j].location.y + blobs[j].image.rows;
				if (i > y_beg && i < y_end)
					if (i > y_beg - 5 && i < y_end + 5)
					{
						counter++;

					}
			}
		}
		if (counter < old_counter && counter >3)
		{
			int string_number = 0;
			for (int j = 0; j < blobs_counter; j++)
			{
				if (numbers[j] > -1)
				{
					int y_beg = blobs[j].location.y;
					int y_end = blobs[j].location.y + blobs[j].image.rows;
					if (old_i > y_beg && old_i < y_end)
					{
						matrx[matrx_counter][string_number] = j;
						string_number++;
						numbers[j] = -1;

					}
				}
			}
			lengths[matrx_counter] = string_number;
			matrx_counter++;
			counter = 0;

		}
		old_i = i;
		old_counter = counter;
	}


	for (int i = 0; i < matrx_counter; i++)
	{
		SortRow(i, lengths[i]);
		InsertSpace(i, lengths[i]);
		CorrectO(i, lengths[i]);
		//CorrectI(i, lengths[i]);
	}

	std::string* ret = new std::string[matrx_counter];
	for (int i = 0; i < matrx_counter; i++)
	{
		ret[i] = "";
		for (int j = 0; j < lengths[i]; j++)
		{
			if (matrx[i][j] != -2)
			{
				std::string tmp = blobs[matrx[i][j]].code;
				tmp = tmp[tmp.length() - 1];
				ret[i] += tmp;
			}
			else
			{
				ret[i] += " ";
			}
		}
	}
	string_counter = matrx_counter;
	return ret;
}


void Recognition::SortRow(int number, int Length)
{
	int* sorted = new int[1000];
	for (int i = 0; i < 1000; i++)
		sorted[i] = 0;
	int poz = -1;
	int counter = 0;
	do
	{
		double min = 100000.;
		
		poz = -1;
		for (int i = 0; i < Length; i++)
		{
			if (matrx[number][i] != -1)
			{
				if (blobs[matrx[number][i]].location.x < min)
				{
					min = blobs[matrx[number][i]].location.x;
					poz = i;
				}
			}
		}
		if (poz != -1)
		{
			sorted[counter] = matrx[number][poz];
			matrx[number][poz] = -1;
			counter++;
		}
	} while (poz > -1);
		for (int i = 0; i < Length; i++)
		{
			matrx[number][i] = sorted[i];
		}

}

void Recognition::CorrectO(int number, int Length)
{
	char t0, t1, t2;
	for (int i = 0; i < Length; i++)
	{
		if (i > 0 && i < Length - 1)
		{
			if (matrx[number][i - 1] == -2)
				t0 = ' ';
			else
				t0 = blobs[matrx[number][i - 1]].code[blobs[matrx[number][i - 1]].code.length() - 1];

			if (matrx[number][i] == -2)
				t1 = ' ';
			else
				t1 = blobs[matrx[number][i]].code[blobs[matrx[number][i]].code.length() - 1];
			if (matrx[number][i + 1] == -2)
				t2 = ' ';
			else
				t2 = blobs[matrx[number][i + 1]].code[blobs[matrx[number][i + 1]].code.length() - 1];

			bool a1 = t0 >= 43 && t0 <= 62 || t0==' '; // left digit
		
			bool a3 = t2 >= 43 && t2 <= 62 || t2==' '; // right digit;

			if (t1 == '0')
			{
				if (!a1 || !a3)
					blobs[matrx[number][i]].code[blobs[matrx[number][i]].code.length() - 1] = 'O';
			}
			if (t1 == 'O' || t1 == 'o')
			{
				if (a1 && a3)
					blobs[matrx[number][i]].code[blobs[matrx[number][i]].code.length() - 1] = '0';
			}

		}
		if (i == 0 && Length>1)
		{
			
			if (matrx[number][i] == -2)
				t1 = ' ';
			else
				t1 = blobs[matrx[number][i]].code[blobs[matrx[number][i]].code.length() - 1];
			if (matrx[number][i + 1] == -2)
				t2 = ' ';
			else
				t2 = blobs[matrx[number][i + 1]].code[blobs[matrx[number][i + 1]].code.length() - 1];

			
			
			bool a3 = t2 >= 43 && t2 <= 62 || t2 == ' '; // right digit;


			if (t1 == '0')
			{
				if (!a3)
					blobs[matrx[number][i]].code[blobs[matrx[number][i]].code.length() - 1] = 'O';
			}
			if (t1 == 'O' || t1 == 'o')
			{
				if (a3)
					blobs[matrx[number][i]].code[blobs[matrx[number][i]].code.length() - 1] = '0';
			}
		}
		if (i == Length - 1 && Length>1)
		{
			if (matrx[number][i - 1] == -2)
				t0 = ' ';
			else
				t0 = blobs[matrx[number][i - 1]].code[blobs[matrx[number][i - 1]].code.length() - 1];

			if (matrx[number][i] == -2)
				t1 = ' ';
			else
				t1 = blobs[matrx[number][i]].code[blobs[matrx[number][i]].code.length() - 1];

			bool a1 = t0 >= 43 && t0 <= 62 || t0 == ' '; // left digit

			if (t1 == '0')
			{
				if (!a1)
					blobs[matrx[number][i]].code[blobs[matrx[number][i]].code.length() - 1] = 'O';
			}
			if (t1 == 'O' || t1 == 'o')
			{
				if (a1)
					blobs[matrx[number][i]].code[blobs[matrx[number][i]].code.length() - 1] = '0';
			}
		}
	}
}

void Recognition::CorrectI(int number, int Length)
{
	char t0, t1, t2;
	for (int i = 0; i < Length; i++)
	{
		if (i > 0 && i < Length - 1)
		{
			if (matrx[number][i - 1] == -2)
				t0 = ' ';
			else
				t0 = blobs[matrx[number][i - 1]].code[blobs[matrx[number][i - 1]].code.length() - 1];

			if (matrx[number][i] == -2)
				t1 = ' ';
			else
				t1 = blobs[matrx[number][i]].code[blobs[matrx[number][i]].code.length() - 1];
			if (matrx[number][i + 1] == -2)
				t2 = ' ';
			else
				t2 = blobs[matrx[number][i + 1]].code[blobs[matrx[number][i + 1]].code.length() - 1];

			bool a1 = t0 >= 43 && t0 <= 62 || t0 == ' '; // left digit

			bool a3 = t2 >= 43 && t2 <= 62 || t2 == ' '; // right digit;

			if (t1 == '1')
			{
				if (!a1 || !a3)
					blobs[matrx[number][i]].code[blobs[matrx[number][i]].code.length() - 1] = 'I';
			}
			if (t1 == 'I' || t1 == 'i')
			{
				if (a1 && a3)
					blobs[matrx[number][i]].code[blobs[matrx[number][i]].code.length() - 1] = '1';
			}

		}
		if (i == 0 && Length>1)
		{

			if (matrx[number][i] == -2)
				t1 = ' ';
			else
				t1 = blobs[matrx[number][i]].code[blobs[matrx[number][i]].code.length() - 1];
			if (matrx[number][i + 1] == -2)
				t2 = ' ';
			else
				t2 = blobs[matrx[number][i + 1]].code[blobs[matrx[number][i + 1]].code.length() - 1];



			bool a3 = t2 >= 43 && t2 <= 62 || t2 == ' '; // right digit;


			if (t1 == '1')
			{
				if (!a3)
					blobs[matrx[number][i]].code[blobs[matrx[number][i]].code.length() - 1] = 'I';
			}
			if (t1 == 'I' || t1 == 'i')
			{
				if (a3)
					blobs[matrx[number][i]].code[blobs[matrx[number][i]].code.length() - 1] = '1';
			}
		}
		if (i == Length - 1 && Length>1)
		{
			if (matrx[number][i - 1] == -2)
				t0 = ' ';
			else
				t0 = blobs[matrx[number][i - 1]].code[blobs[matrx[number][i - 1]].code.length() - 1];

			if (matrx[number][i] == -2)
				t1 = ' ';
			else
				t1 = blobs[matrx[number][i]].code[blobs[matrx[number][i]].code.length() - 1];

			bool a1 = t0 >= 43 && t0 <= 62 || t0 == ' '; // left digit

			if (t1 == '1')
			{
				if (!a1)
					blobs[matrx[number][i]].code[blobs[matrx[number][i]].code.length() - 1] = 'I';
			}
			if (t1 == 'I' || t1 == 'i')
			{
				if (a1)
					blobs[matrx[number][i]].code[blobs[matrx[number][i]].code.length() - 1] = '1';
			}
		}
	}
}

void Recognition::InsertSpace(int number, int& Length)
{
	int* sorted = new int[1000];
	double average = 0;
	for (int i = 0; i < Length; i++)
	{
		average += blobs[matrx[number][i]].image.cols;
	}

	average /= Length;
	
	sorted[0] = matrx[number][0];
	int counter = 1;

	for (int i = 1; i < Length; i++)
	{
		for (int j = 2; j<10;j++)
		if (blobs[matrx[number][i]].location.x - blobs[matrx[number][i - 1]].location.x>average*j)
		{
			sorted[counter] = -2;
			counter++;
		}

		sorted[counter] = matrx[number][i];
		counter++;

	}

	for (int i = 0; i < counter; i++)
	{
		matrx[number][i] = sorted[i];
	}
	Length = counter;
}
bool Recognition::PrePro(Mat* src, Mat* big, int& counter)
{
	bool res = Preprocessing::RotateAndCut(big, counter);
	src[0].release();
	src[0] = big[0].clone();
	return res;
}



bool Recognition::PrePro2(Mat* src, Mat* big, int& counter)
{
	bool res = Preprocessing::RotateAndCut(big, counter);
	src[0].release();
	src[0] = big[0].clone();
	return res;
}

void Recognition::Gravitation(Blob_* _src)
{
	int width = _src[0].image.cols;
	int height = _src[0].image.rows;

	if (width < 5 || height < 5) return;

	int stride = _src[0].image.step;

	unsigned char *src_ = (unsigned char*)(_src[0].image.data);

	double sum_i = 0;
	double sum_j = 0;
	int number_w = 0;

	for (int i = 0; i < height; i++)
	{
		int dop = stride * i;

		for (int j = 0; j < width; j++)
		{
			int dopp = dop + j;// *3;
			if (src_[dopp]>0/*250*/)
			{
				sum_i += i;
				sum_j += j;
				number_w++;

			}
		}
	}

	if (number_w < 1) return;

	sum_i /= number_w;
	sum_j /= number_w;

	
	
	int width_new = 2*max(sum_j, width - sum_j);
	int height_new = 2*max(sum_i, height-sum_i);
	cv::Size sz(width_new, height_new);

	Mat out(sz, _src[0].image.type(), cv::Scalar::all(0));


	Rect source = cv::Rect(Point(0,0), Point(width,height));

	int beg_x = 0; 
	int end_x = 0;

	int beg_y = 0;
	int end_y = 0;

	if (width - sum_j > sum_j)
	{
		beg_x = width - 2 * sum_j;
		//src[0].location.x -= (2*sum_j - width);
		int lok = _src[0].location.x;
		_src[0].location.x -= (width_new - width);
		end_x = out.cols;

	}
	else
	{
		beg_x = 0;
		end_x = width;
	}
	if (height - sum_i > sum_i)
	{
		beg_y = height - 2 * sum_i;
		//src[0].location.y -= (2*sum_i - height);
		_src[0].location.y -= (height_new - height);
		end_y = out.rows;
	}
	else
	{
		beg_y = 0;
		end_y = height;
	}
	Rect target = cv::Rect(Point(beg_x,beg_y), Point(end_x,end_y));
	_src[0].image(source).copyTo(out(target));
	_src[0].image.release();
	_src[0].image=out.clone();
	out.release();

}

Mat Recognition::ReProcessing3(Mat* _src)
{

	Blob_ * big_blobs = new Blob_[blobs_counter];
	Blob_ * small_blobs = new Blob_[blobs_counter];
	int counter_big_blobs = 0;
	int counter_small_blobs = 0;

	int w = _src[0].cols;
	int h = _src[0].rows;

	for (int i = 0; i < blobs_counter; i++)
	{
		int wi = blobs[i].image.cols;
		int hi = blobs[i].image.rows;
		bool cond = wi > 0 && hi > 0 && wi < w / 2 && hi < h / 2;

		if (cond)
		{
			Point begin = blobs[i].location;
			Point end(begin.x + blobs[i].image.cols, begin.y + blobs[i].image.rows);


			blobs[i].image.release();

			blobs[i].image = Preprocessing::ChangeFrame2(_src, begin, end);

			Preprocessing::Enhance(&blobs[i].image);
			Preprocessing::SisThreshold(&blobs[i].image);
			Preprocessing::Invert(&blobs[i].image);

			cvtColor(blobs[i].image, blobs[i].image, COLOR_BGR2GRAY);



			if (blobs[i].image.cols > blobs[i].image.rows)
			{
				big_blobs[counter_big_blobs] = blobs[i];
				counter_big_blobs++;
			}
			else
			{
				small_blobs[counter_small_blobs] = blobs[i];
				counter_small_blobs++;
			}
		}
	}



	Mat res_mat(_src[0].rows, _src[0].cols, CV_8UC1, Scalar(0));
	res_mat = BlobsBuild_::PutBlobsBlackWhite(res_mat, big_blobs, counter_big_blobs, 1);



	int counter = 0;
	Blob_* blobs_new = BlobCounter_::GetBlobs(res_mat, true, true, counter);

	blobs_counter = counter + counter_small_blobs;

	delete[] blobs;
	blobs = new Blob_[blobs_counter];

	for (int i = 0; i < counter; i++)
	{
		blobs[i] = blobs_new[i];
	}


	for (int i = 0; i < counter_small_blobs; i++)
	{
		blobs[i + counter] = small_blobs[i];
	}

	delete[] small_blobs;
	delete[] blobs_new;
	for (int i = 0; i < blobs_counter; i++)
	{
		Preprocessing::Dilation2(&blobs[i].image);
	}


	
	Mat res_mat2(_src[0].rows, _src[0].cols, CV_8UC1, Scalar(0));
	BlobsBuild_::PutBlobsBlackWhite(&res_mat2, blobs, blobs_counter, 1);

	//imwrite("c:\\0000000aaa.jpg", res_mat2);
	return res_mat2;
}

Mat Recognition::ReProcessing4(Mat* _src)
{

	Blob_ * big_blobs = new Blob_[blobs_counter];
	Blob_ * small_blobs = new Blob_[blobs_counter];
	int counter_big_blobs = 0;
	int counter_small_blobs = 0;

	int w = _src[0].cols;
	int h = _src[0].rows;

	for (int i = 0; i < blobs_counter; i++)
	{
		int wi = blobs[i].image.cols;
		int hi = blobs[i].image.rows;
		bool cond = wi > 0 && hi > 0 && wi < w / 2 && hi < h / 2;

		if (cond)
		{
			Point begin = blobs[i].location;
			Point end(begin.x + blobs[i].image.cols, begin.y + blobs[i].image.rows);


			blobs[i].image.release();

			blobs[i].image = Preprocessing::ChangeFrame2(_src, begin, end);

			Preprocessing::Enhance(&blobs[i].image);
			Preprocessing::SisThreshold(&blobs[i].image);
			Preprocessing::Invert(&blobs[i].image);

			cvtColor(blobs[i].image, blobs[i].image, COLOR_BGR2GRAY);



			if (blobs[i].image.cols*1.5 > blobs[i].image.rows)
			{
				big_blobs[counter_big_blobs] = blobs[i];
				counter_big_blobs++;
			}
			else
			{
				small_blobs[counter_small_blobs] = blobs[i];
				counter_small_blobs++;
			}
		}
	}



	Mat res_mat(_src[0].rows, _src[0].cols, CV_8UC1, Scalar(0));
	BlobsBuild_::PutBlobsBlackWhite(&res_mat, big_blobs, counter_big_blobs, 1);

	int counter = 0;
	Blob_* blobs_new = BlobCounter_::GetBlobs(res_mat, true, true, counter);
	res_mat.release();


	blobs_counter = counter + counter_small_blobs;
	
	delete[] blobs;
	blobs = new Blob_[blobs_counter];

	for (int i = 0; i < counter; i++)
	{
		blobs[i] = blobs_new[i];
	}


	for (int i = 0; i < counter_small_blobs; i++)
	{
		blobs[i + counter] = small_blobs[i];
	}

	delete[] small_blobs;
	delete[] blobs_new;

	for (int i = 0; i < blobs_counter; i++)
	{
		Preprocessing::Dilation2(&blobs[i].image);
		if (!bold)
			Preprocessing::Erosion2(&blobs[i].image);
	}
	
	Mat res_mat2(_src[0].rows, _src[0].cols, CV_8UC1, Scalar(0));
	BlobsBuild_::PutBlobsBlackWhite(&res_mat2, blobs, blobs_counter, 1);

	//imwrite("c:\\0000000aaa.jpg", res_mat2);
	return res_mat2;
}