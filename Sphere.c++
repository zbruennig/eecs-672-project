// Sphere.c++

#include "Sphere.h"

Sphere::Sphere(ShaderIF* sIF, float center[], float radius, float color[]) : shaderIF(sIF)
{
  xmin = center[0] - radius;
  xmax = center[0] + radius;
  ymin = center[1] - radius;
  ymax = center[1] + radius;
  zmin = center[2] - radius;
  zmax = center[2] + radius;

  kd[0] = ka[0] = color[0];
  kd[1] = ka[1] = color[1];
  kd[2] = ka[2] = color[2];

  generateSphere();
}

Sphere::~Sphere()
{
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Sphere::getMCBoundingBox(double* xyzLimits) const
{
  xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void Sphere::generateSphere() {

}

void Sphere::renderSphere() {

}

void Sphere::render()
{
  GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	glUseProgram(shaderIF->getShaderPgmID());

	cryph::Matrix4x4 mc_ec, ec_lds;
	getMatrices(mc_ec, ec_lds);
	float mat[16];
	glUniformMatrix4fv(shaderIF->ppuLoc("mc_ec"), 1, false, mc_ec.extractColMajor(mat));
	glUniformMatrix4fv(shaderIF->ppuLoc("ec_lds"), 1, false, ec_lds.extractColMajor(mat));

	renderSphere();

	glUseProgram(pgm);
}
