#############################################################################
# Makefile for building: BISTU_Draughts.app/Contents/MacOS/BISTU_Draughts
# Generated by qmake (3.0) (Qt 5.3.2)
# Project:  BISTU_Draughts.pro
# Template: app
# Command: /usr/local/Qt-5.3.2/bin/qmake -spec macx-clang CONFIG+=x86_64 -o Makefile BISTU_Draughts.pro
#############################################################################

MAKEFILE      = Makefile

####### Compiler, tools and options

CC            = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang
CXX           = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++
DEFINES       = -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB
CFLAGS        = -pipe -g -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk -mmacosx-version-min=10.6 -Wall -W -fPIE $(DEFINES)
CXXFLAGS      = -pipe -g -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk -mmacosx-version-min=10.6 -Wall -W -fPIE $(DEFINES)
INCPATH       = -I/usr/local/Qt-5.3.2/mkspecs/macx-clang -I. -I. -IBackEnd -I/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers -I/usr/local/Qt-5.3.2/lib/QtGui.framework/Versions/5/Headers -I/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers -I. -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/System/Library/Frameworks/AGL.framework/Headers -F/usr/local/Qt-5.3.2/lib
LINK          = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++
LFLAGS        = -headerpad_max_install_names -Wl,-syslibroot,/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk -mmacosx-version-min=10.6
LIBS          = $(SUBLIBS) -F/usr/local/Qt-5.3.2/lib -framework QtWidgets -framework QtGui -framework QtCore -framework OpenGL -framework AGL 
AR            = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ar cq
RANLIB        = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib -s
QMAKE         = /usr/local/Qt-5.3.2/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
STRIP         = 
INSTALL_FILE  = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = $(COPY_FILE)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = chessboard.cpp \
		chesslabel.cpp \
		globalVariable.cpp \
		main.cpp \
		BackEnd/Checker_AlphaBetaSearch.cpp \
		BackEnd/Checker_CheckerState.cpp qrc_PieceImages.cpp \
		moc_chessboard.cpp \
		moc_chesslabel.cpp
OBJECTS       = chessboard.o \
		chesslabel.o \
		globalVariable.o \
		main.o \
		Checker_AlphaBetaSearch.o \
		Checker_CheckerState.o \
		qrc_PieceImages.o \
		moc_chessboard.o \
		moc_chesslabel.o
DIST          = /usr/local/Qt-5.3.2/mkspecs/features/spec_pre.prf \
		/usr/local/Qt-5.3.2/mkspecs/qdevice.pri \
		/usr/local/Qt-5.3.2/mkspecs/features/device_config.prf \
		/usr/local/Qt-5.3.2/mkspecs/common/shell-unix.conf \
		/usr/local/Qt-5.3.2/mkspecs/common/unix.conf \
		/usr/local/Qt-5.3.2/mkspecs/common/mac.conf \
		/usr/local/Qt-5.3.2/mkspecs/common/macx.conf \
		/usr/local/Qt-5.3.2/mkspecs/common/gcc-base.conf \
		/usr/local/Qt-5.3.2/mkspecs/common/gcc-base-mac.conf \
		/usr/local/Qt-5.3.2/mkspecs/common/clang.conf \
		/usr/local/Qt-5.3.2/mkspecs/common/clang-mac.conf \
		/usr/local/Qt-5.3.2/mkspecs/qconfig.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_clucene_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_core.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_core_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_designer.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_designer_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_designercomponents_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_gui.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_help.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_help_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_network.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_network_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_opengl.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_sql.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_svg.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_svg_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_testlib.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_uitools.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_uitools_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_widgets.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_xml.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/features/qt_functions.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/qt_config.prf \
		/usr/local/Qt-5.3.2/mkspecs/macx-clang/qmake.conf \
		/usr/local/Qt-5.3.2/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/usr/local/Qt-5.3.2/mkspecs/features/exclusive_builds.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/default_pre.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/mac/default_pre.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/resolve_config.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/default_post.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/mac/sdk.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/mac/default_post.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/mac/objective_c.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/warn_on.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/qt.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/resources.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/moc.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/unix/opengl.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/uic.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/unix/thread.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/mac/rez.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/testcase_targets.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/exceptions.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/yacc.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/lex.prf \
		BISTU_Draughts.pro chessboard.cpp \
		chesslabel.cpp \
		globalVariable.cpp \
		main.cpp \
		BackEnd/Checker_AlphaBetaSearch.cpp \
		BackEnd/Checker_CheckerState.cpp
QMAKE_TARGET  = BISTU_Draughts
DESTDIR       = #avoid trailing-slash linebreak
TARGET        = BISTU_Draughts.app/Contents/MacOS/BISTU_Draughts

####### Custom Compiler Variables
QMAKE_COMP_QMAKE_OBJECTIVE_CFLAGS = -pipe \
		-g \
		-isysroot \
		/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk \
		-mmacosx-version-min=10.6 \
		-Wall \
		-W



first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile BISTU_Draughts.app/Contents/PkgInfo BISTU_Draughts.app/Contents/Resources/empty.lproj BISTU_Draughts.app/Contents/Info.plist $(TARGET)

$(TARGET):  $(OBJECTS)  
	@test -d BISTU_Draughts.app/Contents/MacOS/ || mkdir -p BISTU_Draughts.app/Contents/MacOS/
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: BISTU_Draughts.pro /usr/local/Qt-5.3.2/mkspecs/macx-clang/qmake.conf /usr/local/Qt-5.3.2/mkspecs/features/spec_pre.prf \
		/usr/local/Qt-5.3.2/mkspecs/qdevice.pri \
		/usr/local/Qt-5.3.2/mkspecs/features/device_config.prf \
		/usr/local/Qt-5.3.2/mkspecs/common/shell-unix.conf \
		/usr/local/Qt-5.3.2/mkspecs/common/unix.conf \
		/usr/local/Qt-5.3.2/mkspecs/common/mac.conf \
		/usr/local/Qt-5.3.2/mkspecs/common/macx.conf \
		/usr/local/Qt-5.3.2/mkspecs/common/gcc-base.conf \
		/usr/local/Qt-5.3.2/mkspecs/common/gcc-base-mac.conf \
		/usr/local/Qt-5.3.2/mkspecs/common/clang.conf \
		/usr/local/Qt-5.3.2/mkspecs/common/clang-mac.conf \
		/usr/local/Qt-5.3.2/mkspecs/qconfig.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_clucene_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_core.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_core_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_designer.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_designer_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_designercomponents_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_gui.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_help.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_help_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_network.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_network_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_opengl.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_sql.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_svg.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_svg_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_testlib.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_uitools.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_uitools_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_widgets.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_xml.pri \
		/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/local/Qt-5.3.2/mkspecs/features/qt_functions.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/qt_config.prf \
		/usr/local/Qt-5.3.2/mkspecs/macx-clang/qmake.conf \
		/usr/local/Qt-5.3.2/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/usr/local/Qt-5.3.2/mkspecs/features/exclusive_builds.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/default_pre.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/mac/default_pre.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/resolve_config.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/default_post.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/mac/sdk.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/mac/default_post.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/mac/objective_c.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/warn_on.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/qt.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/resources.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/moc.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/unix/opengl.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/uic.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/unix/thread.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/mac/rez.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/testcase_targets.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/exceptions.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/yacc.prf \
		/usr/local/Qt-5.3.2/mkspecs/features/lex.prf \
		BISTU_Draughts.pro \
		PieceImages.qrc \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/QtWidgets.prl \
		/usr/local/Qt-5.3.2/lib/QtGui.framework/QtGui.prl \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/QtCore.prl
	$(QMAKE) -spec macx-clang CONFIG+=x86_64 -o Makefile BISTU_Draughts.pro
/usr/local/Qt-5.3.2/mkspecs/features/spec_pre.prf:
/usr/local/Qt-5.3.2/mkspecs/qdevice.pri:
/usr/local/Qt-5.3.2/mkspecs/features/device_config.prf:
/usr/local/Qt-5.3.2/mkspecs/common/shell-unix.conf:
/usr/local/Qt-5.3.2/mkspecs/common/unix.conf:
/usr/local/Qt-5.3.2/mkspecs/common/mac.conf:
/usr/local/Qt-5.3.2/mkspecs/common/macx.conf:
/usr/local/Qt-5.3.2/mkspecs/common/gcc-base.conf:
/usr/local/Qt-5.3.2/mkspecs/common/gcc-base-mac.conf:
/usr/local/Qt-5.3.2/mkspecs/common/clang.conf:
/usr/local/Qt-5.3.2/mkspecs/common/clang-mac.conf:
/usr/local/Qt-5.3.2/mkspecs/qconfig.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_bootstrap_private.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_clucene_private.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_concurrent.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_concurrent_private.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_core.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_core_private.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_designer.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_designer_private.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_designercomponents_private.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_gui.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_gui_private.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_help.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_help_private.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_network.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_network_private.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_opengl.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_opengl_private.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_openglextensions.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_openglextensions_private.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_platformsupport_private.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_printsupport.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_printsupport_private.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_sql.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_sql_private.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_svg.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_svg_private.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_testlib.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_testlib_private.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_uitools.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_uitools_private.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_widgets.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_widgets_private.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_xml.pri:
/usr/local/Qt-5.3.2/mkspecs/modules/qt_lib_xml_private.pri:
/usr/local/Qt-5.3.2/mkspecs/features/qt_functions.prf:
/usr/local/Qt-5.3.2/mkspecs/features/qt_config.prf:
/usr/local/Qt-5.3.2/mkspecs/macx-clang/qmake.conf:
/usr/local/Qt-5.3.2/mkspecs/features/spec_post.prf:
.qmake.stash:
/usr/local/Qt-5.3.2/mkspecs/features/exclusive_builds.prf:
/usr/local/Qt-5.3.2/mkspecs/features/default_pre.prf:
/usr/local/Qt-5.3.2/mkspecs/features/mac/default_pre.prf:
/usr/local/Qt-5.3.2/mkspecs/features/resolve_config.prf:
/usr/local/Qt-5.3.2/mkspecs/features/default_post.prf:
/usr/local/Qt-5.3.2/mkspecs/features/mac/sdk.prf:
/usr/local/Qt-5.3.2/mkspecs/features/mac/default_post.prf:
/usr/local/Qt-5.3.2/mkspecs/features/mac/objective_c.prf:
/usr/local/Qt-5.3.2/mkspecs/features/warn_on.prf:
/usr/local/Qt-5.3.2/mkspecs/features/qt.prf:
/usr/local/Qt-5.3.2/mkspecs/features/resources.prf:
/usr/local/Qt-5.3.2/mkspecs/features/moc.prf:
/usr/local/Qt-5.3.2/mkspecs/features/unix/opengl.prf:
/usr/local/Qt-5.3.2/mkspecs/features/uic.prf:
/usr/local/Qt-5.3.2/mkspecs/features/unix/thread.prf:
/usr/local/Qt-5.3.2/mkspecs/features/mac/rez.prf:
/usr/local/Qt-5.3.2/mkspecs/features/testcase_targets.prf:
/usr/local/Qt-5.3.2/mkspecs/features/exceptions.prf:
/usr/local/Qt-5.3.2/mkspecs/features/yacc.prf:
/usr/local/Qt-5.3.2/mkspecs/features/lex.prf:
BISTU_Draughts.pro:
PieceImages.qrc:
/usr/local/Qt-5.3.2/lib/QtWidgets.framework/QtWidgets.prl:
/usr/local/Qt-5.3.2/lib/QtGui.framework/QtGui.prl:
/usr/local/Qt-5.3.2/lib/QtCore.framework/QtCore.prl:
qmake: FORCE
	@$(QMAKE) -spec macx-clang CONFIG+=x86_64 -o Makefile BISTU_Draughts.pro

qmake_all: FORCE

BISTU_Draughts.app/Contents/PkgInfo: 
	@test -d BISTU_Draughts.app/Contents || mkdir -p BISTU_Draughts.app/Contents
	@$(DEL_FILE) BISTU_Draughts.app/Contents/PkgInfo
	@echo "APPL????" >BISTU_Draughts.app/Contents/PkgInfo
BISTU_Draughts.app/Contents/Resources/empty.lproj: 
	@test -d BISTU_Draughts.app/Contents/Resources || mkdir -p BISTU_Draughts.app/Contents/Resources
	@touch BISTU_Draughts.app/Contents/Resources/empty.lproj
	
BISTU_Draughts.app/Contents/Info.plist: 
	@test -d BISTU_Draughts.app/Contents || mkdir -p BISTU_Draughts.app/Contents
	@$(DEL_FILE) BISTU_Draughts.app/Contents/Info.plist
	@sed -e "s,@SHORT_VERSION@,1.0,g" -e "s,@TYPEINFO@,????,g" -e "s,@ICON@,,g" -e "s,@BUNDLEIDENTIFIER@,BISTU.BISTU_Draughts,g" -e "s,@EXECUTABLE@,BISTU_Draughts,g" -e "s,@TYPEINFO@,????,g" /usr/local/Qt-5.3.2/mkspecs/macx-clang/Info.plist.app >BISTU_Draughts.app/Contents/Info.plist
dist: 
	@test -d .tmp/BISTU_Draughts1.0.0 || mkdir -p .tmp/BISTU_Draughts1.0.0
	$(COPY_FILE) --parents $(DIST) .tmp/BISTU_Draughts1.0.0/ && $(COPY_FILE) --parents PieceImages.qrc .tmp/BISTU_Draughts1.0.0/ && $(COPY_FILE) --parents chessboard.h chesslabel.h globalVariable.h BackEnd/Checker_AlphaBetaSearch.h BackEnd/Checker_CheckerState.h BackEnd/DataStructure.h .tmp/BISTU_Draughts1.0.0/ && $(COPY_FILE) --parents chessboard.cpp chesslabel.cpp globalVariable.cpp main.cpp BackEnd/Checker_AlphaBetaSearch.cpp BackEnd/Checker_CheckerState.cpp .tmp/BISTU_Draughts1.0.0/ && (cd `dirname .tmp/BISTU_Draughts1.0.0` && $(TAR) BISTU_Draughts1.0.0.tar BISTU_Draughts1.0.0 && $(COMPRESS) BISTU_Draughts1.0.0.tar) && $(MOVE) `dirname .tmp/BISTU_Draughts1.0.0`/BISTU_Draughts1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/BISTU_Draughts1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) -r BISTU_Draughts.app
	-$(DEL_FILE) Makefile


####### Sub-libraries

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

check: first

compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_rcc_make_all: qrc_PieceImages.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_PieceImages.cpp
qrc_PieceImages.cpp: PieceImages.qrc \
		Images/red1.png \
		Images/blackKing.png \
		Images/avaliable.png \
		Images/redKing.png \
		Images/canMove.png \
		Images/blackKing1.png \
		Images/redKing1.png \
		Images/black1.png \
		Images/red.png \
		Images/black.png \
		Images/avaliable1.png
	/usr/local/Qt-5.3.2/bin/rcc -name PieceImages PieceImages.qrc -o qrc_PieceImages.cpp

compiler_moc_header_make_all: moc_chessboard.cpp moc_chesslabel.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_chessboard.cpp moc_chesslabel.cpp
moc_chessboard.cpp: /usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QLabel \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qlabel.h \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QPushButton \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qpushbutton.h \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QGridLayout \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qgridlayout.h \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QMessageBox \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qmessagebox.h \
		chesslabel.h \
		/usr/local/Qt-5.3.2/lib/QtGui.framework/Versions/5/Headers/QMouseEvent \
		/usr/local/Qt-5.3.2/lib/QtGui.framework/Versions/5/Headers/qevent.h \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QApplication \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qapplication.h \
		globalVariable.h \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/QPair \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/qpair.h \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/QList \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/qlist.h \
		BackEnd/DataStructure.h \
		BackEnd/Checker_AlphaBetaSearch.h \
		BackEnd/Checker_CheckerState.h \
		chessboard.h
	/usr/local/Qt-5.3.2/bin/moc $(DEFINES) -D__APPLE__ -D__GNUC__=4 -I/usr/local/Qt-5.3.2/mkspecs/macx-clang -I/Users/Dmm/Project/BISTU_Draughts -I/Users/Dmm/Project/BISTU_Draughts -I/Users/Dmm/Project/BISTU_Draughts/BackEnd -I/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Headers -I/usr/local/Qt-5.3.2/lib/QtGui.framework/Headers -I/usr/local/Qt-5.3.2/lib/QtCore.framework/Headers -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/usr/include/c++/4.2.1 -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/usr/include/c++/4.2.1/backward -I/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/6.0/include -I/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/usr/include -F/usr/local/Qt-5.3.2/lib chessboard.h -o moc_chessboard.cpp

moc_chesslabel.cpp: /usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QLabel \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qlabel.h \
		/usr/local/Qt-5.3.2/lib/QtGui.framework/Versions/5/Headers/QMouseEvent \
		/usr/local/Qt-5.3.2/lib/QtGui.framework/Versions/5/Headers/qevent.h \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QApplication \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qapplication.h \
		globalVariable.h \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/QPair \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/qpair.h \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/QList \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/qlist.h \
		chesslabel.h
	/usr/local/Qt-5.3.2/bin/moc $(DEFINES) -D__APPLE__ -D__GNUC__=4 -I/usr/local/Qt-5.3.2/mkspecs/macx-clang -I/Users/Dmm/Project/BISTU_Draughts -I/Users/Dmm/Project/BISTU_Draughts -I/Users/Dmm/Project/BISTU_Draughts/BackEnd -I/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Headers -I/usr/local/Qt-5.3.2/lib/QtGui.framework/Headers -I/usr/local/Qt-5.3.2/lib/QtCore.framework/Headers -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/usr/include/c++/4.2.1 -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/usr/include/c++/4.2.1/backward -I/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/6.0/include -I/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/usr/include -F/usr/local/Qt-5.3.2/lib chesslabel.h -o moc_chesslabel.cpp

compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_rcc_clean compiler_moc_header_clean 

####### Compile

chessboard.o: chessboard.cpp chessboard.h \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QLabel \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qlabel.h \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QPushButton \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qpushbutton.h \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QGridLayout \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qgridlayout.h \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QMessageBox \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qmessagebox.h \
		chesslabel.h \
		/usr/local/Qt-5.3.2/lib/QtGui.framework/Versions/5/Headers/QMouseEvent \
		/usr/local/Qt-5.3.2/lib/QtGui.framework/Versions/5/Headers/qevent.h \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QApplication \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qapplication.h \
		globalVariable.h \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/QPair \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/qpair.h \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/QList \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/qlist.h \
		BackEnd/DataStructure.h \
		BackEnd/Checker_AlphaBetaSearch.h \
		BackEnd/Checker_CheckerState.h \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/QDebug \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/qdebug.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o chessboard.o chessboard.cpp

chesslabel.o: chesslabel.cpp chesslabel.h \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QLabel \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qlabel.h \
		/usr/local/Qt-5.3.2/lib/QtGui.framework/Versions/5/Headers/QMouseEvent \
		/usr/local/Qt-5.3.2/lib/QtGui.framework/Versions/5/Headers/qevent.h \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QApplication \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qapplication.h \
		globalVariable.h \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/QPair \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/qpair.h \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/QList \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/qlist.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o chesslabel.o chesslabel.cpp

globalVariable.o: globalVariable.cpp /usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/QString \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/qstring.h \
		globalVariable.h \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/QPair \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/qpair.h \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/QList \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/qlist.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o globalVariable.o globalVariable.cpp

main.o: main.cpp /usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QApplication \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qapplication.h \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QDialog \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qdialog.h \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QInputDialog \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qinputdialog.h \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QLabel \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qlabel.h \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/QTextCodec \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/qtextcodec.h \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QGridLayout \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qgridlayout.h \
		chessboard.h \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QPushButton \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qpushbutton.h \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/QMessageBox \
		/usr/local/Qt-5.3.2/lib/QtWidgets.framework/Versions/5/Headers/qmessagebox.h \
		chesslabel.h \
		/usr/local/Qt-5.3.2/lib/QtGui.framework/Versions/5/Headers/QMouseEvent \
		/usr/local/Qt-5.3.2/lib/QtGui.framework/Versions/5/Headers/qevent.h \
		globalVariable.h \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/QPair \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/qpair.h \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/QList \
		/usr/local/Qt-5.3.2/lib/QtCore.framework/Versions/5/Headers/qlist.h \
		BackEnd/DataStructure.h \
		BackEnd/Checker_AlphaBetaSearch.h \
		BackEnd/Checker_CheckerState.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

Checker_AlphaBetaSearch.o: BackEnd/Checker_AlphaBetaSearch.cpp BackEnd/Checker_AlphaBetaSearch.h \
		BackEnd/Checker_CheckerState.h \
		BackEnd/DataStructure.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Checker_AlphaBetaSearch.o BackEnd/Checker_AlphaBetaSearch.cpp

Checker_CheckerState.o: BackEnd/Checker_CheckerState.cpp BackEnd/Checker_CheckerState.h \
		BackEnd/DataStructure.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Checker_CheckerState.o BackEnd/Checker_CheckerState.cpp

qrc_PieceImages.o: qrc_PieceImages.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_PieceImages.o qrc_PieceImages.cpp

moc_chessboard.o: moc_chessboard.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_chessboard.o moc_chessboard.cpp

moc_chesslabel.o: moc_chesslabel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_chesslabel.o moc_chesslabel.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

