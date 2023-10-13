#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H
//QT库
#include <QWidget>
#include <QOpenGLWidget>
#include <qopenglfunctions_3_3_core.h>
#include <qopenglshaderprogram.h>
#include <qopengltexture.h>
#include <QCoreApplication>
//STL库
#include <vector>
#include <set>
//GLM库
#include <glm/matrix.hpp>
#include <glm/glm.hpp>
//自定义库
#include "camera.h"
struct Vertex {
    float position[3];
    float color[3];
    float uv[2];
    Vertex(float x, float y, float z, float r, float g, float b, float u, float v) {
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
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:
    Camera camera;
    float deltaTime = 0.0f;
    float mixValue = 0.0f;
    glm::mat4 model;
    QOpenGLTexture* texture;
    QOpenGLTexture* texture2;
    std::unique_ptr<QTimer> timer;

    QOpenGLShaderProgram shaderProgram;
    std::vector<unsigned int> VAOs, VBOs, EBOs;
    std::vector<Vertex> vertices = { // 顶点坐标和颜色
        //后面
        { 50.0f, 50.0f, 50.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
        {-50.0f, 50.0f, 50.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
        {-50.0f,-50.0f, 50.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
        { 50.0f,-50.0f, 50.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
        //前面
        {-50.0f,-50.0f,-50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f},
        {-50.0f, 50.0f,-50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f},
        { 50.0f, 50.0f,-50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f},
        { 50.0f,-50.0f,-50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f},
        //左面
        {-50.0f, 50.0f, 50.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f},
        {-50.0f, 50.0f,-50.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f},
        {-50.0f,-50.0f,-50.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f},
        {-50.0f,-50.0f, 50.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f},
        //右面
        { 50.0f,-50.0f,-50.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
        { 50.0f, 50.0f,-50.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
        { 50.0f, 50.0f, 50.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
        { 50.0f,-50.0f, 50.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
        //上面
        { 50.0f, 50.0f, 50.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f},
        { 50.0f, 50.0f,-50.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f},
        {-50.0f, 50.0f,-50.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f},
        {-50.0f, 50.0f, 50.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f},
        //下面
        {-50.0f,-50.0f,-50.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
        { 50.0f,-50.0f,-50.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
        { 50.0f,-50.0f, 50.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
        {-50.0f,-50.0f, 50.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
    };

    std::vector<unsigned int> indices = {
         0, 1, 2, 0, 2, 3,
         4, 5, 6, 4, 6, 7,
         8, 9,10, 8,10,11,
        12,13,14,12,14,15,
        16,17,18,16,18,19,
        20,21,22,20,22,23,
    };

    void loadShaderProgram();
    void loadTexture();
private:
    std::set<int> pressedKeys;
    std::unique_ptr<QTimer> timerKey;
public slots:
    void onTimeout();
    void onTimeoutKey();
signals:

};

#endif // OPENGLWIDGET_H
