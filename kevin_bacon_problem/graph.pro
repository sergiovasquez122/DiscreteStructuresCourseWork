TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    graph.cpp \
    bfs.cpp \
    graphbuilder.cpp

HEADERS += \
    graph.h \
    bfs.h \
    graphbuilder.h
