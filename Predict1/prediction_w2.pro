#-------------------------------------------------
#
# Project created by QtCreator 2016-06-27T15:18:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prediction_w2
TEMPLATE = app


SOURCES += main.cpp\
        mainpredict.cpp \
    mathmethods.cpp \
    fileop.cpp \
    filedialog.cpp \
    dwritefile.cpp \
    params_mat.cpp \
    extramnk.cpp

HEADERS  += mainpredict.h \
    mathmethods.h \
    fileop.h \
    filedialog.h \
    dwritefile.h \
    params_mat.h \
    extramnk.h

FORMS    += mainpredict.ui \
    filedialog.ui \
    dwritefile.ui \
    params_mat.ui
