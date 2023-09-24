#include "openglwidget.h"
#include <qdebug.h>
#include <string>

#include <QtCore/QTimer>
#include <QtCore/QTime>
#ifdef _DEBUG
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fmt/color.h>
#endif // _DEBUG
OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    timer = new QTimer(this); //timer只负责触发onTimeout()函数，不负责获取时间
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start(1000 / 256);
}

OpenGLWidget::~OpenGLWidget()
{
    glDeleteVertexArrays(VAOs.size(), VAOs.data());
    VAOs.clear();
    glDeleteBuffers(VBOs.size(), VBOs.data());
    VBOs.clear();
    glDeleteBuffers(EBOs.size(), EBOs.data());
    EBOs.clear();
    shaderProgram.release();
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // 设置渲染方式
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    initShaderProgram();

}

void OpenGLWidget::resizeGL(int w, int h)
{
}

void OpenGLWidget::paintGL()
{
    glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram.bind();
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
    std::string vertexShaderPath = "../shader/rectangle.vert";
    std::string fragmentShaderPath = "../shader/rectangle.frag";

    success = shaderProgram.addShaderFromSourceFile(
        QOpenGLShader::Vertex, vertexShaderPath.c_str());
    //success = shaderProgram.addCacheableShaderFromSourceCode(
    //    QOpenGLShader::Vertex, vertexShaderSource);
    if (!success) {
        qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" 
            << shaderProgram.log();
    }
    success = shaderProgram.addShaderFromSourceFile(
        QOpenGLShader::Fragment, fragmentShaderPath.c_str());
    if (!success) {
        qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
            << shaderProgram.log();
    }
    success = shaderProgram.link();
    if (!success) {
        qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" 
            << shaderProgram.log();
    }

#ifdef _DEBUG
    fmt::print(fmt::fg(fmt::color::green), "Shader Compiled Successfully!!!\n");
#endif // _DEBUG
}

void OpenGLWidget::setNewRect(float dx, float dy, float dz)
{
    makeCurrent();
    unsigned int VAO, VBO, EBO;
    std::vector<float> vertices = this->vertices;
    int step = 6; //x,y,z,r,g,b
    for (size_t i = 0; i < vertices.size()/ step; i++)
    {
        vertices[i*step+0] += dx;
        vertices[i*step+1] += dy;
        vertices[i*step+2] += dz;
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, step * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, step * sizeof(float), (void*)(3* sizeof(decltype(indices)::value_type)));
    glEnableVertexAttribArray(1);

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

void OpenGLWidget::onTimeout() {
    //int msesecondTime = QTime::currentTime().msecsSinceStartOfDay();
    //float blueColor = sin(msesecondTime / 789) / 2.0f + 0.5f;
//    static float blueColor = 0.0f;
//    static float step = 0.01f;
//
//    blueColor += step;
//    if (blueColor > 1.0f) {
//        step = -0.01f;
//        blueColor = 1.0f - 0.001f;
//    }
//    else if (blueColor < 0.0f) {
//        step = 0.01f;
//        blueColor = 0.0f + 0.001f;
//    }
//#ifdef _DEBUG
//    fmt::print(fmt::fg(
//        fmt::rgb((1.0f - blueColor) * 256, 0, blueColor * 256)),
//        "BlueColor value is {:.2}, step is {:+.2}\n",blueColor, step);
//#endif // _DEBUG
//
//
//    makeCurrent();
//    shaderProgram.setUniformValue("ourColor", 
//        1.0f - blueColor, 0.0f, blueColor,1.0f);
//    doneCurrent();
//    update();

}