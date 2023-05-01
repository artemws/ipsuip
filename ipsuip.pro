TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    countries.h \
    functions.h

DISTFILES += \
    README.md \
    ip2cidr.awk
