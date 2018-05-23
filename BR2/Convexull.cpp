#include "Convexull.h"


Convexull_::Convexull_()
{
}


Convexull_::~Convexull_()
{
}

Point2* Convexull_::convexhull(Point2* pts, long& count)
{
	//return pts;
	long N = count;
	if (N <= 1)
		return pts;
	Multysort::Quicksort(pts, count);
	Point2 left = pts[0];
	Point2 right = pts[N - 1];

	SDLL* lower = new SDLL(left);
	SDLL* upper = new SDLL(left);
	for (long i = 0; i < N; i++)
	{
		double det = Point2::Area2(left, right, pts[i]);
		if (det > 0)
			upper = upper->Append(new SDLL(pts[i]));
		else if (det < 0)
			lower = lower->Prepend(new SDLL(pts[i]));
	}
	lower = lower->Prepend(new SDLL(right));
	upper = upper->Append(new SDLL(right))->Next();

	eliminate(lower);
	eliminate(upper);

	if (lower->prev->val.Equals(upper->val))
		lower->prev->Delete_();
	if (upper->prev->val.Equals(lower->val))
		upper->prev->Delete_();

	count = lower->Size() + upper->Size();
	Point2* res = new Point2[count];
	lower->CopyInto(res, 0);
	upper->CopyInto(res, lower->Size());
	
	return res;
}

Point* Convexull_::Point2ToPoint(Point2* point, int count)
{
	
	int new_count = 0;
	for (int i = 0; i < count; i++)
	{
		if (point[i].x > 0.5 && point[i].y > 0.5)
		{
			new_count++;
		}
	}
	Point* ret = new Point[new_count];
	new_count = 0;
	for (int i = 0; i < count; i++)
	{
		if (point[i].x > 0.5 && point[i].y > 0.5)
		{
			int x = point[i].x;
			int y = point[i].y;
			
			ret[new_count].x = point[i].x;
			ret[new_count++].y = point[i].y;
			int p = i;
		}
	}
	count = new_count;
	//delete[] point;
	return ret;


}
void Convexull_::eliminate(SDLL* start)
{
	SDLL* v = start;
	SDLL* w = start->Prev();
	bool fwd = false;
	while (v->Next() != start || !fwd)
	{
		if (v->Next() == w)
			fwd = true;
		if (Point2::Area2(v->val, v->Next()->val, v->Next()->Next()->val) < 0)
			v = v->Next();
		else
		{
			v->Next()->Delete_();
			v = v->Prev();
		}
	}
}
