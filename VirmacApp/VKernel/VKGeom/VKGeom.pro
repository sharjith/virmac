#-------------------------------------------------
#
# Project created by QtCreator 2016-07-02T13:43:19
#
#-------------------------------------------------

QT       += core gui

TARGET = VKGeom
TEMPLATE = lib

DEFINES += VKGEOM_LIBRARY

SOURCES += vkgeom.cpp \
    AxisSystem.cpp \
    BasicSurface.cpp \
    BezierCurve.cpp \
    BoundingBox.cpp \
    Bsp.cpp \
    BSplineCurve.cpp \
    Circle3D.cpp \
    Cone.cpp \
    Conic.cpp \
    Curve.cpp \
    Curve2D.cpp \
    Cylinder.cpp \
    Ellipse3D.cpp \
    ExtrudedSurface.cpp \
    Geometry.cpp \
    Geometry2D.cpp \
    GeomException.cpp \
    Helix.cpp \
    Hyperbola3D.cpp \
    Line2D.cpp \
    Line3D.cpp \
    ListException.cpp \
    Matrix22.cpp \
    Matrix33.cpp \
    MMath.cpp \
    OffsetCurve.cpp \
    OffsetSurface.cpp \
    OneAxis.cpp \
    OneAxis2D.cpp \
    Parabola3D.cpp \
    PCurve.cpp \
    PipeSurface.cpp \
    Plane.cpp \
    Point2D.cpp \
    Point3D.cpp \
    RevolvedSurface.cpp \
    RuledSurface.cpp \
    Sphere.cpp \
    Surface.cpp \
    SweptSurface.cpp \
    Torus.cpp \
    Triangle.cpp \
    Vector2D.cpp \
    Vector3D.cpp \
    ListIteratorOfListOfOneAxis.cpp \
    ListIteratorOfListOfPoint3D.cpp \
    ListIteratorOfListOfTriangle.cpp \
    ListNodeOfOneAxis.cpp \
    ListNodeOfPoint3D.cpp \
    ListNodeOfTriangle.cpp \
    ListOfOneAxis.cpp \
    ListOfPoint3D.cpp \
    ListOfTriangle.cpp \
    CircularArc.cpp

HEADERS += vkgeom.h\
        vkgeom_global.h \
    AxisSystem.h \
    BasicSurface.h \
    BezierCurve.h \
    BoundingBox.h \
    Bsp.h \
    BSplineCurve.h \
    Circle3D.h \
    Cone.h \
    Conic.h \
    Curve.h \
    Curve2D.h \
    Cylinder.h \
    Ellipse3D.h \
    ExtrudedSurface.h \
    Geometry.h \
    Geometry2D.h \
    GeomException.h \
    Helix.h \
    Hyperbola3D.h \
    Line2D.h \
    Line3D.h \
    ListException.h \
    Matrix22.h \
    Matrix33.h \
    MMath.h \
    OffsetCurve.h \
    OffsetSurface.h \
    OneAxis.h \
    OneAxis2D.h \
    Parabola3D.h \
    PCurve.h \
    PipeSurface.h \
    Plane.h \
    Point2D.h \
    Point3D.h \
    RevolvedSurface.h \
    RuledSurface.h \
    Sphere.h \
    Surface.h \
    SweptSurface.h \
    Torus.h \
    Triangle.h \
    Vector2D.h \
    Vector3D.h \
    ListIteratorOfListOfOneAxis.h \
    ListIteratorOfListOfPoint3D.h \
    ListIteratorOfListOfTriangle.h \
    ListNodeOfOneAxis.h \
    ListNodeOfPoint3D.h \
    ListNodeOfTriangle.h \
    ListOfOneAxis.h \
    ListOfPoint3D.h \
    ListOfTriangle.h \
    CircularArc.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

QMAKE_MAC_SDK = macosx10.12

