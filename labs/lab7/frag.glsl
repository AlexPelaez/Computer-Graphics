#version 330 core

in vec2 ourTexCoord;

out vec4 fragColor;

uniform sampler2D ourTex;

/**
 * TODO: PART-1 update the fragment shader to get the texture coordinates from
 * the vertex shader
 */

/**
 * TODO: PART-3 update the fragment shader to get the fragColor color from the
 * texture, and add the sampler2D.
 */

void main() {
    fragColor = texture(ourTex, ourTexCoord);
}
