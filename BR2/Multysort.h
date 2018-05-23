#pragma once
#include "Point2.h"
class Multysort
{
public:
	Multysort();
	~Multysort();
	static void swap(Point2* arr, int s, int t)
	{
		Point2 tmp = arr[s]; arr[s] = arr[t]; arr[t] = tmp;
	}
	

	static void qsort(Point2* arr, int a, int b)
	{

		if (a < b)
		{
			int i = a, j = b;
			Point2 x = (Point2)(arr[(i + j) / 2]);
			do
			{
				while (arr[i].Less(x)) i++;
				while (x.Less(arr[j])) j--;
				if (i <= j)
				{
					swap(arr, i, j);
					i++; j--;
				}
			} while (i <= j);
			qsort(arr, a, j);
			qsort(arr, i, b);
		}
	}

	static void Quicksort(Point2* arr, int Lenght)
	{
		qsort(arr, 0, Lenght - 1);
	}
};




