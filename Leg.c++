// Leg.c++

#include "Leg.h"

typedef float vec3[3];

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

  upper = upperRadius;
  lower = lowerRadius;
  x = xc;
  y = yc;

  kd[0] = ka[0] = color[0];
  kd[1] = ka[1] = color[1];
  kd[2] = ka[2] = color[2];

  generateLeg();
}

Leg::~Leg()
{
  glDeleteBuffers(2, sides);
  glDeleteBuffers(2, top);
  glDeleteBuffers(2, bottom);
  glDeleteVertexArrays(3, vao);
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
  int nPoints = 2*(POINTS_AROUND_SLICE + 1);
  vec3* coords = new vec3[nPoints];
  vec3* normals = new vec3[nPoints];
  float theta = 0.0;
  float dTheta = 2*M_PI/POINTS_AROUND_SLICE;

  for (int i=0; i<=POINTS_AROUND_SLICE; i++) {
    coords[2*i][0] = x + upper * cos(theta);
    coords[2*i][1] = y + upper * sin(theta);
    coords[2*i][2] = zmax;
    coords[2*i + 1][0] = x + lower * cos(theta);
    coords[2*i + 1][1] = y + lower * sin(theta);
    coords[2*i + 1][2] = zmin;

    //I spent almost an hour on a whiteboard figuring out this next part.
    float height = zmax - zmin;
    float length = lower - upper;
    float phi = atan(length/height);
    normals[2*i][0] = normals[2*i+1][0] = cos(theta)*cos(phi);
    normals[2*i][1] = normals[2*i+1][1] = sin(theta)*cos(phi);
    normals[2*i][2] = normals[2*i+1][2] = sin(phi);
    theta += dTheta;
  }

  glGenVertexArrays(3, vao);
  glBindVertexArray(vao[0]);

  glGenBuffers(2, sides);

  glBindBuffer(GL_ARRAY_BUFFER, sides[0]);
  glBufferData(GL_ARRAY_BUFFER, nPoints*sizeof(vec3), coords, GL_STATIC_DRAW);
  glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

  glBindBuffer(GL_ARRAY_BUFFER, sides[1]);
  glBufferData(GL_ARRAY_BUFFER, nPoints*sizeof(vec3), normals, GL_STATIC_DRAW);
  glVertexAttribPointer(shaderIF->pvaLoc("mcNormal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));

  delete[] coords;
  delete[] normals;

  //GENERATE THE TOP CIRCLE

  nPoints = POINTS_AROUND_SLICE + 2; //duplicate and center of circle
  coords = new vec3[nPoints];
  normals = new vec3[nPoints];
  coords[0][0] = x;
  coords[0][1] = y;
  coords[0][2] = zmax;
  normals[0][0] = normals[0][1] = 0;
  normals[0][2] = 1;

  for (int i=1; i<nPoints; i++) {
    coords[i][0] = x + upper * cos(theta);
    coords[i][1] = y + upper * sin(theta);
    coords[i][2] = zmax;
    normals[i][0] = normals[i][1] = 0;
    normals[i][2] = 1;
    theta += dTheta;
  }

  glBindVertexArray(vao[1]);

  glGenBuffers(2, top);

  glBindBuffer(GL_ARRAY_BUFFER, top[0]);
  glBufferData(GL_ARRAY_BUFFER, nPoints*sizeof(vec3), coords, GL_STATIC_DRAW);
  glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

  glBindBuffer(GL_ARRAY_BUFFER, top[1]);
  glBufferData(GL_ARRAY_BUFFER, nPoints*sizeof(vec3), normals, GL_STATIC_DRAW);
  glVertexAttribPointer(shaderIF->pvaLoc("mcNormal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));

  delete[] coords;
  delete[] normals;

  //GENERATE THE BOTTOM CIRCLE

  coords = new vec3[nPoints];
  normals = new vec3[nPoints];
  coords[0][0] = x;
  coords[0][1] = y;
  coords[0][2] = zmin;
  normals[0][0] = normals[0][1] = 0;
  normals[0][2] = -1;

  for (int i=1; i<nPoints; i++) {
    coords[i][0] = x + lower * cos(theta);
    coords[i][1] = y + lower * sin(theta);
    coords[i][2] = zmin;
    normals[i][0] = normals[i][1] = 0;
    normals[i][2] = -1;
    theta += dTheta;
  }

  glBindVertexArray(vao[2]);

  glGenBuffers(2, bottom);

  glBindBuffer(GL_ARRAY_BUFFER, bottom[0]);
  glBufferData(GL_ARRAY_BUFFER, nPoints*sizeof(vec3), coords, GL_STATIC_DRAW);
  glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

  glBindBuffer(GL_ARRAY_BUFFER, bottom[1]);
  glBufferData(GL_ARRAY_BUFFER, nPoints*sizeof(vec3), normals, GL_STATIC_DRAW);
  glVertexAttribPointer(shaderIF->pvaLoc("mcNormal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));

  delete[] coords;
  delete[] normals;

}

void Leg::renderLeg() {
  glBindVertexArray(vao[0]);
  glUniform3fv(shaderIF->ppuLoc("kd"), 1, kd);
  glUniform3fv(shaderIF->ppuLoc("ka"), 1, kd); //We will make ka the same as kd
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 2*(POINTS_AROUND_SLICE+1));

  glBindVertexArray(vao[1]);
  glUniform3fv(shaderIF->ppuLoc("kd"), 1, kd);
  glUniform3fv(shaderIF->ppuLoc("ka"), 1, kd);
	glDrawArrays(GL_TRIANGLE_FAN, 0, (POINTS_AROUND_SLICE+2));

  glBindVertexArray(vao[2]);
  glUniform3fv(shaderIF->ppuLoc("kd"), 1, kd);
  glUniform3fv(shaderIF->ppuLoc("ka"), 1, kd);
	glDrawArrays(GL_TRIANGLE_FAN, 0, (POINTS_AROUND_SLICE+2));
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
