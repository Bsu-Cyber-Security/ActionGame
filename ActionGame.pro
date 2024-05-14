QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++23

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    app/scene/gamescene.cpp \
    app/pixmap_manager/pixmap_manager.cpp \
    app/view/view.cpp \
    app/main.cpp \


HEADERS += \
    app/pixmap_manager/pixmap_manager.h \
    app/resource_holder/resource_holder.h \
    app/scene/game_state.h \
    app/scene/gamescene.h \
    app/view/view.h \
    core/level/level.h \
    core/player/player.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
