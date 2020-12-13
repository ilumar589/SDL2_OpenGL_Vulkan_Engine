#version 330 core

out vec4 FragColor;
in vec3 our_color;
in vec2 texture_coord;

uniform sampler2D our_texture;

void main() {
    FragColor = texture(our_texture, texture_coord) * vec4(our_color, 1.0);
}