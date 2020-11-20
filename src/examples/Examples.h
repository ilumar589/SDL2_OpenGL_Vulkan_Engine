//
// Created by Valar on 11/5/2020.
//

#ifndef SDL2_OPENGL_VULKAN_ENGINE_EXAMPLES_H
#define SDL2_OPENGL_VULKAN_ENGINE_EXAMPLES_H

#include <glad/glad.h>
#include <tuple>
#include <optional>

namespace Examples {
    GLuint triangleVertexArrayBuffer();
    GLuint squareWithElementBufferObject();
    // Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data
    GLuint helloTriangleExercise1();
    // Same two triangles using separate vaos and vbos
    std::tuple<GLuint, GLuint> helloTriangleExercise2();
    GLuint colorOnAttributes();
    // return the vertex array object handle and texture handle pair
    std::optional<std::tuple<GLuint, GLuint>> loadTexture();

}

#endif //SDL2_OPENGL_VULKAN_ENGINE_EXAMPLES_H
