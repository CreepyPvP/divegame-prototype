#include "mesh_gen.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Mesh generateSquareMesh() {
    Mesh mesh;
    float vertexData[] = {
        -0.5,  0.5,
        0.5,  0.5,
        -0.5, -0.5,
        0.5, -0.5,
    };
    unsigned int indices [] = {
        0, 1, 2,
        1, 3, 2
    };

    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);

    unsigned int buffers[2];
    glGenBuffers(2, buffers);
    unsigned int vertexBuffer = buffers[0];
    unsigned int indexBuffer = buffers[1];

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 4, vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(int) * 2, 0);

    glBindVertexArray(0);

    return mesh;
}
