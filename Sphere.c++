// Sphere.c++

#include "Sphere.h"

typedef float vec3[3];

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

  x = center[0];
  y = center[1];
  z = center[2];
  r = radius;

  generateSphere();
}

Sphere::~Sphere()
{
  glDeleteBuffers(2, sides);
  glDeleteBuffers(2, top);
  glDeleteBuffers(2, bottom);
  glDeleteVertexArrays(3, vao);
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

  //GENERATE THE TOP (with fan)

  vec3* coords = new vec3[THETA_POINTS+2];
  vec3* normals = new vec3[THETA_POINTS+2];
  float theta = 0.0;
  float dTheta = 2*M_PI/THETA_POINTS;
  float phi = 0.0;
  float dPhi = M_PI/PHI_POINTS;

  coords[0][0] = x;
  coords[0][1] = y;
  coords[0][2] = z+r;
  normals[0][0] = 0;
  normals[0][1] = 0;
  normals[0][2] = 1;

  phi+=dPhi;
  for (int i=1; i<=THETA_POINTS+1; i++) {
    //Spherical coordinates - we'll use them a bunch
    coords[i][0] = x + r*cos(theta)*sin(phi);
    coords[i][1] = y + r*sin(theta)*sin(phi);
    coords[i][2] = z + r*cos(phi);
    normals[i][0] = cos(theta)*sin(phi);
    normals[i][1] = sin(theta)*sin(phi);
    normals[i][2] = cos(phi);
    theta += dTheta;
  }

  glGenVertexArrays(3, vao);

  glBindVertexArray(vao[0]);
  glGenBuffers(2, top);

  glBindBuffer(GL_ARRAY_BUFFER, top[0]);
  glBufferData(GL_ARRAY_BUFFER, (THETA_POINTS+2)*sizeof(vec3), coords, GL_STATIC_DRAW);
  glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

  glBindBuffer(GL_ARRAY_BUFFER, top[1]);
  glBufferData(GL_ARRAY_BUFFER, (THETA_POINTS+2)*sizeof(vec3), normals, GL_STATIC_DRAW);
  glVertexAttribPointer(shaderIF->pvaLoc("mcNormal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));

  delete[] coords;
  delete[] normals;

  //GENERATE THE BOTTOM (with fan)

  theta = 0;
  phi = dPhi - M_PI;
  coords = new vec3[THETA_POINTS+2];
  normals = new vec3[THETA_POINTS+2];

  coords[0][0] = x;
  coords[0][1] = y;
  coords[0][2] = z-r;
  normals[0][0] = 0;
  normals[0][1] = 0;
  normals[0][2] = -1;
  for (int i=1; i<=THETA_POINTS+1; i++) { // exact same for loop as above
    coords[i][0] = x + r*cos(theta)*sin(phi);
    coords[i][1] = y + r*sin(theta)*sin(phi);
    coords[i][2] = z + r*cos(phi);
    normals[i][0] = cos(theta)*sin(phi);
    normals[i][1] = sin(theta)*sin(phi);
    normals[i][2] = cos(phi);
    theta += dTheta;
  }

  glBindVertexArray(vao[1]);
  glGenBuffers(2, bottom);

  glBindBuffer(GL_ARRAY_BUFFER, bottom[0]);
  glBufferData(GL_ARRAY_BUFFER, (THETA_POINTS+2)*sizeof(vec3), coords, GL_STATIC_DRAW);
  glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

  glBindBuffer(GL_ARRAY_BUFFER, bottom[1]);
  glBufferData(GL_ARRAY_BUFFER, (THETA_POINTS+2)*sizeof(vec3), normals, GL_STATIC_DRAW);
  glVertexAttribPointer(shaderIF->pvaLoc("mcNormal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));

  delete[] coords;
  delete[] normals;

  // Generate the remaining sides (using strip)

  theta = 0.0;
  phi = dPhi; //start here instead of the top since we already generated it

  vec3** c = new vec3*[PHI_POINTS-1];
  vec3** n = new vec3*[PHI_POINTS-1];
  for (int i=0; i<PHI_POINTS-1; i++) {
    c[i] = new vec3[THETA_POINTS];
    n[i] = new vec3[THETA_POINTS];
  }

  // for each circle of points on each level of phi, generate their coordinates
  // and normal vectors procedurally. Just work your way down the sphere
  for(int i=0; i<PHI_POINTS-1; i++){
    for(int j=0; j<THETA_POINTS; j++){
      c[i][j][0] = x + r*cos(theta)*sin(phi);
      c[i][j][1] = y + r*sin(theta)*sin(phi);
      c[i][j][2] = y + r*cos(phi);
      n[i][j][0] = cos(theta)*sin(phi);
      n[i][j][1] = sin(theta)*sin(phi);
      n[i][j][2] = cos(phi);
      theta+=dTheta;
    }
    phi += dPhi;
  }

  std::cout << c[PHI_POINTS-2][THETA_POINTS-1][0] << '\n';
  std::cout << c[PHI_POINTS-2][THETA_POINTS-1][1] << '\n';
  std::cout << c[PHI_POINTS-2][THETA_POINTS-1][2] << '\n';

  delete[] c;
  delete[] n;

}

void Sphere::renderSphere() {
  glBindVertexArray(vao[0]);
  glUniform3fv(shaderIF->ppuLoc("kd"), 1, kd);
  glUniform3fv(shaderIF->ppuLoc("ka"), 1, ka);
  glDrawArrays(GL_TRIANGLE_FAN, 0, THETA_POINTS+2);

  glBindVertexArray(vao[1]);
  glUniform3fv(shaderIF->ppuLoc("kd"), 1, kd);
  glUniform3fv(shaderIF->ppuLoc("ka"), 1, ka);
  glDrawArrays(GL_TRIANGLE_FAN, 0, THETA_POINTS+2);

  // glBindVertexArray(vao[2]);
  // glUniform3fv(shaderIF->ppuLoc("kd"), 1, kd);
  // glUniform3fv(shaderIF->ppuLoc("ka"), 1, ka);
  // glDrawArrays(GL_TRIANGLE_FAN, 0, (POINTS_AROUND_SLICE+2));
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
