#version 430

#define PI 3.14159265358

struct SlimeCell {
	vec2 position;
	float orientation;
	int type;
};

layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

layout(std430, binding = 0)
buffer SlimeData {
	SlimeCell slimeData[];
};

layout(rgba32f, binding = 1) uniform image2D img_input;

layout(rgba32f, binding = 2) uniform image2D img_output;


uniform float sensorAngle;
uniform float sensorDistance;
uniform float turnSensitivity;
uniform float movementSpeed;


float hash(vec2 stateI){
	uint state = uint(stateI.x * 10000 + stateI.y * 10000);
    state ^= 2747636419u;
    state *= 2654435769u;
    state ^= state >> 16;
    state *= 2654435769u;
    state ^= state >> 16;
    state *= 2654435769u;
    return int(state) / 4294967295.0;
}

void sense(int currentInvocation) {
	ivec2 leftSensor = ivec2(slimeData[currentInvocation].position + 
		sensorDistance * vec2(cos(slimeData[currentInvocation].orientation + sensorAngle), 
		sin(slimeData[currentInvocation].orientation + sensorAngle)));
	ivec2 frontSensor = ivec2(slimeData[currentInvocation].position + 
		sensorDistance * vec2(cos(slimeData[currentInvocation].orientation), 
		sin(slimeData[currentInvocation].orientation)));
	ivec2 rightSensor = ivec2(slimeData[currentInvocation].position + 
		sensorDistance * vec2(cos(slimeData[currentInvocation].orientation - sensorAngle), 
		sin(slimeData[currentInvocation].orientation - sensorAngle)));

	float fl = imageLoad(img_input, leftSensor).r;
	float ff = imageLoad(img_input, frontSensor).r;
	float fr = imageLoad(img_input, rightSensor).r;

	if(ff > fl && ff > fr) {
		
	} else if(ff < fl && ff < fr) {
		float newOrientation = hash(slimeData[currentInvocation].position * 2);

		if(newOrientation > 0.5) {
			slimeData[currentInvocation].orientation += turnSensitivity * 
				(hash(slimeData[currentInvocation].position) / 2 + 0.5);
		} else {
			slimeData[currentInvocation].orientation -= turnSensitivity * 
				(hash(slimeData[currentInvocation].position) / 2 + 0.5);
		}
	} else if(fl > fr) {
		slimeData[currentInvocation].orientation += turnSensitivity * (hash(slimeData[currentInvocation].position) / 2 + 0.5);
	} else if(fr > fl) {
		slimeData[currentInvocation].orientation -= turnSensitivity * (hash(slimeData[currentInvocation].position) / 2 + 0.5);
	}
}

void move(int currentInvocation) {
	vec2 movement = movementSpeed * vec2(cos(slimeData[currentInvocation].orientation), sin(slimeData[currentInvocation].orientation));
	vec2 newPos = slimeData[currentInvocation].position + movement;

	if(newPos.x >= imageSize(img_input).x || newPos.x < 0 || newPos.y >= imageSize(img_input).y || newPos.y < 0) {
		slimeData[currentInvocation].orientation = hash(slimeData[currentInvocation].position) * 2 * PI;
	} else {
		slimeData[currentInvocation].position = newPos;
	}
}

void main() {
	int currentInvocation = int(gl_GlobalInvocationID.y * gl_NumWorkGroups.x * 8 + gl_GlobalInvocationID.x * 8 + gl_LocalInvocationID.y * 8 + gl_LocalInvocationID.x);

	sense(currentInvocation);
	move(currentInvocation);

	ivec2 pixel_coords = ivec2(slimeData[currentInvocation].position);
	vec4 pixel = vec4(0.1 + imageLoad(img_output, pixel_coords).r, 0.0, 0.0, 1.0);
	imageStore(img_output, pixel_coords, pixel);
}