#include "SDLL.h"


SDLL::SDLL()
{
}


SDLL::~SDLL()
{
}

SDLL::SDLL(Point2 _val)
{
	val = _val; 
	next = prev = this;
}

SDLL* SDLL::Prev()
{
	return prev;
}

SDLL* SDLL::Next()
{
	return next;
}


void SDLL::Delete_()
{
	next->prev = prev; prev->next = next;
	next = prev = nullptr;
}

SDLL* SDLL::Prepend(SDLL* elt)
{
	elt->next = this; elt->prev = prev; prev->next = elt; prev = elt;
	return elt;
}

SDLL* SDLL::Append(SDLL* elt)
{
	elt->prev = this; elt->next = next; next->prev = elt; next = elt;
	return elt;
}
int SDLL::Size()
{
	int count = 0;
	SDLL* node = this;
	do
	{
		count++;
		node = node->next;
	} while (node != this);
	return count;
}

void SDLL::CopyInto(Point2* vals, int i)
{
	SDLL* node = this;
	do
	{
		vals[i++] = node->val;
		node = node->next;
	} while (node != this);
}
	
