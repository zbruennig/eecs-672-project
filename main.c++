// main.c++: Starter for EECS 672 Projects 2-4

#include "ExtendedController.h"
#include "Block.h"
#include "Sphere.h"
#include "Leg.h"
#include "Bumper.h"

void createScene(ExtendedController& c, ShaderIF* sIF)
{
	//Define the colors of everything we'll need.
	float table[] = {121.0/255, 91.0/255, 69.0/255};
	float pockets[] = {0.1,0.1,0.1};
	float pocketSides[] = {106.0/255, 116.0/255, 111.0/255};
	float legs[] = {0.3, 0.3, 0.3};
	float playingField[] = {34.0/255, 168.0/255, 52.0/255};
	float bumper[] = {9.0/255, 186.0/255, 26.0/255};

	float yellow[] = {1.0, 224.0/255, 26.0/255};
	float blue[] = {26.0/255, 88.0/255, 1};
	float red[] = {1, 26.0/255, 43.0/255};
	float purple[] = {181.0/255, 26.0/255, 1};
	float orange[] = {1, 90.0/255, 26.0/255};
	float green[] = {0, 77.0/255, 36.0/255};
	float brown[] = {144.0/255, 36.0/255, 36.0/255};
	float black[] = {0.08,0.08,0.08};
	float cue[] = {233.0/255, 233.0/255, 233.0/255};

	c.addModel(new Block(sIF, 0, 0, -0.5, 262, 135, 1, playingField)); //playing area
	c.addModel(new Block(sIF, 0, 0, -5.5, 262, 135, 9, table)); //underneath
	c.addModel(new Block(sIF, -136, 0, -3, 10, 119, 14, table)); //left side
	c.addModel(new Block(sIF, 136, 0, -3, 10, 119, 14, table)); //right side
	c.addModel(new Block(sIF, -64, 72.5, -3, 118, 10, 14, table)); //up left
	c.addModel(new Block(sIF, 64, 72.5, -3, 118, 10, 14, table)); //up right
	c.addModel(new Block(sIF, -64, -72.5, -3, 118, 10, 14, table)); //down left
	c.addModel(new Block(sIF, 64, -72.5, -3, 118, 10, 14, table)); //down right

	//Pool balls
	float position[3] = {-100, -30, 3.175};
	c.addModel(new Sphere(sIF, position, 3.175, cue)); //cue ball
	position[0] = 60; position[1] = 0;
	c.addModel(new Sphere(sIF, position, 3.175, yellow)); //1 ball
	position[0] = 65.499; position[1] = -3.175;
	c.addModel(new Sphere(sIF, position, 3.175, blue)); //2 ball
	position[1] = 3.175;
	c.addModel(new Sphere(sIF, position, 3.175, red)); //3 ball
	position[0] = 70.999; position[1] = -6.35;
	c.addModel(new Sphere(sIF, position, 3.175, purple)); //4 ball
	position[1] = 6.35;
	c.addModel(new Sphere(sIF, position, 3.175, orange)); //5 ball
	position[0] = 76.498; position[1] = -3.175;
	c.addModel(new Sphere(sIF, position, 3.175, green)); //6 ball
	position[1] = 3.175;
	c.addModel(new Sphere(sIF, position, 3.175, brown)); //7 ball
	position[0] = 81.997; position[1] = 0;
	c.addModel(new Sphere(sIF, position, 3.175, black)); //8 ball
	position[0] = 70.999;
	c.addModel(new Sphere(sIF, position, 3.175, yellow)); //9 ball

	float points[4][2] = { {127,55.5}, {131,59.5}, {131,-59.5}, {127,-55.5} }; //right bumper
	c.addModel(new Bumper(sIF, points, 0, 4, bumper));

	for(int i=0; i<4; i++){
		points[i][0] *= -1;
	}
	c.addModel(new Bumper(sIF, points, 0, 4, bumper)); //left bumper

	//top and bottom bumpers
	float points2[4][2] = { {-123, 67.5}, {-5, 67.5}, {-9, 63.5}, {-119, 63.5} };
	c.addModel(new Bumper(sIF, points2, 0, 4, bumper));
	for(int i=0; i<4; i++){
		points2[i][0] *= -1;
	}
	c.addModel(new Bumper(sIF, points2, 0, 4, bumper));
	for(int i=0; i<4; i++){
		points2[i][1] *= -1;
	}
	c.addModel(new Bumper(sIF, points2, 0, 4, bumper));
	for(int i=0; i<4; i++){
		points2[i][0] *= -1;
	}
	c.addModel(new Bumper(sIF, points2, 0, 4, bumper));

	//Legs of the table
	c.addModel(new Leg(sIF, -92, -53.5, -10, -60, 8, 12, legs));
	c.addModel(new Leg(sIF, 92, -53.5, -10, -60, 8, 12, legs));
	c.addModel(new Leg(sIF, -92, 53.5, -10, -60, 8, 12, legs));
	c.addModel(new Leg(sIF, 92, 53.5, -10, -60, 8, 12, legs));
	//bridge connecting the legs
	c.addModel(new Block(sIF, -92, 0, -18, 6, 100, 16, legs));
	c.addModel(new Block(sIF, 92, 0, -18, 6, 100, 16, legs));

	//pockets and pocketSides
	c.addModel(new Leg(sIF, 0, 72.5, -8, 0, 5, 5, pockets));
	c.addModel(new Block(sIF, 0, 72.5, -9, 10, 10, 2, pocketSides));
	c.addModel(new Block(sIF, 0, 78.5, -3, 14, 2, 14, pocketSides));

	c.addModel(new Leg(sIF, 0, -72.5, -8, 0, 5, 5, pockets));
	c.addModel(new Block(sIF, 0, -72.5, -9, 10, 10, 2, pocketSides));
	c.addModel(new Block(sIF, 0, -78.5, -3, 14, 2, 14, pocketSides));

	c.addModel(new Leg(sIF, -135, 70.5, -8, 0, 5, 5, pockets));
	c.addModel(new Leg(sIF, 135, 70.5, -8, 0, 5, 5, pockets));

	c.addModel(new Leg(sIF, -135, -70.5, -8, 0, 5, 5, pockets));
	c.addModel(new Leg(sIF, 135, -70.5, -8, 0, 5, 5, pockets));

	c.addModel(new Block(sIF, -136, -68.5, -9, 10, 18, 2, pocketSides));
	c.addModel(new Block(sIF, -127, -72.5, -9, 8, 10, 2, pocketSides));
	c.addModel(new Block(sIF, -140.5, -68.5, -2, 1, 18, 12, pocketSides));
	c.addModel(new Block(sIF, -132, -77, -2, 18, 1, 12, pocketSides));
	c.addModel(new Block(sIF, -136, -62.5, -4, 10, 6, 8, pocketSides));
	c.addModel(new Block(sIF, -126, -72.5, -4, 8, 10, 8, pocketSides));

	c.addModel(new Block(sIF, 136, -68.5, -9, 10, 18, 2, pocketSides));
	c.addModel(new Block(sIF, 127, -72.5, -9, 8, 10, 2, pocketSides));
	c.addModel(new Block(sIF, 140.5, -68.5, -2, 1, 18, 12, pocketSides));
	c.addModel(new Block(sIF, 132, -77, -2, 18, 1, 12, pocketSides));
	c.addModel(new Block(sIF, 136, -62.5, -4, 10, 6, 8, pocketSides));
	c.addModel(new Block(sIF, 126, -72.5, -4, 8, 10, 8, pocketSides));

	c.addModel(new Block(sIF, -136, 68.5, -9, 10, 18, 2, pocketSides));
	c.addModel(new Block(sIF, -127, 72.5, -9, 8, 10, 2, pocketSides));
	c.addModel(new Block(sIF, -140.5, 68.5, -2, 1, 18, 12, pocketSides));
	c.addModel(new Block(sIF, -132, 77, -2, 18, 1, 12, pocketSides));
	c.addModel(new Block(sIF, -136, 62.5, -4, 10, 6, 8, pocketSides));
	c.addModel(new Block(sIF, -126, 72.5, -4, 8, 10, 8, pocketSides));

	c.addModel(new Block(sIF, 136, 68.5, -9, 10, 18, 2, pocketSides));
	c.addModel(new Block(sIF, 127, 72.5, -9, 8, 10, 2, pocketSides));
	c.addModel(new Block(sIF, 140.5, 68.5, -2, 1, 18, 12, pocketSides));
	c.addModel(new Block(sIF, 132, 77, -2, 18, 1, 12, pocketSides));
	c.addModel(new Block(sIF, 136, 62.5, -4, 10, 6, 8, pocketSides));
	c.addModel(new Block(sIF, 126, 72.5, -4, 8, 10, 8, pocketSides));
}

void set3DViewingInformation(double overallBB[])
{

	ModelView::setMCRegionOfInterest(overallBB);

	// MC -> EC:

	// Compute/set eye, center, up
	cryph::AffPoint eye(0, -10, 10);

	double x = 0.5*(overallBB[0] + overallBB[1]);
	double y = 0.5*(overallBB[2] + overallBB[3]);
	double z = 0.5*(overallBB[4] + overallBB[5]);
	cryph::AffPoint center(x, y, z);

	cryph::AffVector up = cryph::AffVector::zu;

	ModelView::setEyeCenterUp(eye, center, up);

	// EC -> LDS:

	// Specify the initial projection type desired
	ModelView::setProjection(ORTHOGONAL);


	double radius = overallBB[1]-overallBB[0];

	// Compute/set ecZmin, ecZmax (It is often useful to exaggerate
	// these limits somewhat to prevent unwanted depth clipping.)
	double ecZmin = radius*-50, ecZmax = radius*50;
	ModelView::setECZminZmax(ecZmin, ecZmax);

	// Compute/set ecZpp
	double ecZpp = radius*-0.1;
	ModelView::setProjectionPlaneZ(ecZpp);
}

int main(int argc, char* argv[])
{
	ExtendedController c("Pool Hall", MVC_USE_DEPTH_BIT);
	c.reportVersions(std::cout);

	ShaderIF* sIF = new ShaderIF("shaders/basic.vsh", "shaders/phong.fsh");

	createScene(c, sIF);

	glClearColor(.2, .0, .0, 1.0);

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
