#include "BlobsBuild.h"


BlobsBuild_::BlobsBuild_()
{
}


BlobsBuild_::~BlobsBuild_()
{
}

Mat BlobsBuild_::PutBlobsBlackWhite(Mat src, Blob_* blobs, int blobsCount, int WhiteNoBlack)
{
	unsigned char clr = 255;
	if (WhiteNoBlack == 0)
		clr = 0;
	unsigned char* src_ = (unsigned char*)src.data;
	int srcStride = src.step;

	for (int i = 0; i < blobsCount; i++)
	{

		int yy = blobs[i].location.y;
		int xx = blobs[i].location.x;


		int widthBlob = blobs[i].image.cols;
		int heightBlob = blobs[i].image.rows;

		int dstStride = blobs[i].image.step;


		unsigned char* dst_ = (unsigned char*)blobs[i].image.data;


		for (int y = 0; y < heightBlob; y++)
		{
			int dop = srcStride*(y + blobs[i].location.y);
			int bdop = dstStride*y;
			for (int x = 0; x < widthBlob; x++)
			{
				int dopp = dop + (x + blobs[i].location.x);// *3;
				int bdopp = bdop + x;
				if (dst_[bdopp] == clr)
				{
					src_[dopp] = dst_[bdopp];
					/*src_[dopp + 1] = dst_[bdopp];
					src_[dopp + 2] = dst_[bdopp];*/
				}

			}

		}

	}
	
	return src;
	
}


Mat BlobsBuild_::PutBlobsBlackWhite3(Mat src, Blob_* blobs, int blobsCount, int WhiteNoBlack)
{

	unsigned char* src_ = (unsigned char*)src.data;
	int srcStride = src.step;

	try
	{
		for (int i = 0; i < blobsCount; i++)
		{

			int yy = blobs[i].location.y;
			int xx = blobs[i].location.x;


			int widthBlob = blobs[i].image.cols;
			int heightBlob = blobs[i].image.rows;

			int dstStride = blobs[i].image.step;


			unsigned char* dst_ = (unsigned char*)blobs[i].image.data;


			for (int y = 0; y < heightBlob; y++)
			{
				int dop = srcStride*(y + blobs[i].location.y);
				int bdop = dstStride*y;
				for (int x = 0; x < widthBlob; x++)
				{
					int dopp = dop + (x + blobs[i].location.x) * 3;
					int bdopp = bdop + x * 3;
					if (dst_[bdopp] == 255)
					{
						src_[dopp] = dst_[bdopp];
						src_[dopp + 1] = dst_[bdopp + 1];
						src_[dopp + 2] = dst_[bdopp + 2];
					}

				}

			}

		}
	}
	catch (...)
	{
		int r = 15;
	}

	return src;

}

Mat BlobsBuild_::PutBlobsBlackWhiteCentre(Mat src, Blob_* blobs, int blobsCount, int WhiteNoBlack, Point& p, bool gravy)
{
	unsigned char clr = 255;
	if (WhiteNoBlack == 0)
		clr = 0;
	unsigned char* src_ = (unsigned char*)src.data;
	int srcStride = src.step;
	double kx = 0;
	double ky = 0;
	for (int i = 0; i < blobsCount; i++)
	{

		int yy = blobs[i].location.y;
		int xx = blobs[i].location.x;


		int widthBlob = blobs[i].image.cols;
		int heightBlob = blobs[i].image.rows;

		int dstStride = blobs[i].image.step;


		unsigned char* dst_ = (unsigned char*)blobs[i].image.data;
		
		long counter = 0;
		int l = 0;
		for (int y = 0; y < heightBlob; y++)
		{
			int bdop = dstStride*y;
			for (int x = 0; x < widthBlob; x++)
			{
				int bdopp = bdop + x;
				l= dst_[bdopp];
				if (l > 0)
				{
					kx += x;
					ky += y;
					counter++;
				};

			}

		}
		kx /= counter;
		ky /= counter;
		
		for (int y = 0; y < heightBlob; y++)
		{
			int p=0;
			if (gravy)
				p = y + (src.rows / 2 - ky);
			else
				p = y + (src.rows / 2 - blobs[0].image.rows / 2);
				if (p>src.rows - 1)
					p = src.rows - 1;
				if (p < 0)
					p = 0;


			int dop = srcStride*(p);
			int bdop = dstStride*y;
			for (int x = 0; x < widthBlob; x++)
			{
				int p = 0;
				if (gravy)
					p = x + (src.cols / 2 - kx);
				else
					p = x + (src.cols / 2 - blobs[0].image.cols / 2);
				if (p>src.cols - 1)
					p = src.rows - 1;
				if (p < 0)
					p = 0;
				int dopp = dop + (p);// *3;
				int bdopp = bdop + x;
				if (dst_[bdopp] == clr)
				{
					src_[dopp] = dst_[bdopp];
					/*src_[dopp + 1] = dst_[bdopp];
					src_[dopp + 2] = dst_[bdopp];*/
				}

			}

		}

	}
	if (gravy)
	{
		p.x = (src.cols / 2 - (blobs[0].location.x + kx));
		p.y = (src.rows / 2 - (blobs[0].location.y + ky));
	}
	else
	{
		p.x = (src.cols / 2 - (blobs[0].location.x + blobs[0].image.cols / 2));
		p.y = (src.rows / 2 - (blobs[0].location.y + blobs[0].image.rows / 2));
	}
	return src;

}