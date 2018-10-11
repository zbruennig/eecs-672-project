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
	float ka[3], kd[3];

  float xmin, xmax, ymin, ymax, zmin, zmax;

	void generateSphere();
	void renderSphere();
};

#endif
