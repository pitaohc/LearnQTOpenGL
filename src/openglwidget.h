#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <qopenglfunctions_3_3_core.h>
#include <qopenglshaderprogram.h>
#include<vector>

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
    std::vector<float> vertices = { 
        +0.5f, +0.5f, +0.0f,
        -0.5f, +0.5f, +0.0f,
        -0.5f, -0.5f, +0.0f,
        +0.5f, -0.5f, +0.0f };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 2, 3
    };

    void initShaderProgram();
public slots:
    void onTimeout();
signals:

};

#endif // OPENGLWIDGET_H
