PROJECT     = client

CMAKE       = cmake
TOOLCHAIN   = -DCMAKE_TOOLCHAIN_FILE="clang-toolchain.cmake"
CMAKE_FLAGS =

BUILD       = Build
SOURCE      = Sources
INCLUDE     = Includes

SOURCES     = $(wildcard $(SOURCE)/*.cpp)
OBJECTS     = $(patsubst $(SOURCE)/%.cpp,$(BUILD)/CMakeFiles/$(PROJECT).dir/$(SOURCE)/%.cpp.o,$(SOURCES))

all: $(PROJECT)
$(PROJECT): debug

release: CMakeLists.txt
	$(CMAKE) --build $(BUILD) --config Release

debug: CMakeLists.txt
	$(CMAKE) --build $(BUILD) --config Debug

.PHONY: $(OBJECTS)
CMakeLists.txt: $(OBJECTS)
	$(CMAKE) -B $(BUILD) $(TOOLCHAIN)

clean:
	rm -fr Bin/*
	rm -fr Build/*

extra-clean:
	rm -fr Bin
	rm -fr Build
