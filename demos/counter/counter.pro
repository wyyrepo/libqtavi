include(../demo_config.pri)
TARGET        = counter

win32: CONFIG += console
macx:  CONFIG -= app_bundle

SOURCES       += main.cpp
