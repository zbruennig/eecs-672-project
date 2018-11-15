#version 410 core

// phong.fsh - a fragment shader that implements a Phong Lighting model.

in PVA
{
	vec3 ecPosition;
	vec3 ecUnitNormal; //TODO: Conditionally negate
} pvaIn;

// For lighing model:
uniform mat4 ec_lds; // so projection type and hence vHat can be determined

// Phong material properties (RGB reflectances);
uniform vec3 ka = vec3(0.0, 0.0, 0.0); // default: black
uniform vec3 kd = vec3(0.0, 0.0, 0.0);
uniform vec3 ks = vec3(0.0, 0.0, 0.0);
uniform float m = 1;
// Lighting environment
// RGB strength of assumed ambient light:
uniform vec3 La = vec3(0.25, 0.25, 0.25);
/*uniform vec3 L[] = {vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0)};*/ //TODO make right

// output color from the lighting model:
out vec4 fragmentColor;

vec4 evaluateLightingModel() //TODO Change
{
	vec3 liHat = vec3(0.0, 0.0, 1.0); // directional light in EC at eye (a flashlight)

	//Compute each component, and the dot product separately
	float dotProduct = ( (liHat.x * pvaIn.ecUnitNormal.x) + (liHat.y * pvaIn.ecUnitNormal.y) + (liHat.z * pvaIn.ecUnitNormal.z) );
	float r = ka.r * La.r;
	float g = ka.g * La.g;
	float b = ka.b * La.b;

	if (dotProduct < 0) {
	//I don't want to worry about orientation of the normal vector
	//In our current model, things this might incorrectly affect will not be visible
		dotProduct *= -1;
	}
	r += kd.r * dotProduct;
	g += kd.g * dotProduct;
	b += kd.b * dotProduct;

	return vec4(r, g, b, 1);
}

float atten(float i, vec3 Q){ //TODO typeof i?
	return 0; //TODO
}

void main()
{
	fragmentColor = evaluateLightingModel();
}
