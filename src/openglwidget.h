#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H
//QT��
#include <QWidget>
#include <QOpenGLWidget>
#include <qopenglfunctions_3_3_core.h>
#include <qopenglshaderprogram.h>
#include <qopengltexture.h>
//STL��
#include <vector>
#include <set>
//GLM��
#include <glm/matrix.hpp>
#include <glm/glm.hpp>
//�Զ����
#include "camera.h"
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
    void keyPressEvent(QKeyEvent* event) override;
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
    std::vector<Vertex> vertices = { // �����������ɫ
{
        +0.5f, +0.5f, +0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f // ���Ͻ�
},
{
        -0.5f, +0.5f, +0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f // ���Ͻ�
},
{
        -0.5f, -0.5f, +0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f // ���½�
},
{
        +0.5f, -0.5f, +0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f // ���½�
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
