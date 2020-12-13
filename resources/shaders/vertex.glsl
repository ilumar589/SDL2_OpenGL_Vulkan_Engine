#version 330 core
layout (location = 0) in vec3 a_pos;   // the position variable has attribute position 0
layout (location = 1) in vec3 a_color; // the color variable has attribute position 1
layout (location = 2) in vec2 a_texture_coord;

out vec3 our_color; // output a color to the fragment shader
out vec2 texture_coord;

void main() {
    gl_Position = vec4(a_pos, 1.0);
    our_color = a_color; // set ourColor to the input color we got from the vertex data
    texture_coord = vec2(a_texture_coord.x, a_texture_coord.y);
}
