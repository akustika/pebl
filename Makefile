#//////////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////////////////////////////////////
#//
#//	Copyright (c) 2003-2011
#//	Shane T. Mueller, Ph.D.  smueller at obereed dot net
#//
#//     This file is part of the PEBL project.
#//
#//    PEBL is free software; you can redistribute it and/or modify
#//    it under the terms of the GNU General Public License as published by
#//    the Free Software Foundation; either version 2 of the License, or
#//    (at your option) any later version.
#//
#//    PEBL is distributed in the hope that it will be useful,
#//    but WITHOUT ANY WARRANTY; without even the implied warranty of
#//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#//    GNU General Public License for more details.
#//
#//    You should have received a copy of the GNU General Public License
#//    along with PEBL; if not, write to the Free Software
#//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
#//
#//////////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////////////////////////////////////////////

#This only affects install location.  The binary should be 
#locatable anywhere
PREFIX = /usr/local/
#On mac, one might prefer the following:
#PREFIX = /opt/local/



C   = gcc
CXX = g++ 
DEBUGFLAGS = -lefence -DPEBL_DEBUG -g

CFLAGS =   -O3 -std=c99 -DPREFIX=$(PREFIX)


CXXFLAGS =  -O3  -Wno-deprecated -Wall -pedantic -DPEBL_UNIX  -DENABLE_BINRELOC -DPREFIX=$(PREFIX)  



SDL_CONFIG = /usr/bin/sdl-config

SDL_FLAGS = -I/usr/include/SDL -D_REENTRANT
SDL_LIBS = -L/usr/lib -Wl,-rpath,/usr/local/lib -lSDL -lpthread 


#Comment/uncomment below on OSX
#OSX_FLAGS = -framework AppKit -lSDLmain -DPEBL_OSX
OSX_FLAGS =

SDLIMG_FLAGS =  -L/usr/lib -Wl,-rpath,/usr/lib
SDLIMG_LIBS =   -lSDL -lpthread -lSDL_image -lSDL_net


SHELL = /bin/bash
BISON = /usr/bin/bison
FLEX  = /usr/bin/flex

BIN_DIR  = bin
SBIN_DIR = sbin
OBJ_DIR  = obj
OUT_DIR  = output
SRC_DIR  = src
BASE_DIR = src/base
APPS_DIR = src/apps
LIBS_DIR = src/libs
OBJECTS_DIR = src/objects
DEVICES_DIR = src/devices
PLATFORMS_DIR = src/platforms
SDL_DIR = src/platforms/sdl
UTIL_DIR = src/utility
TEST_DIR = src/tests


vpath %.o   $(OBJ_DIR)
vpath %.cpp $(SRC_DIR)
vpath %.c   $(SRC_DIR)
vpath %.h   $(SRC_DIR)
vpath %.hpp $(SRC_DIR)
vpath %.y   $(SRC_DIR)
vpath %.l   $(SRC_DIR)


PUTILITIES_SRC = $(UTIL_DIR)/PEBLUtility.cpp \
		$(UTIL_DIR)/PError.cpp \
		$(UTIL_DIR)/BinReloc.cpp \
		$(UTIL_DIR)/PEBLPath.cpp

PUTILITIES_OBJ  = $(patsubst %.cpp, %.o, $(PUTILITIES_SRC))
PUTILITIES_INC  = $(patsubst %.cpp, %.h, $(PUTILITIES_SRC))


PEBLBASE_SRCXX =	$(BASE_DIR)/Evaluator.cpp \
			$(BASE_DIR)/FunctionMap.cpp \
			$(BASE_DIR)/grammar.tab.cpp \
			$(BASE_DIR)/PEBLObject.cpp \
			$(BASE_DIR)/Loader.cpp \
			$(BASE_DIR)/PComplexData.cpp \
			$(BASE_DIR)/PList.cpp \
			$(BASE_DIR)/PNode.cpp \
			$(BASE_DIR)/VariableMap.cpp \
			$(DEVICES_DIR)/PEventLoop.cpp \
			$(BASE_DIR)/Variant.cpp 

PEBLBASE_OBJXX = $(patsubst %.cpp, %.o, $(PEBL_SRCXX))


PEBLBASE_SRC = lex.yy.c
PEBLBASE_OBJ = $(patsubst %.c, %.o, $(PEBL_SRC))


POBJECT_SRC  =  $(OBJECTS_DIR)/PEnvironment.cpp \
		$(OBJECTS_DIR)/PWidget.cpp \
		$(OBJECTS_DIR)/PWindow.cpp  \
		$(OBJECTS_DIR)/PImageBox.cpp \
		$(OBJECTS_DIR)/PCanvas.cpp  \
		$(OBJECTS_DIR)/PColor.cpp  \
		$(OBJECTS_DIR)/PDrawObject.cpp \
		$(OBJECTS_DIR)/PFont.cpp \
		$(OBJECTS_DIR)/PTextObject.cpp \
		$(OBJECTS_DIR)/PLabel.cpp \
		$(OBJECTS_DIR)/PTextBox.cpp \
		$(PUTILITIES_SRC)


POBJECT_OBJ  = $(patsubst %.cpp, %.o, $(POBJECT_SRC))
POBJECT_INC  = $(patsubst %.cpp, %.h, $(POBJECT_SRC))


PDEVICES_SRC =  $(DEVICES_DIR)/PDevice.cpp \
	$(DEVICES_DIR)/PEventQueue.cpp \
	$(DEVICES_DIR)/PEvent.cpp\
	$(DEVICES_DIR)/PKeyboard.cpp \
	$(DEVICES_DIR)/PTimer.cpp \
	$(DEVICES_DIR)/DeviceState.cpp \
	$(DEVICES_DIR)/PStream.cpp \
	$(DEVICES_DIR)/PAudioOut.cpp \
	$(DEVICES_DIR)/PNetwork.cpp \
	$(DEVICES_DIR)/PParallelPort.cpp 


PDEVICES_OBJ  = $(patsubst %.cpp, %.o, $(PDEVICES_SRC))
PDEVICES_INC  = $(patsubst %.cpp, %.h, $(PDEVICES_SRC))



PLATFORM_SDL_SRC  =	$(SDL_DIR)/PlatformEnvironment.cpp \
			$(SDL_DIR)/PlatformWidget.cpp \
			$(SDL_DIR)/PlatformWindow.cpp \
			$(SDL_DIR)/PlatformImageBox.cpp \
			$(SDL_DIR)/PlatformKeyboard.cpp \
			$(SDL_DIR)/PlatformFont.cpp \
			$(SDL_DIR)/PlatformLabel.cpp \
			$(SDL_DIR)/PlatformTextBox.cpp \
			$(SDL_DIR)/PlatformTimer.cpp	\
			$(SDL_DIR)/PlatformDrawObject.cpp \
			$(SDL_DIR)/PlatformCanvas.cpp \
			$(SDL_DIR)/SDLUtility.cpp \
		   	$(SDL_DIR)/PlatformEventQueue.cpp \
			$(SDL_DIR)/PlatformAudioOut.cpp \
			$(SDL_DIR)/PlatformNetwork.cpp

PLATFORM_SDL_OBJ  = 	$(patsubst %.cpp, %.o, $(PLATFORM_SDL_SRC))
PLATFORM_SDL_INC  = 	$(patsubst %.cpp, %.h, $(PLATFORM_SDL_SRC))


FUNCTIONLIB_SRC = $(LIBS_DIR)/PEBLMath.cpp \
		  		$(LIBS_DIR)/PEBLStream.cpp \
	 	  		$(LIBS_DIR)/PEBLObjects.cpp \
                  $(LIBS_DIR)/PEBLEnvironment.cpp \
                  $(LIBS_DIR)/PEBLList.cpp \
                  $(LIBS_DIR)/PEBLString.cpp

FUNCTIONLIB_OBJ =  $(patsubst %.cpp, %.o, $(FUNCTIONLIB_SRC))
FUNCTIONLIB_INC =  $(patsubst %.cpp, %.h, $(FUNCTIONLIB_SRC))

TEST_VARIANT_SRC = $(TEST_DIR)/VariantTest.cpp $(PEBLBASE_SRCXX) \
			$(PDEVICES_SRC) \
			$(FUNCTIONLIB_SRC) \
			$(POBJECT_SRC) \
			$(PLATFORM_SDL_SRC)
TEST_VARIANT_OBJ = $(patsubst %.cpp, %.o, $(TEST_VARIANT_SRC))
TEST_VARIANT_INC = $(patsubst %.cpp, %.h, $(TEST_VARIANT_SRC))



TEST_VARIABLE_MAP_SRC = $(TEST_DIR)/VariableMapTest.cpp \
		$(PEBLBASE_SRCXX) \
			$(PDEVICES_SRC) \
			$(FUNCTIONLIB_SRC) \
			$(POBJECT_SRC) \
			$(PLATFORM_SDL_SRC)


TEST_VARIABLE_MAP_OBJ = $(patsubst %.cpp, %.o, $(TEST_VARIABLE_MAP_SRC))
TEST_VARIABLE_MAP_INC = $(patsubst %.cpp, %.h, $(TEST_VARIABLE_MAP_SRC))



TEST_PNODE_SRC = $(TEST_DIR)/PNodeTest.cpp $(BASE_DIR)/Variant.cpp\
   $(BASE_DIR)/PComplexData.cpp $(BASE_DIR)/PList.cpp $(BASE_DIR)/PNode.cpp \
   $(OBJECTS_DIR)/PObject.cpp $(UTIL_DIR)/PEBLUtility.cpp
TEST_PNODE_OBJ = $(patsubst %.cpp, %.o, $(TEST_PNODE_SRC))
TEST_PNODE_INC = $(patsubst %.cpp, %.h, $(TEST_PNODE_SRC))

TEST_PARSER_SRC = $(TEST_DIR)/ParserTest.cpp $(PEBLBASE_SRCXX) \
			$(PDEVICES_SRC) \
			$(FUNCTIONLIB_SRC) \
			$(POBJECT_SRC) \
			$(PLATFORM_SDL_SRC)

TEST_PARSER_OBJ = $(patsubst %.cpp, %.o, $(TEST_PARSER_SRC))
TEST_PARSER_INC = $(patsubst %.cpp, %.h, $(TEST_PARSER_SRC))


TEST_FMAP_SRC = $(TEST_DIR)/FunctionMapTest.cpp $(BASE_DIR)/FunctionMap.cpp $(BASE_DIR)/Variant.cpp $(BASE_DIR)/PComplexData.cpp $(BASE_DIR)/PList.cpp $(BASE_DIR)/PNode.cpp $(OBJECTS_DIR)/PObject.cpp $(UTIL_DIR)/PEBLUtility.cpp
TEST_FMAP_OBJ = $(patsubst %.cpp, %.o, $(TEST_FMAP_SRC))
TEST_FMAP_INC = $(patsubst %.cpp, %.h, $(TEST_FMAP_SRC))


TEST_MATHLIBS_SRC = $(TEST_DIR)/MathLibTest.cpp $(LIBS_DIR)/PEBLMath.cpp $(BASE_DIR)/Variant.cpp $(BASE_DIR)/PList.cpp  $(BASE_DIR)/PComplexData.cpp
TEST_MATHLIBS_OBJ = $(patsubst %.cpp, %.o, $(TEST_MATHLIBS_SRC))
TEST_MATHLIBS_INC = $(patsubst %.cpp, %.h, $(TEST_MATHLIBS_SRC))

TEST_WINDOW_SRC = $(PLATFORM_SDL_SRC) $(POBJECT_SRC) $(PDEVICES_SRC)  $(TEST_DIR)/WindowTest.cpp
TEST_WINDOW_OBJ = $(patsubst %.cpp, %.o, $(TEST_WINDOW_SRC))
TEST_WINDOW_INC = $(patsubst %.cpp, %.h, $(TEST_WINDOW_SRC))

TEST_COLOR_SRC =  $(OBJECTS_DIR)/PColor.cpp $(OBJECTS_DIR)/PObject.cpp $(BASE_DIR)/PComplexData.cpp  $(PUTILITIES_SRC) $(TEST_DIR)/ColorTest.cpp
TEST_COLOR_OBJ = $(patsubst %.cpp, %.o, $(TEST_COLOR_SRC))
TEST_COLOR_INC = $(patsubst %.cpp, %.h, $(TEST_COLOR_SRC))

TEST_FONT_SRC =  $(PEBLBASE_SRCXX) $(FUNCTIONLIB_SRC) $(OBJECTS_DIR)/PColor.cpp $(OBJECTS_DIR)/PObject.cpp $(BASE_DIR)/PComplexData.cpp $(OBJECTS_DIR)/PFont.cpp  $(PUTILITIES_SRC) $(TEST_DIR)/FontTest.cpp
TEST_FONT_OBJ = $(patsubst %.cpp, %.o, $(TEST_FONT_SRC))
TEST_FONT_INC = $(patsubst %.cpp, %.h, $(TEST_FONT_SRC))

TEST_PSTREAM_SRC =   $(DEVICES_DIR)/PStream.cpp $(DEVICES_DIR)/PDevice.cpp $(TEST_DIR)/PStreamTest.cpp
TEST_PSTREAM_OBJ = $(patsubst %.cpp, %.o, $(TEST_PSTREAM_SRC))
TEST_PSTREAM_INC = $(patsubst %.cpp, %.h, $(TEST_PSTREAM_SRC))

TEST_AUDIOOUT_SRC = src/platforms/sdl/PlatformAudioOut.cpp src/devices/PAudioOut.cpp src/devices/PDevice.cpp $(TEST_DIR)/AudioOutTest.cpp
TEST_AUDIOOUT_OBJ = $(patsubst %.cpp, %.o, $(TEST_AUDIOOUT_SRC))
TEST_AUDIOOUT_INC = $(patsubst %.cpp, %.h, $(TEST_AUDIOOUT_SRC))

TEST_PATH_SRC = $(TEST_DIR)/PathTest.cpp  $(UTIL_DIR)/PEBLPath.cpp
TEST_PATH_OBJ = $(patsubst %.cpp, %.o, $(TEST_PATH_SRC))
TEST_PATH_INC = $(patsubst %.cpp, %.h, $(TEST_PATH_SRC))


VCG_MAKER_SRC = $(BASE_DIR)/VCG.cpp  $(PEBLBASE_SRCXX)  $(POBJECT_SRC) $(FUNCTIONLIB_SRC) $(PUTILITY_SRC)
VCG_MAKER_OBJ = $(patsubst %.cpp, %.o, $(VCG_MAKER_SRC))
VCG_MAKER_INC = $(patsubst %.cpp, %.h, $(VCG_MAKER_SRC))


PEBLMAIN_SRC = 		$(APPS_DIR)/PEBL.cpp \
			$(PEBLBASE_SRCXX) \
			$(PDEVICES_SRC) \
			$(FUNCTIONLIB_SRC) \
			$(POBJECT_SRC) \
			$(PLATFORM_SDL_SRC)

PEBLMAIN_OBJ = $(patsubst %.cpp, %.o, $(PEBLMAIN_SRC))
PEBLMAIN_INC = $(patsubst %.cpp, %.h, $(PEBLMAIN_SRC))

PEBLMAIN_EXTRA = $(LIBS_DIR)/Functions.h \
	           	$(OBJECTS_DIR)/RGBColorNames.h \


DIRS = \
	$(OBJ_DIR) \
	$(OBJ_DIR)/$(SRC_DIR) \
	$(OBJ_DIR)/$(BASE_DIR) \
	$(OBJ_DIR)/$(APPS_DIR) \
	$(OBJ_DIR)/$(OBJECTS_DIR) \
	$(OBJ_DIR)/$(LIBS_DIR) \
	$(OBJ_DIR)/$(DEVICES_DIR) \
	$(OBJ_DIR)/$(PLATFORMS_DIR) \
	$(OBJ_DIR)/$(SDL_DIR) \
	$(OBJ_DIR)/$(UTIL_DIR) \
	$(OBJ_DIR)/$(TEST_DIR)


##############################
# Dependencies
#

main:  $(DIRS) $(PEBLMAIN_OBJ) $(PEBLMAIN_INC)

	$(CXX) $(CXXFLAGS)   -o $(BIN_DIR)/pebl -I$(PREFIX)include/SDL -D_REENTRANT \
	   -L$(PREFIX)/lib -lSDL -lpthread -lSDL_image -lSDL_ttf -lSDL_gfx  -lSDL_net -lpng \
       $(OSX_FLAGS) $(BASE_DIR)/$(PEBLBASE_SRC) $(patsubst %.o, $(OBJ_DIR)/%.o, \
       $(PEBLMAIN_OBJ))

deb:    main
	epm -f deb pebl

parse:
	bison -d $(BASE_DIR)/grammar.y -o $(BASE_DIR)/grammar.tab.cpp
	flex -o$(BASE_DIR)/lex.yy.c  $(BASE_DIR)/Pebl.l

parse-debug:
	bison -d $(BASE_DIR)/grammar.y -t --verbose --graph=bison.vcg -o $(BASE_DIR)/grammar.tab.cpp
	flex  -o$(BASE_DIR)/lex.yy.c -d $(BASE_DIR)/Pebl.l

.PHONY: tests
tests:  $(BIN_DIR)/varianttest $(BIN_DIR)/variablemaptest $(BIN_DIR)/pnodetest $(BIN_DIR)/parsertest $(BIN_DIR)/functionmaptest

$(BIN_DIR)/varianttest: $(TEST_VARIANT_OBJ) $(TEST_VARIANT_INC)  $(POBJECT_OBJ) $(PLATFORM_SDL_OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/varianttest 	-Wall -I$(PREFIX)include/SDL -D_REENTRANT  \
	   -L$(PREFIX)lib -lSDL -lpthread -lSDL_image -lSDL_ttf  $(BASE_DIR)/lex.yy.c $(patsubst %.o, $(OBJ_DIR)/%.o, $(TEST_VARIANT_OBJ))

$(BIN_DIR)/variablemaptest: $(TEST_VARIABLE_MAP_OBJ) $(TEST_VARIABLE_MAP_INC)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/variablemaptest -I$(PREFIX)include/SDL -D_REENTRANT \
	-L$(PREFIX)lib -lSDL -lpthread -lSDL_image -lSDL_ttf -lSDL_gfx  $(OSX_FLAGS) \
	 $(BASE_DIR)/$(PEBLBASE_SRC) $(patsubst %.o, $(OBJ_DIR)/%.o, $(TEST_VARIABLE_MAP_OBJ))

$(BIN_DIR)/pnodetest: $(TEST_PNODE_OBJ) $(TEST_PNODE_INC)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/pnodetest $(patsubst %.o, $(OBJ_DIR)/%.o, $(TEST_PNODE_OBJ))

$(BIN_DIR)/parsertest: $(TEST_PARSER_OBJ) $(TEST_PARSER_INC)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/parsertest -g -O2 -Wall -I$(PREFIX)include/SDL -D_REENTRANT  \
	   -L$(PREFIX)lib -lSDL -lpthread -lSDL_image -lSDL_ttf \
	 $(BASE_DIR)/$(PEBLBASE_SRC) $(patsubst %.o, $(OBJ_DIR)/%.o, $(TEST_PARSER_OBJ))

$(BIN_DIR)/functionmaptest:  $(TEST_FMAP_OBJ) $(TEST_FMAP_INC)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/functionmaptest  $(patsubst %.o, $(OBJ_DIR)/%.o, $(TEST_FMAP_OBJ))

$(BIN_DIR)/mathlibstest:  $(TEST_MATHLIBS_OBJ) $(TEST_MATHLIBS_INC)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/mathlibstest  $(patsubst %.o, $(OBJ_DIR)/%.o, $(TEST_MATHLIBS_OBJ))

$(BIN_DIR)/colortest:  $(TEST_COLOR_OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/colortest  $(patsubst %.o, $(OBJ_DIR)/%.o, $(TEST_COLOR_OBJ))

$(BIN_DIR)/fonttest:  $(TEST_FONT_OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/fonttest  $(patsubst %.o, $(OBJ_DIR)/%.o, $(TEST_FONT_OBJ))

$(BIN_DIR)/VCGMaker: $(APPS_DIR)/VCGMaker.cpp $(VCG_MAKER_OBJ) $(VCG_MAKER_INC) $(PUTILITIES_OBJ) $(PLATFORM_SDL_OBJ) $(PDEVICES_OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/VCGMaker -O2 -Wall -I$(PREFIX)include/SDL -D_REENTRANT  \
	   -L$(PREFIX)lib -lSDL -lpthread -lSDL_image -lSDL_ttf -lSDL_gfx  $(BASE_DIR)/$(PEBLBASE_SRC) \
        $(APPS_DIR)/VCGMaker.cpp $(patsubst %.o, $(OBJ_DIR)/%.o, $(VCG_MAKER_OBJ) $(PLATFORM_SDL_OBJ) $(PDEVICES_OBJ))

$(BIN_DIR)/windowtest:  $(TEST_WINDOW_OBJ) $(TEST_WINDOW_INC)
	$(CXX) $(CXXFLAGS) -O2 -Wall -I$(PREFIX)include/SDL -D_REENTRANT  \
	   -L$(PREFIX)lib -lSDL -lpthread -lSDL_image -lSDL_ttf -o $(BIN_DIR)/windowtest \
            $(patsubst %.o, $(OBJ_DIR)/%.o, $(TEST_WINDOW_OBJ))

$(BIN_DIR)/pstreamtest:  $(TEST_PSTREAM_OBJ) $(TEST_PSTREAM_INC)
	$(CXX) $(CXXFLAGS)  -O2 -Wall -I$(PREFIX)include/SDL -D_REENTRANT  \
	   -L$(PREFIX)lib  -o $(BIN_DIR)/pstreamtest  $(patsubst %.o, $(OBJ_DIR)/%.o, $(TEST_PSTREAM_OBJ))

$(BIN_DIR)/audioouttest: $(TEST_AUDIOOUT_SRC) $(TEST_AUDIOOUT_OBJ) $(TEST_AUDIOOUT_INC)
	$(CXX) $(CXXFLAGS) -O2 -Wall -I$(PREFIX)include/SDL -D_REENTRANT  \
	   -L$(PREFIX)lib -lSDL -lpthread -o $(BIN_DIR)/audioouttest  $(patsubst %.o, $(OBJ_DIR)/%.o, $(TEST_AUDIOOUT_OBJ))

$(BIN_DIR)/pathtest: $(TEST_PATH_SRC) $(TEST_PATH_OBJ) $(TEST_PATH_INC)
	$(CXX) $(CXXFLAGS) -O2 -Wall  -D_REENTRANT  \
	   -L$(PREFIX)lib  -lpthread -o $(BIN_DIR)/pathtest  $(patsubst %.o, $(OBJ_DIR)/%.o, $(TEST_PATH_OBJ))

%.h:
	echo Updating %.h
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $(OBJ_DIR)/$@ $(SDL_FLAGS)


$(DIRS): %:
	-test -d $@ || mkdir $@


dox: $(PEBLBASE_SRCXX)
	doxygen pebl.dox


remake: ready clean $(PROGS)

ready:
	-rm -f $(OUT_DIR)/*

.PHONY: dep
dep:
	$(CXX) -MM $(CXXFLAGS)    $(PEBLMAIN_SRC)  > .depend

.PHONY: clean
clean:
	-rm -f $(patsubst %.o, $(OBJ_DIR)/%.o, $(PEBLBASE_OBJ)) \
	$(patsubst %.o,  $(OBJ_DIR)/%.o, $(PEBLBASE_OBJSXX))  \
	$(patsubst %.o,  $(OBJ_DIR)/%.o, $(PEBLMAIN_OBJ))


.PHONY: install

uninstall:
	rm -Rf $(PREFIX)bin/pebl
	rm -Rf $(PREFIX)share/pebl

install: uninstall

	install -d $(PREFIX)bin/	

	cp bin/pebl $(PREFIX)bin/pebl
	rm -Rf $(PREFIX)share/pebl
	install -d $(PREFIX)share/pebl
	install -d $(PREFIX)share/pebl/media
	install -d $(PREFIX)share/pebl/pebl-lib
	cp -R media/* $(PREFIX)share/pebl/media/
	cp  pebl-lib/*.pbl $(PREFIX)share/pebl/pebl-lib/
	rm -Rf $(PREFIX)share/pebl/media/CVS
	rm -Rf $(PREFIX)share/pebl/media/images/CVS
	rm -Rf $(PREFIX)share/pebl/media/sounds/CVS
	rm -Rf $(PREFIX)share/pebl/media/fonts/CVS
	rm -Rf $(PREFIX)share/pebl/media/text/CVS
	rm -Rf $(PREFIX)share/pebl/pebl-lib/CVS
	chmod -R uga+r $(PREFIX)share/pebl/
#	chmod +s $(PREFIX)bin/pebl ##suid root

ifeq (.depend,$(wildcard .depend))
include .depend
endif
