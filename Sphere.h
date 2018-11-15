// Sphere.h

#ifndef SPHERE_H
#define SPHERE_H

#include "SceneElement.h"
#include "ShaderIF.h"

typedef float vec3[3];

class Sphere : public SceneElement
{
public:
	// As before: you will likely want to add parameters to the constructor
	Sphere(ShaderIF* sIF, float center[], float radius, PhongMaterial matl);
	virtual ~Sphere();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	static const int THETA_POINTS = 32;
	static const int PHI_POINTS = 16;

	GLuint vao[3];
	GLuint sides[2]; // 0: coordinates; 1: normal vectors
	GLuint top[2]; // 0: coordinates; 1: normal vectors
	GLuint bottom[2]; // 0: coordinates; 1: normal vectors
	GLuint ebo[THETA_POINTS*(PHI_POINTS-2)];

	vec3** c = nullptr;
	vec3** n = nullptr;
	GLuint vertices[PHI_POINTS-2][THETA_POINTS][4];

	float x, y, z, r;
  float xmin, xmax, ymin, ymax, zmin, zmax;

	PhongMaterial matl;

	void generateSphere();
	void renderSphere();
};

#endif
