#include "camera.h"

void Camera::ProcessKeyboard(Camera_Movement direction,GLfloat deltaTime){
    GLfloat velocity=MovementSpeed*deltaTime;
    if(direction==FORWARD)Position+=Front*velocity;
    else if(direction==BACKWARD)Position-=Front*velocity;
    else if(direction==RIGHT)Position+=Right*velocity;
    else if(direction==LEFT)Position-=Right*velocity;
    else if(direction==UP)Position+=Up*velocity;
    else if(direction==DOWN)Position-=Up*velocity;
}

void Camera::ProcessMouseMovent(GLfloat xoffset,GLfloat yoffset,GLboolean constrainPitch){
    xoffset*=MouseSensitivity;
    yoffset*=MouseSensitivity;

    Yaw+=xoffset;
    Pitch+=yoffset;

    if(constrainPitch){
        if(Pitch>89.0f)Pitch=89.0f;
        else if(Pitch<-89.0f)Pitch=-89.0f;
    }

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yoffset){
    Zoom-=yoffset;
    if(Zoom<1.0f)Zoom=1.0f;
    //if(Zoom>45.0f)Zoom=45.0f;
}
//bool Point();
