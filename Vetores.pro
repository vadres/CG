QT += core
QT += gui

TARGET = Vetores
CONFIG += console

TEMPLATE = app

SOURCES += main.cpp \
    vector3f.cpp \
    color.cpp \
    ray3f.cpp \
    raycastingresult.cpp \
    object3d.cpp \
    sphere.cpp \
    triangle.cpp \
    camera.cpp \
    perspective.cpp \
    material.cpp \
    raytracer.cpp \
    scene.cpp \
    light.cpp \
    teste.cpp \
    cylinder.cpp

HEADERS += \
    vector3f.h \
    color.h \
    ray3f.h \
    raycastingresult.h \
    object3d.h \
    sphere.h \
    triangle.h \
    camera.h \
    projection.h \
    perspective.h \
    material.h \
    raytracer.h \
    scene.h \
    light.h \
    cylinder.h
