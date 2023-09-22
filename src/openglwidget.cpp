#include "openglwidget.h"
#include <qdebug.h>

#ifdef _DEBUG
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fmt/color.h>
#endif // _DEBUG
OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    shaderProgram = 0;

}

OpenGLWidget::~OpenGLWidget()
{
    glDeleteVertexArrays(VAOs.size(), VAOs.data());
    VAOs.clear();
    glDeleteBuffers(VBOs.size(), VBOs.data());
    VBOs.clear();
    glDeleteBuffers(EBOs.size(), EBOs.data());
    EBOs.clear();
    glDeleteProgram(shaderProgram);
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // 设置渲染方式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    initShaderProgram();

}

void OpenGLWidget::resizeGL(int w, int h)
{
}

void OpenGLWidget::paintGL()
{
    glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);
    for (size_t i = 0; i < VAOs.size(); i++)
    {
        glBindVertexArray(VAOs[i]);
        glDrawElements(GL_TRIANGLES, indices.size() , GL_UNSIGNED_INT, 0);

    }
    //for (const unsigned int VAO : VAOs) {
    //    glBindVertexArray(VAO);
    //    glDrawElements(GL_TRIANGLES, indices.size() , GL_UNSIGNED_INT, 0);
    //}
}

void OpenGLWidget::initShaderProgram()
{
    int success;
    char infoLog[512];
    // 编译着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    // 检查编译是否成功
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
    }

    // 创建着色器程序
    shaderProgram = glCreateProgram();
    // 将着色器附加到程序上
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // 链接着色器程序
    glLinkProgram(shaderProgram);
    // 检查链接是否成功
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
    }
    // 删除着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
#ifdef _DEBUG
    fmt::print(fmt::fg(fmt::color::green), "Shader Compiled Successfully!!!\n");
#endif // _DEBUG
}

void OpenGLWidget::setNewRect(float dx, float dy, float dz)
{
    makeCurrent();
    unsigned int VAO, VBO, EBO;
    std::vector<float> vertices = this->vertices;
    for (size_t i = 0; i < vertices.size()/3; i++)
    {
        vertices[i*3+0] += dx;
        vertices[i*3+1] += dy;
        vertices[i*3+2] += dz;
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    VAOs.emplace_back(VAO);
    VBOs.emplace_back(VBO);
    EBOs.emplace_back(EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(decltype(vertices)::value_type), vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(decltype(indices)::value_type), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    doneCurrent();
    update();
#ifdef _DEBUG
    fmt::print(fmt::fg(fmt::color::green), "VAO Created Successfully!!!\n");
    fmt::print("{}\n", VAOs);
    fmt::print(fmt::fg(fmt::color::green), "VBO Created Successfully!!!\n");
    fmt::print("{}\n", VBOs);
    fmt::print(fmt::fg(fmt::color::green), "EBO Created Successfully!!!\n");
    fmt::print("{}\n", EBOs);
#endif // _DEBUG

}

void OpenGLWidget::cleanAllRects()
{
#ifdef _DEBUG
    fmt::print(fmt::fg(fmt::color::yellow), "VAOs Cleaned Successfully!!!\n");
    fmt::print("{}\n", VAOs);
    fmt::print(fmt::fg(fmt::color::yellow), "VBOs Cleaned Successfully!!!\n");
    fmt::print("{}\n", VBOs);
    fmt::print(fmt::fg(fmt::color::yellow), "EBOs Cleaned Successfully!!!\n");
    fmt::print("{}\n", EBOs);
#endif // _DEBUG

    makeCurrent();
    glDeleteVertexArrays(VAOs.size(), VAOs.data());   
    VAOs.clear();                                     
    glDeleteBuffers(VBOs.size(), VBOs.data());        
    VBOs.clear();                                     
    glDeleteBuffers(EBOs.size(), EBOs.data());        
    EBOs.clear();
    doneCurrent();
    update();
}
