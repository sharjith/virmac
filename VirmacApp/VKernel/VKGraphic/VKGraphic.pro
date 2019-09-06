#-------------------------------------------------
#
# Project created by QtCreator 2016-07-02T13:56:47
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = VKGraphic
TEMPLATE = lib

DEFINES += VKGRAPHIC_LIBRARY

SOURCES += vkgraphic.cpp \
    VGLTrihedron.cpp \
    VGLAxisSystem.cpp \
    VGLCamera.cpp \
    VGLColor.cpp \
    VGLCurve.cpp \
    VGLGrid.cpp \
    VGLMaterial.cpp \
    VGLObject.cpp \
    VGLOneAxis.cpp \
    VGLPlane.cpp \
    VGLPoint.cpp \
    VGLSurface.cpp \
    ListIteratorOfListOfVGLObject.cpp \
    ListNodeOfVGLObject.cpp \
    ListOfVGLObject.cpp

HEADERS += vkgraphic.h\
        vkgraphic_global.h \
    VGLTrihedron.h \
    VGLAxisSystem.h \
    VGLCamera.h \
    VGLColor.h \
    VGLCurve.h \
    VGLGrid.h \
    VGLMaterial.h \
    VGLObject.h \
    VGLOneAxis.h \
    VGLPlane.h \
    VGLPoint.h \
    VGLSurface.h \
    VGLTypeEnums.h \
    ListIteratorOfListOfVGLObject.h \
    ListNodeOfVGLObject.h \
    ListOfVGLObject.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

mac: LIBS += -framework OpenGL -framework GLUT
else:unix: LIBS += -lGL -lGLU -lglut
else:win32: LIBS += -lopengl32 -lglu32 -lglut

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../VKGeom/release/ -lVKGeom
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../VKGeom/debug/ -lVKGeom
else:unix: LIBS += -L$$OUT_PWD/../VKGeom/ -lVKGeom

INCLUDEPATH += $$PWD/../VKGeom
DEPENDPATH += $$PWD/../VKGeom

QMAKE_MAC_SDK = macosx10.12
