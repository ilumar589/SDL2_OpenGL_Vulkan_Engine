//
// Created by eduard.parvu on 10/13/2020.
//

#ifndef SDL2_OPENGL_VULKAN_ENGINE_SHADER_H
#define SDL2_OPENGL_VULKAN_ENGINE_SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
private:
    GLuint programId;

public:
    Shader(const Shader& other) = delete; // copy not allowed through the copy constructor
    Shader(Shader&& other) = delete; // move not allowed through the move constructor
    Shader& operator=(const Shader& other) = delete; // copy not allowed through the copy operator
    Shader& operator=(Shader && other) = delete; // move not allowed through the move operator

    Shader(const char* vertexPath, const char* fragmentPath);
    void use() const noexcept;
    GLuint& getProgramId();

    //utility uniform functions
    void setBool(const std::string& name, bool value) const noexcept;
    void setInt(const std::string& name, int value) const noexcept;
    void setFloat(const std::string& name, float value) const noexcept;
};


#endif //SDL2_OPENGL_VULKAN_ENGINE_SHADER_H
