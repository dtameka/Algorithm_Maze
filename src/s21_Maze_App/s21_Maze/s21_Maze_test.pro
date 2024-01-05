#-------------------------------------------------
#
# Project created by QtCreator 2022-11-14T20:18:10
#
#-------------------------------------------------

QT       += core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets

LIBS     += -lgtest -lpthread -lgcov

# TARGET = First-test
# TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


QMAKE_CXXFLAGS += --coverage
CONFIG += c++17
QMAKE_CXXFLAGS_WARN_OFF += -Wunused-value
QMAKE_CXXFLAGS_WARN_ON -= -Wall

SOURCES += \
    s21_Maze_test.cc \
    s21_cave.cc \
    s21_maze.cc \

HEADERS += \
    s21_cave.h \
    s21_maze.h \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

