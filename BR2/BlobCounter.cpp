#include "BlobCounter.h"


BlobCounter_::BlobCounter_()
{
}


BlobCounter_::~BlobCounter_()
{
	/*if (objectsCount>0)
		delete[] objectLabels;*/
}

void BlobCounter_::ProcessImage(Mat srcImg, bool WhiteNoBlack)
{

	unsigned char ColorIs;

	if (WhiteNoBlack)
		ColorIs = 0;
	else
		ColorIs = 255;


	int width = srcImg.cols;
	int height = srcImg.rows;



	objectLabels = new int[width * height];


	for (int i = 0; i < width*height; i++)
		objectLabels[i] = 0;

	int labelsCount = 0;


	int		maxObjects = ((width / 2) + 1) * ((height / 2) + 1) + 1;
	int* map = new int[maxObjects];

	
	for (int i = 0; i < maxObjects; i++)
	{
		map[i] = i;
	}


	int srcStride = srcImg.step;
	


	unsigned char*	src = (unsigned char*)srcImg.data;
	


	if (src[0] != ColorIs)
	{
		objectLabels[0] = ++labelsCount;
	}
	

	for (int x = 1; x < width; x++)
	{
		
		if (src[x] != ColorIs)
		{

			if (src[x-1] != ColorIs)
			{

				objectLabels[x] = objectLabels[x - 1];
			}
			else
			{

				objectLabels[x] = ++labelsCount;
			}
		}
	}


	for (int y = 1; y < height; y++)
	{
		int dop = y* srcImg.step;
		if (src[dop] != ColorIs)
		{

			if (src[dop-srcStride] != ColorIs)
			{

				objectLabels[dop] = objectLabels[dop - width];
			}
			else if (src[dop + 1 - srcStride] != ColorIs)
			{

				objectLabels[dop] = objectLabels[dop + 1 - width];
			}
			else
			{

				objectLabels[dop] = ++labelsCount;
			}
		}
		

		for (int x = 1; x < width - 1; x++)
		{
			int dopp = dop + x;
			if (src[dopp] != ColorIs)
			{

				if (src[dopp - 1] != ColorIs)
				{

					objectLabels[dopp] = objectLabels[dopp - 1];
				}
				else if (src[dopp - 1 - srcStride] != ColorIs)
				{

					objectLabels[dopp] = objectLabels[dopp - 1 - width];
				}
				else if (src[dopp - srcStride] != ColorIs)
				{

					objectLabels[dopp] = objectLabels[dopp - width];
				}

				if (src[dopp+1 - srcStride] != ColorIs)
				{
					if (objectLabels[dopp] == 0)
					{

						objectLabels[dopp] = objectLabels[dopp + 1 - width];
					}
					else
					{
						int	l1 = objectLabels[dopp];
						int l2 = objectLabels[dopp + 1 - width];

						if (l1 >= 0 && l2 >= 0 && l1<maxObjects && l2<maxObjects)
						{
							if ((l1 != l2) && (map[l1] != map[l2]))
							{

								if (map[l1] == l1)
								{

									map[l1] = map[l2];
								}
								else if (map[l2] == l2)
								{
									map[l2] = map[l1];
								}
								else
								{

									map[map[l1]] = map[l2];
									map[l1] = map[l2];
								}


								for (int i = 0; i <= labelsCount; i++)
								{
									if (map[i] != i)
									{

										int j = map[i];
										while (j != map[j])
										{
											j = map[j];
										}

										map[i] = j;

									}
								}
							}
						}

					}
				}

				if (objectLabels[dopp] == 0)
				{

					objectLabels[dopp] = ++labelsCount;
				}
			}
		}


		if (src[dop] != ColorIs)
		{

			if (src[dop-1] != ColorIs)
			{

				objectLabels[dop] = objectLabels[dop - 1];
			}
			else if (src[dop-1 - srcStride] != ColorIs)
			{

				objectLabels[dop] = objectLabels[dop - 1 - width];
			}
			else if (src[dop-srcStride] != ColorIs)
			{

				objectLabels[dop] = objectLabels[dop - width];
			}
			else
			{

				objectLabels[dop] = ++labelsCount;
			}
		}
		


	}

	int* reMap = new int[maxObjects];
	for (int i = 0; i < maxObjects; i++)
		reMap[i] = 0;

	objectsCount = 0;
	for (int i = 1; i <= labelsCount; i++)
	{
		if (map[i] == i)
		{

			reMap[i] = ++objectsCount;
		}
	}

	for (int i = 1; i <= labelsCount; i++)
	{
		if (map[i] != i)
		{
			reMap[i] = reMap[map[i]];
		}
	}


	for (int i = 0, n = width * height; i < n; i++)
	{
		if (objectLabels[i] >= 0 && objectLabels[i]<maxObjects)
			objectLabels[i] = reMap[objectLabels[i]];
	}
	delete[] map;
	delete[] reMap;
}

Rect* BlobCounter_::GetObjectRectangles(Mat srcImg, bool WhiteNoBlack)
{
	
	BlobCounter_* blobCounter = new BlobCounter_();


	blobCounter->ProcessImage(srcImg, WhiteNoBlack);

	int*	labels = blobCounter->objectLabels;
	int		count = blobCounter->objectsCount;


	int		width = srcImg.cols;
	int		height = srcImg.rows;
	int		i = 0, label;


	int*	x1 = new int[count + 1];
	int*	y1 = new int[count + 1];
	int*	x2 = new int[count + 1];
	int*	y2 = new int[count + 1];

	for (int j = 1; j <= count; j++)
	{
		x1[j] = width;
		y1[j] = height;
	}


	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++, i++)
		{

			label = labels[i];


			if (label == 0)
				continue;



			if (x < x1[label])
			{
				x1[label] = x;
			}
			if (x > x2[label])
			{
				x2[label] = x;
			}
			if (y < y1[label])
			{
				y1[label] = y;
			}
			if (y > y2[label])
			{
				y2[label] = y;
			}
		}
	}


	Rect* rects = new Rect[count];

	for (int j = 1; j <= count; j++)
	{
		rects[j - 1] = Rect(x1[j], y1[j], x2[j] - x1[j] + 1, y2[j] - y1[j] + 1);
	}

	return rects;
}

Blob_* BlobCounter_::GetBlobs(Mat srcImg, bool WithMorpho, bool WhiteNoBlack, int&  countB)
{
	
	BlobCounter_* blobCounter = new BlobCounter_();


	blobCounter->ProcessImage(srcImg, WhiteNoBlack);

	int* labels = blobCounter->objectLabels;


	countB = 0;

	int count = blobCounter->objectsCount;

	int width = srcImg.cols;
	int height = srcImg.rows;

	int i = 0, label;


	int* x1 = new int[count + 1];
	int* y1 = new int[count + 1];
	int* x2 = new int[count + 1];
	int* y2 = new int[count + 1];

	for (int i = 0; i < count + 1; i++)
	{
		x1[i] = 0;
		x2[i] = 0;
		y1[i] = 0;
		y2[i] = 0;
	}

	for (int k = 1; k <= count; k++)
	{
		x1[k] = width;
		y1[k] = height;
	}


	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++, i++)
		{

			
			label = blobCounter->objectLabels[i];


			if (label == 0)
				continue;


			if (label >= 0 && label<count-1)
			{
				if (x < x1[label])
				{
					x1[label] = x;
				}
				if (x > x2[label])
				{
					x2[label] = x;
				}
				if (y < y1[label])
				{
					y1[label] = y;
				}
				if (y > y2[label])
				{
					y2[label] = y;
				}
			}
		}
	}
	
	Blob_* objects = new Blob_[count];
	//Mat* mats = new Mat[count];
	

	int srcStride = srcImg.step;
	
	Mat* dstImg;
	int counterT = 0;
	for (int k = 1; k <= count; k++)
	{
		int xmin = x1[k];
		int xmax = x2[k];
		int ymin = y1[k];
		int ymax = y2[k];
		int objectWidth = xmax - xmin + 1;
		int objectHeight = ymax - ymin + 1;
		if (objectWidth * objectHeight > 100 && objectHeight>0 && objectWidth>0)
		{
			
			objects[countB].image = Mat::zeros(objectHeight, objectWidth, CV_8UC1); 

			int dstStride = objects[countB].image.step;




			unsigned char* src = (unsigned char*)srcImg.data;// +ymin * srcStride + xmin;
			unsigned char* dst = (unsigned char*)objects[countB].image.data;
			int p = ymin * width + xmin;

			

			int w = objects[countB].image.rows;
			int h = objects[countB].image.cols;

			
			for (int y = ymin; y < ymax; y++)
			{
				int dop_dst = (y - ymin)*objects[countB].image.step;
				int dop_src = y*srcImg.step;
				for (int x = xmin; x < xmax; x++, /*src++, dst++,*/ p++)
				{
					int dopp_dst = dop_dst + (x-xmin);
					int dopp_src = dop_src + x;
					if (!WhiteNoBlack)
						dst[dopp_dst] = 255;

					
					if (blobCounter->objectLabels[dopp_src/*p*/] == k)
					{

						
						dst[dopp_dst] = src[dopp_src];
					}
					

				}
				
			}

			objects[countB].SetBlob(Point(xmin, ymin), true, true);
			objects[countB].number = k - 1;
			objects[countB].location.x = xmin;
			objects[countB].location.y = ymin;

			countB++;
		}

	}


	Blob_* ret = new Blob_[countB];
	
	for (int iii = 0; iii < countB; iii++)
	{


		Blob_ tmp = objects[iii];
		
		ret[iii].image = tmp.image;
		ret[iii].area = tmp.area;
		ret[iii].location = tmp.location;

	}

	delete[] objects;
	delete[] labels;
	delete blobCounter;

	
	return ret;

}

