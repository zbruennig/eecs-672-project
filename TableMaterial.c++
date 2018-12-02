// TableMaterial.c++

#include "TableMaterial.h"

TableMaterial::TableMaterial(ShaderIF* sIF, const std::string texImageSource, PhongMaterial matl) :
/*wrapS(GL_CLAMP_TO_BORDER), wrapT(GL_CLAMP_TO_BORDER),*/ SceneElement(sIF), matl(matl)
{
  defineInitialGeometry();
  texID = readTextureImage(texImageSource);
}

void TableMaterial::defineInitialGeometry() {

}

void TableMaterial::renderTableMaterial() {
  establishMaterial(matl);
  establishTexture(texID); // SEE COMMENTS AT THE TOP OF THIS FILE

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
