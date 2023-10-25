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
#include "cube.h"
#include "mesh.h"
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
    void mousePressEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:
    Mesh* mesh;
    float lastX, lastY;
    Cube lightCube;
    QOpenGLTexture* texture;
    QOpenGLTexture* texture_spec;
    std::vector<Cube> cubes;
    QOpenGLShaderProgram lightShaderProgram;
    QOpenGLShaderProgram cubeSaderProgram;
    QOpenGLShaderProgram meshShaderProgram;
    Camera camera;
    float deltaTime = 0.0f;

    std::unique_ptr<QTimer> timer;


private:
    std::set<int> pressedKeys;
    std::unique_ptr<QTimer> timerKey;
public slots:
    void onTimeout();
    void onTimeoutKey();
signals:

};

#endif // OPENGLWIDGET_H
