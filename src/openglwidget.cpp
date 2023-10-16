#include "openglwidget.h"
#include <qdebug.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <QKeyEvent>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#ifdef _DEBUG
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fmt/color.h>
#endif // _DEBUG
constexpr int FPS = 144;
constexpr glm::vec3 POSITIONDEFAULT(0.0f, 0.0f, 100.0f);
OpenGLWidget::OpenGLWidget(QWidget* parent) :
    QOpenGLWidget(parent), timer(nullptr)
{
    /*
        注意：camera默认朝向为(0.0f,0.0f,-1.0f)，如果面片z轴坐标大于10会不在视野内。
        并且z值越小，距离越远，面片在屏幕上也越小
    */
    camera = Camera(POSITIONDEFAULT); //初始化相机位置

    setFocusPolicy(Qt::StrongFocus); //设置焦点策略,否则键盘事件不响应

    timer = std::make_unique<QTimer>(this);//timer只负责触发onTimeout()函数，不负责获取时间
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start(1000 / FPS);

    timerKey = std::make_unique<QTimer>(this);//timer只负责触发onTimeout()函数，不负责获取时间
    connect(timerKey.get(), SIGNAL(timeout()), this, SLOT(onTimeoutKey()));

}

OpenGLWidget::~OpenGLWidget()
{
    if (timer != nullptr)
    {
        timer->stop();
        timer.release();
#ifdef _DEBUG
        fmt::print(fmt::fg(fmt::color::red), "Release timer successfully.\n");
#endif // _DEBUG
    }
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    //开启深度测试
    glEnable(GL_DEPTH_TEST);
    // 设置渲染方式
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

    glEnable(GL_CULL_FACE); // 开启面剔除

    cubes.push_back(Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(20.0f, 20.0f, 20.0f)));
    cubes.push_back(Cube(glm::vec3(40.0f, 40.0f, 10.0f), glm::vec3(30.0f, 45.0f, 60.0f), glm::vec3(20.0f, 20.0f, 20.0f)));


    int success = false;
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "../shader/cube.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "../shader/cube.frag");
    success = shaderProgram.link();
    if (!success)
    {
        qCritical() << "shaderProgram link failed!" << endl
            << shaderProgram.log() << endl;
    }

}

void OpenGLWidget::resizeGL(int w, int h)
{
#ifdef _DEBUG
    fmt::print("INFO: resize to {}x{}\n", w, h);
#endif //_DEBUG
    glViewport(0, 0, w, h);
}

void OpenGLWidget::paintGL()
{
    glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float angle = deltaTime / 3000.0f * 360.0f;
    for (auto& cube : cubes)
    {
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)this->width() / (float)this->height(), 0.1f, 1000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        cube.rotation.y += angle;
        glm::mat4 model = cube.getModel();

        shaderProgram.bind();
        glUniformMatrix4fv(shaderProgram.uniformLocation("model"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(shaderProgram.uniformLocation("projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(shaderProgram.uniformLocation("view"), 1, GL_FALSE, &view[0][0]);
        cube.draw(shaderProgram);
    }

}


void OpenGLWidget::onTimeoutKey()
{
#ifdef _DEBUG
    fmt::print("Keys: {}\n", pressedKeys);
#endif // _DEBUG
    if (pressedKeys.empty())
    {
        timerKey->stop();
        return;
    }
    for (auto& key : pressedKeys)
    {
        switch (key)
        {
        case Qt::Key_W:
            camera.ProcessKeyboard(FORWARD, deltaTime);
            break;
        case Qt::Key_S:
            camera.ProcessKeyboard(BACKWARD, deltaTime);
            break;
        case Qt::Key_A:
            camera.ProcessKeyboard(LEFT, deltaTime);
            break;
        case Qt::Key_D:
            camera.ProcessKeyboard(RIGHT, deltaTime);
            break;
        case Qt::Key_Q:
            camera.ProcessKeyboard(UP, deltaTime);
            break;
        case Qt::Key_E:
            camera.ProcessKeyboard(DOWN, deltaTime);
            break;
        case Qt::Key_G:
            camera.Position = POSITIONDEFAULT;
            break;
        case Qt::Key_Escape:
            QCoreApplication::quit();
            break;
        default:
            break;
        }
    }
}



void OpenGLWidget::setNewRect(float dx, float dy, float dz)
{
    float x, y, z;
    x = rand() % 100 - 50;
    y = rand() % 100 - 50;
    z = rand() % 100 - 50;
    float roll, yaw, pitch;
    pitch = (float)(rand() % 3600) / 10.0f - 180;
    yaw = (float)(rand() % 3600) / 10.0f - 180;
    roll = (float)(rand() % 3600) / 10.0f - 180;
    cubes.push_back(Cube(glm::vec3(x, y, z), glm::vec3(pitch, yaw, roll), glm::vec3(10.0f, 10.0f, 10.0f)));

}

void OpenGLWidget::cleanAllRects()
{
    cubes.clear();
}

void OpenGLWidget::onTimeout() {
    ////获取当前毫秒数
    int currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    static int lastTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
#ifdef _DEBUG
    fmt::print("FPS = {}, Tick Time: {}ms, Current Time: {}ms\n", (int)(1000.0f / deltaTime), deltaTime, currentTime);
#endif // _DEBUG
    update();
}

/*
* 重写键盘事件
*/
void OpenGLWidget::keyPressEvent(QKeyEvent* event)
{
    QOpenGLWidget::keyPressEvent(event);

    //按键按下，key值放入容器，如果是长按触发的repeat就不判断
    if (!event->isAutoRepeat())
    {
        pressedKeys.insert(event->key());
    }
    //判断是否运行，不然一直触发就一直不能timeout
    if (!timerKey->isActive())
    {
        timerKey->start(5);
        return;
    }
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent* event)
{
    QOpenGLWidget::keyReleaseEvent(event);
    if (!event->isAutoRepeat())
    {
        pressedKeys.erase(event->key());
    }
    if (pressedKeys.empty())
    {
        timerKey->stop();
    }
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
    QOpenGLWidget::mouseMoveEvent(event);
    //获得鼠标变化坐标
    static bool firstMouse = true;
    static float lastX, lastY;
    if (firstMouse)
    {
        lastX = event->x();
        lastY = event->y();
        firstMouse = false;
    }
#ifdef _DEBUG
    fmt::print(
        "last pos: ({},{}), current pos: ({},{})\n",
        lastX, lastY, event->x(), event->y());
#endif // _DEBUG

    float xoffset = event->x() - lastX;
    float yoffset = lastY - event->y(); // reversed since y-coordinates go from bottom to top

    lastX = event->x();
    lastY = event->y();

    camera.ProcessMouseMovement(xoffset, yoffset);

}

void OpenGLWidget::wheelEvent(QWheelEvent* event)
{
    QOpenGLWidget::wheelEvent(event);
    camera.ProcessMouseScroll(event->delta() / 120);
}
