QT       += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Cost.cpp \
    Information.cpp \
    addContact.cpp \
    addressPage.cpp \
    callPage.cpp \
    callingPage.cpp \
    costMapPage.cpp \
    findPage.cpp \
    main.cpp \
    loginMainPage.cpp \
    modifyContact.cpp \
    otherPage.cpp \
    smsPage.cpp

HEADERS += \
    Cost.h \
    Information.h \
    addContact.h \
    addressPage.h \
    callPage.h \
    callingPage.h \
    costMapPage.h \
    findPage.h \
    loginMainPage.h \
    modifyContact.h \
    otherPage.h \
    smsPage.h

FORMS += \
    addContact.ui \
    addressPage.ui \
    callPage.ui \
    costMapPage.ui \
    findPage.ui \
    loginMainPage.ui \
    otherPage.ui \
    smsPage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    icon.rc
