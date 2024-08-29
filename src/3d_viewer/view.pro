QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


# Подключение доп библиотеки qgifimage
include(gifimage/qtgifimage.pri)
#include(3rdParty/giflib.pri)


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    model/model.cpp \
    model/utils/affine.cpp \
    model/utils/parser.cpp \
    main.cpp \
    model/utils/validator.cpp \
    view/glview.cpp \
    view/view.cpp \
    controller/controller.cpp

HEADERS += \
    controller/controller.h \
    model/model.h \
    model/utils/affine.h \
    model/utils/parser.h \
    model/utils/validator.h \
    view/glview.h \
    view/view.h

FORMS += \
    view/view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/view
