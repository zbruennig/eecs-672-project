// TableMaterial.c++

#include <iostream>
#include <math.h>

#include "TableMaterial.h"

GLuint TableMaterial::indexList[3][4] = {
  {6,7,0,1},
  {6,0,4,2},
  {1,7,3,5}
};

TableMaterial::TableMaterial(ShaderIF* sIF, float cx, float cy, float cz, float lx, float ly, float lz, const std::string texImageSource, PhongMaterial matl) :
wrapS(GL_CLAMP_TO_BORDER), wrapT(GL_CLAMP_TO_BORDER), SceneElement(sIF), matl(matl)
{
  xmin = cx - lx/2; xmax = cx + lx/2;
	ymin = cy - ly/2; ymax = cy + ly/2;
	zmin = cz - lz/2; zmax = cz + lz/2;

  defineInitialGeometry();
  texID = readTextureImage(texImageSource);
}

void TableMaterial::defineInitialGeometry() {
  typedef float vec2[2];
	typedef float vec3[3];

  vec3 vtx[] = { // The 8 unique vertices (Note the order)
		{xmin, ymin, zmax}, {xmin, ymax, zmax},
		{xmax, ymin, zmax}, {xmax, ymax, zmax},
		{xmax, ymin, zmin}, {xmax, ymax, zmin},
		{xmin, ymin, zmin}, {xmin, ymax, zmin}
	};

  vec2 st[] = {
    {0,0}, {0,1},
    {1,0}, {1,1},
    {1,1}, {1,0},
    {0,1}, {0,0}
  };

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);

	glGenBuffers(2, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(vec3), vtx, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

  glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
  glBufferData(GL_ARRAY_BUFFER, 8*sizeof(vec2), st, GL_STATIC_DRAW);
  glVertexAttribPointer(shaderIF->pvaLoc("texCoords"), 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(shaderIF->pvaLoc("texCoords"));

	glGenBuffers(3, ebo);
	for (int i=0 ; i<3 ; i++)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), indexList[i], GL_STATIC_DRAW);
	}

	glDisableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));

}

void TableMaterial::getMCBoundingBox(double* xyzLimits) const
{
  xyzLimits[0] = xmin;
  xyzLimits[1] = xmax;
  xyzLimits[2] = ymin;
  xyzLimits[3] = ymax;
  xyzLimits[4] = zmin;
  xyzLimits[5] = zmax;
}

bool TableMaterial::handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY)
{
	return this->ModelView::handleCommand(anASCIIChar, ldsX, ldsY);
}

void TableMaterial::renderTableMaterial() {
  establishMaterial(matl);
  establishTexture(texID, wrapS, wrapT); // SEE COMMENTS AT THE TOP OF THIS FILE

  glBindVertexArray(vao[0]);

// ... one or more glDrawArrays and/or glDrawElements calls
  glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 0.0, 0.0, 1.0);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 1.0, 0.0, 0.0);
  glDrawArrays(GL_TRIANGLE_STRIP, 2, 4);
  glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 0.0, 0.0, -1.0);
  glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);

  // The three faces that are drawn with glDrawElements
  glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), -1.0, 0.0, 0.0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
  glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);
  glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 0.0, -1.0, 0.0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
  glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);
  glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 0.0, 1.0, 0.0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[2]);
  glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);

  glUniform1i(shaderIF->ppuLoc("usingTexture"), false);
}

void TableMaterial::render() {
  GLint pgm;
  glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);

  glUseProgram(shaderIF->getShaderPgmID());

  establishLightingEnvironment();
  establishView();

  renderTableMaterial();

  glUseProgram(pgm);
}
