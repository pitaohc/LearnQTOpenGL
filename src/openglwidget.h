#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <qopenglfunctions_3_3_core.h>
#include <qopenglshaderprogram.h>
#include<vector>

struct Vertex {
    float position[3];
    float color[3];
    Vertex(float x, float y, float z, float r, float g, float b) {
        position[0] = x;
        position[1] = y;
        position[2] = z;
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }
};

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget* parent = nullptr);
    ~OpenGLWidget();
    void setNewRect(float dx, float dy, float dz);
    void cleanAllRects();
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:
    QTimer* timer;
    QOpenGLShaderProgram shaderProgram;
    std::vector<unsigned int> VAOs, VBOs, EBOs;
    std::vector<Vertex> vertices = { // �����������ɫ
{
        +0.5f, +0.5f, +0.0f, 1.0f, 0.0f, 0.0f // ���Ͻ�
},
{
        -0.5f, +0.5f, +0.0f, 0.0f, 0.0f, 0.0f // ���Ͻ�
},
{
        -0.5f, -0.5f, +0.0f, 0.0f, 0.0f, 1.0f // ���½�
},
{
        +0.5f, -0.5f, +0.0f, 1.0f, 0.0f, 1.0f // ���½�
},
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        //0, 2, 3
    };

    void initShaderProgram();
public slots:
    void onTimeout();
signals:

};

#endif // OPENGLWIDGET_H
