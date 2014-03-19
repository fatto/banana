TARGET = banana

CXXFLAGS = -Wall -g -MMD -std=c++11 -stdlib=libc++ -I./include -I./nanovg/src -DGLFW_INCLUDE_GLCOREARB -DGLCOREARB_PROTOTYPES
LFLAGS = -Wall -std=c++11 -stdlib=libc++ -lc++abi -L./library
LIBRARY = -lglfw -lGL -lnanovg

SRC := $(wildcard src/*.cpp)
OBJ := $(addprefix obj/,$(notdir $(SRC:.cpp=.o)))
DEF := $(OBJ:.o=.d)
rm = rm -f

$(TARGET): $(OBJ) library/libnanovg.a
	@clang++ $(LFLAGS) $(LIBRARY) $^ -o $@
	@echo "Linking complete!"

library/libnanovg.a : obj/nanovg.o obj/stb_image.o
	@ar crf $@ $^
	@echo "Created library "$@" successfully!"

obj/nanovg.o : nanovg/src/nanovg.c
	@clang -std=c11 -c -o $@ $<
	@echo "Compiled "$<" successfully!"

obj/stb_image.o : nanovg/src/stb_image.c
	@clang -std=c11 -c -o $@ $<
	@echo "Compiled "$<" successfully!"

obj/%.o : src/%.cpp
	@clang++ $(CXXFLAGS) -c -o $@ $<
	@echo "Compiled "$<" successfully!"

.PHONEY: clean
clean:
	@$(rm) $(OBJ) obj/nanovg.o obj/stb_image.o
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@$(rm) $(TARGET) library/libnanovg.a $(DEF)
	@echo "Executable removed!"

.PHONEY: run
run : $(TARGET)
	@exec ./$(TARGET)
-include $(OBJECTS:.o:.d)