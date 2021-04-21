QT       += core gui
QT       += charts
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Change path to your paho-mqtt library
LIBS += \
#    /media/cyfio/Pan/Ubuntu/local/paho/c/lib/libpaho-mqtt3a.so\
    /media/cyfio/Pan/Ubuntu/local/paho/c/lib/libpaho-mqtt3a.so.1\
#    /media/cyfio/Pan/Ubuntu/local/paho/c/lib/libpaho-mqtt3a.so.1.3.2\
#    /media/cyfio/Pan/Ubuntu/local/paho/c/lib/libpaho-mqtt3as.so\
    /media/cyfio/Pan/Ubuntu/local/paho/c/lib/libpaho-mqtt3as.so.1\
#    /media/cyfio/Pan/Ubuntu/local/paho/c/lib/libpaho-mqtt3as.so.1.3.2\
#    /media/cyfio/Pan/Ubuntu/local/paho/c/lib/libpaho-mqtt3c.so\
    /media/cyfio/Pan/Ubuntu/local/paho/c/lib/libpaho-mqtt3c.so.1\
#    /media/cyfio/Pan/Ubuntu/local/paho/c/lib/libpaho-mqtt3c.so.1.3.2\
#    /media/cyfio/Pan/Ubuntu/local/paho/c/lib/libpaho-mqtt3cs.so\
    /media/cyfio/Pan/Ubuntu/local/paho/c/lib/libpaho-mqtt3cs.so.1\
#    /media/cyfio/Pan/Ubuntu/local/paho/c/lib/libpaho-mqtt3cs.so.1.3.2\

INCLUDEPATH += \
    /media/cyfio/Pan/Ubuntu/local/paho/c/include \
    $$PWD/functions \
    $$PWD/modules \
    $$PWD/widgets

SOURCES += \
    functions/algorithm/encryption.cpp \
    functions/utils/utils.cpp \
    main.cpp \
    modules/backend/backendmanager.cpp \
    modules/backend/local/imgdatamanager.cpp \
    modules/backend/local/localdatamanager.cpp \
    modules/backend/local/localmanager.cpp \
    modules/backend/local/rdatamanager.cpp \
    modules/backend/remote/remoteadc.cpp \
    modules/backend/remote/remotecamera.cpp \
    modules/backend/remote/remotekeeper.cpp \
    modules/backend/remote/remotemanager.cpp \
    modules/configure/configurationmanager.cpp \
    modules/transmittion/mymqttclient.cpp \
    modules/user/userinfomanager.cpp \
    widgets/fromtoedit/fromtoedit.cpp \
    widgets/gallerypage/gallerypage.cpp \
    widgets/immornitorpage/immonitorpage.cpp \
    widgets/labelslider/labelslider.cpp \
    widgets/mainmenu/mainmenu.cpp \
    widgets/mainwindow/mainwindow.cpp \
    widgets/mytabwidget/mytabwidget.cpp \
    widgets/pagewidget/pagewidget.cpp \
    widgets/rchartpage/rchartpage.cpp \
    widgets/resistancepage/resistancepage.cpp \
    widgets/settingpage/settingpage.cpp \
    widgets/stackedpage/stackedpage.cpp \
    widgets/warninglabel/warninglabel.cpp

HEADERS += \
    functions/algorithm/include/encryption.h \
    functions/utils/include/utils.h \
    modules/backend/backendmanager.h \
    modules/backend/local/imgdatamanager.h \
    modules/backend/local/localdatamanager.h \
    modules/backend/local/localmanager.h \
    modules/backend/local/rdatamanager.h \
    modules/backend/remote/remoteadc.h \
    modules/backend/remote/remotecamera.h \
    modules/backend/remote/remotekeeper.h \
    modules/backend/remote/remotemanager.h \
    modules/configure/include/configurationmanager.h \
    modules/transmittion/mymqttclient.h \
    modules/user/include/userinfomanager.h \
    widgets/fromtoedit/fromtoedit.h \
    widgets/gallerypage/gallerypage.h \
    widgets/immornitorpage/immonitorpage.h \
    widgets/labelslider/labelslider.h \
    widgets/mainmenu/mainmenu.h \
    widgets/mainwindow/mainwindow.h \
    widgets/mytabwidget/mytabwidget.h \
    widgets/pagewidget/pagewidget.h \
    widgets/rchartpage/rchartpage.h \
    widgets/resistancepage/resistancepage.h \
    widgets/settingpage/settingpage.h \
    widgets/stackedpage/stackedpage.h \
    widgets/warninglabel/warninglabel.h

FORMS += \
    widgets/fromtoedit/fromtoedit.ui \
    widgets/gallerypage/gallerypage.ui \
    widgets/immornitorpage/immonitorpage.ui \
    widgets/labelslider/labelslider.ui \
    widgets/mainmenu/mainmenu.ui \
    widgets/mainwindow/mainwindow.ui\
    widgets/mytabwidget/mytabwidget.ui \
    widgets/rchartpage/rchartpage.ui \
    widgets/resistancepage/resistancepage.ui \
    widgets/settingpage/settingpage.ui \
    widgets/stackedpage/stackedpage.ui \
    widgets/warninglabel/warninglabel.ui

TRANSLATIONS += \
    app_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    config.json
