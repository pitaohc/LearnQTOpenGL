#pragma once
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
        void initVertexs();
        void initShader();
        void initTextures();
        void updateModel();
    public:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        glm::mat4 model, view, projection;
    public:
        unsigned int VAO;
        void init();
        void draw();
        Cube() :
            position(glm::vec3(0.0f, 0.0f, 0.0f)),
            rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
            scale(glm::vec3(50.0f, 50.0f, 50.0f)),
            VAO(0), VBO(0), EBO(0),
            model(glm::mat4(1.0f)),
            view(glm::mat4(1.0f)),
            projection(glm::mat4(1.0f)),
            gl(nullptr) {

        }
        Cube(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) :
            position(position),
            rotation(rotation),
            scale(scale),
            VAO(0), VBO(0), EBO(0),
            gl(nullptr),
            model(glm::mat4(1.0f)),
            view(glm::mat4(1.0f)),
            projection(glm::mat4(1.0f)) {

        }
    };

}
using CUBE::Cube; //暴露Cube类
