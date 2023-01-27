#version 330 core

in vec2 textureCoords;

uniform sampler2D renderTexture;

out vec4 color;

uniform vec4 baseColor;
uniform vec4 midColor;
uniform vec4 fullColor;

float mixValue = 0.5;

void main(){
	float colorValue = texture(renderTexture, textureCoords).r;

	if(colorValue > mixValue) {
		color = mix(midColor, fullColor, (colorValue - (1 - mixValue)) / mixValue);
	} else {
		color = mix(baseColor, midColor, colorValue / mixValue);
	}
}