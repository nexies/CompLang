TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../libs
OBJECTS_DIR = ../obj/CompLang
MOC_DIR = ../moc/CompLang

TARGET = CompLang

SOURCES += \
        source/lindex_basic_bit_types.cpp \
        source/lindex_basic_data_types.cpp \
        source/lindex_construct_data_types.cpp \
        source/lindex_uint2_t.cpp \
        source/lindex_vtable.cpp \
        source/lindex_instance.cpp \
        source/main.cpp

HEADERS += \
    source/lindex_basic_bit_types.h \
    source/lindex_basic_data_types.h \
    source/lindex_construct_data_types.h \
    source/lindex_uint2_t.h \
    source/lindex_vtable.h \
    source/lindex.h \
    source/lindex_instance.h
