// main.c++: Starter for EECS 672 Projects 2-4

#include "ExtendedController.h"
#include "TEMPLATE_Subclass.h"
#include "Block.h"

void createScene(ExtendedController& c, ShaderIF* sIF)
{
	// TODO: Implement this function
	c.addModel(new Block(sIF, 0.0, 0, 0, 3.5, 1.5, 2.5));
}

void set3DViewingInformation(double overallBB[])
{

	ModelView::setMCRegionOfInterest(overallBB);

	// MC -> EC:

	// Compute/set eye, center, up
	cryph::AffPoint eye(4.0, -3.0, 5.0);

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

	glClearColor(1.0, 1.0, 1.0, 1.0);

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