#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <string>

struct TilemapShader {
    unsigned int id;

    unsigned int uniformModel;
    unsigned int uniformView;
    unsigned int uniformProjection;
    unsigned int uniformWidth;
    unsigned int uniformHeight;
    unsigned int uniformTileDataOffset;
};

TilemapShader createTilemapShader(std::string vertex, std::string fragment);

void useShader(unsigned int id);

void setUniformMat4(unsigned int uniformId, glm::mat4* matrix);

void setUniform1i(unsigned int uniformId, unsigned int value);

void setUniformVec3(unsigned int uniformId, glm::vec3* vec);

typedef unsigned int Texture;

Texture loadTexture(std::string file);

void bindTexture(Texture texture);
