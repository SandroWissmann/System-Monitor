QT += quick

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        src/format.cpp \
        src/helper.cpp \
        src/linux/cpu_states.cpp \
        src/linux/l_memory.cpp \
        src/linux/l_parser.cpp \
        src/linux/l_process.cpp \
        src/linux/l_processor.cpp \
        src/memory.cpp \
        src/parser.cpp \
        src/process.cpp \
        src/processor.cpp \
        src/system.cpp

RESOURCES += qml.qrc \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    LICENSE.md \
    README.md \
    images/application.png \

HEADERS += \
    include/format.h \
    include/helper.h \
    include/linux/cpu_states.h \
    include/linux/l_memory.h \
    include/linux/l_parser.h \
    include/linux/l_process.h \
    include/linux/l_processor.h \
    include/memory.h \
    include/parser.h \
    include/process.h \
    include/processor.h \
    include/system.h
