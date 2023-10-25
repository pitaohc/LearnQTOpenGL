#include "model.h"

using namespace std;
using namespace MODEL;

void MODEL::Model::draw(Shader& shader)
{
   for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].draw(shader);
}

void MODEL::Model::loadModel(std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    /*
    aiProcess_Triangulate 三角化处理
    aiProcess_FlipUVs 翻转UV坐标
    */
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        qCritical() << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void MODEL::Model::processNode(aiNode* node, const aiScene* scene)
{
    // 处理节点所有的网格（如果有的话）
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // 节点对象只存储了网格对应的索引
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // 接下来对它的子节点重复这一过程
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh MODEL::Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    // 处理顶点
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // 处理顶点位置、法线和纹理坐标
        QVector3D vector;
        // 顶点位置
        vector.setX(mesh->mVertices[i].x);
        vector.setY(mesh->mVertices[i].y);
        vector.setZ(mesh->mVertices[i].z);
        vertex.position = vector;
        // 顶点法线
        vector.setX(mesh->mNormals[i].x);
        vector.setY(mesh->mNormals[i].y);
        vector.setZ(mesh->mNormals[i].z);
        vertex.norm = vector;
        // 顶点纹理坐标
        if (mesh->mTextureCoords[0]) // 网格是否有纹理坐标？
        {
            QVector2D vec;
            // 一个顶点最多可以有8个不同的纹理坐标，我们假设它们都是在位置0
            vec.setX(mesh->mTextureCoords[0][i].x);
            vec.setY(mesh->mTextureCoords[0][i].y);
            vertex.texCoords = vec;
        }
        else
        {
            vertex.texCoords = QVector2D(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }
    // 处理索引
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // 网格的每个面都有3个索引，它们都指向顶点数组中的一个顶点
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // 处理材质
    if (mesh->mMaterialIndex >= 0)
    {
        //aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        //
        //vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        //textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        //vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        //textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    return Mesh(vertices, indices, textures);
}

std::vector<Texture> MODEL::Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    vector<Texture> textures;
    //textures.reserve(mat->GetTextureCount(type)); //一次性分配空间
    //for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    //{
    //    aiString path;
    //    // 获取纹理的文件路径
    //    mat->GetTexture(type, i, &path);
    //    // 检查纹理是否已经被加载过了，如果是的话，就跳过加载，确保每个纹理只被加载一次
    //    bool skip = false;
    //    for (unsigned int j = 0; j < textures_loaded.size(); j++)
    //    {
    //        if (std::strcmp(textures_loaded[j].path.data(), path.C_Str()) == 0)
    //        {
    //            textures.push_back(textures_loaded[j]);
    //            skip = true; // 一个纹理文件可能会被加载多次，确保不会对它重复加载
    //            break;
    //        }
    //    }
    //    if (!skip)
    //    {   // 如果纹理还没有被加载，则加载它
    //        Texture texture;
    //        QOpenGLTexture* tex = new QOpenGLTexture(QImage(path.C_Str()).mirrored());
    //        texture.id = tex->textureId();
    //        texture.type = typeName;
    //        texture.path = path.C_Str();
    //        textures.push_back(texture);
    //        textures_loaded.push_back(texture); // 添加到已加载的纹理中
    //    }
    //}
    return textures;
}
