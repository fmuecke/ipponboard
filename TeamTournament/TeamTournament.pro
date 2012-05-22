#------------------------------------------------------------------------------
# This app depends on:
#   - gamepad
#   - core
# These need to be build first.
#PRE_TARGETDEPS += ../gamepad ../core

TEMPLATE = app
LANGUAGE = C++
CONFIG += windows precompile_header
DEFINES += _WIN32 TEAM_VIEW

# Use Precompiled headers (PCH)
# (inclusion of header in HEADERS section is not required!)
PRECOMPILED_HEADER  = ../base/pch.h

INCLUDEPATH += $$quote($$(BOOST))

QMAKE_LIBDIR += $$quote($$(BOOST)/lib) \
    $$quote($$(BOOST)/stage/lib) \
    ../lib

DESTDIR = ../bin

CONFIG(release, release|debug) {
    TARGET = Ipponboard_team
    QMAKE_LIBS += -lshell32 -lWinmm -lgamepad -lcore
}

CONFIG(debug, release|debug) {
    TARGET = Ipponboard_team_d
    QMAKE_LIBS += -lshell32 -lWinmm -lgamepad_d -lcore_d
}

CONFIG(__GNUC__) {
    QMAKE_CXXFLAGS += -std=c++0x
    QMAKE_LIBS += -lboost_serialization
    QMAKE_LIBS += -lboost_system
    QMAKE_LIBS += -lboost_filesystem
}

HEADERS = ../base/pch.h \
    ../base/clubmanager.h \
    ../base/clubmanagerdlg.h \
    ../widgets/countdown.h \
    ../widgets/scaledimage.h \
    ../widgets/scaledtext.h \
    ../widgets/splashscreen.h \
    ../util/path_helpers.h \
    ../util/qstring_serialization.h \
    ../base/mainwindow.h \
    ../base/settingsdlg.h \
    ../base/view.h \
    scorescreen.h

SOURCES = ../base/clubmanager.cpp \
    ../base/clubmanagerdlg.cpp \
    ../base/mainwindow.cpp \
    ../base/settingsdlg.cpp \
    ../base/view.cpp \
    ../widgets/countdown.cpp \
    ../widgets/scaledimage.cpp \
    ../widgets/scaledtext.cpp \
    ../widgets/splashscreen.cpp \
    main.cpp \
    scorescreen.cpp

FORMS = ../base/clubmanagerdlg.ui \
    mainwindow.ui \
    scorescreen.ui \
    ../base/settingsdlg.ui \
    ../base/view_horizontal.ui \
    ../widgets/splashscreen.ui \
    ../widgets/countdown.ui

OTHER_FILES +=

RESOURCES += ../base/ipponboard.qrc

TRANSLATIONS = ../i18n/ipponboard_team_de.ts

win32:RC_FILE = ../base/Ipponboard_team.rc

# remove unneccessary output files
QMAKE_POST_LINK += del /Q ..\\bin\\$${TARGET}.exp
QMAKE_POST_LINK += && del /Q ..\\bin\\$${TARGET}.lib

# copy all needed files to destdir
QMAKE_POST_LINK += && copy_files.cmd