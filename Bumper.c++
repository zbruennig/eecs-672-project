// Bumper.c++

#include <iostream>
#include <math.h>

#include "Bumper.h"

typedef float vec3[3];

// index lists for the three faces that can't be drawn with glDrawArrays
GLuint Bumper::indexList[3][4] = {
	{ 6, 7, 0, 1 }, // xmin face
	{ 6, 0, 4, 2 }, // ymin face
	{ 1, 7, 3, 5 }  // ymax face
};

Bumper::Bumper(ShaderIF* sIF, float xy[4][2], float minZ, float maxZ, float color[]) :
	SceneElement(sIF)
{
  xmin = xy[0][0];
  ymin = xy[0][1];
  xmax = xy[0][0];
  ymax = xy[0][1];

  for (int i=1; i<4; i++) {
    float x = xy[i][0];
    float y = xy[i][1];
    xmin = x < xmin ? x : xmin;
    xmax = x > xmax ? x : xmax;
    ymin = y < ymin ? y : ymin;
    ymax = y > ymax ? y : ymax;
  }

  zmin = minZ;
  zmax = maxZ;

	for(int i=0; i<4; i++){
		for(int j=0; j<2; j++){
			xys[i][j] = xy[i][j];
		}
	}

	kd[0] = ka[0] = color[0];
  kd[1] = ka[1] = color[1];
  kd[2] = ka[2] = color[2];

	defineBumper();
}

Bumper::~Bumper()
{
	glDeleteBuffers(3,ebo);
	glDeleteBuffers(1, vbo);
	glDeleteVertexArrays(1, vao);
}

void Bumper::defineBumper()
{
	//carefully diagrammed out to map to the remaining copied code
	vec3 vtx[] = {
		{xys[0][0], xys[0][1], zmax}, {xys[1][0], xys[1][1], zmax},
		{xys[3][0], xys[3][1], zmax}, {xys[2][0], xys[2][1], zmax},
		{xys[3][0], xys[3][1], zmin}, {xys[2][0], xys[2][1], zmin},
		{xys[0][0], xys[0][1], zmin}, {xys[1][0], xys[1][1], zmin}
	};
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);

	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(vec3), vtx, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

	glGenBuffers(3, ebo);
	for (int i=0 ; i<3 ; i++)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), indexList[i], GL_STATIC_DRAW);
	}

	glDisableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Bumper::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

bool Bumper::handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY)
{
	return this->ModelView::handleCommand(anASCIIChar, ldsX, ldsY);
}

void Bumper::renderBumper()
{
	glBindVertexArray(vao[0]);
	glUniform3fv(shaderIF->ppuLoc("kd"), 1, kd);
	glUniform3fv(shaderIF->ppuLoc("ka"), 1, kd); //We will make ka the same as kd

	// Additional computation to calculate the normal vectors
	cryph::AffVector vec1, vec2, cross;

	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 0, 0, 1);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	vec1 = cryph::AffVector(xys[3][0]-xys[2][0], xys[3][1] - xys[2][1], 0);
	vec2 = cryph::AffVector(0, 0, 1);
	cross = vec1.cross(vec2);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), cross.dx, cross.dy, cross.dz);
	glDrawArrays(GL_TRIANGLE_STRIP, 2, 4);


	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 0, 0, -1);
	glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);

	// The three faces that are drawn with glDrawElements
	vec1 = cryph::AffVector(xys[1][0]-xys[0][0], xys[1][1] - xys[0][1], 0);
	vec2 = cryph::AffVector(xys[1][0]-xys[0][0], xys[1][1] - xys[0][1], 1);
	cross = vec1.cross(vec2);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), cross.dx, cross.dy, cross.dz);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);

	vec1 = cryph::AffVector(xys[2][0]-xys[0][0], xys[2][1] - xys[0][1], 0);
	vec2 = cryph::AffVector(0, 0, 1);
	cross = vec1.cross(vec2);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), cross.dx, cross.dy, cross.dz);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);

	vec1 = cryph::AffVector(0, 0, 1);
	vec2 = cryph::AffVector(xys[3][0]-xys[1][0], xys[3][1] - xys[1][1], 0);
	cross = vec1.cross(vec2);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), cross.dx, cross.dy, cross.dz);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[2]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);
}

void Bumper::render()
{
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	glUseProgram(shaderIF->getShaderPgmID());

	cryph::Matrix4x4 mc_ec, ec_lds;
	getMatrices(mc_ec, ec_lds);
	float mat[16];
	glUniformMatrix4fv(shaderIF->ppuLoc("mc_ec"), 1, false, mc_ec.extractColMajor(mat));
	glUniformMatrix4fv(shaderIF->ppuLoc("ec_lds"), 1, false, ec_lds.extractColMajor(mat));

	renderBumper();

	glUseProgram(pgm);
}
