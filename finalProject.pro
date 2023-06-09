QT       += core gui
QT += widgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    confirm.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    signin.cpp

HEADERS += \
    confirm.h \
    login.h \
    mainwindow.h \
    signin.h

FORMS += \
    confirm.ui \
    login.ui \
    mainwindow.ui \
    signin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    captchaImages.qrc
