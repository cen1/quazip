QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
        main.cpp

TARGET = example

INCLUDEPATH += C:/zlib/include C:/quazip/include/QuaZip-Qt5-1.2/quazip
LIBS += -LC:/quazip/lib -LC:/zlib/lib

win32:CONFIG(release, debug|release) {
    LIBS += -lquazip1-qt5 -lzlib
}
win32:CONFIG(debug, debug|release) {
    LIBS += -lquazip1-qt5d -lzlibd
}

OTHER_FILES += \
    helloworld.zip
