################################################################################
# Created by Eclipse CDT
# Modified by Marc Wren - www.soul-fresh.com
# TODO: Document...
################################################################################

# Any of the properties below can be overridden by declaring (or modifying)
# them in the makefile.init file in the root of the project.
PROJECT_ROOT = ..
BUILD_COMMANDS_DIR = ${PROJECT_ROOT}/../sfBuild/build
BASE_BIN_DIR = ../bin
BASE_SRC_DIR = ../src
TEST_ENV_DIR = ../../../../../ffglVFXExported
COPY_TO_TEST_ENV = true
OF_ROOT = ../../../../../of_preRelease_v0061_osxSL_FAT
# TODO Is there a good way to autodiscover this?
OS = OSX
BUNDLE_TEMPLATE_DIR = ../../bundleTemplates/src

# Commands
RM = rm -rf
MKDIR = mkdir -p
CP = cp
MV = mv

# These variables will be populated later.
OBJS = 
LIBS = 
LIB_DIRS =
INCLUDE_DIRS =
FRAMEWORKS =

# OS dependent compiler flags.
ifeq ($(strip ${OS}), OSX)
	CC = g++
	LINKER_FLAGS = -arch i386 -mmacosx-version-min=10.4 -isysroot /Developer/SDKs/MacOSX10.5.sdk -w 
	DEFINES = -D__MACOSX_CORE__
	COMPILE_FLAGS = -Wall -c -fmessage-length=0 -mmacosx-version-min=10.4 -m32
ifeq ($(findstring Release,$(MAKECMDGOALS)),Release)
	LINKER_FLAGS += -arch ppc -nostartfiles 
endif
endif

# Setup variables for different build configurations.
# TODO Make it easy to create different build configurations.
ifeq ($(findstring Debug,$(MAKECMDGOALS)),Debug)
	COMPILE_FLAGS += -g3
	BUILD_CONFIGURATION_NAME = Debug
	BIN_DIR = ${BASE_BIN_DIR}/${BUILD_CONFIGURATION_NAME}
else
	BUILD_CONFIGURATION_NAME = Release
	BIN_DIR = ${BASE_BIN_DIR}/${BUILD_CONFIGURATION_NAME}
	COMPILE_FLAGS += -O0
endif

ifeq ($(findstring Plugin,$(MAKECMDGOALS)),Plugin)
	LINKER_FLAGS += -bundle
else
	DEFINES += -D__SF_RUN_AS_STANDALONE_APPLICATION__
endif

# All of the sources participating in the build are defined here
-include $(shell find . -name "src*.mk" | grep -v srcTemplate.mk)
-include ${BUILD_COMMANDS_DIR}/of.mk
-include ${BUILD_COMMANDS_DIR}/addons.mk
# TODO Create a make file for the openFrameworks addons.

# You can override any of the properties above for your individual projects by 
# specifying them in the following file:
-include ../makefile.init

# Build Targets
DebugPlugin: printParameters setupPlugin ${PROJECT_NAME} postPlugin

DebugApplication: printParameters setupApplication ${PROJECT_NAME} postApplication

ReleasePlugin: printParameters setupPlugin ${PROJECT_NAME} postPlugin

# The main compilation target for this project.
${PROJECT_NAME}: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MacOS X C++ Linker'
	@echo '------------------------------'
	${MKDIR} ${BIN_DIR}
	${CC} ${LIB_DIRS} ${LINKER_FLAGS} ${FRAMEWORKS} $(OBJS) $(LIBS) -o ${BIN_DIR}/${PROJECT_NAME}
	@echo '------------------------------'
	@echo 'Finished building target: $@'
	@echo ' '

printParameters:
	@echo '------------------------------'
	@echo 'Current working directory: ${PWD}'
	@echo 'PROJECT_NAME: ${PROJECT_NAME}' 
	@echo 'PLUGIN_MAJOR_VERSION: ${PLUGIN_MAJOR_VERSION}'
	@echo 'PLUGIN_MINOR_VERSION: ${PLUGIN_MINOR_VERSION}'
	@echo 'PLUGIN_BUILD_NUMBER: ${PLUGIN_BUILD_NUMBER}'
	@echo 'PROJECT_ROOT: ${PROJECT_ROOT}'
	@echo 'BASE_BIN_DIR: ${BASE_BIN_DIR}'
	@echo 'BIN_DIR: ${BIN_DIR}'
	@echo 'BASE_SRC_DIR: ${BASE_SRC_DIR}'
	@echo 'TEST_ENV_DIR: ${TEST_ENV_DIR}'
	@echo 'COPY_TO_TEST_ENV: ${COPY_TO_TEST_ENV}'
	@echo 'OF_ROOT: ${OF_ROOT}'
	@echo 'OS: ${OS}'
	@echo 'BUNDLE_TEMPLATE_DIR: ${BUNDLE_TEMPLATE_DIR}'
	@echo '------------------------------'
	@echo ''

# Setup targets to be performed before compilation.
setupPlugin:
	@echo 'Setup Plugin'
	@echo '------------------------------'
	@echo 'No setup required.'
#	cat main.cpp.plugin.template | sed s:PLUGIN_ID:${PLUGIN_ID}: | sed s:PLUGIN_NAME:${PLUGIN_NAME}: | sed s:PLUGIN_MAJOR_VERSION:${PLUGIN_MAJOR_VERSION}: | sed s:PLUGIN_MINOR_VERSION:${PLUGIN_MINOR_VERSION}: > ../src/main.cpp
	@echo '------------------------------'
	@echo ''

setupApplication:
	@echo 'Setup Application'
	@echo '------------------------------'
	@echo 'No setup required.'
#	cat main.cpp.application.template > ../src/main.cpp
	@echo '------------------------------'
	@echo ''

# Post targets to be called after compilation.
postPluginOSX: packagePlugin copyToTestEnv

postPlugin: postPlugin${strip ${OS}}

postApplicationOSX: packageApplication

postApplication: postApplication${strip ${OS}}

# Clean targets.
clean:
	@echo 'Clean'
	@echo '------------------------------'
	-${RM} ${BASE_BIN_DIR} ${OBJS_BASE_DIRS}
	@echo '------------------------------'
	@echo 'Finished clean'
	@echo ''

cleanDebug:
	@echo 'Clean Debug'
	@echo '------------------------------'
	-${RM} ${BASE_BIN_DIR}/Debug ${OBJS_BASE_DIRS}/Debug
	@echo '------------------------------'
	@echo 'Finished clean'
	@echo ''

cleanRelease:
	@echo 'Clean Release'
	@echo '------------------------------'
	-${RM} ${BASE_BIN_DIR}/Release ${OBJS_BASE_DIRS}/Release
	@echo '------------------------------'
	@echo 'Finished clean'
	@echo ''

# Package the output executable into the final format required for use by the target OS.
# TODO Should this go in the makefile.targets file? If so, how do we call it safely from this file?
# TODO Putting this step in an external make file could allow me to overwrite it for different operating systems.
packagePlugin:
	@echo 'Packaging Plugin for OSX'
	@echo '------------------------------' 
# Copy the template bundle into our working directory.
	rm -rf ${BIN_DIR}/${PROJECT_NAME}.bundle
	svn export --force ${BUNDLE_TEMPLATE_DIR} ${BIN_DIR}
# Rename the fmodex library so it can be found by the plugin at runtime.
	install_name_tool -change ./libfmodex.dylib @loader_path/libfmodex.dylib "${BIN_DIR}/${PROJECT_NAME}"
# Move output files into the bundle folder.
	mv ${BIN_DIR}/${PROJECT_NAME} ${BIN_DIR}/template/Contents/MacOS/${PROJECT_NAME} 
# Change the variables inside the Info.plist file from the template folder to match this project.
	cat ${BIN_DIR}/template/Contents/Info.plist | sed s:XXX:${PROJECT_NAME}:g | sed s:VVV:${PLUGIN_MAJOR_VERSION}.${PLUGIN_MINOR_VERSION}.${PLUGIN_BUILD_NUMBER}:g > ${BIN_DIR}/template/Contents/Info.plist
# Create our output bundle
	mv ${BIN_DIR}/template ${BIN_DIR}/${PROJECT_NAME}.bundle
# Save the build number on Release builds
ifeq (${strip ${BUILD_CONFIGURATION_NAME}}, Release)
	echo ${PLUGIN_BUILD_NUMBER} > ../buildnumber.txt
endif
	@echo '------------------------------'
	@echo 'Finished packaging plugin'
	@echo ''
	
packageApplication:
	@echo 'Packaging Application for OSX'
	@echo '------------------------------' 
	cp ${BUNDLE_TEMPLATE_DIR}/template/Contents/MacOS/libfmodex.dylib ${BIN_DIR}
# Rename the fmodex library so it can be found by the plugin at runtime.
	install_name_tool -change ./libfmodex.dylib @loader_path/libfmodex.dylib "${BIN_DIR}/${PROJECT_NAME}" 
	@echo '------------------------------'
	@echo 'Finished packaging application'
	@echo ''

# Copy the finished plugin into a test environment, if that is wanted.
copyToTestEnv:
ifeq ($(strip ${COPY_TO_TEST_ENV}), true)
	@echo 'Copying output to test environment'
	@echo '------------------------------'
	rm -rf ${TEST_ENV_DIR}/${PROJECT_NAME}.bundle
	cp -R ${BIN_DIR}/${PROJECT_NAME}.bundle ${TEST_ENV_DIR}/${PROJECT_NAME}.bundle
	@echo '------------------------------'
	@echo 'Finished copying to test environment'
	@echo ''
endif

# TODO Implement this make file as described below.
# TODO Implement help as the default target.
.PHONY: test
#.PHONY: help
help:
 
	# openFrameworks universal makefile
	#
	# targets:
	# make Debug:  makes the application with debug symbols
	# make Release: makes the app with optimizations
	# make: the same as make Release
	# make CleanDebug: cleans the Debug target
	# make CleanRelease: cleans the Release target
	# make clean: cleans everything
	#
	# this should work with any OF app, just copy any example
	# change the name of the folder and it should compile
	# only .cpp support, don't use .c files
	# it will look for files in any folder inside the application
	# folder except that in the EXCLUDE_FROM_SOURCE variable
	# but you'll need to add the include paths in USER_CFLAGS
	#
	# to add addons to your application, edit the addons.make file
	# in this directory and add the names of the addons you want to
	# include
	#

-include ../makefile.targets
