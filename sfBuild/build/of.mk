################################################################################
# by Marc Wren - www.soul-fresh.com
# This file contains the definitions necessary to compile an ofxFFGLPlugin against openframeworks.
################################################################################

OBJS += \
	${OF_ROOT}/libs/openFrameworksCompiled/lib/osx/openFrameworks.a \
	${OF_ROOT}/libs/glee/lib/osx/GLee.a \
	${OF_ROOT}/libs/rtAudio/lib/osx/rtAudio.a \
	${OF_ROOT}/libs/poco/lib/osx/CppUnit.a \
	${OF_ROOT}/libs/poco/lib/osx/PocoFoundation.a \
	${OF_ROOT}/libs/poco/lib/osx/PocoNet.a \
	${OF_ROOT}/libs/poco/lib/osx/PocoUtil.a \
	${OF_ROOT}/libs/poco/lib/osx/PocoXML.a \
	${OF_ROOT}/libs/freetype/lib/osx/freetype.a \
	${OF_ROOT}/libs/FreeImage/lib/osx/freeimage.a

LIBS += -lfmodex

LIB_DIRS += \
	-L"${OF_ROOT}/libs/openFrameworksCompiled/lib/osx" \
	-L"${OF_ROOT}/addons/Debug" \
	-L"${OF_ROOT}/libs/fmodex/lib/osx" \
	-L"${OF_ROOT}/libs/FreeImage/lib/osx" \
	-L"${OF_ROOT}/libs/freetype/lib/osx" \
	-L"${OF_ROOT}/libs/glee/lib/osx" \
	-L"${OF_ROOT}/libs/poco/lib/osx" \
	-L"${OF_ROOT}/libs/rtAudio/lib/osx"\
	-F${OF_ROOT}/libs/glut/lib/osx

INCLUDE_DIRS += \
	-I"${OF_ROOT}/libs/openFrameworks/app" \
	-I"${OF_ROOT}/libs/openFrameworks/communication" \
	-I"${OF_ROOT}/libs/openFrameworks/events" \
	-I"${OF_ROOT}/libs/openFrameworks/graphics" \
	-I"${OF_ROOT}/libs/openFrameworks/sound" \
	-I"${OF_ROOT}/libs/openFrameworks/utils" \
	-I"${OF_ROOT}/libs/openFrameworks/video" \
	-I"${OF_ROOT}/libs/openFrameworks" \
	-I"${OF_ROOT}/libs/fmodex/include" \
	-I"${OF_ROOT}/libs/FreeImage/include" \
	-I"${OF_ROOT}/libs/freetype/include" \
	-I"${OF_ROOT}/libs/freetype/include/freetype2/freetype" \
	-I"${OF_ROOT}/libs/freetype/include/freetype2/freetype/config" \
	-I"${OF_ROOT}/libs/glee/include" \
	-I"${OF_ROOT}/libs/poco/include" \
	-I"${OF_ROOT}/libs/rtAudio/include"

FRAMEWORKS += \
	-framework AGL \
	-framework ApplicationServices \
	-framework AudioToolbox \
	-framework Carbon \
	-framework CoreAudio \
	-framework CoreMidi \
	-framework CoreFoundation \
	-framework CoreServices \
	-framework OpenGL \
	-framework QuickTime \
	-framework AppKit \
	-framework Cocoa \
	-framework GLUT \
	-framework IOKit \
	-framework CoreVideo \
	-framework Foundation \
	-framework QTKit
