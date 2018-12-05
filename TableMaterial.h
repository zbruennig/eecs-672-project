// TableMaterial.h

#ifndef TABLEMATERIAL_H
#define TABLEMATERIAL_H

#include "SceneElement.h"
#include "ShaderIF.h"

class TableMaterial : public SceneElement
{
public:
  TableMaterial(ShaderIF* sIF, float cx, float cy, float cz, float lx, float ly, float lz, const std::string texImageSource, PhongMaterial matl);
  void render();
  void renderTableMaterial();
  void getMCBoundingBox(double* xyzLimits) const;
  bool handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY);
private:

  GLuint vao[1];
  GLuint vbo[2];
  GLuint ebo[3];
  GLuint texID;
  GLenum wrapS;
  GLenum wrapT;
  PhongMaterial matl;

  float xmin, xmax, ymin, ymax, zmin, zmax;

  void defineInitialGeometry();

  static GLuint indexList[3][4];
};
#endif
