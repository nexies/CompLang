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
        source/lindex_construct_data_types.cpp \
        source/lindex_uint2_t.cpp \
        source/lindex_instance.cpp \
        source/main.cpp \
        source/t_lindex_type.cpp \
        source/t_lindex_type_table.cpp

HEADERS += \
    source/lindex_basic_bit_types.h \
    source/lindex_construct_data_types.h \
    source/lindex_uint2_t.h \
    source/lindex.h \
    source/lindex_instance.h \
    source/t_lindex_type.h \
    source/t_lindex_type_table.h
