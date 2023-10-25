#include "mesh.h"
using namespace std;
void MESH::Mesh::draw(QOpenGLShaderProgram& shaderProgram)
{
    assert(gl != nullptr);
    gl->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    shaderProgram.bind();

    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (size_t i = 0; i < textures.size(); i++)
    {
        int index;
        const string& type = textures[i].type;
        if (type == "texture_diffuse")
        {
            index = diffuseNr++;
        }
        else if (type == "texture_specular")
        {
            index = specularNr++;
        }
        string finalname = "material." + type + std::to_string(index);
        gl->glActiveTexture(GL_TEXTURE0 + i); // 在绑定之前激活相应的纹理单元
        gl->glUniform1i(shaderProgram.uniformLocation(finalname.c_str()), i); // 绑定shader对象到对应的纹理单元
        gl->glBindTexture(GL_TEXTURE_2D, textures[i].id); // 提供texture
    }


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
    vector<Vertex> vertexs;
    vector<unsigned int> indices;
    vertexs = {
        //前
        Vertex(QVector3D(+0.5f, 0.5f, 0.5f),QVector3D(1.0f, 1.0f, 1.0f),QVector2D(1.0f,1.0f)),//前右上
        Vertex(QVector3D(-0.5f, 0.5f, 0.5f),QVector3D(1.0f, 1.0f, 1.0f),QVector2D(0.0f,1.0f)),//前左上
        Vertex(QVector3D(-0.5f,-0.5f, 0.5f),QVector3D(1.0f, 1.0f, 1.0f),QVector2D(0.0f,0.0f)),//前左下
        Vertex(QVector3D(+0.5f,-0.5f, 0.5f),QVector3D(1.0f, 1.0f, 1.0f),QVector2D(1.0f,0.0f)),//前右下
        //后
        Vertex(QVector3D(-0.5f, 0.5f,-0.5f),QVector3D(0.0f, 1.0f, 1.0f),QVector2D(1.0f,1.0f)),//后左上
        Vertex(QVector3D(+0.5f, 0.5f,-0.5f),QVector3D(0.0f, 1.0f, 1.0f),QVector2D(0.0f,1.0f)),//后右上
        Vertex(QVector3D(+0.5f,-0.5f,-0.5f),QVector3D(0.0f, 1.0f, 1.0f),QVector2D(0.0f,0.0f)),//后右下
        Vertex(QVector3D(-0.5f,-0.5f,-0.5f),QVector3D(0.0f, 1.0f, 1.0f),QVector2D(1.0f,0.0f)),//后左下
        //左
        Vertex(QVector3D(-0.5f, 0.5f, 0.5f),QVector3D(0.0f, 0.0f, 1.0f),QVector2D(1.0f,1.0f)),//前左上
        Vertex(QVector3D(-0.5f, 0.5f,-0.5f),QVector3D(0.0f, 0.0f, 1.0f),QVector2D(0.0f,1.0f)),//后左上
        Vertex(QVector3D(-0.5f,-0.5f,-0.5f),QVector3D(0.0f, 0.0f, 1.0f),QVector2D(0.0f,0.0f)),//后左下
        Vertex(QVector3D(-0.5f,-0.5f, 0.5f),QVector3D(0.0f, 0.0f, 1.0f),QVector2D(1.0f,0.0f)),//前左下
        //右
        Vertex(QVector3D(0.5f, 0.5f,-0.5f),QVector3D(1.0f, 1.0f, 0.0f),QVector2D(1.0f,1.0f)),//后右上
        Vertex(QVector3D(0.5f, 0.5f, 0.5f),QVector3D(1.0f, 1.0f, 0.0f),QVector2D(0.0f,1.0f)),//前右上
        Vertex(QVector3D(0.5f,-0.5f, 0.5f),QVector3D(1.0f, 1.0f, 0.0f),QVector2D(0.0f,0.0f)),//前右下
        Vertex(QVector3D(0.5f,-0.5f,-0.5f),QVector3D(1.0f, 1.0f, 0.0f),QVector2D(1.0f,0.0f)),//后右下
        //上
        Vertex(QVector3D(+0.5f, 0.5f,-0.5f),QVector3D(0.0f, 1.0f, 0.0f),QVector2D(1.0f,1.0f)),//后右上
        Vertex(QVector3D(-0.5f, 0.5f,-0.5f),QVector3D(0.0f, 1.0f, 0.0f),QVector2D(0.0f,1.0f)),//后左上
        Vertex(QVector3D(-0.5f, 0.5f, 0.5f),QVector3D(0.0f, 1.0f, 0.0f),QVector2D(0.0f,0.0f)),//前左上
        Vertex(QVector3D(+0.5f, 0.5f, 0.5f),QVector3D(0.0f, 1.0f, 0.0f),QVector2D(1.0f,0.0f)),//前右上
        //下
        Vertex(QVector3D(+0.5f,-0.5f, 0.5f),QVector3D(1.0f, 0.0f, 1.0f),QVector2D(1.0f,1.0f)),//前右下
        Vertex(QVector3D(-0.5f,-0.5f, 0.5f),QVector3D(1.0f, 0.0f, 1.0f),QVector2D(0.0f,1.0f)),//前左下
        Vertex(QVector3D(-0.5f,-0.5f,-0.5f),QVector3D(1.0f, 0.0f, 1.0f),QVector2D(0.0f,0.0f)),//后左下
        Vertex(QVector3D(+0.5f,-0.5f,-0.5f),QVector3D(1.0f, 0.0f, 1.0f),QVector2D(1.0f,0.0f)),//后右下
    };
    indices = {
        0,1,2 , 0,2,3, //前
        4,5,6 , 4,6,7, //后
        8,9,10, 8,10,11, //左
        12,13,14, 12,14,15, //右
        16,17,18, 16,18,19, //上
        20,21,22,20,22,23, //下
    };

    vector<Texture> textures;
    QOpenGLTexture* tex;
    tex = new QOpenGLTexture(QImage("../resources/texture.png").mirrored());
#ifdef _DEBUG
    fmt::print("texture {}: {}x{}px\n", tex->textureId(), tex->width(), tex->height());
#endif // _DEBUG
    textures.push_back({ tex->textureId(), "texture_diffuse", "../resources/texture.png" });
    tex = new QOpenGLTexture(QImage("../resources/texture2.png").mirrored());
#ifdef _DEBUG
    fmt::print("texture {}: {}x{}px\n", tex->textureId(), tex->width(), tex->height());
#endif // _DEBUG
    textures.push_back({ tex->textureId(), "texture_diffuse", "../resources/texture2.png" });
    QOpenGLContext* currentContext = QOpenGLContext::currentContext();
    QOpenGLFunctions_3_3_Core* gl = currentContext->versionFunctions<QOpenGLFunctions_3_3_Core>();
    assert(gl != nullptr);
    return new Mesh(gl, vertexs, indices, textures);
}
