#include "cube.h"

using ShaderProgram = QOpenGLShaderProgram;
using namespace CUBE;
void Cube::init()
{
    /*
    不能在initializeOpenGLFunctions()调用前调用，会导致错误，因此将init函数与构造函数分开，
    这样允许声明在类中
    */
    QOpenGLContext* currentContext = QOpenGLContext::currentContext();
    gl = currentContext->versionFunctions<QOpenGLFunctions_3_3_Core>();

    initVertexs();
    initShader();
    initTextures();
}

void Cube::initVertexs()
{
    vertexs = {
        //前
        { 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f}, //前右上
        {-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f}, //前左上
        {-0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f}, //前左下
        { 0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f}, //前右下
        //后
        { 0.5f, 0.5f,-0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f}, //后右上
        {-0.5f, 0.5f,-0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f}, //后左上
        {-0.5f,-0.5f,-0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f}, //后左下
        { 0.5f,-0.5f,-0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f}, //后右下
        //左
        {-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}, //前左上
        {-0.5f,-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}, //前左下
        {-0.5f,-0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}, //后左下
        {-0.5f, 0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}, //后左上
        //右
        { 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f}, //前右上
        { 0.5f,-0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f}, //前右下
        { 0.5f,-0.5f,-0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f}, //后右下
        { 0.5f, 0.5f,-0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f}, //后右上
        //上
        { 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f}, //前右上
        {-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f}, //前左上
        {-0.5f, 0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f}, //后左上
        { 0.5f, 0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f}, //后右上
        //下
        {-0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f}, //前左下
        { 0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f}, //前右下
        {-0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f}, //后左下
        { 0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f}, //后右下
    };
    indices = {
        0,1,2 , 0,2,3, //前
        6,5,4 , 7,6,4, //后
        10,9,8, 11,10,8, //左
        12,13,14, 12,14,15, //右
        18,17,16, 19,18,16, //上
        22,21,20, 21,22,23, //下
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

    // 顶点属性
    gl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(decltype(vertexs)::value_type),
        (void*)(offsetof(Vertex, position)));
    gl->glEnableVertexAttribArray(0);
    // 颜色属性
    gl->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(decltype(vertexs)::value_type),
        (void*)(offsetof(Vertex, color)));
    gl->glEnableVertexAttribArray(1);
    // 纹理坐标属性
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

void Cube::initShader()
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

void Cube::initTextures()
{
    textures.emplace_back(std::make_unique<QOpenGLTexture>(
        QImage("../resources/texture.png").mirrored()));
    textures.emplace_back(std::make_unique<QOpenGLTexture>(
        QImage("../resources/texture2.png").mirrored()));
}

void Cube::updateModel()
{
    model = glm::mat4(1.0f);
    //根据rotate旋转model矩阵
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // 绕x轴旋转
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // 绕y轴旋转
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // 绕z轴旋转
    //根据scale缩放model矩阵
    model = glm::scale(model, scale);
    //根据position移动model矩阵
    model = glm::translate(model, position);
}

void Cube::draw()
{
    gl->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    shader.bind();
    updateModel();

    gl->glUniformMatrix4fv(shader.uniformLocation("model"), 1, GL_FALSE, &model[0][0]);
    gl->glUniformMatrix4fv(shader.uniformLocation("projection"), 1, GL_FALSE, &projection[0][0]);
    gl->glUniformMatrix4fv(shader.uniformLocation("view"), 1, GL_FALSE, &view[0][0]);
    textures[0]->bind(0);
    textures[0]->generateMipMaps();
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    textures[1]->bind(1);
    textures[1]->generateMipMaps();
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    gl->glBindVertexArray(VAO);
    gl->glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    gl->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

