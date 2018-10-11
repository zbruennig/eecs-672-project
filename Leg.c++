// Leg.c++

#include "Leg.h"

Leg::Leg(ShaderIF* sIF, float xc, float yc, float minz, float maxz,
  float upperRadius, float lowerRadius, float color[]) : shaderIF(sIF)
{

  float radius = upperRadius > lowerRadius ? upperRadius : lowerRadius;
  xmin = xc - radius;
  xmax = xc + radius;
  ymin = yc - radius;
  ymax = yc + radius;
  zmin = minz;
  zmax = maxz;

  kd[0] = ka[0] = color[0];
  kd[1] = ka[1] = color[1];
  kd[2] = ka[2] = color[2];

  generateLeg();
}

Leg::~Leg()
{
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Leg::getMCBoundingBox(double* xyzLimits) const
{
  xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void Leg::generateLeg() {

}

void Leg::renderLeg() {

}

void Leg::render()
{
  GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	glUseProgram(shaderIF->getShaderPgmID());

	cryph::Matrix4x4 mc_ec, ec_lds;
	getMatrices(mc_ec, ec_lds);
	float mat[16];
	glUniformMatrix4fv(shaderIF->ppuLoc("mc_ec"), 1, false, mc_ec.extractColMajor(mat));
	glUniformMatrix4fv(shaderIF->ppuLoc("ec_lds"), 1, false, ec_lds.extractColMajor(mat));

	renderLeg();

	glUseProgram(pgm);
}
