#############################################################################
# Makefile for building: bin/release/Shaders
# Generated by qmake (2.01a) (Qt 4.8.7) on: Fri Sep 29 13:50:51 2017
# Project:  Shaders.pro
# Template: app
# Command: /usr/lib/x86_64-linux-gnu/qt4/bin/qmake -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile Shaders.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_PHONON_LIB -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -std=c++0x -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtOpenGL -I/usr/include/phonon -I/usr/include/qt4 -I. -Isrc -Isrc/interface -I/usr/include/qt4/phonon_compat -I/usr/X11R6/include -Itemp -Itemp
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -L/usr/X11R6/lib -lGLEW -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -lphonon -lQtOpenGL -lQtGui -lQtCore -lGL -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/x86_64-linux-gnu/qt4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = obj/release/

####### Files

SOURCES       = src/interface/GLWidget.cpp \
		src/interface/main.cpp \
		src/interface/mainwindow.cpp \
		src/Bitmap.cpp \
		src/Camera.cpp \
		src/importer.cpp \
		src/Light.cpp \
		src/ModelAsset.cpp \
		src/ModelInstance.cpp \
		src/Program.cpp \
		src/Shader.cpp \
		src/ShadersControler.cpp \
		src/Texture.cpp \
		src/Quaternions.cpp temp/moc_GLWidget.cpp \
		temp/moc_mainwindow.cpp \
		temp/qrc_Res.cpp
OBJECTS       = obj/release/GLWidget.o \
		obj/release/main.o \
		obj/release/mainwindow.o \
		obj/release/Bitmap.o \
		obj/release/Camera.o \
		obj/release/importer.o \
		obj/release/Light.o \
		obj/release/ModelAsset.o \
		obj/release/ModelInstance.o \
		obj/release/Program.o \
		obj/release/Shader.o \
		obj/release/ShadersControler.o \
		obj/release/Texture.o \
		obj/release/Quaternions.o \
		obj/release/moc_GLWidget.o \
		obj/release/moc_mainwindow.o \
		obj/release/qrc_Res.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		Shaders.pro
QMAKE_TARGET  = Shaders
DESTDIR       = bin/release/
TARGET        = bin/release/Shaders

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

all: Makefile $(TARGET)

$(TARGET): temp/ui_mainwindow.h $(OBJECTS)  
	@$(CHK_DIR_EXISTS) bin/release/ || $(MKDIR) bin/release/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: Shaders.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/lib/x86_64-linux-gnu/libQtOpenGL.prl \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile Shaders.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_phonon.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/opengl.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/lib/x86_64-linux-gnu/libQtOpenGL.prl:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile Shaders.pro

dist: 
	@$(CHK_DIR_EXISTS) obj/release/Shaders1.0.0 || $(MKDIR) obj/release/Shaders1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) obj/release/Shaders1.0.0/ && $(COPY_FILE) --parents src/interface/GLWidget.h src/interface/mainwindow.h src/Bitmap.h src/Camera.h src/importer.h src/Light.h src/ModelAsset.h src/ModelInstance.h src/Program.h src/Shader.h src/ShadersControler.h src/stb_image.h src/Texture.h src/Quaternions.h obj/release/Shaders1.0.0/ && $(COPY_FILE) --parents Res.qrc obj/release/Shaders1.0.0/ && $(COPY_FILE) --parents src/interface/GLWidget.cpp src/interface/main.cpp src/interface/mainwindow.cpp src/Bitmap.cpp src/Camera.cpp src/importer.cpp src/Light.cpp src/ModelAsset.cpp src/ModelInstance.cpp src/Program.cpp src/Shader.cpp src/ShadersControler.cpp src/Texture.cpp src/Quaternions.cpp obj/release/Shaders1.0.0/ && $(COPY_FILE) --parents src/interface/mainwindow.ui obj/release/Shaders1.0.0/ && (cd `dirname obj/release/Shaders1.0.0` && $(TAR) Shaders1.0.0.tar Shaders1.0.0 && $(COMPRESS) Shaders1.0.0.tar) && $(MOVE) `dirname obj/release/Shaders1.0.0`/Shaders1.0.0.tar.gz . && $(DEL_FILE) -r obj/release/Shaders1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: temp/moc_GLWidget.cpp temp/moc_mainwindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) temp/moc_GLWidget.cpp temp/moc_mainwindow.cpp
temp/moc_GLWidget.cpp: src/Program.h \
		src/Shader.h \
		src/Texture.h \
		src/Bitmap.h \
		src/Camera.h \
		src/ShadersControler.h \
		src/ModelAsset.h \
		src/ModelInstance.h \
		src/importer.h \
		src/Light.h \
		src/Quaternions.h \
		src/interface/GLWidget.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) src/interface/GLWidget.h -o temp/moc_GLWidget.cpp

temp/moc_mainwindow.cpp: src/interface/mainwindow.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) src/interface/mainwindow.h -o temp/moc_mainwindow.cpp

compiler_rcc_make_all: temp/qrc_Res.cpp
compiler_rcc_clean:
	-$(DEL_FILE) temp/qrc_Res.cpp
temp/qrc_Res.cpp: Res.qrc \
		resources/capa02.jpg \
		resources/capa01.jpg \
		resources/icon.jpg
	/usr/lib/x86_64-linux-gnu/qt4/bin/rcc -name Res Res.qrc -o temp/qrc_Res.cpp

compiler_image_collection_make_all: temp/qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) temp/qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: temp/ui_mainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) temp/ui_mainwindow.h
temp/ui_mainwindow.h: src/interface/mainwindow.ui \
		src/interface/GLWidget.h \
		src/Program.h \
		src/Shader.h \
		src/Texture.h \
		src/Bitmap.h \
		src/Camera.h \
		src/ShadersControler.h \
		src/ModelAsset.h \
		src/ModelInstance.h \
		src/importer.h \
		src/Light.h \
		src/Quaternions.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic src/interface/mainwindow.ui -o temp/ui_mainwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

obj/release/GLWidget.o: src/interface/GLWidget.cpp src/interface/GLWidget.h \
		src/Program.h \
		src/Shader.h \
		src/Texture.h \
		src/Bitmap.h \
		src/Camera.h \
		src/ShadersControler.h \
		src/ModelAsset.h \
		src/ModelInstance.h \
		src/importer.h \
		src/Light.h \
		src/Quaternions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/release/GLWidget.o src/interface/GLWidget.cpp

obj/release/main.o: src/interface/main.cpp src/interface/mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/release/main.o src/interface/main.cpp

obj/release/mainwindow.o: src/interface/mainwindow.cpp src/interface/mainwindow.h \
		temp/ui_mainwindow.h \
		src/interface/GLWidget.h \
		src/Program.h \
		src/Shader.h \
		src/Texture.h \
		src/Bitmap.h \
		src/Camera.h \
		src/ShadersControler.h \
		src/ModelAsset.h \
		src/ModelInstance.h \
		src/importer.h \
		src/Light.h \
		src/Quaternions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/release/mainwindow.o src/interface/mainwindow.cpp

obj/release/Bitmap.o: src/Bitmap.cpp src/Bitmap.h \
		src/stb_image.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/release/Bitmap.o src/Bitmap.cpp

obj/release/Camera.o: src/Camera.cpp src/Camera.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/release/Camera.o src/Camera.cpp

obj/release/importer.o: src/importer.cpp src/importer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/release/importer.o src/importer.cpp

obj/release/Light.o: src/Light.cpp src/Light.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/release/Light.o src/Light.cpp

obj/release/ModelAsset.o: src/ModelAsset.cpp src/ModelAsset.h \
		src/Program.h \
		src/Shader.h \
		src/Texture.h \
		src/Bitmap.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/release/ModelAsset.o src/ModelAsset.cpp

obj/release/ModelInstance.o: src/ModelInstance.cpp src/ModelInstance.h \
		src/ModelAsset.h \
		src/Program.h \
		src/Shader.h \
		src/Texture.h \
		src/Bitmap.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/release/ModelInstance.o src/ModelInstance.cpp

obj/release/Program.o: src/Program.cpp src/Program.h \
		src/Shader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/release/Program.o src/Program.cpp

obj/release/Shader.o: src/Shader.cpp src/Shader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/release/Shader.o src/Shader.cpp

obj/release/ShadersControler.o: src/ShadersControler.cpp src/ShadersControler.h \
		src/Program.h \
		src/Shader.h \
		src/Texture.h \
		src/Bitmap.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/release/ShadersControler.o src/ShadersControler.cpp

obj/release/Texture.o: src/Texture.cpp src/Texture.h \
		src/Bitmap.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/release/Texture.o src/Texture.cpp

obj/release/Quaternions.o: src/Quaternions.cpp src/Quaternions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/release/Quaternions.o src/Quaternions.cpp

obj/release/moc_GLWidget.o: temp/moc_GLWidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/release/moc_GLWidget.o temp/moc_GLWidget.cpp

obj/release/moc_mainwindow.o: temp/moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/release/moc_mainwindow.o temp/moc_mainwindow.cpp

obj/release/qrc_Res.o: temp/qrc_Res.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/release/qrc_Res.o temp/qrc_Res.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

