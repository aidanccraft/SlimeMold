#version 330 core

layout(location = 0) in vec2 position;

out vec2 textureCoords;

void main(){
    textureCoords = vec2((position.x + 1.0) / 2.0,
			1 - (position.y + 1.0) / 2.0);

    gl_Position = vec4(position.xy, 0.0, 1.0);
}