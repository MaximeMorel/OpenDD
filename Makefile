# user dirs
SRC_DIR		= ./src/
OBJ_DIR		= ./obj/
DEP_DIR		= ./dep/
BIN_DIR		= ./

# bin name
BIN		= opendd

# additionnal lib and includes dir
LIB_DIR		= ./
INC_DIR		= ./

# compile commands
CC 	= gcc
CPP = g++
LD	= gcc

# flags and libs
CPPFLAGS	= -I$(INC_DIR) -O3 -D_GNU_SOURCE=1 -D_REENTRANT -W -Wall -pipe
CFLAGS		= -I$(INC_DIR) -O3 -D_GNU_SOURCE=1 -D_REENTRANT -W -Wall -pipe
LDFLAGS		= -L$(LIB_DIR) -s -lSDL -lpthread -lSDL_image -lGL -lGLU -lopenal -lvorbisfile -ljpeg -lm


SRCS_CPP	= $(wildcard $(SRC_DIR)*.cpp)
SRCS_C		= $(wildcard $(SRC_DIR)*.c)

DEPS	= $(SRCS_CPP:$(SRC_DIR)%.cpp=$(DEP_DIR)%.d) $(SRCS_C:$(SRC_DIR)%.c=$(DEP_DIR)%.d)
OBJS	= $(SRCS_CPP:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o) $(SRCS_C:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# rules
all: test_dir $(BIN_DIR)/$(BIN)

$(BIN_DIR)/$(BIN): $(OBJS)
	$(LD) $+ -o $@ $(LDFLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(DEP_DIR)%.d: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -MM -MD -o $@ $<

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CPP) $(CPPFLAGS) -o $@ -c $<

$(DEP_DIR)%.d: $(SRC_DIR)%.cpp
	$(CPP) $(CPPFLAGS) -MM -MD -o $@ $<

-include $(DEPS)


.PHONY: clean distclean test_dir


test_dir:
    ${shell if [ ! -d $(OBJ_DIR) ]; then  mkdir -pv $(OBJ_DIR); fi }
    ${shell if [ ! -d $(DEP_DIR) ]; then  mkdir -pv $(DEP_DIR); fi }
    ${shell if [ ! -d $(BIN_DIR) ]; then  mkdir -pv $(BIN_DIR); fi }

run: $(BIN_DIR)/$(BIN)
	$(BIN_DIR)/$(BIN)

gdb: $(BIN_DIR)/$(BIN)
	gdb $(BIN_DIR)/$(BIN)

valgrind: $(BIN_DIR)/$(BIN)
	valgrind $(BIN_DIR)/$(BIN)

callgrind: $(BIN_DIR)/$(BIN)
	valgrind --tool=callgrind $(BIN_DIR)/$(BIN)

doc:
	doxygen

clean:
	rm -f $(OBJ_DIR)*.o $(SRC_DIR)*~ $(DEP_DIR)*.d *~

distclean: clean
	rm -f $(BIN_DIR)/$(BIN)

cleanall: distclean


tar: clean
	tar -cvzf ../${shell basename `pwd`}.tgz ../${shell basename `pwd`}
