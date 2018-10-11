// main.c++: Starter for EECS 672 Projects 2-4

#include "ExtendedController.h"
#include "Block.h"
#include "Sphere.h"
#include "Leg.h"

void createScene(ExtendedController& c, ShaderIF* sIF)
{
	// TODO: Implement this function

	//Define the colors of everything we'll need.
	float table[] = {1,1,1}; //TODO update
	float sides[] = {1,1,1}; //TODO update
	float pockets[] = {0.1,0.1,0.1};
	float pocketSides[] = {106.0/255, 116.0/255, 111.0/255};
	float legs[] = {0.3, 0.3, 0.3};

	float yellow[] = {1.0, 224.0/255, 26.0/255};
	float blue[] = {26.0/255, 88.0/255, 1};
	float red[] = {1, 26.0/255, 43.0/255};
	float purple[] = {181.0/255, 26.0/255, 1};
	float orange[] = {1, 90.0/255, 26.0/255};
	float green[] = {0, 77.0/255, 36.0/255};
	float brown[] = {144.0/255, 36.0/255, 36.0/255};
	float black[] = {0.08,0.08,0.08};
	float cue[] = {233.0/255, 233.0/255, 233.0/255};

	c.addModel(new Block(sIF, 0.0, 0, 0, 3.5, 1.5, 2.5, cue));

	float center[] = {0, 0, 0};
	c.addModel(new Sphere(sIF, center, 10, purple));
	// c.addModel(new Block(sIF, 4, 4, 4, 0.5, 1.5, 2.5, red));
}

void set3DViewingInformation(double overallBB[])
{

	ModelView::setMCRegionOfInterest(overallBB);

	// MC -> EC:

	// Compute/set eye, center, up
	cryph::AffPoint eye(10.0, -5.0, 8.0);

	double x = 0.5*(overallBB[0] + overallBB[1]);
	double y = 0.5*(overallBB[2] + overallBB[3]);
	double z = 0.5*(overallBB[4] + overallBB[5]);
	cryph::AffPoint center(x, y, z);

	cryph::AffVector up = cryph::AffVector::zu;

	ModelView::setEyeCenterUp(eye, center, up);

	// EC -> LDS:

	// Specify the initial projection type desired
	ModelView::setProjection(ORTHOGONAL);

	// Compute/set ecZmin, ecZmax (It is often useful to exaggerate
	// these limits somewhat to prevent unwanted depth clipping.)
	double ecZmin = -1000, ecZmax = 1000;
	ModelView::setECZminZmax(ecZmin, ecZmax);

	// Compute/set ecZpp
	double ecZpp = -100;
	ModelView::setProjectionPlaneZ(ecZpp);
}

int main(int argc, char* argv[])
{
	ExtendedController c("Pool Hall", MVC_USE_DEPTH_BIT);
	c.reportVersions(std::cout);

	ShaderIF* sIF = new ShaderIF("shaders/basic.vsh", "shaders/phong.fsh");

	createScene(c, sIF);

	glClearColor(81.0/255, 0, 0, 1.0);

	double xyz[6];
	c.getOverallMCBoundingBox(xyz);
	std::cout << "Bounding box: " << xyz[0] << " <= x <= " << xyz[1] << '\n';
	std::cout << "              " << xyz[2] << " <= y <= " << xyz[3] << '\n';
	std::cout << "              " << xyz[4] << " <= z <= " << xyz[5] << "\n\n";
	set3DViewingInformation(xyz);

	c.run();

	delete sIF;

	return 0;
}
