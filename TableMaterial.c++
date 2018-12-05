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
  defineInitialGeometry();
  texID = readTextureImage(texImageSource);
}

void TableMaterial::defineInitialGeometry() {

}

void TableMaterial::renderTableMaterial() {
  establishMaterial(matl);
  establishTexture(texID, wrapS, wrapT); // SEE COMMENTS AT THE TOP OF THIS FILE

  // glBindVertexArray(vao[0]);

// ... one or more glDrawArrays and/or glDrawElements calls

// TURN OFF your "using a texture map" uniform variable before leaving.
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
