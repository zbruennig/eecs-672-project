// main.c++: Starter for EECS 672 Projects 2-4

#include "ExtendedController.h"
#include "Block.h"
#include "Sphere.h"
#include "Leg.h"
#include "Bumper.h"
#include "TableMaterial.h"

void createScene(ExtendedController& c, ShaderIF* sIF)
{
	//Define the material properties of everything we'll need.
	PhongMaterial playingField(34.0/255, 168.0/255, 52.0/255, 0.25,0.25,0,1,0);
	PhongMaterial table(121.0/255, 91.0/255, 69.0/255, 0.25,0.25,0,1,0);
	PhongMaterial tableTranslucent(121.0/255, 91.0/255, 69.0/255, 0.25,0.25,0,1,.5);
	PhongMaterial pockets(0.1,0.1,0.1, .25,.25,0,1,0);
	PhongMaterial pocketSides(106.0/255, 116.0/255, 111.0/255, 0.25,0.25,0,1,0);
	PhongMaterial legs(0.3, 0.3, 0.3, 0.25,0.25,0,1,0);
	PhongMaterial bumper(9.0/255, 186.0/255, 26.0/255, 0.25,0.25,0,1,0);

	PhongMaterial yellow(1.0, 224.0/255, 26.0/255, 0.25,0.25,0.,1,0);
	PhongMaterial blue(13.0/255, 44.0/255, 0.5, 0.25,0.25,0,1,0);
	PhongMaterial lightblue(26.0/255, 88.0/255, 1, 0.25,0.25,0,1,0);
	PhongMaterial red(1, 26.0/255, 43.0/255, 0.25,0.25,0,1,0);
	PhongMaterial purple(181.0/255, 26.0/255, 1, 0.25,0.25,0,1,0);
	PhongMaterial orange(1, 90.0/255, 26.0/255, 0.25,0.25,0,1,0);
	PhongMaterial green(0, 77.0/255, 36.0/255, 0.25,0.25,0,1,0);
	PhongMaterial brown(144.0/255, 36.0/255, 36.0/255, 0.25,0.25,0,1,0);
	PhongMaterial black(0.08,0.08,0.08, 0.25,0.25,0,1,0);
	PhongMaterial cue(233.0/255, 233.0/255, 233.0/255, 0.25,0.25,0,1,0);

	c.addModel(new TableMaterial(sIF, 0, 0, -0.5, 262, 135, 1, "./textures/felt2.jpg", playingField)); //playing area
	c.addModel(new TableMaterial(sIF, 0, 0, -5.5, 262, 135, 9, "./textures/wood.jpg", table)); //underneath //table
	c.addModel(new TableMaterial(sIF, -136, 0, -3, 10, 119, 14, "./textures/wood.jpg", table)); //left side
	c.addModel(new TableMaterial(sIF, 136, 0, -3, 10, 119, 14, "./textures/wood.jpg", table)); //right side
	c.addModel(new TableMaterial(sIF, -64, 72.5, -3, 118, 10, 14, "./textures/wood.jpg", table)); //up left
	c.addModel(new TableMaterial(sIF, 64, 72.5, -3, 118, 10, 14, "./textures/wood.jpg", table)); //up right
	c.addModel(new TableMaterial(sIF, -64, -72.5, -3, 118, 10, 14, "./textures/wood.jpg", table)); //down left
	c.addModel(new TableMaterial(sIF, 64, -72.5, -3, 118, 10, 14, "./textures/wood.jpg", table)); //down right

	//Pool chalk
	c.addModel(new Block(sIF, 30, 72, 5, 2, 2, 2, lightblue));
	c.addModel(new Block(sIF, -50, -74.5, 5, 2, 2, 2, lightblue));
	c.addModel(new Block(sIF, 133, -10, 5, 2, 2, 2, lightblue));

	// Pool balls
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

	// Legs of the table
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

	double x = 0.5*(overallBB[0] + overallBB[1]);
	double y = 0.5*(overallBB[2] + overallBB[3]);
	double z = 0.5*(overallBB[4] + overallBB[5]);
	cryph::AffPoint eye(x, y-50, z+100);
	cryph::AffPoint center(x, y, z);

	cryph::AffVector up = cryph::AffVector::yu;

	ModelView::setEyeCenterUp(eye, center, up);

	// EC -> LDS:

	// Specify the initial projection type desired
	ModelView::setProjection(ORTHOGONAL);


	double radius = overallBB[1]-overallBB[0];

	// Compute/set ecZmin, ecZmax (It is often useful to exaggerate
	// these limits somewhat to prevent unwanted depth clipping.)
	double ecZmin = -100000, ecZmax = 1000;
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
