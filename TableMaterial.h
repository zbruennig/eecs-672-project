// TableMaterial.h

#ifndef TABLEMATERIAL_H
#define TABLEMATERIAL_H

#include "SceneElement.h"
#include "ShaderIF.h"

typedef float vec3[3];

class TableMaterial : public SceneElement
{
  TableMaterial(ShaderIF* sIF, float cx, float cy, float cz, float lx, float ly, float lz, const std::string texImageSource, PhongMaterial matl);

  GLuint vao[1];
  GLuint vbo[3];
  GLuint ebo[3];
  GLuint texID;
  GLenum wrapS;
  GLenum wrapT;
  PhongMaterial matl;

  float xmin, xmax, ymin, ymax, zmin, zmax;

  void defineInitialGeometry();

  static GLuint indexList[3][4];

  void render();
  void renderTableMaterial();
};
#endif
