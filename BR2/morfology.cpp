#include "morfology.h"


morfology_::morfology_()
{
}


morfology_::~morfology_()
{
}

void morfology_::CalcPerimeterAreaRight(Blob_* blob, Mat image)
{

	unsigned char ColorIs;

	if (blob->whiteNoBlack)
		ColorIs = 0;
	else
		ColorIs = 255;
	/*int size = (int)(blob->perimetr);
	Point* coord = new Point[size];*/
	long count = 0;


	long xc = 0;
	long yc = 0;
	float perimetr = 0.0f;
	long area = 0;

	int width = image.cols;
	int height = image.rows;


	int srcStride = image.step;
	int srcOffset = srcStride - width;


	
	unsigned char* src = (unsigned char*)(image.data); 


		for (int y = 0; y < height; y++)
		{
			int dop = y*image.step;
			for (int x = 0; x < width; x++/*, src++, new_src++*/)
			{
				int dopp = dop + x;
				if (src[dopp] != ColorIs)
				{
					area++;
					xc += x;
					yc += y;
				}

				}
			}

		
			if (area != 0)
			{
				xc = (long)(0.5 + xc * 1.0 / area);
				yc = (long)(0.5 + yc * 1.0 / area);
			}


		
	
			blob->area = area;
			blob->xC = xc;
			blob->yC = yc;
	
}





 void morfology_::SetBlob(Blob_* blob, float Perimeter, long _QuantityPointsInPerimetr, long Area, long xc, long yc)
{
	blob->perimetr = Perimeter;
	blob->area = Area;
	blob->quantityPointsInPerimeter = _QuantityPointsInPerimetr;
	double p = (double)Perimeter;
	double a = (double)Area;
	if (a != 0)
		blob->compactness = 4 * 3.149526 *a / (p*p);
	else
		blob->compactness = 0;
	//blob.XC=(int)(xc/Area+0.5);
	//blob.YC=(int)(yc/Area+0.5);
	blob->xC = xc;
	blob->yC = yc;
}

 Point2* morfology_::GetPerimeterCoord(Blob_ blob, long& count)
 {
	 count = 0;
	 Point* points = GetPerimetersCoord(blob, blob.whiteNoBlack, count);
	 Point2* points2 = new Point2[count];

	 for (int i = 0; i < count; i++)
	 {
		 points2[i].x = 0;
		 points2[i].y = 0;
	 }

	 for (int i = 0; i < count; i++)
		 points2[i] = Point2(points[i]);

	// delete points;
	 /*return Convexull_::convexhull(points2, count);*/
	 return points2;

 }

 Point2* morfology_::GetConvexityCoord(Blob_ blob, long& count)
 {
	 count = 0;
	 Point* points = GetPerimetersCoord(blob, blob.whiteNoBlack, count);
	 Point2* points2 = new Point2[count];

	 for (int i = 0; i < count; i++)
	 {
		 points2[i].x = 0;
		 points2[i].y = 0;
	 }

	 for (int i = 0; i < count; i++)
		 points2[i] = Point2(points[i]);

	 delete[] points;
	 Point2* ret;
	 ret = Convexull_::convexhull(points2, count);
	 delete[] points2;
	 return ret;

 }



 Point* morfology_::GetPerimetersCoord(Blob_ blob, bool WhiteNoBlack, long& count)
 {

	 unsigned char ColorIs;

	 if (WhiteNoBlack)
		 ColorIs = 0;
	 else
		 ColorIs = 255;

	 //Point* coord = new Point[(int)(blob.QuantityPointsInPerimeter)];
	 Point* coord = new Point[10000000];

	 for (int i = 0; i < 10000000; i++)
	 {
		 coord[i].x = 0;
		 coord[i].y = 0;
	 }

	 int width = blob.image.cols;
	 int height = blob.image.rows;

	 int srcStride = blob.image.step;
	 int srcOffset = srcStride - width;

	 unsigned char* src = (unsigned char *)blob.image.data;

	 for (int y = 0; y < height; y++)
	 {
		 int dop = y*srcStride;
		 for (int x = 0; x < width; x++)
		 {
			 int dopp = dop + x;
			 if (src[dopp] != ColorIs)
			 {
				 bool flag = false;
				 if (y == 0 || x == 0 || y == height - 1 || x == width - 1)
				 {
					 flag = true;
				 }
				 else
				 {
					 if (src[dopp - 1] == ColorIs)
						 flag = true;
					 if (src[dopp+1] == ColorIs)
						 flag = true;

					 if (src[dopp - srcStride] == ColorIs)
						 flag = true;

					 if (src[dopp + srcStride] == ColorIs)
						 flag = true;
				 }
				 if (flag)
				 {
					 coord[count].x = x;
					 coord[count++].y = y;
				 }
			 }
		 }

		 
	 }

	 Point* coord1 = new Point[count];
	 for (int i = 0; i < count; i++)
	 {
		 coord1 = coord;
	 }
	// delete[] coord;
	 return coord1;
 }
