// Bumper.h

#ifndef BUMPER_H
#define BUMPER_H

#include <GL/gl.h>

#include "ModelView.h"
#include "ShaderIF.h"
#include "AffVector.h"
#include "SceneElement.h"

class Bumper : public SceneElement
{
public:
	Bumper(ShaderIF* sIF, float xy[4][2], float minZ, float maxZ,
		 PhongMaterial matl);
	virtual ~Bumper();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimits) const;
	bool handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY);
	void render();
	void renderBumper();
private:
	GLuint vao[1];
	GLuint vbo[1];
	GLuint ebo[3];

	// "float" here to match the need to send float to VBO.
  float xys[4][2];
	float xmin, xmax, ymin, ymax, zmin, zmax;

	PhongMaterial matl;

	static GLuint indexList[3][4];

	void defineBumper();
};

#endif
