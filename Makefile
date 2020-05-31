# Makefile shamelessly stolen from Hase.
# I can hardly manage makefiles as it is, yet alone something with
# multiple-targets like sparrow3D!
# whoops.

SRC = lib/font.c lib/sound.c lib/menu.c 
OBJ = font.o sound.o menu.o
DEP = $(SRC:.c=.d)

DYNAMIC = -lSDL_ttf -lSDL_mixer -lSDL_image -lSDL -lm
CFLAGS = -O3 -fsingle-precision-constant -Wimplicit-function-declaration -Wunused
GENERAL_TWEAKS = -ffast-math
#==PC defaults==
FLAGS = -DDESKTOP $(GENERAL_TWEAKS)

ifdef NO_DEBUG
	FLAGS += -O3
else
	FLAGS += -g
endif

SDL = `sdl-config --cflags`

SPARROW_FOLDER = ../sparrow3d
SPARROW3D_STATIC_LIB = libsparrow3d.a
SPARROWNET_STATIC_LIB = libsparrowNet.a
SPARROWSOUND_STATIC_LIB = libsparrowSound.a

DYNAMIC += -lSDL_net

ifdef TARGET
	include $(SPARROW_FOLDER)/target-files/$(TARGET).mk
	BUILD = ./build/$(TARGET)/main
	SPARROW_LIB = $(SPARROW_FOLDER)/build/$(TARGET)/sparrow3d
else
	TARGET = "Default (change with make TARGET=otherTarget. See All targets with make targets)"
	BUILD = .
	SPARROW_LIB = $(SPARROW_FOLDER)
endif
LIB += -L$(SPARROW_LIB)
INCLUDE += -I$(SPARROW_FOLDER)

EFEMMERA_STATIC = $(SPARROW_LIB)/$(SPARROW3D_STATIC_LIB) $(SPARROW_LIB)/$(SPARROWSOUND_STATIC_LIB) $(SPARROW_LIB)/$(SPARROWNET_STATIC_LIB) $(STATIC)

ifneq ($(TARGET),win32)
DYNAMIC += -lz
endif

CFLAGS += $(PARAMETER) $(FLAGS)  -DBUILDING_DLL

all: tests
	@echo "=== Built for Target "$(TARGET)" ==="

targets:
	@echo "The targets are the same like for sparrow3d. :P"

test-menu: tests/test-menu.c $(OBJ) makeBuildDir
	$(CC) $(CFLAGS) $(LINK_FLAGS) $< $(OBJ) $(SDL) $(INCLUDE) $(LIB) $(EFEMMERA_STATIC) $(DYNAMIC) -o $(BUILD)/tests/$@$(SUFFIX)

tests: test-menu
	@echo "=== Tests built ==="
#efemmera: main.c $(OBJ) makeBuildDir
	#$(CC) $(CFLAGS) $(LINK_FLAGS) $< $(OBJ) $(SDL) $(INCLUDE) $(LIB) $(EFEMMERA_STATIC) $(DYNAMIC) -o $(BUILD)/$@$(SUFFIX)

%.d: %.c
	$(CC) -MM $(CFLAGS) $(INCLUDE) $(SDL) $< -MF $@

%.o:
	$(CC) $(CFLAGS) -c $< $(SDL) $(INCLUDE)

makeBuildDir:
	 @if [ ! -d $(BUILD:/efemmera=/) ]; then mkdir $(BUILD:/efemmera=/);fi
	 @if [ ! -d $(BUILD) ]; then mkdir $(BUILD);fi

clean:
	rm -f *.o *.d
	rm -f lib/*.d lib/*.o
	rm -f $(BUILD)/tests/test-menu$(SUFFIX)
	rm -f $(BUILD)/efemmera$(SUFFIX)

oclean:
	rm -f *.o
	rm -f *.d

-include $(DEP)
