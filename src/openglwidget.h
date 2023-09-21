#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <qopenglfunctions_3_3_core.h>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget* parent = nullptr);
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:
    unsigned int VAO, VBO, EBO;
    unsigned int shaderProgram;
    float vertices[12] = {
        +0.5f, +0.5f, +0.0f, 
        -0.5f, +0.5f, +0.0f,
        -0.5f, -0.5f, +0.0f,
        +0.5f, -0.5f, +0.0f
    };
    unsigned int indices[6] = {
        0, 1, 2,
        0, 2, 3
    };
    const char* vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";
signals:

};

#endif // OPENGLWIDGET_H
