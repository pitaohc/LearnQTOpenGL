#include "openglwidget.h"
#include <qdebug.h>


OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{


}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // ������Ⱦ��ʽ
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    int success;
    char infoLog[512];
    // ������ɫ��
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,nullptr);
    glCompileShader(vertexShader);
    // �������Ƿ�ɹ�
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if (!success) {
        glGetShaderInfoLog(vertexShader,512,nullptr,infoLog);
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

    // ������ɫ������
    shaderProgram = glCreateProgram();
    // ����ɫ�����ӵ�������
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // ������ɫ������
    glLinkProgram(shaderProgram);
    // ��������Ƿ�ɹ�
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram,512,nullptr,infoLog);
        qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
    }
    // ɾ����ɫ��
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    qDebug() << "Compile Shader success!!!\n";

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(decltype(vertices)::value_type), vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(decltype(indices)::value_type), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    qDebug() << "Create VAO success!!!\n";
}

void OpenGLWidget::resizeGL(int w, int h)
{
}

void OpenGLWidget::paintGL()
{
    glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES,0,3);
    glDrawElements(GL_TRIANGLES, indices.size() , GL_UNSIGNED_INT, 0);
}
