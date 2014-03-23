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
#PRECOMPILED_HEADER  = ../base/pch.h
#disabled for mingw!

INCLUDEPATH += $$quote($$(BOOST_DIR))

QMAKE_LIBDIR += $$quote($$(BOOST_DIR)/stage/lib) \
    ../lib

DESTDIR = ../bin

CONFIG(release, release|debug) {
    TARGET = Ipponboard_team
    QMAKE_LIBS += -lgamepad -lcore -lshell32 -lwinmm
}

CONFIG(debug, release|debug) {
    TARGET = Ipponboard_team_d
    QMAKE_LIBS += -lgamepad_d -lcore_d -lshell32 -lwinmm 
}

# Auto select compiler
win32-g++: COMPILER = mingw
win32-msvc2010: COMPILER = msvc
win32-msvc2012: COMPILER = msvc

contains(COMPILER, mingw) {
    QMAKE_CXXFLAGS += -std=c++11
	# get rid of some nasty boost warnings
	QMAKE_CXXFLAGS += -Wno-unused-local-typedefs
	#QMAKE_CXXFLAGS += -std=c++0x
    QMAKE_LIBS += -lboost_serialization-mgw48-mt-1_53
	QMAKE_LIBS += -lboost_system-mgw48-mt-1_53
	QMAKE_LIBS += -lboost_filesystem-mgw48-mt-1_53

	# copy all needed files to destdir
	QMAKE_POST_LINK += copy_files.cmd
}


contains(COMPILER, msvc) {
    QMAKE_CXX += /FS
    DEFINES += "WINVER=0x0501"
    DEFINES += WIN32 _WIN32_WINNT=0x0501
	
    # remove unneccessary output files
    QMAKE_POST_LINK += del /Q ..\\bin\\$${TARGET}.exp ..\\bin\\$${TARGET}.lib

    # copy all needed files to destdir
    QMAKE_POST_LINK += & copy_files.cmd
}

HEADERS = ../base/pch.h \
    ../base/ClubManager.h \
    ../base/ClubManagerDlg.h \
    ../Widgets/Countdown.h \
    ../Widgets/ScaledImage.h \
    ../Widgets/ScaledText.h \
    ../Widgets/SplashScreen.h \
    ../util/path_helpers.h \
    ../util/qstring_serialization.h \
    ../base/MainWindowBase.h \
    ../base/SettingsDlg.h \
    ../base/View.h \
    ScoreScreen.h

SOURCES = ../base/ClubManager.cpp \
    ../base/ClubManagerDlg.cpp \
    ../base/MainWindowBase.cpp \
    ../base/SettingsDlg.cpp \
    ../base/View.cpp \
    ../Widgets/Countdown.cpp \
    ../Widgets/ScaledImage.cpp \
    ../Widgets/ScaledText.cpp \
    ../Widgets/SplashScreen.cpp \
    Main.cpp \
    ScoreScreen.cpp

FORMS = ../base/ClubManagerDlg.ui \
    MainWindow.ui \
    ScoreScreen.ui \
    ../base/SettingsDlg.ui \
    ../base/view_horizontal.ui \
    ../Widgets/SplashScreen.ui \
    ../Widgets/Countdown.ui

OTHER_FILES +=

RESOURCES += ../base/Ipponboard.qrc

TRANSLATIONS = ../i18n/ipponboard_team_de.ts

win32:RC_FILE = ../base/Ipponboard_team.rc
