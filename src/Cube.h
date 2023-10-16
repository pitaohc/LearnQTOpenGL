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
        float norm[3];
        float color[3];
        float uv[2];
        Vertex(float x, float y, float z, float nx, float ny, float nz, float r, float g, float b, float u, float v) {
            this->position[0] = x;
            this->position[1] = y;
            this->position[2] = z;
            this->norm[0] = nx;
            this->norm[1] = ny;
            this->norm[2] = nz;
            this->color[0] = r;
            this->color[1] = g;
            this->color[2] = b;
            this->uv[0] = u;
            this->uv[1] = v;
        }
        Vertex() = default;
        Vertex(const glm::vec3& pos, const glm::vec3& norm, const glm::vec3& color, const glm::vec2& uv) {
            this->position[0] = pos.x;
            this->position[1] = pos.y;
            this->position[2] = pos.z;
            this->norm[0] = norm.x;
            this->norm[1] = norm.y;
            this->norm[2] = norm.z;
            this->color[0] = color.x;
            this->color[1] = color.y;
            this->color[2] = color.z;
            this->uv[0] = uv.x;
            this->uv[1] = uv.y;
        }
    };
    class Cube
    {
    private:
        bool isInit = false;
        unsigned int VBO, EBO;
        std::vector<Vertex> vertexs;
        std::vector<unsigned int> indices;

    public:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

    public:
        unsigned int VAO;
        void create();
        void init();
        void draw(QOpenGLShaderProgram& shader);
        glm::mat4 getModel();
        Cube() :
            position(glm::vec3(0.0f, 0.0f, 0.0f)),
            rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
            scale(glm::vec3(1.0f, 1.0f, 1.0f)),
            VAO(0), VBO(0), EBO(0), isInit(false) {
            create();
        }
        Cube(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) :
            position(position),
            rotation(rotation),
            scale(scale),
            VAO(0), VBO(0), EBO(0), isInit(false) {
            create();
        }
        ~Cube()
        {
            QOpenGLContext* currentContext = QOpenGLContext::currentContext();
            QOpenGLFunctions_3_3_Core* gl = currentContext->versionFunctions<QOpenGLFunctions_3_3_Core>();
            assert (gl != nullptr);
            //释放VAO,VBO,EBO
            gl->glDeleteVertexArrays(1, &VAO);
            gl->glDeleteBuffers(1, &VBO);
            gl->glDeleteBuffers(1, &EBO);

        }
    };

}
using CUBE::Cube; //暴露Cube类
