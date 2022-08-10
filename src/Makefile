CXX = g++

EXE = math_solver
BUILD_DIR = ../build
IMGUI_DIR = ./imgui
IMPLOT_DIR = ./implot
CREDIT_DIR = ./credit_calc
DEPOSIT_DIR = ./deposit_calc
PARSER_DIR = ./shunting_yard
LEXER_DIR = ./lexer
CALC_DIR = ./calc
STACK_DIR = ./stack
VALIDATION_DIR = ./validation
DIRS = $(IMGUI_DIR)/ $(IMPLOT_DIR)/ $(CREDIT_DIR)/ $(DEPOSIT_DIR)/ $(PARSER_DIR)/ $(LEXER_DIR)/ $(CALC_DIR)/ $(STACK_DIR)/ $(VALIDATION_DIR)/

SOURCES = main.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMPLOT_DIR)/implot.cpp $(IMPLOT_DIR)/implot_items.cpp $(IMPLOT_DIR)/implot_demo.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
SOURCES += $(CREDIT_DIR)/credit_calc.c
SOURCES += $(DEPOSIT_DIR)/deposit_calc.c
SOURCES += $(PARSER_DIR)/shunting.c 
SOURCES += $(LEXER_DIR)/lexer.c 
SOURCES += $(STACK_DIR)/stack.c 
SOURCES += $(CALC_DIR)/calc.c 
SOURCES += $(VALIDATION_DIR)/validation.c 

OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
UNAME_S := $(shell uname -s)

CXXFLAGS = -I $(IMGUI_DIR) -I $(IMPLOT_DIR) -I $(IMGUI_DIR)/backends 
CXXFLAGS += -g -Wall -Wformat
LIBS = -lpcre

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux)
	ECHO_MESSAGE = "Linux"
	LIBS += $(shell pkg-config --static --libs glfw3) $(shell pkg-config --libs opengl)

	CXXFLAGS += $(shell pkg-config --cflags glfw3)
endif

ifeq ($(UNAME_S), Darwin) 
	ECHO_MESSAGE = "Mac OS X"
	LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
	LIBS += $(shell pkg-config --libs glfw3)

	CXXFLAGS += $(shell pkg-config --cflags glfw3)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

%.o:$(CREDIT_DIR)/%.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(DEPOSIT_DIR)/%.c
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

%.o:$(LEXER_DIR)/%.c
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

%.o:$(CALC_DIR)/%.c
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

%.o:$(PARSER_DIR)/%.c
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

%.o:$(STACK_DIR)/%.c
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

%.o:$(VALIDATION_DIR)/%.c
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

%.o:$(IMPLOT_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

all: $(EXE)

.PHONY: install
install: $(EXE)
	install -m 557 $(BUILD_DIR)/$(EXE) ~/Desktop

uninstall:
	rm -rf ~/Desktop/$(EXE)

dvi: $(DIRS)
	mkdir -p ../docs
	doxygen Doxyfile

dist: $(DIRS) Makefile test.mk main.cpp
	mkdir -p ../dist
	tar cvzf ../dist/Math_Solver_1.0.tgz $(DIRS) Makefile test.mk main.cpp

tests:
	$(MAKE) -f test.mk 

gcov_report:
	$(MAKE) -f test.mk gcov_report


$(EXE): $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CXX) -o $(BUILD_DIR)/$@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f  $(OBJS) imgui.ini
	$(MAKE) -f test.mk clean

fclean: clean
	rm -rf $(BUILD_DIR)
	rm -rf ../dist
	rm -rf ../docs
