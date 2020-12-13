//
// Created by Valar on 11/5/2020.
//

#ifndef SDL2_OPENGL_VULKAN_ENGINE_EXAMPLES_H
#define SDL2_OPENGL_VULKAN_ENGINE_EXAMPLES_H

#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <tuple>
#include <optional>

namespace Examples {

    struct GLuint2 {
        GLuint value1;
        GLuint value2;
    };

    GLuint triangleVertexArrayBuffer();
    GLuint squareWithElementBufferObject();
    // Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data
    GLuint helloTriangleExercise1();
    // Same two triangles using separate vaos and vbos
    GLuint2 helloTriangleExercise2();
    GLuint colorOnAttributes();
    // return the vertex array object handle and texture handle pair
    GLuint2 loadTexture();

}

#endif //SDL2_OPENGL_VULKAN_ENGINE_EXAMPLES_H
