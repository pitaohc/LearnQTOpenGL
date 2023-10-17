#pragma once
//std
#include <vector>
#include <string>
//assimp

//glm

//qt
#include <QOpenGLShader>
#include <QOpenGLFunctions_3_3_Core>
//fmt
#ifdef _DEBUG
#include <fmt/format.h>
#include <fmt/color.h>
#include <fmt/ranges.h>
#endif //_DEBUG
namespace MESH
{
    struct Vertex {
        QVector3D position;
        QVector3D norm;
        QVector2D texCoords;
    };
    struct Texture {
        unsigned int id;  //纹理对象ID
        std::string type; //贴图类型：漫反射、镜面光等
        std::string path; //纹理路径
    };
    class Mesh {
    public:
        //构造函数
        Mesh(QOpenGLFunctions_3_3_Core* glFuns,
            std::vector<Vertex> vertices,
            std::vector<unsigned int> indices,
            std::vector<Texture> textures) :
            gl(glFuns),
            vertices(vertices), indices(indices), textures(textures),
            VAO(0), VBO(0), EBO(0) {
            setupMesh();
        }
    public:
        //元数据
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
        void draw(QOpenGLShaderProgram& shaderProgram);
    private:
        //渲染数据
        unsigned int VAO, VBO, EBO;
        void setupMesh();
        QOpenGLFunctions_3_3_Core* gl;
    };
    Mesh* testBuildMesh();
}

using MESH::Mesh; // 暴露Mesh类

