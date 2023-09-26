#pragma once

struct Vertex {
    float x;
    float y;
};

struct Mesh {
    unsigned int vao;
    int indexCount;
};

Mesh generateSquareMesh();
