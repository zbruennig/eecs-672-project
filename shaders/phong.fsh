#version 410 core

// phong.fsh - a fragment shader that implements a Phong Lighting model.

in PVA
{
	vec3 ecPosition;
	vec3 ecUnitNormal;
	vec3 p_ecLightPos0;
	vec3 p_ecLightPos1;
	vec3 p_ecLightPos2;
	vec2 texCoords;
} pvaIn;

// For lighing model:
uniform mat4 ec_lds; // so projection type and hence vHat can be determined

uniform int actualNumLights = 3;

// Phong material properties (RGB reflectances);
uniform vec3 ka = vec3(0.0, 0.0, 0.0); // default: black
uniform vec3 kd = vec3(0.0, 0.0, 0.0);
uniform vec3 ks = vec3(0.0, 0.0, 0.0);
uniform float m = 1;
// Lighting environment
// RGB strength of assumed ambient light:
uniform vec3 La = vec3(0.25, 0.25, 0.25);
uniform vec3 L[] = vec3[3](vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0));
/*uniform*/ vec3 p_ecLightPos[] = vec3[3](vec3(0.0, 0.0, 10.0), vec3(0.0, 0.0, -10.0), vec3(25.0, 40.0, 15.0));
//cs for lighting model attenuation function
uniform vec4 c = vec4(1,1,0,0);

// *************** NEW ******************
//Translucency, alpha, and texture variables
uniform bool usingAlphaBlending = false;
uniform float alpha = 1.0;
uniform bool isOpaque = true;
uniform bool isTranslucent = false;

uniform bool usingTexture = false;
uniform sampler2D texMap;

// output color from the lighting model:
out vec4 fragmentColor;

float atten(int i, vec3 Q){
	float d = distance(Q, p_ecLightPos[i]);
	return c[0] / (c[1] + c[2]*d + c[3]*d*d);
}

vec4 evaluateLightingModel()
{
	p_ecLightPos[0] = pvaIn.p_ecLightPos0;
	p_ecLightPos[1] = pvaIn.p_ecLightPos1;
	p_ecLightPos[2] = pvaIn.p_ecLightPos2;

	vec3 vHat = -1*pvaIn.ecPosition;
	if(false){ //other perspectives
		vec3 v = vec3(-1*ec_lds[0][2]/ec_lds[0][0], -1*ec_lds[1][2]/ec_lds[1][1], 1);
		vHat = normalize(v);
	}

	vec3 ec_nHat = dot(pvaIn.ecUnitNormal, vHat) < 0 ? pvaIn.ecUnitNormal * -1 : pvaIn.ecUnitNormal;

	vec3 liHat[3] = vec3[3](vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0));
	for(int i = 0; i<actualNumLights; i++){
		liHat[i] = normalize(p_ecLightPos[i] - pvaIn.ecPosition);
	}

	vec3 riHat[3] = vec3[3](vec3(0.0, 0.0, 1.0), vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0));
	for(int i = 0; i<actualNumLights; i++){
		vec3 u = normalize(ec_nHat);
		vec3 perp = liHat[i] - (dot(u, liHat[i]) * u);
		riHat[i] = normalize(liHat[i] * 2*perp);
	}

	//All parameters defined, this is the equation!
	vec3 I = ka*La;
	for(int i=0; i<actualNumLights; i++){
		float fiQ = atten(i, pvaIn.ecPosition);
		vec3 diff = kd * dot(ec_nHat, liHat[i]);
		float specular = dot(riHat[i], vHat);

		//I would be using the first one, but it produces weird results. Sorry.
		/*vec3 spec = ks * pow(specular, m);*/
		vec3 spec = ks * specular;
		I += fiQ * (diff + spec);
	}
	return vec4(I, 0);
}

void main()
{
	fragmentColor = evaluateLightingModel();

	// Special instructions just in case texture mapping
	if(usingTexture) {
		vec4 texColor = texture(texMap, pvaIn.texCoords);
		fragmentColor = texColor * fragmentColor;
	 //TODO remove, also get texMap in here
	}

	fragmentColor.a = alpha;

	//TODO look over logic
	if(usingAlphaBlending) {
		if(isOpaque) {
			if (fragmentColor.a <= 1) {
				discard;
			}
		}
		else{
			if (fragmentColor.a > 1){
				discard;
			}
		}
	}
}
