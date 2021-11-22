QT -= gui
QT      += core network
CONFIG += c++11
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        server/server.cpp \
        sslhelper.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    server/server.h \
    sslhelper.h

#第三方库的头文件和库保存目录
3RDPARTY_DIR = $$PWD/3rdParty
win32 {
    3RDPARTY_INCLUDE_DIR = $$3RDPARTY_DIR/Windows/include
    3RDPARTY_LIB_DIR = $$3RDPARTY_DIR/Windows/lib
} else {
    3RDPARTY_INCLUDE_DIR = $$3RDPARTY_DIR/Linux/include
    3RDPARTY_LIB_DIR = $$3RDPARTY_DIR/Linux/lib
}

INCLUDEPATH += \
    $$3RDPARTY_INCLUDE_DIR \
    $$PWD/server



win32 {
    CONFIG(debug, debug|release) {
        LIBS += -L$$3RDPARTY_LIB_DIR -lcrypto-46d -lqtnetworkngd -lssl-48d -ltls-20d
    } else {
        LIBS += -L$$3RDPARTY_LIB_DIR -lcrypto-46 -lqtnetworkng -lssl-48 -ltls-20
    }
    LIBS += -lAdvapi32 -lBcrypt -luser32 -lwsock32 -lWS2_32 -lDbghelp
} else {
    LIBS += -L$$3RDPARTY_LIB_DIR -lqtnetworkng -lssl -lcrypto
}
