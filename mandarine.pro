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
    metaexplorer.cpp \
    infoexplorer.cpp \
    playlistcontrols.cpp \
    playercontrols.cpp \
    playersliders.cpp \
    aboutdialog.cpp \
    qlabelclickable.cpp \
    fileinformationsdialog.cpp \
    playlisttablemodel.cpp \
    qtableviewclickable.cpp \
    qtreeviewclickable.cpp

HEADERS  += \
    mainwindow.h \
    libraryexplorer.h \
    metaexplorer.h \
    infoexplorer.h \
    playlistcontrols.h \
    playercontrols.h \
    playersliders.h \
    aboutdialog.h \
    qlabelclickable.h \
    fileinformationsdialog.h \
    playlisttablemodel.h \
    qtableviewclickable.h \
    qtreeviewclickable.h

FORMS    += \
    mainwindow.ui \
    libraryexplorer.ui \
    metaexplorer.ui \
    infoexplorer.ui \
    playlistcontrols.ui \
    playercontrols.ui \
    playersliders.ui \
    aboutdialog.ui \
    fileinformationsdialog.ui

RESOURCES += \
    icons/icons.qrc
