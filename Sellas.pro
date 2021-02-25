QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

test_conf {
   # test specific files and options here
   QT += testlib
   SOURCES += test/test.cpp
} else {
   # app specific files and options here
   SOURCES += main.cpp
}

SOURCES += \
    database/databasemanager.cpp \
    http/requests.cpp \
    model/boss.cpp \
    model/sellas.cpp \
    model/sellasparser.cpp \
    ui/bossdifficultbutton.cpp \
    ui/bosslistwidget.cpp \
    ui/sellasbutton.cpp \
    ui/sellaslistwidget.cpp \
    ui/widget.cpp

HEADERS += \
    database/databasemanager.h \
    http/requests.h \
    model/boss.h \
    model/sellas.h \
    model/sellasparser.h \
    ui/bossdifficultbutton.h \
    ui/bosslistwidget.h \
    ui/sellasbutton.h \
    ui/sellaslistwidget.h \
    ui/widget.h

FORMS += \
    bosslistwidget.ui \
    widget.ui

TRANSLATIONS += \
    Sellas_ko_KR.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    LICENSE.txt \
    README.md \
    data/sellas.json

RESOURCES += \
    resource.qrc
