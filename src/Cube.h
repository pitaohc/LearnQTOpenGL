#pragma once
#include <vector>
#include <string>

#include <glm/glm.hpp>

#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <QOpenGLFunctions_3_3_Core>
#ifdef _DEBUG
#include <fmt/format.h>
#include <fmt/color.h>
#include <fmt/ranges.h>
#endif // _DEBUG
namespace CUBE {
    struct Vertex {
        float position[3];
        float color[3];
        float uv[2];
        Vertex(float x, float y, float z, float r, float g, float b, float u, float v) {
            position[0] = x;
            position[1] = y;
            position[2] = z;
            color[0] = r;
            color[1] = g;
            color[2] = b;
            uv[0] = u;
            uv[1] = v;
        }
    };
    class Cube
    {
    private:
        unsigned int VBO, EBO;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
    public:
        unsigned int VAO;
        void draw();
    };

}
using CUBE::Cube;
