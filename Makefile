# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -DSFML_STATIC -I"C:\Users\monst\Documents\libraries\SFML-2.6.1\include" -I"include"
LDFLAGS = -L"C:\Users\monst\Documents\libraries\SFML-2.6.1\lib" -lsfml-main -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows

# Directories
SRC_DIR = bin\src
BUILD_DIR = build
INCLUDE_DIR = include
MEDIA_DIR = bin\media

# Files
TARGET = $(BUILD_DIR)\Flappy-The-Bird.exe
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
MEDIA_FILES = $(wildcard $(MEDIA_DIR)/*.png)

# Default rule
all: $(TARGET) copy_media

# Build executable
$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Copy media files
copy_media:
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	if exist "$(MEDIA_DIR)" xcopy /Y "$(MEDIA_DIR)\*.png" "$(BUILD_DIR)\"

# Clean build
clean:
	if exist "$(BUILD_DIR)\*.o" del /Q "$(BUILD_DIR)\*.o"
	if exist "$(BUILD_DIR)\*.png" del /Q "$(BUILD_DIR)\*.png"
	if exist "$(TARGET)" del /Q "$(TARGET)"

# Phony targets
.PHONY: all clean copy_media