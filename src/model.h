#pragma once
//stl
#include <vector>
#include <string>
//assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
//qt
#include <QOpenGLShader>
#include <QOpenGLFunctions_3_3_Core>
//gl

//fmt
#ifdef _DEBUG
#include <fmt/format.h>
#include <fmt/color.h>
#include <fmt/ranges.h>
#endif // _DEBUG
//local
#include "mesh.h"
namespace MODEL
{
using Shader = QOpenGLShaderProgram;
using Texture = MESH::Texture;
using Mesh = MESH::Mesh;
using Vertex = MESH::Vertex;
class Model
{
public: //构造函数
    Model(const char* path)
    {
        loadModel(std::string(path));
    }
    Model() = default;
public: //成员函数
    void draw(Shader& shader);
    void loadModel(std::string& path);
public:
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
private:
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};
}
using MODEL::Model;

