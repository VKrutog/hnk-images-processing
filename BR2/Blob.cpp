#include "Blob.h"
#include "morfology.h"


Blob_::Blob_(Point location, bool WithMorpho, bool WhiteNoBlack) 
{
	//image = image;
	location = location;
	perimetr = 0;
	area = 0;
	roundness = 0.0;
	elongation = 0.0;
	xC = 0;
	yC = 0;
	rmax = 0.0;
	rmin = 0.0;
	compactness = 0.0;
	whiteNoBlack = WhiteNoBlack;

	if (WithMorpho)
	{
		//morfology.GetPerimeterArea(this);
		//morfology_::CalcPerimeterAreaRight(this, image);
		//this.elongation=morfology.CalcElongation( morfology.CalcMomemts(this));
		//morfology::CalcRadiusRoundnessElongation(this);
		/*roughnessB=*///morfology.CalcRoughnessB(this, this.whiteNoBlack, degreeRoughnessB);
		//this.convexity = morfology.CalcConvexity(this);

	}
}

//Blob_::Blob_(Mat* image, Point location, bool WithMorpho, bool WhiteNoBlack)
//{
//	this->image = (*image).clone();
//	this->location = location;
//	this->perimetr = 0;
//	this->area = 0;
//	this->roundness = 0.0;
//	this->elongation = 0.0;
//	this->xC = 0;
//	this->yC = 0;
//	this->rmax = 0.0;
//	this->rmin = 0.0;
//	this->compactness = 0.0;
//	this->whiteNoBlack = WhiteNoBlack;
//
//	if (WithMorpho)
//	{
//		//morfology.GetPerimeterArea(this);
//		morfology_::CalcPerimeterAreaRight(this);
//		//this.elongation=morfology.CalcElongation( morfology.CalcMomemts(this));
//		//morfology::CalcRadiusRoundnessElongation(this);
//		/*roughnessB=*///morfology.CalcRoughnessB(this, this.whiteNoBlack, degreeRoughnessB);
//		//this.convexity = morfology.CalcConvexity(this);
//
//	}
//}

void Blob_::SetBlob( Point location, bool WithMorpho, bool WhiteNoBlack)
{
	//image = image;
	location = location;
	//this->owner = owner;
	perimetr = 0;
	area = 0;
	roundness = 0.0;
	elongation = 0.0;
	xC = 0;
	yC = 0;
	rmax = 0.0;
	rmin = 0.0;
	compactness = 0.0;
	whiteNoBlack = WhiteNoBlack;
	if (WithMorpho)
	{
		//morfology.GetPerimeterArea(this);
		morfology_::CalcPerimeterAreaRight(this,image);
		//this.elongation=morfology.CalcElongation( morfology.CalcMomemts(this));
		//morfology.CalcRadiusRoundnessElongation(this);
		/*roughnessB=*///morfology.CalcRoughnessB(this, this.whiteNoBlack, degreeRoughnessB);
		//this.convexity = morfology.CalcConvexity(this);

	}
}


Blob_::Blob_(Mat _image, Point location, bool WithMorpho, bool WhiteNoBlack)
{
	image = _image;
	location = location;
	//this->owner = owner;
	perimetr = 0;
	area = 0;
	roundness = 0.0;
	elongation = 0.0;
	xC = 0;
	yC = 0;
	rmax = 0.0;
	rmin = 0.0;
	compactness = 0.0;
	whiteNoBlack = WhiteNoBlack;
	if (WithMorpho)
	{
		//morfology.GetPerimeterArea(this);
		morfology_::CalcPerimeterAreaRight(this, image);
		//this.elongation=morfology.CalcElongation( morfology.CalcMomemts(this));
		//morfology.CalcRadiusRoundnessElongation(this);
		/*roughnessB=*///morfology.CalcRoughnessB(this, this.whiteNoBlack, degreeRoughnessB);
		//this.convexity = morfology.CalcConvexity(this);

	}
}

Blob_::Blob_(Point location, Mat owner, bool WithMorpho, bool WhiteNoBlack)
{
	//image = image;
	location = location;
	owner = owner;
	perimetr = 0;
	area = 0;
	roundness = 0.0;
	elongation = 0.0;
	xC = 0;
	yC = 0;
	rmax = 0.0;
	rmin = 0.0;
	compactness = 0.0;
	whiteNoBlack = WhiteNoBlack;
	if (WithMorpho)
	{
		//morfology.GetPerimeterArea(this);
		//morfology_::CalcPerimeterAreaRight(this,image);
		//this.elongation=morfology.CalcElongation( morfology.CalcMomemts(this));
		//morfology.CalcRadiusRoundnessElongation(this);
		/*roughnessB=*///morfology.CalcRoughnessB(this, this.whiteNoBlack, degreeRoughnessB);
		//this.convexity = morfology.CalcConvexity(this);

	}
}

Blob_::~Blob_()
{
	/*if (this->image)
		delete this->image;*/
	image.release();
	src.release();

}
