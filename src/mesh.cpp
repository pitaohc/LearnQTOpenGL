#include "mesh.h"
using namespace std;
void MESH::Mesh::draw(QOpenGLShaderProgram& shaderProgram)
{
    assert(gl != nullptr);
    gl->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    shaderProgram.bind();
    gl->glBindTexture(GL_TEXTURE_2D, textures.front().id);
    gl->glBindVertexArray(VAO);
    gl->glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    gl->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void MESH::Mesh::setupMesh()
{
    assert(gl != nullptr);
    //生成VAO,VBO,EBO
    gl->glGenVertexArrays(1, &VAO);
    gl->glGenBuffers(1, &VBO);
    gl->glGenBuffers(1, &EBO);
    //绑定VAO和VBO对象
    gl->glBindVertexArray(VAO);
    gl->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //初始化数据
    gl->glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(decltype(vertices)::value_type),
        vertices.data(), GL_STATIC_DRAW);
    gl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(decltype(indices)::value_type),
        indices.data(), GL_STATIC_DRAW);

    //解析属性值
    // 顶点属性
    int location = 0;
    gl->glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(decltype(vertices)::value_type),
        (void*)(offsetof(Vertex, Vertex::position)));
    gl->glEnableVertexAttribArray(location);
    // 法向属性
    location = 1;
    gl->glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(decltype(vertices)::value_type),
        (void*)(offsetof(Vertex, Vertex::norm)));
    gl->glEnableVertexAttribArray(location);
    // 纹理坐标属性
    location = 2;
    gl->glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, sizeof(decltype(vertices)::value_type),
        (void*)(offsetof(Vertex, Vertex::texCoords)));
    gl->glEnableVertexAttribArray(location);

    gl->glBindBuffer(GL_ARRAY_BUFFER, 0);
    gl->glBindVertexArray(0);
}

#include <QOpenGLTexture>
Mesh* MESH::testBuildMesh()
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    Vertex v;
    v.position = { 0.5f, 0.5f, 0.0f };
    v.norm = { 0.0f, 0.0f, 1.0f };
    v.texCoords = { 1.0f, 1.0f };
    vertices.push_back(v);
    v.position = { -0.5f, 0.5f, 0.0f };
    v.norm = { 0.0f, 0.0f, 1.0f };
    v.texCoords = { 0.0f, 1.0f };
    vertices.push_back(v);
    v.position = { -0.5f, -0.5f, 0.0f };
    v.norm = { 0.0f, 0.0f, 1.0f };
    v.texCoords = { 0.0f, 0.0f };
    vertices.push_back(v);
    v.position = { 0.5f, -0.5f, 0.0f };
    v.norm = { 0.0f, 0.0f, 1.0f };
    v.texCoords = { 1.0f, 0.0f };
    vertices.push_back(v);
    indices = { 0,1,2,0,2,3 };
    vector<Texture> textures;
    QOpenGLTexture tex(QImage("../resources/texture.png"));
    textures.push_back({ tex.textureId(), "diffuse", "../resources/texture.png" });
    QOpenGLTexture tex2 = QOpenGLTexture(QImage("../resources/texture2.png"));
    textures.push_back({ tex2.textureId(), "diffuse", "../resources/texture2.png" });
    QOpenGLContext* currentContext = QOpenGLContext::currentContext();
    QOpenGLFunctions_3_3_Core* gl = currentContext->versionFunctions<QOpenGLFunctions_3_3_Core>();
    assert(gl != nullptr);
    return new Mesh(gl, vertices, indices, textures);

}
