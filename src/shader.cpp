#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"

#include <fstream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define internal static


internal std::string readFile(std::string file) {
    try {
        std::ifstream handle(file);
        handle.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        std::stringstream buffer;
        buffer << handle.rdbuf();
        return buffer.str();
    } catch (...) {
        printf("failed to read file: %s", file.c_str());
    }
    return "";
}

internal unsigned int createShader(std::string vFile, std::string fFile) {
    std::string vRaw = readFile(vFile);
    std::string fRaw = readFile(fFile);

    const char* vCode = vRaw.c_str();
    const char* fCode = fRaw.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        printf("Error compiling vertex shader: %s\n", infoLog);
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        printf("Error compiling fragment shader: %s\n", infoLog);
    }

    unsigned int shaderId = glCreateProgram();
    glAttachShader(shaderId, vertex);
    glAttachShader(shaderId, fragment);
    glLinkProgram(shaderId);
    glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderId, 512, NULL, infoLog);
        printf("Error linking shader: %s", infoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shaderId;
}

TilemapShader createTilemapShader(std::string vFile, std::string fFile) {
    TilemapShader shader;

    shader.id = createShader(vFile, fFile);

    shader.uniformModel = glGetUniformLocation(shader.id, "model");
    shader.uniformView = glGetUniformLocation(shader.id, "view");
    shader.uniformProjection = glGetUniformLocation(shader.id, "projection");
    shader.uniformWidth = glGetUniformLocation(shader.id, "width");
    shader.uniformHeight = glGetUniformLocation(shader.id, "height");
    shader.uniformTileDataOffset = glGetUniformLocation(shader.id, "tileDataOffset");

    return shader;
}

void useShader(unsigned int id) {
    glUseProgram(id);
}

void setUniformMat4(unsigned int uniformId, glm::mat4 *matrix) {
    glUniformMatrix4fv(uniformId, 1, GL_FALSE, &(*matrix)[0][0]);
}

void setUniform1i(unsigned int uniformId, unsigned int value) {
    glUniform1i(uniformId, value);
}

void setUniformVec3(unsigned int uniformId, glm::vec3* vec) {
    glUniform3fv(uniformId, 1, &(vec->x));
}

Texture loadTexture(std::string file) {
    Texture texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nr_channels;
    unsigned char *data = stbi_load(file.c_str(), &width, &height, &nr_channels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    } else {
        printf("failed to load texture: %s", file.c_str());
    }

    return texture;
}

void bindTexture(Texture texture) {
    glBindTexture(GL_TEXTURE_2D, texture);
}
