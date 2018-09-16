TEMPLATE       = app

MOC_DIR        = ./tmp
OBJECTS_DIR    = ./tmp
DESTDIR        = ./

QT += core gui
contains(QT_VERSION, ^5.*){
	QT += widgets
}

CONFIG        += release

GWAVI_PATH = ../../3rdparty/libgwavi
SRC_PATH   = ../../src

INCLUDEPATH   += $$GWAVI_PATH/inc
INCLUDEPATH   += $$GWAVI_PATH/src
INCLUDEPATH   += $$SRC_PATH

HEADERS       += $$SRC_PATH/QAviWriter.h
SOURCES       += $$SRC_PATH/QAviWriter.cpp

LIBS += ../../libqtavi.a
LIBS += $$GWAVI_PATH/lib/libgwavi.a