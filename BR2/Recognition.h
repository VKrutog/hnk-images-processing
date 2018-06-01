/************************************************************************************************************************************************************************************************/
/*                          HIP V.1. Vadym Krutoholovyi. 02.05.2018																												*/
/*								Copyright - WeAreBrain - 2018																														*/
/*																																																*/
/*								Recognition();																																					*/	 																																															
/* Example of using:																																											*/
/*
/* #include "opencv2/imgproc/imgproc.hpp"
/* #include "opencv2/highgui/highgui.hpp"																																																*/
/* #include "Preprocessing.h"																																									*/
/* #include "Recognition.h"																																										*/
/*	...																																															*/
/*																																																*/
/*																																																*/
/* Recognition* rec = new Recognition();																																						*/
/* 																																																*/
/* rec->SetEDB_fileNames(file_names, counter); 																																					*/
/*																																																*/																	
/*	file_names - set of pathes to *.edb files	           ;																																	*/
/*	counter - number of *.edb files																																								*/
/*																																																*/
/*  int str_counter;																																											*/                        
/*  std::string* ret= rec->SetImage(res_mat, str_counter);																																		*/
/*																																																*/
/* ret = array of result strings																																								*/
/* res_mat - source image																																										*/
/* str_counter - number of strings																																								*/
/*																																																*/
/************************************************************************************************************************************************************************************************/




#pragma once
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/photo.hpp"

#include <stdio.h>

#include "Blob.h"
#include "BlobCounter.h"
#include "BlobsBuild.h"
#include "morfology.h"
#include "convexull.h"
#include "Point2.h"
#include <fstream>
#include <iostream>
#include <ctime>

using namespace std;
using namespace cv;

class Recognition
{
public:
	Recognition();
	~Recognition();

	std::string* edb;
	int edb_counter;
	

	void SetEDB(std::string _edb_file_name);
	std::string* Recognition::SetImage(Mat* _src, int& string_counter);
	Blob_* GetBlobs(int& _blob_counter);
	void ReadEDB(std::string _edb_file_name);
	void WriteEDB(std::string _edb_file_name);
	int BestVar(std::string str, int& dif);
	void DRec(int number);
	void ARec(std::string str);
	void NewEDB();
	std::string ChangeLet(std::string str, char ch);
	void SetEDB_fileNames(std::string* _edb_file_names, int _edb_file_names_counter);
	std::string edb_file_name;
	void NewImage();
	void SetBlobSourceImage(Mat* src);
	std::string* SetImage2(Mat* _src, int& string_counter);
	std::string* SetImage3(Mat* _src, int& string_counter);
	

private:
	
	
	std::string* edb_file_names;
	int edb_file_names_counter;
	Mat* src;
	Mat* prcd;
	Blob_* blobs;
	int blobs_counter;
	int error;
	bool Normalization();
	int DifStrings(std::string str1, std::string str2);
	void Sort();
	void Recogize();
	double RecogizeCompare(int _edb_counter, std::string* _edb);
	int BestVarCompare(std::string str, int& dif, int edb_counter, std::string* edb);
	std::string* ReadEDBCompare(std::string _edb_file_name, int& edb_counter);
	int matrx[1000][1000];
	std::string* Get_Strings(int& string_counter);
	void SortRow(int number, int Length);
	void InsertSpace(int number, int& Length);
	void CorrectO(int number, int Length);
	void CorrectI(int number, int Length);
	bool PrePro(Mat* src, Mat* big, int& counter);
	Mat ReProcessing(Mat* _src);
	bool TicketYesNo(Mat* src, Mat* big, int& counter);
	Blob_* Marking2(Mat* _src, Mat* bmp, int& counter);
	Blob_* Recognition::Marking2(Mat* _src, Mat* bmp, int& counter, double ht, double wt);
	void Gravitation(Blob_* _src);
	void CodeCorrection3(Blob_* blobs, int counter, double ht, double wt);
	std::string GetCode3(Mat* src, int sx, int sy, double ht, double wt, double grav_x, double grav_y);
	std::string GetCode4(Mat* src, int sx, int sy, double ht, double wt, double grav_x, double grav_y);
	std::string* Get_Strings2(int& string_counter);
	bool TicketYesNo2(Mat* src, Mat* big, int& counter);
	Mat ReProcessing2(Mat* _src);
	void Marking3(Mat* _src, Mat* bmp, int& counter, double ht, double wt);
	Mat ReProcessing3(Mat* _src);
};

