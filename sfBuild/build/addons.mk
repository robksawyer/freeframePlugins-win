################################################################################
# by Marc Wren - www.soul-fresh.com
# This file contains the definitions necessary to compile an ofxFFGLPlugin against openframeworks addons.
################################################################################

# TODO Make this dynamic and compile specific addons as opposed to all.
LIBS += -lofAddons

# TODO Only include those addons that are necessary.
INCLUDE_DIRS += \
	-I"${OF_ROOT}/addons/ofx3DModelLoader/src" \
	-I"${OF_ROOT}/addons/ofx3DModelLoader/src/3DS" \
	-I"${OF_ROOT}/addons/ofx3DUtils/src" \
	-I"${OF_ROOT}/addons/ofxDirList/src" \
	-I"${OF_ROOT}/addons/ofxFFGLPlugin/libs/FFGL" \
	-I"${OF_ROOT}/addons/ofxFFGLPlugin/src" \
	-I"${OF_ROOT}/addons/ofxMidi/src"\
	-I"${OF_ROOT}/addons/ofxMidi/libs"\
	-I"${OF_ROOT}/addons/ofxMidi/events"\
	-I"${OF_ROOT}/addons/ofxNetwork/src" \
	-I"${OF_ROOT}/addons/ofxOpenCv/src" \
	-I"${OF_ROOT}/addons/ofxOsc/src" \
	-I"${OF_ROOT}/addons/ofxThread/src" \
	-I"${OF_ROOT}/addons/ofxVectorGraphics/src" \
	-I"${OF_ROOT}/addons/ofxVectorMath/src" \
	-I"${OF_ROOT}/addons/ofxXmlSettings/src" \
	-I"${OF_ROOT}/addons/ofxOpenCv/libs/opencv/include" \
	-I"${OF_ROOT}/addons/ofxOsc/libs/oscpack/include/ip" \
	-I"${OF_ROOT}/addons/ofxOsc/libs/oscpack/include/osc" \
	-I"${OF_ROOT}/addons/ofxVectorGraphics/libs" \
	-I"${OF_ROOT}/addons/ofxXmlSettings/libs"\
	-I"${OF_ROOT}/addons/PennerEasing"
