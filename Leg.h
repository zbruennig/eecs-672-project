// Leg.h

#ifndef LEG_H
#define LEG_H

#include "ModelView.h"
#include "ShaderIF.h"

class Leg : public ModelView
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
	ShaderIF* shaderIF;
	float ka[3], kd[3];

  float xmin, xmax, ymin, ymax, zmin, zmax;

	void generateLeg();
	void renderLeg();
};

#endif
