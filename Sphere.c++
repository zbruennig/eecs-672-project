// Sphere.c++

#include "Sphere.h"

Sphere::Sphere(ShaderIF* sIF, float center[], float radius, PhongMaterial matl) :
  SceneElement(sIF), matl(matl)
{
  xmin = center[0] - radius;
  xmax = center[0] + radius;
  ymin = center[1] - radius;
  ymax = center[1] + radius;
  zmin = center[2] - radius;
  zmax = center[2] + radius;

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
  glDeleteBuffers(THETA_POINTS*(PHI_POINTS-2), ebo);
  glDeleteVertexArrays(3, vao);

  if(c != nullptr){
    for(int i=0; i<PHI_POINTS-1; i++){
      if(n[i] != nullptr){
        delete[] n[i];
      }
    }
    delete[] c;
  }

  if(n != nullptr){
    for(int i=0; i<PHI_POINTS-1; i++){
      if(n[i] != nullptr){
        delete[] n[i];
      }
    }
    delete[] n;
  }
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

  c = new vec3*[PHI_POINTS-1];
  n = new vec3*[PHI_POINTS-1];
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
      c[i][j][2] = z + r*cos(phi);
      n[i][j][0] = cos(theta)*sin(phi);
      n[i][j][1] = sin(theta)*sin(phi);
      n[i][j][2] = cos(phi);
      theta+=dTheta;
    }
    phi += dPhi;
  }

  //We cannot draw triangles directly, we will need to use an ebo
  //Instead we will need to create a whole bunch of indices

  //We build our indices as a function of PHI_POINTS and THETA_POINTS
  for(int i=0; i<PHI_POINTS-2; i++){
    for(int j=0; j<THETA_POINTS; j++){
      vertices[i][j][0] = THETA_POINTS*i + j;
      vertices[i][j][1] = THETA_POINTS*(i+1) + j;
      if(j+1 != THETA_POINTS){
        vertices[i][j][2] = THETA_POINTS*i + j + 1;
        vertices[i][j][3] = THETA_POINTS*(i+1) + j + 1;
      }
      else{
        vertices[i][j][2] = THETA_POINTS*(i-1) + j + 1;
        vertices[i][j][3] = THETA_POINTS*i + j + 1;
      }
    }
  }

  //Now we need to stuff our 3d arrays into vaos and vbos
  //Convert to 2d first

  vec3* c1 = new vec3[(PHI_POINTS-1)*THETA_POINTS];
  vec3* n1 = new vec3[(PHI_POINTS-1)*THETA_POINTS];
  for(int i=0; i<PHI_POINTS-1; i++){
    for(int j=0; j<THETA_POINTS; j++){
      for(int k=0; k<3; k++){
        c1[i*THETA_POINTS+j][k] = c[i][j][k];
        n1[i*THETA_POINTS+j][k] = n[i][j][k];
      }
    }
  }

  glBindVertexArray(vao[2]);
  glGenBuffers(2, sides);

  glBindBuffer(GL_ARRAY_BUFFER, sides[0]);
  glBufferData(GL_ARRAY_BUFFER, (PHI_POINTS-1)*THETA_POINTS*sizeof(vec3), c1, GL_STATIC_DRAW);
  glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

  glBindBuffer(GL_ARRAY_BUFFER, sides[1]);
  glBufferData(GL_ARRAY_BUFFER, (PHI_POINTS-1)*THETA_POINTS*sizeof(vec3), n1, GL_STATIC_DRAW);
  glVertexAttribPointer(shaderIF->pvaLoc("mcNormal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));

  delete[] c1;
  delete[] n1;

  glGenBuffers(THETA_POINTS*(PHI_POINTS-2), ebo);
  for(int i=0; i<PHI_POINTS-2; i++){
    for(int j=0; j<THETA_POINTS; j++){
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i*THETA_POINTS+j]);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), vertices[i][j], GL_STATIC_DRAW);
    }
  }
}

void Sphere::renderSphere() {
  glBindVertexArray(vao[0]);
  establishMaterial(matl);
  glDrawArrays(GL_TRIANGLE_FAN, 0, THETA_POINTS+2);

  glBindVertexArray(vao[1]);
  establishMaterial(matl);
  glDrawArrays(GL_TRIANGLE_FAN, 0, THETA_POINTS+2);

  glBindVertexArray(vao[2]);
  establishMaterial(matl);
  for(int i=0; i<THETA_POINTS*(PHI_POINTS-2); i++){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);
  }
}

void Sphere::render()
{
  GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	glUseProgram(shaderIF->getShaderPgmID());

  establishView();
  establishLightingEnvironment();

	renderSphere();

	glUseProgram(pgm);
}
