QT       += core gui\
            openglwidgets\



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Basics/camera.cpp \
    Basics/resourcemanager.cpp \
    Basics/shader.cpp \
    Basics/texture2d.cpp \
    Functions/graph.cpp \
    Functions/polygonstriangulating.cpp \
    Object/ObjectMap/objectbuilding.cpp \
    Object/ObjectMap/objectplane.cpp \
    Object/ObjectMap/objectway.cpp \
    Object/objectmap.cpp \
    Object/objectmap3d.cpp \
    Renderer/dynamicspritelinestripplane.cpp \
    Renderer/sprite.cpp \
    Renderer/spritecube.cpp \
    Renderer/staticspritelinestripe.cpp \
    Renderer/staticspritelinestripplane.cpp \
    Renderer/staticspritepolygon.cpp \
    Renderer/staticspritepolygonplane.cpp \
    Renderer/staticspriteprism.cpp \
    Renderer/statictextrenderer.cpp \
    Renderer/textrenderer.cpp \
    Xml/node.cpp \
    Xml/tinystr.cpp \
    Xml/tinyxml.cpp \
    Xml/tinyxmlerror.cpp \
    Xml/tinyxmlparser.cpp \
    Xml/way.cpp \
    Xml/xmlmanager.cpp \
    Xml/xmlreader.cpp \
    glwindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Basics/camera.h \
    Basics/resourcemanager.h \
    Basics/shader.h \
    Basics/texture2d.h \
    Functions/graph.h \
    Functions/polygonstriangulating.h \
    Object/ObjectMap/objectbuilding.h \
    Object/ObjectMap/objectplane.h \
    Object/ObjectMap/objectway.h \
    Object/objectmap.h \
    Object/objectmap3d.h \
    Renderer/dynamicspritelinestripplane.h \
    Renderer/sprite.h \
    Renderer/spritecube.h \
    Renderer/staticspritelinestripe.h \
    Renderer/staticspritelinestripplane.h \
    Renderer/staticspritepolygon.h \
    Renderer/staticspritepolygonplane.h \
    Renderer/staticspriteprism.h \
    Renderer/statictextrenderer.h \
    Renderer/textrenderer.h \
    Xml/node.h \
    Xml/tinystr.h \
    Xml/tinyxml.h \
    Xml/way.h \
    Xml/xmlmanager.h \
    Xml/xmlreader.h \
    glwindow.h \
    mainwindow.h

LIBS+=\
    -lopengl32\

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
