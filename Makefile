SRC_DIR      := src
OBJ_DIR      := obj
SRC_FILES    := $(wildcard $(SRC_DIR)/*.cpp)
C_SRC_FILES  := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES    := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
INCLUDES     := -Iinclude
LDFLAGS      :=
LIBRARIES    := -ldl -lpthread -lGL -lGLU -lGLEW -lsfml-graphics -lsfml-system -lsfml-window
CPPFLAGS     := 
CXXFLAGS     	:=

engine.x86_64: $(OBJ_FILES)
	g++ $(LDFLAGS) -o $@ $^ $(LIBRARIES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $< $(INCLUDES)


.PHONY: clean

clean:
	rm  $(OBJ_DIR)/*.o engine.x86_64
