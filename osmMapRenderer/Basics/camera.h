#ifndef CAMERA_H
#define CAMERA_H

#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

const GLfloat YAW=-90.0f;
const GLfloat PITCH=0.0f;
const GLfloat SPEED=2.5f;
const GLfloat SENSITIVITY=0.1f;
const GLfloat ZOOM=80.0f;

enum Camera_Movement{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera:QOpenGLFunctions
{
public:
    QVector3D Position;
    QVector3D Front;
    QVector3D Up;
    QVector3D Right;
    QVector3D WorldUp;

    GLfloat Yaw;
    GLfloat Pitch;

    GLfloat MovementSpeed;
    GLfloat MouseSensitivity;
    GLfloat Zoom;

    Camera(QVector3D position = QVector3D(0.0f, 0.0f, 0.0f), QVector3D up = QVector3D(0.0f, 1.0f, 0.0f),float yaw = YAW, float pitch = PITCH)
        :Front(QVector3D(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {

        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    QMatrix4x4 GetViewMatrix(){
        QMatrix4x4 mat;
        mat.lookAt(Position,Position+Front,Up);
        return mat;
    }
    QMatrix4x4 GetProjectionMatrix(GLuint width,GLuint height,GLfloat Near=0.1f,GLfloat Far=100.0f){
        QMatrix4x4 mat;
        mat.perspective(qDegreesToRadians(Zoom),(GLfloat)width/height,Near,Far);
        return mat;
    }
    void ProcessKeyboard(Camera_Movement direction,GLfloat deltaTime);
    void ProcessMouseMovent(GLfloat xoffset,GLfloat yoffset,GLboolean constrainPitch = true);
    void ProcessMouseScroll(GLfloat yoffset);
    //bool Point();
private:
    void updateCameraVectors(){
        QVector3D front;
        front.setX(cos(qDegreesToRadians(Yaw))*cos(qDegreesToRadians(Pitch)));
        front.setY(sin(qDegreesToRadians(Pitch)));
        front.setZ(sin(qDegreesToRadians(Yaw))*cos(qDegreesToRadians(Pitch)));
        Front=front.normalized();
        Right=QVector3D::crossProduct(Front,WorldUp).normalized();
        Up=QVector3D::crossProduct(Right,Front).normalized();
        //qDebug()<<Position<<"\n";
    }
};

#endif // CAMERA_H
