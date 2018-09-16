include(../demo_config.pri)
TARGET        = slideshow

HEADERS       += ExportDialog.h
SOURCES       += ExportDialog.cpp
SOURCES       += main.cpp

mac:RC_FILE    = icons/film.icns
RESOURCES      = icons/icons.qrc