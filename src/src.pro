# qmake project file for building the libqtavi library

include(../config.pri)

TARGET       = qtavi
TEMPLATE     = lib

MOC_DIR      = ../tmp
OBJECTS_DIR  = ../tmp
DESTDIR      = ../

contains(CONFIG, QtAviDll) {
    CONFIG  += dll
    DEFINES += QTAVI_DLL QTAVI_DLL_BUILD
} else {
    CONFIG  += staticlib
}

INCLUDEPATH   += $$GWAVI_PATH/inc
INCLUDEPATH   += $$GWAVI_PATH/src

HEADERS  = QAviWriter.h
SOURCES += QAviWriter.cpp