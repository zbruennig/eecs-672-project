// Sphere.h

#ifndef SPHERE_H
#define SPHERE_H

#include "ModelView.h"
#include "ShaderIF.h"

class Sphere : public ModelView
{
public:
	// As before: you will likely want to add parameters to the constructor
	Sphere(ShaderIF* sIF, float center[], float radius, float color[]);
	virtual ~Sphere();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	ShaderIF* shaderIF;
	GLuint vao[3];
	GLuint sides[2]; // 0: coordinates; 1: normal vectors
	GLuint top[2]; // 0: coordinates; 1: normal vectors
	GLuint bottom[2]; // 0: coordinates; 1: normal vectors
	float ka[3], kd[3];

	const int THETA_POINTS = 32;
	const int PHI_POINTS = 16;
	float x, y, z, r;
  float xmin, xmax, ymin, ymax, zmin, zmax;

	void generateSphere();
	void renderSphere();
};

#endif
