//
// Created by Valar on 11/5/2020.
//

#include "Examples.h"
#include <stb_image.h>

GLuint Examples::triangleVertexArrayBuffer() {
    float triangleData[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };

    GLuint vao, vbo;

    glGenVertexArrays(1, &vao); // consider a vertex array an object that holds the state of one vertex buffer object,
    // by state meaning all the vertex attribute pointers towards the vertex buffer object data
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0); // we have to enable each attribute pointer

    glBindVertexArray(0);

    return vao;
}

GLuint Examples::squareWithElementBufferObject() {
    // a square is composed of two triangles but seeing as their vertices intersect we
    // can use something called indexed drawing with an element buffer object

    float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };

    int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };

    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // ..:: Initialization code :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(vao);
    // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 4. then set the vertex attributes pointers
    glVertexAttribPointer(0,3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0); // we have to enable each attribute pointer
    glBindVertexArray(0);

    return vao;
}

GLuint Examples::helloTriangleExercise1() {
    float vertices[] = {
            -1.0f, 0.0f, 0.0f, // first triangle bottom left
            -0.5f, 1.0f, 0.0f, // first triangle top
            0.0f, 0.0f, 0.0f,  // first triangle bottom right

            0.04f, 0.0f, 0.0f, // second triangle bottom left
            0.5f, 1.0f, 0.0f, // second triangle top
            1.0f, 0.0f, 0.0f  // second triangle bottom right
    };

    GLuint vao, vbo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    return vao;

//        glDrawArrays(GL_TRIANGLES, 0, 6); used in loop
}

std::tuple<GLuint, GLuint> Examples::helloTriangleExercise2() {
    float firstTriangleVertices[] = {
            -1.0f, 0.0f, 0.0f, // first triangle bottom left
            -0.5f, 1.0f, 0.0f, // first triangle top
            0.0f, 0.0f, 0.0f,  // first triangle bottom right
    };

    GLuint firstTriangleVao, firstTriangleVbo;
    glGenVertexArrays(1, &firstTriangleVao);
    glGenBuffers(1, &firstTriangleVbo);
    glBindVertexArray(firstTriangleVao);
    glBindBuffer(GL_ARRAY_BUFFER, firstTriangleVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangleVertices), firstTriangleVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    float secondTriangleVertices[] = {
            0.04f, 0.0f, 0.0f, // second triangle bottom left
            0.5f, 1.0f, 0.0f, // second triangle top
            1.0f, 0.0f, 0.0f  // second triangle bottom right
    };

    GLuint secondTriangleVao, secondTriangleVbo;
    glGenVertexArrays(1, &secondTriangleVao);
    glGenBuffers(1, &secondTriangleVbo);
    glBindVertexArray(secondTriangleVao);
    glBindBuffer(GL_ARRAY_BUFFER, secondTriangleVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangleVertices), secondTriangleVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    return std::make_tuple(firstTriangleVao, secondTriangleVao);
}

GLuint Examples::colorOnAttributes() {
    float vertices[] = {
            //positions          //colors
            0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom left
            0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f  // top
    };

    GLuint vao, vbo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), reinterpret_cast<const void *>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    return vao;
}

std::optional<std::tuple<GLuint, GLuint>> Examples::loadTexture() {
    GLuint textureHandle;
    int width, height, nrOfChannels;

    glGenTextures(1, &textureHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_uc *textureData = stbi_load("resources/textures/container.jpg", &width, &height, &nrOfChannels, 0);

    if (textureData) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(textureData);

        float vertices[] = {
                // positions          // colors           // texture coords
                0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
                0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
                -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
                -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
        };

        GLuint vao, vbo;

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), reinterpret_cast<const void *>(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), reinterpret_cast<const void *>(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);

        return std::optional<std::tuple<GLuint, GLuint>>{std::make_tuple(vao, textureHandle)};
    }

    return std::optional<std::tuple<GLuint, GLuint>>{};
}