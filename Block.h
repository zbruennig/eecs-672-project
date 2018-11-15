// Block.h - graciously stolen and modified from the MandM sample

#ifndef BLOCK_H
#define BLOCK_H

#include <GL/gl.h>

#include "ModelView.h"
#include "ShaderIF.h"
#include "SceneElement.h"

class Block : public SceneElement
{
public:
	Block(ShaderIF* sIF, float cx, float cy, float cz, // lower left corner
	      float lx, float ly, float lz, float colorIn[], PhongMaterial matl);// lengths in 3 directions
	virtual ~Block();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimits) const;
	bool handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY);
	void render();
	void renderBlock();
private:
	GLuint vao[1];
	GLuint vbo[1];
	GLuint ebo[3];

	// "float" here to match the need to send float to VBO.
	float xmin, xmax, ymin, ymax, zmin, zmax;
	float kd[3];

	PhongMaterial matl;

	static GLuint indexList[3][4];

	void defineBlock();
};

#endif
