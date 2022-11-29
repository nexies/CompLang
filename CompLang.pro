TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../libs
OBJECTS_DIR = ../obj/CompLang
MOC_DIR = ../moc/CompLang

TARGET = CompLang

SOURCES += \
        source/main.cpp \
        source/t_bit_types.cpp \
    source/t_data_types.cpp

HEADERS += \
    source/t_bit_types.h \
    source/t_data_types.h
