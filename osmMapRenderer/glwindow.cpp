#include "glwindow.h"

#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include "Xml/xmlreader.h"
#include "Renderer/textrenderer.h"

GLWindow::GLWindow(QWidget *parent):QOpenGLWidget(parent){
    QSurfaceFormat surfaceFormat;
    surfaceFormat.setSamples(9);
    setFormat(surfaceFormat);
}

GLWindow::~GLWindow(){
    res->Clear();
}

void GLWindow::initializeGL(){
    initializeOpenGLFunctions();

    //glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_MULTISAMPLE);

    Init();
}

void GLWindow::paintGL(){
    glClearColor(0.94f,0.95f,0.98f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    Update();
    Render();
}

void GLWindow::resizeGL(int width,int height){
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    QMatrix4x4 projection;
    projection.ortho(0.0f,this->width(),0.0f,this->height(),-1.0f,1.0f);
    Shader shader=res->GetShader("sprite");
    shader.use();
    shader.setMat4("projection",projection);
    shader.unuse();
    shader=res->GetShader("polygon");
    shader.use();
    shader.setMat4("projection",projection);
    shader.unuse();
}

void GLWindow::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons()&Qt::LeftButton){
        int xoffset=event->pos().x()-MouseLeftButtonPos.x();
        int yoffset=event->pos().y()-MouseLeftButtonPos.y();
        //camera.ProcessMouseMovent(xoffset,-yoffset);
        //qDebug()<<xoffset<<" "<<yoffset<<"\n";
        camera.Position+=QVector3D(-xoffset/10000.0,yoffset/10000.0,0);
        update();
        MouseLeftButtonPos=event->pos();
    }
}


void GLWindow::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton)MouseLeftButtonPos=event->pos();
}

void GLWindow::wheelEvent(QWheelEvent *event){
    //qDebug()<<event->angleDelta()<<"\n";
    if(event->angleDelta().y()>0)camera.Position.setZ(camera.Position.z()/1.1);
    else camera.Position.setZ(camera.Position.z()*1.1);
    // if(event->angleDelta().y()>0)Map.Size*=1.1;
    // else Map.Size/=1.1;
    update();
}

void GLWindow::keyPressEvent(QKeyEvent *event){
    //static int i=0;
    //qDebug()<<event->key()<<" "<<i++<<"\n";
    KeyPressed[event->key()]=true;
    if(event->key()==Qt::Key_W)camera.ProcessKeyboard(FORWARD,0.01);
    else if(event->key()==Qt::Key_S)camera.ProcessKeyboard(BACKWARD,0.01);
    else if(event->key()==Qt::Key_A)camera.ProcessKeyboard(LEFT,0.01);
    else if(event->key()==Qt::Key_D)camera.ProcessKeyboard(RIGHT,0.01);
    else if(event->key()==Qt::Key_Q)camera.ProcessKeyboard(UP,0.01);
    else if(event->key()==Qt::Key_E)camera.ProcessKeyboard(DOWN,0.01);
    update();
}

void GLWindow::keyReleaseEvent(QKeyEvent *event){
    //qDebug()<<event->key()<<"\n";
    KeyPressed[event->key()]=false;

}

void GLWindow::Init(){
    camera=Camera(QVector3D(0.0,0.0,5));
    res=new ResourceManager();
    LoadShaders();

    textRenderer=new TextRenderer(res->GetShader("text"));
    string s="宋";
    string font="宋体";
    textRenderer->Load(s,font,128);

    LoadTextures();
    Map.Load("map.xml",res->GetShader("prism"),QVector3D(-0.05,-0.05,0),QVector3D(0.1,0.1,0.02));
}

void GLWindow::LoadShaders(){

    res->LoadShader(":/shaders/res/shaders/sprite.vert",":/shaders/res/shaders/sprite.frag",nullptr,"sprite");
    res->LoadShader(":/shaders/res/shaders/polygon.vert",":/shaders/res/shaders/polygon.frag",nullptr,"polygon");
    res->LoadShader(":/shaders/res/shaders/cube.vert",":/shaders/res/shaders/cube.frag",nullptr,"cube");
    res->LoadShader(":/shaders/res/shaders/prism.vert",":/shaders/res/shaders/prism.frag",nullptr,"prism");
    res->LoadShader(":/shaders/res/shaders/text.vert",":/shaders/res/shaders/text.frag",nullptr,"text");

    QMatrix4x4 projection;
    projection.ortho(0.0f,width(),0.0f,height(),-1.0f,1.0f);
    Shader shader=res->GetShader("sprite");
    shader.use();
    shader.setInt("image",0);
    shader.setMat4("projection",projection);
    shader.unuse();
    shader=res->GetShader("polygon");
    shader.use();
    shader.setMat4("projection",projection);
    shader.unuse();
}

void GLWindow::LoadTextures(){
    res->LoadTexture2D(":/textures/res/textures/diamond.png","diamond");
    res->LoadTexture2D(":/textures/res/textures/stone.png","stone");
}

void GLWindow::Update(){
}

void GLWindow::Render(){
    Map.Render(camera,camera.GetProjectionMatrix(width(),height()));
}

void GLWindow::LoadFile(const char* file){
    Map.Load(file,res->GetShader("prism"),QVector3D(-0.05,-0.05,0),QVector3D(0.1,0.1,0.02));
    update();
}

void GLWindow::ChangeCameraMode(bool mode){
    _cameramode=mode;
    if(mode)camera=Camera(QVector3D(0,0,1),QVector3D(0,0,1));
    else camera=Camera(QVector3D(0,0,5));
    update();
}
