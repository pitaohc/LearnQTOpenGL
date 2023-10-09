#include "cube.h"

using ShaderProgram = QOpenGLShaderProgram;
void CUBE::Cube::init()
{
    QOpenGLContext* currentContext = QOpenGLContext::currentContext();
    gl = currentContext->versionFunctions<QOpenGLFunctions_3_3_Core>();

    initVertexs();
    initShader();
    initTextures();
}

void CUBE::Cube::initVertexs()
{
    vertexs = {
        { 1.0f, 1.0f, 1.0f,1.0f,1.0f,1.0f,1.0f,1.0f}, // ����ǰ 0
        { 1.0f, 1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f,1.0f}, // ���Ϻ� 1
        { 1.0f,-1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f,1.0f}, // ���º� 2
        { 1.0f,-1.0f, 1.0f,1.0f,1.0f,1.0f,1.0f,1.0f}, // ����ǰ 3
        {-1.0f, 1.0f, 1.0f,1.0f,1.0f,1.0f,1.0f,1.0f}, // ����ǰ 4
        {-1.0f, 1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f,1.0f}, // ���Ϻ� 5
        {-1.0f,-1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f,1.0f}, // ���º� 6
        {-1.0f,-1.0f, 1.0f,1.0f,1.0f,1.0f,1.0f,1.0f}, // ����ǰ 7
    };
    indices = {
        0,4,3, 0,4,7,// ǰ
        1,6,2, 1,6,5,// ��
        4,6,5, 4,6,7,// ��
        0,2,1, 0,2,3,// ��
        0,5,1, 0,5,4,// ��
        2,7,3, 2,7,6,// ��
    };

    gl->glGenVertexArrays(1, &VAO);
    gl->glGenBuffers(1, &VBO);
    gl->glGenBuffers(1, &EBO);

    gl->glBindVertexArray(VAO);
    gl->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    gl->glBufferData(GL_ARRAY_BUFFER, vertexs.size() * sizeof(decltype(vertexs)::value_type),
        vertexs.data(), GL_STATIC_DRAW);
    gl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(decltype(indices)::value_type),
        indices.data(), GL_STATIC_DRAW);

    // ��������
    gl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(decltype(vertexs)::value_type),
        (void*)(offsetof(Vertex, position)));
    gl->glEnableVertexAttribArray(0);
    // ��ɫ����
    gl->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(decltype(vertexs)::value_type),
        (void*)(offsetof(Vertex, color)));
    gl->glEnableVertexAttribArray(1);
    // ������������
    gl->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(decltype(vertexs)::value_type),
        (void*)(offsetof(Vertex, uv)));
    gl->glEnableVertexAttribArray(2);

    gl->glBindBuffer(GL_ARRAY_BUFFER, 0);
    gl->glBindVertexArray(0);


#ifdef _DEBUG
    fmt::print(fmt::fg(fmt::color::green), "VAO, VBO, EBO Created Successfully!!!\n");
    fmt::print("{}, {}, {}\n", VAO, VBO, EBO);
#endif // _DEBUG


}

void CUBE::Cube::initShader()
{
    int success;
    char infoLog[512];
    std::string vertexShaderPath = "../shader/rectangle.vert";
    std::string fragmentShaderPath = "../shader/rectangle.frag";

    success = shader.addShaderFromSourceFile(
        QOpenGLShader::Vertex, vertexShaderPath.c_str());
    //success = shaderProgram.addCacheableShaderFromSourceCode(
    //    QOpenGLShader::Vertex, vertexShaderSource);
    if (!success) {
        qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
            << shader.log();
    }
    success = shader.addShaderFromSourceFile(
        QOpenGLShader::Fragment, fragmentShaderPath.c_str());
    if (!success) {
        qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
            << shader.log();
    }
    success = shader.link();
    if (!success) {
        qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
            << shader.log();
    }

#ifdef _DEBUG
    fmt::print(fmt::fg(fmt::color::green), "Shader Compiled Successfully!!!\n");
#endif // _DEBUG
    shader.bind();
    shader.setUniformValue("ourTexture", 0);
    shader.setUniformValue("ourTexture2", 1);

}

void CUBE::Cube::initTextures()
{

    textures.emplace_back(QOpenGLTexture(
        QImage("../resources/texture.png").mirrored()));
    textures.emplace_back(QOpenGLTexture(
        QImage("../resources/texture2.png").mirrored()));
}

void CUBE::Cube::draw()
{


}

