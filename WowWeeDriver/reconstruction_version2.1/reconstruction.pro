TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    robotdriver.cpp \
    robotcameraexample.cpp

HEADERS += \
    robotdriver.h \
    robotcolor.h \
    jpegworkaround.h


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

unix:!macx:!symbian: LIBS += -ljpeg
