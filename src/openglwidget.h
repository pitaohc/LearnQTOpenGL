#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <qopenglfunctions_3_3_core.h>
#include <qopenglshaderprogram.h>
#include<vector>
#include <qopengltexture.h>

struct Vertex {
    float position[3];
    float color[3];
    float uv[2];
    Vertex(float x, float y, float z, float r, float g, float b,float u,float v) {
        position[0] = x;
        position[1] = y;
        position[2] = z;
        color[0] = r;
        color[1] = g;
        color[2] = b;
        uv[0] = u;
        uv[1] = v;
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
    QOpenGLTexture* texture;
    QOpenGLTexture* texture2;
    QTimer* timer;
    QOpenGLShaderProgram shaderProgram;
    std::vector<unsigned int> VAOs, VBOs, EBOs;
    std::vector<Vertex> vertices = { // 顶点坐标和颜色
{
        +0.5f, +0.5f, +0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f // 右上角
},
{
        -0.5f, +0.5f, +0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f // 左上角
},
{
        -0.5f, -0.5f, +0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f // 左下角
},
{
        +0.5f, -0.5f, +0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f // 右下角
},
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 2, 3
    };

    void loadShaderProgram();
    void loadTexture();
public slots:
    void onTimeout();
signals:

};

#endif // OPENGLWIDGET_H
