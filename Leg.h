// Leg.h

#ifndef LEG_H
#define LEG_H

#include "ModelView.h"
#include "ShaderIF.h"
#include "SceneElement.h"

class Leg : public SceneElement
{
public:
	// As before: you will likely want to add parameters to the constructor
	Leg(ShaderIF* sIF, float xc, float yc, float minz, float maxz,
    float upperRadius, float lowerRadius, float color[]);
	virtual ~Leg();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	GLuint vao[3];
	GLuint sides[2]; // 0: coordinates; 1: normal vectors
	GLuint top[2]; // 0: coordinates; 1: normal vectors
	GLuint bottom[2]; // 0: coordinates; 1: normal vectors
	float ka[3], kd[3];

	const int POINTS_AROUND_SLICE = 72;
	float upper, lower, x, y;

  float xmin, xmax, ymin, ymax, zmin, zmax;

	void generateLeg();
	void renderLeg();
};

#endif
