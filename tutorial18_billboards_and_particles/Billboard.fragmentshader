#version 120

// Interpolated values from the vertex shaders
varying vec2 UV;

uniform sampler2D myTextureSampler;

uniform float LifeLevel;

void main(){
	// Output color = color of the texture at the specified UV
	gl_FragColor = texture2D( myTextureSampler, UV );
	
	// Hardcoded life level, should be in a separate texture.
	if (UV.x < LifeLevel && UV.y > 0.3 && UV.y < 0.7 && UV.x > 0.04 )
		gl_FragColor = vec4(0.2, 0.8, 0.2, 1.0); // Opaque green
}