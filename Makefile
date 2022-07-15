SRC_DIR    := src
OBJ_DIR    := obj
SRC_FILES  := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES  := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
INCLUDES   := -Iinclude
LDFLAGS    :=
LIBRARIES  := -lOpenGL32 -lGlu32 -lGlew32 -lsfml-graphics -lsfml-system -lsfml-window
CPPFLAGS   := -fpermissive
CXXFLAGS   :=

engine.exe: $(OBJ_FILES)
	g++ $(LDFLAGS) -o $@ $^ $(LIBRARIES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $< $(INCLUDES)


.PHONY: clean

clean:
	del /S $(OBJ_DIR)
