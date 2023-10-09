#pragma once
#include <vector>
#include <string>

#include <glm/glm.hpp>

#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <QOpenGLContext>
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
        std::vector<Vertex> vertexs;
        std::vector<unsigned int> indices;
        std::vector<std::unique_ptr<QOpenGLTexture>> textures;
        QOpenGLShaderProgram shader;
        QOpenGLFunctions_3_3_Core* gl;
        void init();
        void initVertexs();
        void initShader();
        void initTextures();

    public:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
    public:
        unsigned int VAO;
        void draw();
        Cube():
            position(glm::vec3(0.0f, 0.0f, 0.0f)),
            rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
            scale(glm::vec3(1.0f, 1.0f, 1.0f)){
            init();
        }
        Cube(const glm::vec3& position,const glm::vec3& rotation, const glm::vec3& scale):
            position(position),
            rotation(rotation),
            scale(scale){
            init();
        }
    };

}
using CUBE::Cube;
