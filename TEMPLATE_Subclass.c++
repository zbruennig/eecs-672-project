// TEMPLATE_Subclass.c++

#include "TEMPLATE_Subclass.h"

TEMPLATE_Subclass::TEMPLATE_Subclass(ShaderIF* sIF) : shaderIF(sIF)
{
	// DON'T FORGET TO SET INSTANCE VARIABLES, PERHAPS USING
	// SOME CONSTRUCTOR PARAMETERS
}

TEMPLATE_Subclass::~TEMPLATE_Subclass()
{
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void TEMPLATE_Subclass::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = -1000.0; // xmin  Give real values!
	xyzLimits[1] = 1000.0;  // xmax         |
	xyzLimits[2] = -1234.5; // ymin         |
	xyzLimits[3] = -1011.2; // ymax         |
	xyzLimits[4] = -3000.0; // zmin         |
	xyzLimits[5] = -2000.0; // zmax        \_/
}

void TEMPLATE_Subclass::render()
{
	// 1. Save current and establish new current shader program
	// ...

	// 2. Establish "mc_ec" and "ec_lds" matrices
	// ...

	// Steps 3 and 4 may be performed in a "renderXxx" method as we have seen.
	// (If so, be sure to add the declaration of the method to the header file.)

	// 3. Set GLSL's "ka" and "kd" uniforms using this object's "ka" and "kd"
	//    instance variables
	// ...

	// 4. Establish any other attributes and make one or more calls to
	//    glDrawArrays and/or glDrawElements
	// ...

	// 5. Reestablish previous shader program
	// ...
}
