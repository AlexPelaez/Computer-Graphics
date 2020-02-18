#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 view1;
uniform mat4 scale;
uniform mat4 rotateX;
uniform mat4 rotateY;
uniform mat4 rotateZ;
uniform mat4 translateZ;
uniform mat4 translateY;
uniform mat4 translateX;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * view1 * scale * rotateZ * rotateX * rotateY * transform * translateZ * translateX * translateY * vec4(aPos, 1.0);
    ourColor = aColor;
}
