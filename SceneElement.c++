// SceneElement.c++

#include "SceneElement.h"
#include "OpenGLImageReader.h"
#include <iostream>

typedef float vec3[3];

float SceneElement::lightPos[4*MAX_NUM_LIGHTS] =
	{
		0.25, 0.5, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0,
		-0.25, 0.5, 1.0, 0.0
	};

// Are coordinates in "lightPos" stored in MC or EC? (You usually want them
// defined in MC, unless you are trying to simulate something like the viewer
// holding a flashlight while moving around the scene.)
bool SceneElement::posInModelCoordinates[MAX_NUM_LIGHTS] =
	{ true, true, true };
// The following is the buffer actually sent to GLSL. It will contain a copy of
// the (x,y,z,w) for light sources defined in EC; it will contain the coordinates
// after transformation to EC if the position was originally specified in MC.
float posToGLSL[4*MAX_NUM_LIGHTS];

float SceneElement::lightStrength[3*MAX_NUM_LIGHTS] =
	{
		0.8, 0.8, 0.8,
		0.5, 0.5, 0.5,
		0.6, 0.6, 0.6
	};

float SceneElement::globalAmbient[] = { 0.2, 0.2, 0.2 };

SceneElement::SceneElement(ShaderIF* sIF) : shaderIF(sIF)
{
}

SceneElement::~SceneElement()
{
}

void SceneElement::establishLightingEnvironment()
{
	const int NUM_LIGHTS = 3;
	glUniform1i(shaderIF->ppuLoc("actualNumLights"), NUM_LIGHTS);

	float c[4] = {200,100,0,0.01}; //TODO add multiple?
	glUniform4fv(shaderIF->ppuLoc("c"), 1, c);

	cryph::AffPoint p1(81.997,0,10); //directly above the 8 ball
	cryph::AffPoint p2(0,0,-30); //below the table
	cryph::AffPoint p3(-200,30,10); //off to the left, lined with the cue ball
	//convert to eye coordinates

	float points[9] = {(float) p1.x, (float) p1.y, (float) p1.z,
										 (float) p2.x, (float) p2.y, (float) p2.z,
										 (float) p3.x, (float) p3.y, (float) p3.z};
	glUniform3fv(shaderIF->ppuLoc("mcLightPos"), 3, points);
}

void SceneElement::establishMaterial(const PhongMaterial& matl)
{
	// This should set all material property parameters, including:
	// "ka", "kd", "ks", "m", and (for project 4) "alpha"
	glUniform3fv(shaderIF->ppuLoc("kd"), 1, matl.kd);
	glUniform3fv(shaderIF->ppuLoc("ka"), 1, matl.ka);
	glUniform3fv(shaderIF->ppuLoc("ks"), 1, matl.ks);
	// glUniform1f(shaderIF->ppuLoc("m"), matl.m); //TODO uncomment if it works
}

void SceneElement::establishTexture( /* ... parameters? ... */ )
{
}

void SceneElement::establishView()
{
	// Line of sight, dynamic view controls, 3D-2D projection, & mapping to LDS:
	cryph::Matrix4x4 mc_ec, ec_lds;
	ModelView::getMatrices(mc_ec, ec_lds);
	float m[16];
	glUniformMatrix4fv(shaderIF->ppuLoc("mc_ec"), 1, false, mc_ec.extractColMajor(m));
	glUniformMatrix4fv(shaderIF->ppuLoc("ec_lds"), 1, false, ec_lds.extractColMajor(m));
}

GLuint SceneElement::readTextureImage(const std::string& imgFileName)
{
	OpenGLImageReader* oglIR = OpenGLImageReader::create(imgFileName.c_str());
	if (oglIR == nullptr)
	{
		std::cerr << "Could not open '" << imgFileName << "' for texture map.\n";
		return 0;
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	GLuint texID[1];
	glGenTextures(1, texID);
	glBindTexture(GL_TEXTURE_2D, texID[0]);
	float white[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, white);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	GLint level = 0;
	int pw = oglIR->getWidth(), ph = oglIR->getHeight();
	GLint iFormat = oglIR->getInternalFormat();
	GLenum format = oglIR->getFormat();
	GLenum type = oglIR->getType();
	const GLint border = 0; // must be zero (only present for backwards compatibility)
	const void* pixelData = oglIR->getTexture();
	glTexImage2D(GL_TEXTURE_2D, level, iFormat, pw, ph, border, format, type, pixelData);
	delete oglIR;
	return texID[0];
}
