################################################################################
ROOT_FOLDER := ..
################################################################################
GROUP1_FILES := engine-console single-console multi-console debug-program
GROUP2_FILES := engine-socket client-console server-console
GROUP3_FILES := single-screen multi-screen
GROUP4_FILES := client-screen server-screen
################################################################################
FILES_TARGET := files
CLEAN_TARGET := clean
################################################################################
COMPILE_COMND := gcc
COMPILE_FLAGS := -Wall -Werror -O3 -lm

SDL_LIB_FLAGS := -lSDL2main -lSDL2 -lSDL2_image
SDL_DIR_FLAGS := -ISDL2/include -LSDL2/lib

WIN_SDL_FLAGS := $(SDL_DIR_FLAGS) -lmingw32 $(SDL_LIB_FLAGS)
WIN_SOC_FLAGS := -lws2_32

LIN_SDL_FLAGS := `sdl2-config --libs --cflags` $(SDL_LIB_FLAGS)
LIN_SOC_FLAGS :=

WIN_DEL_FLAGS :=
WIN_DEL_COMND := del

LIN_DEL_FLAGS :=
LIN_DEL_COMND := rm
################################################################################
SOURCE_FOLDER := $(ROOT_FOLDER)/Source-Files-Folder
OBJECT_FOLDER := $(ROOT_FOLDER)/Object-Files-Folder
BINARY_FOLDER := $(ROOT_FOLDER)/Binary-Files-Folder

ENGINE_FOLDER := $(SOURCE_FOLDER)/Chess-Engine-Folder
ENGLOG_FOLDER := $(SOURCE_FOLDER)/Engine-Logic-Folder
CONSOLE_FOLDER := $(SOURCE_FOLDER)/Game-Console-Folder
MASTER_FOLDER := $(SOURCE_FOLDER)/Game-Master-Folder
SCREEN_FOLDER := $(SOURCE_FOLDER)/Game-Screen-Folder
SOCKET_FOLDER := $(SOURCE_FOLDER)/Game-Socket-Folder

MODULE_SOURCE := Source-Files-Folder
MODULE_HEADER := Header-Files-Folder
################################################################################
ENGLOG_SOURCE := $(ENGLOG_FOLDER)/$(MODULE_SOURCE)
ENGLOG_HEADER := $(ENGLOG_FOLDER)/$(MODULE_HEADER)

ENGINE_SOURCE := $(ENGINE_FOLDER)/$(MODULE_SOURCE)
ENGINE_HEADER := $(ENGINE_FOLDER)/$(MODULE_HEADER)

CONSOLE_SOURCE := $(CONSOLE_FOLDER)/$(MODULE_SOURCE)
CONSOLE_HEADER := $(CONSOLE_FOLDER)/$(MODULE_HEADER)

SCREEN_SOURCE := $(SCREEN_FOLDER)/$(MODULE_SOURCE)
SCREEN_HEADER := $(SCREEN_FOLDER)/$(MODULE_HEADER)

SOCKET_HEADER := $(SOCKET_FOLDER)/$(MODULE_HEADER)
SOCKET_SOURCE := $(SOCKET_FOLDER)/$(MODULE_SOURCE)
################################################################################
ENGLOG_SOURCES := $(wildcard $(ENGLOG_SOURCE)/*.c)
ENGLOG_HEADERS := $(wildcard $(ENGLOG_HEADER)/*.h)
ENGLOG_OBJECTS := $(patsubst $(ENGLOG_SOURCE)/%.c, $(OBJECT_FOLDER)/%.o, $(ENGLOG_SOURCES))

ENGINE_SOURCES := $(wildcard $(ENGINE_SOURCE)/*.c)
ENGINE_HEADERS := $(wildcard $(ENGINE_HEADER)/*.h)
ENGINE_OBJECTS := $(patsubst $(ENGINE_SOURCE)/%.c, $(OBJECT_FOLDER)/%.o, $(ENGINE_SOURCES))

CONSOLE_SOURCES := $(wildcard $(CONSOLE_SOURCE)/*.c)
CONSOLE_HEADERS := $(wildcard $(CONSOLE_HEADER)/*.h)
CONSOLE_OBJECTS := $(patsubst $(CONSOLE_SOURCE)/%.c, $(OBJECT_FOLDER)/%.o, $(CONSOLE_SOURCES))

SCREEN_SOURCES := $(wildcard $(SCREEN_SOURCE)/*.c)
SCREEN_HEADERS := $(wildcard $(SCREEN_HEADER)/*.h)
SCREEN_OBJECTS := $(patsubst $(SCREEN_SOURCE)/%.c, $(OBJECT_FOLDER)/%.o, $(SCREEN_SOURCES))

SOCKET_SOURCES := $(wildcard $(SOCKET_SOURCE)/*.c)
SOCKET_HEADERS := $(wildcard $(SOCKET_HEADER)/*.h)
SOCKET_OBJECTS := $(patsubst $(SOCKET_SOURCE)/%.c, $(OBJECT_FOLDER)/%.o, $(SOCKET_SOURCES))
################################################################################
GROUP1_SOURCES := $(ENGLOG_SOURCES) $(ENGINE_SOURCES) $(CONSOLE_SOURCES)
GROUP1_HEADERS := $(ENGLOG_HEADERS) $(ENGINE_HEADERS) $(CONSOLE_HEADERS)
GROUP1_OBJECTS := $(ENGLOG_OBJECTS) $(ENGINE_OBJECTS) $(CONSOLE_OBJECTS)

GROUP2_SOURCES := $(ENGLOG_SOURCES) $(ENGINE_SOURCES) $(CONSOLE_SOURCES) $(SOCKET_SOURCES)
GROUP2_HEADERS := $(ENGLOG_HEADERS) $(ENGINE_HEADERS) $(CONSOLE_HEADERS) $(SOCKET_HEADERS)
GROUP2_OBJECTS := $(ENGLOG_OBJECTS) $(ENGINE_OBJECTS) $(CONSOLE_OBJECTS) $(SOCKET_OBJECTS)

GROUP3_SOURCES := $(ENGLOG_SOURCES) $(ENGINE_SOURCES) $(SCREEN_SOURCES)
GROUP3_HEADERS := $(ENGLOG_HEADERS) $(ENGINE_HEADERS) $(SCREEN_HEADERS)
GROUP3_OBJECTS := $(ENGLOG_OBJECTS) $(ENGINE_OBJECTS) $(SCREEN_OBJECTS)

GROUP4_SOURCES := $(ENGLOG_SOURCES) $(ENGINE_SOURCES) $(SCREEN_SOURCES) $(SOCKET_SOURCES)
GROUP4_HEADERS := $(ENGLOG_HEADERS) $(ENGINE_HEADERS) $(SCREEN_HEADERS) $(SOCKET_HEADERS)
GROUP4_OBJECTS := $(ENGLOG_OBJECTS) $(ENGINE_OBJECTS) $(SCREEN_OBJECTS) $(SOCKET_OBJECTS)
################################################################################
ifeq ($(OS), Windows_NT)
SOCKET_FLAGS := $(WIN_SOC_FLAGS)
SCREEN_FLAGS := $(WIN_SDL_FLAGS)
else
SOCKET_FLAGS := $(LIN_SOC_FLAGS)
SCREEN_FLAGS := $(LIN_SDL_FLAGS)
endif
################################################################################
GROUP1_FLAGS := $(COMPILE_FLAGS)
GROUP2_FLAGS := $(COMPILE_FLAGS) $(SOCKET_FLAGS)
GROUP3_FLAGS := $(COMPILE_FLAGS) $(SCREEN_FLAGS)
GROUP4_FLAGS := $(COMPILE_FLAGS) $(SCREEN_FLAGS) $(SOCKET_FLAGS)
################################################################################
$(GROUP1_FILES): %: $(OBJECT_FOLDER)/%.o $(GROUP1_OBJECTS) $(MASTER_FOLDER)/%.c $(GROUP1_SOURCES) $(GROUP1_HEADERS)
	$(COMPILE_COMND) $(GROUP1_OBJECTS) $(OBJECT_FOLDER)/$@.o $(GROUP1_FLAGS) -o $@

$(GROUP2_FILES): %: $(OBJECT_FOLDER)/%.o $(GROUP2_OBJECTS) $(MASTER_FOLDER)/%.c $(GROUP2_SOURCES) $(GROUP2_HEADERS)
	$(COMPILE_COMND) $(GROUP2_OBJECTS) $(OBJECT_FOLDER)/$@.o $(GROUP2_FLAGS) -o $@

$(GROUP3_FILES): %: $(OBJECT_FOLDER)/%.o $(GROUP3_OBJECTS) $(MASTER_FOLDER)/%.c $(GROUP3_SOURCES) $(GROUP3_HEADERS)
	$(COMPILE_COMND) $(GROUP3_OBJECTS) $(OBJECT_FOLDER)/$@.o $(GROUP3_FLAGS) -o $@

$(GROUP4_FILES): %: $(OBJECT_FOLDER)/%.o $(GROUP4_OBJECTS) $(MASTER_FOLDER)/%.c $(GROUP4_SOURCES) $(GROUP4_HEADERS)
	$(COMPILE_COMND) $(GROUP4_OBJECTS) $(OBJECT_FOLDER)/$@.o $(GROUP4_FLAGS) -o $@
################################################################################
$(OBJECT_FOLDER)/%.o: $(MASTER_FOLDER)/%.c
	$(COMPILE_COMND) $< -c $(COMPILE_FLAGS) -o $@

$(OBJECT_FOLDER)/%.o: $(ENGLOG_SOURCE)/%.c $(ENGLOG_HEADER)/%.h
	$(COMPILE_COMND) $< -c $(COMPILE_FLAGS) -o $@

$(OBJECT_FOLDER)/%.o: $(ENGINE_SOURCE)/%.c $(ENGINE_HEADER)/%.h
	$(COMPILE_COMND) $< -c $(COMPILE_FLAGS) -o $@

$(OBJECT_FOLDER)/%.o: $(SCREEN_SOURCE)/%.c $(SCREEN_HEADER)/%.h
	$(COMPILE_COMND) $< -c $(COMPILE_FLAGS) -o $@

$(OBJECT_FOLDER)/%.o: $(SOCKET_SOURCE)/%.c $(SOCKET_HEADER)/%.h
	$(COMPILE_COMND) $< -c $(COMPILE_FLAGS) -o $@

$(OBJECT_FOLDER)/%.o: $(CONSOLE_SOURCE)/%.c $(CONSOLE_HEADER)/%.h
	$(COMPILE_COMND) $< -c $(COMPILE_FLAGS) -o $@
################################################################################
OBJECT_FILES := $(ENGLOG_OBJECTS) $(ENGINE_OBJECTS) $(CONSOLE_OBJECTS) $(SCREEN_OBJECTS) $(SOCKET_OBJECTS)

RUNBLE_FILES := $(GROUP1_FILES) $(GROUP2_FILES) $(GROUP3_FILES) $(GROUP4_FILES)

ifeq ($(OS), Windows_NT)
RUNBLE_FILES := $(addsuffix .exe, $(RUNBLE_FILES))
endif

.PRECIOUS: $(OBJECT_FILES) $(RUNBLE_FILES)
################################################################################
ifeq ($(OS), Windows_NT)
DELETE_COMND := $(WIN_DEL_COMND)
DELETE_FLAGS := $(WIN_DEL_FLAGS)
DELETE_FILES := "$(OBJECT_FOLDER)/*.o" $(RUNBLE_FILES)
else
DELETE_COMND := $(LIN_DEL_COMND)
DELETE_FLAGS := $(LIN_DEL_FLAGS)
DELETE_FILES := $(OBJECT_FOLDER)/*.o $(RUNBLE_FILES)
endif
################################################################################
$(FILES_TARGET):
	$(foreach RUNBLE_FILE, $(RUNBLE_FILES), $(info $(RUNBLE_FILE)))

$(CLEAN_TARGET):
	$(DELETE_COMND) $(DELETE_FLAGS) $(DELETE_FILES)
