SOURCES += \
    main.cpp \
    mainwindow.cpp

FORMS += \
    about.ui \
    mainwindow.ui \
    equalizer.ui \
    database_update.ui \
    database_cleanup.ui \
    audio_interfaces.ui \
    audio_formats.ui

RESOURCES += \
    icons/icons.qrc

HEADERS += \
    mainwindow.h

QT += \
    core \
    gui \
    network \
    sql \
    xml \
    webkit

