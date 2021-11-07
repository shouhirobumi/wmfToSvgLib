#-------------------------------------------------
#
# Project created by QtCreator 2019-03-18T11:07:01
#
#-------------------------------------------------

QT       -= gui

TARGET = WmfToSvgCpp
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += include

SOURCES += \
    GdiUtils.cpp \
    main.cpp \
    Properties.cpp \
    SvgBrush.cpp \
    SvgDc.cpp \
    SvgFont.cpp \
    SvgGdi.cpp \
    SvgObject.cpp \
    SvgPalette.cpp \
    SvgPatternBrush.cpp \
    SvgPen.cpp \
    SvgRectRegion.cpp \
    SvgRegion.cpp

HEADERS += \
    Base64.h \
    DataInput.h \
    gdiInfoDefine.h \
    GdiUtils.h \
    IGdi.h \
    IGdiBrush.h \
    IGdiFont.h \
    IGdiObject.h \
    IGdiPalette.h \
    IGdiPatternBrush.h \
    IGdiPen.h \
    IGdiRegion.h \
    ImageUtil.h \
    Point.h \
    Properties.h \
    Size.h \
    SvgBrush.h \
    SvgDc.h \
    SvgFont.h \
    SvgGdi.h \
    SvgObject.h \
    SvgPalette.h \
    SvgPatternBrush.h \
    SvgPen.h \
    SvgRectRegion.h \
    SvgRegion.h \
    tool.h \
    WmfBrush.h \
    WmfConstants.h \
    WmfFont.h \
    WmfObject.h \
    WmfPalette.h \
    WmfParseException.h \
    WmfParser.h \
    WmfPatternBrush.h \
    WmfPen.h \
    WmfRectRegion.h \
    WmfRegion.h \
    ./include/API_WmfToSvg.h \
    ./include/tinyxml2.h
unix {
    target.path = /usr/lib
    INSTALLS += target
    LIBS += _L"./lib/tinyxml2d.a"
}

win32{
    LIBS += _L"./lib/tinyxml2d.lib"
}

DISTFILES += \
    libWmfToSvgCpp.pro.user
