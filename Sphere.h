// Sphere.h

#ifndef SPHERE_H
#define SPHERE_H

#include "ModelView.h"
#include "ShaderIF.h"

typedef float vec3[3];

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

	static const int THETA_POINTS = 32;
	static const int PHI_POINTS = 16;

	GLuint vao[3];
	GLuint sides[2]; // 0: coordinates; 1: normal vectors
	GLuint top[2]; // 0: coordinates; 1: normal vectors
	GLuint bottom[2]; // 0: coordinates; 1: normal vectors
	GLuint ebo[THETA_POINTS*(PHI_POINTS-2)];
	float ka[3], kd[3];

	vec3** c = nullptr;
	vec3** n = nullptr;
	GLuint vertices[PHI_POINTS-2][THETA_POINTS][4];

	float x, y, z, r;
  float xmin, xmax, ymin, ymax, zmin, zmax;

	void generateSphere();
	void renderSphere();
};

#endif
