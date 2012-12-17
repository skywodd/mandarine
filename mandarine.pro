QT += \
    core \
    gui \
    sql \
    multimedia \
    webkitwidgets \
    widgets

TARGET = Mandarine

TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    libraryexplorer.cpp \
    fileexplorer.cpp \
    metaexplorer.cpp \
    infoexplorer.cpp \
    playlistcontrols.cpp \
    playercontrols.cpp \
    playersliders.cpp \
    aboutdialog.cpp \
    audioformatsdialog.cpp \
    audiointerfacesdialog.cpp \
    equalizerdialog.cpp

HEADERS  += \
    mainwindow.h \
    libraryexplorer.h \
    fileexplorer.h \
    metaexplorer.h \
    infoexplorer.h \
    playlistcontrols.h \
    playercontrols.h \
    playersliders.h \
    aboutdialog.h \
    audioformatsdialog.h \
    audiointerfacesdialog.h \
    equalizerdialog.h

FORMS    += \
    mainwindow.ui \
    libraryexplorer.ui \
    fileexplorer.ui \
    metaexplorer.ui \
    infoexplorer.ui \
    playlistcontrols.ui \
    playercontrols.ui \
    playersliders.ui \
    aboutdialog.ui \
    equalizer.ui \
    audioformatsdialog.ui \
    audiointerfacesdialog.ui

RESOURCES += \
    icons/icons.qrc
