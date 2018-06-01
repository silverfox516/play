# example4.pro

QT += core gui widgets
TARGET = freetype4
TEMPLATE = app
SOURCES += freetype4.cpp
MOC_DIR = ./moc
LIBS += -lz -lfreetype
INCLUDEPATH += $$MOC_DIR \
               /usr/local/include \
               /usr/local/include/freetype2

# EOF
