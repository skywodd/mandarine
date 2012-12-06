SOURCES += \
    main.cpp \
    mainwindow.cpp \
    aboutdialog.cpp \
    audiointerfacesdialog.cpp \
    audioformatsdialog.cpp

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
    mainwindow.h \
    aboutdialog.h \
    audiointerfacesdialog.h \
    audioformatsdialog.h

QT += \
    core \
    gui \
    sql \
    multimedia \
    webkitwidgets
