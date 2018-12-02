// TableMaterial.h

#ifndef TABLEMATERIAL_H
#define TABLEMATERIAL_H

#include "SceneElement.h"
#include "ShaderIF.h"

typedef float vec3[3];

class TableMaterial : public SceneElement
{
  TableMaterial(ShaderIF* sIF, const std::string texImageSource, PhongMaterial matl);

  GLuint vao[1];
  GLuint vbo[3];
  GLuint texID;
  PhongMaterial matl;

  void defineInitialGeometry();

  void render();
  void renderTableMaterial();
};
#endif
