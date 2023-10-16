#include "cube.h"
using ShaderProgram = QOpenGLShaderProgram;
using namespace CUBE;
void Cube::create()
{
    vertexs = {
        //前
        Vertex(glm::vec3(+0.5f, 0.5f, 0.5f),glm::vec3(0.0f,0.0f, 1.0f),glm::vec3(1.0f, 1.0f, 1.0f),glm::vec2(1.0f,1.0f)),//前右上
        Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),glm::vec3(0.0f,0.0f, 1.0f),glm::vec3(1.0f, 1.0f, 1.0f),glm::vec2(0.0f,1.0f)),//前左上
        Vertex(glm::vec3(-0.5f,-0.5f, 0.5f),glm::vec3(0.0f,0.0f, 1.0f),glm::vec3(1.0f, 1.0f, 1.0f),glm::vec2(0.0f,0.0f)),//前左下
        Vertex(glm::vec3(+0.5f,-0.5f, 0.5f),glm::vec3(0.0f,0.0f, 1.0f),glm::vec3(1.0f, 1.0f, 1.0f),glm::vec2(1.0f,0.0f)),//前右下
        //后
        Vertex(glm::vec3(-0.5f, 0.5f,-0.5f),glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.0f, 1.0f, 1.0f),glm::vec2(0.0f,1.0f)),//后左上
        Vertex(glm::vec3(+0.5f, 0.5f,-0.5f),glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.0f, 1.0f, 1.0f),glm::vec2(1.0f,1.0f)),//后右上
        Vertex(glm::vec3(+0.5f,-0.5f,-0.5f),glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.0f, 1.0f, 1.0f),glm::vec2(1.0f,0.0f)),//后右下
        Vertex(glm::vec3(-0.5f,-0.5f,-0.5f),glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.0f, 1.0f, 1.0f),glm::vec2(0.0f,0.0f)),//后左下
        //左
        Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),glm::vec3(-1.0f,0.0f,0.0f),glm::vec3(0.0f, 0.0f, 1.0f),glm::vec2(1.0f,1.0f)),//前左上
        Vertex(glm::vec3(-0.5f, 0.5f,-0.5f),glm::vec3(-1.0f,0.0f,0.0f),glm::vec3(0.0f, 0.0f, 1.0f),glm::vec2(1.0f,0.0f)),//后左上
        Vertex(glm::vec3(-0.5f,-0.5f,-0.5f),glm::vec3(-1.0f,0.0f,0.0f),glm::vec3(0.0f, 0.0f, 1.0f),glm::vec2(0.0f,0.0f)),//后左下
        Vertex(glm::vec3(-0.5f,-0.5f, 0.5f),glm::vec3(-1.0f,0.0f,0.0f),glm::vec3(0.0f, 0.0f, 1.0f),glm::vec2(0.0f,1.0f)),//前左下
        //右
        Vertex(glm::vec3(0.5f, 0.5f,-0.5f),glm::vec3(1.0f,0.0f,0.0f),glm::vec3(1.0f, 1.0f, 0.0f),glm::vec2(0.0f,1.0f)),//后右上
        Vertex(glm::vec3(0.5f, 0.5f, 0.5f),glm::vec3(1.0f,0.0f,0.0f),glm::vec3(1.0f, 1.0f, 0.0f),glm::vec2(1.0f,1.0f)),//前右上
        Vertex(glm::vec3(0.5f,-0.5f, 0.5f),glm::vec3(1.0f,0.0f,0.0f),glm::vec3(1.0f, 1.0f, 0.0f),glm::vec2(1.0f,0.0f)),//前右下
        Vertex(glm::vec3(0.5f,-0.5f,-0.5f),glm::vec3(1.0f,0.0f,0.0f),glm::vec3(1.0f, 1.0f, 0.0f),glm::vec2(0.0f,0.0f)),//后右下

        //上
        Vertex(glm::vec3(+0.5f, 0.5f,-0.5f),glm::vec3(0.0f,1.0f,0.0f),glm::vec3(0.0f, 1.0f, 0.0f),glm::vec2(0.0f,0.0f)),//后右上
        Vertex(glm::vec3(-0.5f, 0.5f,-0.5f),glm::vec3(0.0f,1.0f,0.0f),glm::vec3(0.0f, 1.0f, 0.0f),glm::vec2(1.0f,0.0f)),//后左上
        Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),glm::vec3(0.0f,1.0f,0.0f),glm::vec3(0.0f, 1.0f, 0.0f),glm::vec2(1.0f,1.0f)),//前左上
        Vertex(glm::vec3(+0.5f, 0.5f, 0.5f),glm::vec3(0.0f,1.0f,0.0f),glm::vec3(0.0f, 1.0f, 0.0f),glm::vec2(0.0f,1.0f)),//前右上
        //下
        Vertex(glm::vec3(+0.5f,-0.5f, 0.5f),glm::vec3(0.0f,-1.0f,0.0f),glm::vec3(1.0f, 0.0f, 1.0f),glm::vec2(1.0f,0.0f)),//前右下
        Vertex(glm::vec3(-0.5f,-0.5f, 0.5f),glm::vec3(0.0f,-1.0f,0.0f),glm::vec3(1.0f, 0.0f, 1.0f),glm::vec2(0.0f,0.0f)),//前左下
        Vertex(glm::vec3(-0.5f,-0.5f,-0.5f),glm::vec3(0.0f,-1.0f,0.0f),glm::vec3(1.0f, 0.0f, 1.0f),glm::vec2(1.0f,1.0f)),//后左下
        Vertex(glm::vec3(+0.5f,-0.5f,-0.5f),glm::vec3(0.0f,-1.0f,0.0f),glm::vec3(1.0f, 0.0f, 1.0f),glm::vec2(0.0f,1.0f)),//后右下

        //{-0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f}, //前左下
        //{ 0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f}, //前右下
        //{-0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f}, //后左下
        //{ 0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f}, //后右下
    };
    indices = {
        0,1,2 , 0,2,3, //前
        4,5,6 , 4,6,7, //后
        8,9,10, 8,10,11, //左
        12,13,14, 12,14,15, //右
        16,17,18, 16,18,19, //上
        20,21,22,20,22,23, //下
    };

}

void Cube::init()
{
    /*
    不能在initializeOpenGLFunctions()调用前调用，会导致错误，因此将init函数与构造函数分开，
    这样允许声明在类中
    */
    QOpenGLContext* currentContext = QOpenGLContext::currentContext();
    QOpenGLFunctions_3_3_Core* gl = currentContext->versionFunctions<QOpenGLFunctions_3_3_Core>();
    assert(gl != nullptr);

    gl->glGenVertexArrays(1, &VAO);// VAO 顶点数组对象
    gl->glGenBuffers(1, &VBO); // VBO 顶点缓冲对象
    gl->glGenBuffers(1, &EBO); // EBO 索引缓冲对象

    gl->glBindVertexArray(VAO);
    gl->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    gl->glBufferData(GL_ARRAY_BUFFER, vertexs.size() * sizeof(decltype(vertexs)::value_type),
        vertexs.data(), GL_STATIC_DRAW);
    gl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(decltype(indices)::value_type),
        indices.data(), GL_STATIC_DRAW);

    // 顶点属性
    int location = 0;
    gl->glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(decltype(vertexs)::value_type),
        (void*)(offsetof(Vertex, Vertex::position)));
    gl->glEnableVertexAttribArray(location);
    // 法向属性
    location = 1;
    gl->glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(decltype(vertexs)::value_type),
        (void*)(offsetof(Vertex, Vertex::norm)));
    gl->glEnableVertexAttribArray(location);
    // 颜色属性
    location = 2;
    gl->glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(decltype(vertexs)::value_type),
        (void*)(offsetof(Vertex, Vertex::color)));
    gl->glEnableVertexAttribArray(location);
    // 纹理坐标属性
    location = 3;
    gl->glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, sizeof(decltype(vertexs)::value_type),
        (void*)(offsetof(Vertex, Vertex::uv)));
    gl->glEnableVertexAttribArray(location);

    gl->glBindBuffer(GL_ARRAY_BUFFER, 0);
    gl->glBindVertexArray(0);


#ifdef _DEBUG
    fmt::print(fmt::fg(fmt::color::green), "VAO, VBO, EBO Created Successfully!!!\n");
    fmt::print("{}, {}, {}\n", VAO, VBO, EBO);
#endif // _DEBUG
    isInit = true;

}


void Cube::draw(QOpenGLShaderProgram& shaderProgram)
{
    /*
    不能在initializeOpenGLFunctions()调用前调用，会导致错误，因此将init函数与构造函数分开，
    这样允许声明在类中
    */
    QOpenGLContext* currentContext = QOpenGLContext::currentContext();
    QOpenGLFunctions_3_3_Core* gl = currentContext->versionFunctions<QOpenGLFunctions_3_3_Core>();
    assert(gl != nullptr);
    if (!isInit) {
        init();
    }

    gl->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    shaderProgram.bind();

    gl->glBindVertexArray(VAO);
    gl->glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    gl->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

glm::mat4 CUBE::Cube::getModel()
{

    glm::mat4 rotatMat = glm::mat4(1.0f);
    glm::mat4 transMat = glm::mat4(1.0f);
    glm::mat4 scaleMat = glm::mat4(1.0f);
    //rotate
    rotatMat = glm::rotate(rotatMat, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotatMat = glm::rotate(rotatMat, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotatMat = glm::rotate(rotatMat, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    //translate
    transMat = glm::translate(transMat, position);
    //scale
    scaleMat = glm::scale(scaleMat, scale);
    return transMat * rotatMat * scaleMat;
}

