SRC_DIR := src
OBJ_DIR := obj
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
TEST_OBJS = $(patsubst $(OBJ_DIR)/main.o,,$(OBJS))
RUN_OBJS = $(patsubst $(OBJ_DIR)/main_test.o,,$(OBJS))
CC = g++
INCLUDE =
LIBS = 
CPPFLAGS = -Wall -g -std=c++11 -DTIXML_USE_STL
EXECUTABLE = Zork_clone.exe
TEST_EXECUTABLE = Zork_clone_test.exe
COMMANDLINE = 

.PHONY : run
run : $(EXECUTABLE)
	./$(EXECUTABLE) $(COMMANDLINE)

.PHONY : $(EXECUTABLE)
$(EXECUTABLE) :  $(OBJS)
	$(CC) $(CPPFLAGS) -o $(EXECUTABLE) $(RUN_OBJS) $(INCLUDE) $(LIBS)

.PHONY : test
test : $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE) $(COMMANDLINE)

.PHONY : $(TEST_EXECUTABLE)
$(TEST_EXECUTABLE) : $(OBJS)
	$(CC) $(CPPFLAGS) -o $(TEST_EXECUTABLE) $(TEST_OBJS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $(INCLUDE) $(LIBS) $<

clean :
	rm $(EXECUTABLE) $(TEST_EXECUTABLE) $(OBJS)