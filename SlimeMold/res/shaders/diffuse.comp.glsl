#version 430

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout(rgba32f, binding = 1) uniform image2D img_input1;

layout(rgba32f, binding = 2) uniform image2D img_input2;

layout(rgba32f, binding = 3) uniform image2D img_output;

uniform float diffuseRate;
uniform float decayRate;

void main() {
	ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);

	float avgPixelValue = 0;

	for(int i = -1; i <= 1; i++) {
		for(int j = -1; j <= 1; j++) {
		ivec2 coords = ivec2(pixel_coords + vec2(i, j));
			if (coords.x >= 0 && coords.x < gl_NumWorkGroups.x && coords.y >= 0 && coords.y < gl_NumWorkGroups.y) {
				avgPixelValue += min(imageLoad(img_input1, coords).r + imageLoad(img_input2, coords).r, 1);
			}
		}
	}

	avgPixelValue = avgPixelValue / 9;
	avgPixelValue = mix(min(imageLoad(img_input1, pixel_coords).r + imageLoad(img_input2, pixel_coords).r, 1), 
		avgPixelValue, diffuseRate);
	avgPixelValue = max(0, avgPixelValue - decayRate);

	imageStore(img_output, pixel_coords, vec4(avgPixelValue, 0.0, 0.0, 1.0));
}