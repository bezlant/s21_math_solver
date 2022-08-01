CXX = g++

EXE = math_solver
IMGUI_DIR = ./imgui
IMPLOT_DIR = $(IMGUI_DIR)/implot
CREDIT_DIR = ./credit_calc
DEPOSIT_DIR = ./deposit_calc

SOURCES = main.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMPLOT_DIR)/implot.cpp $(IMPLOT_DIR)/implot_items.cpp $(IMPLOT_DIR)/implot_demo.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
SOURCES += $(CREDIT_DIR)/credit_calc.c
SOURCES += $(DEPOSIT_DIR)/deposit_calc.c

OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
UNAME_S := $(shell uname -s)

CXXFLAGS = -pedantic -std=c++11 -I $(IMGUI_DIR) -I $(IMPLOT_DIR) -I $(IMGUI_DIR)/backends 
CXXFLAGS += -g -Wall -Wformat
LIBS =

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

%.o:$(IMPLOT_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

all: $(EXE)

debug:
	@echo $(SOURCES)
	@echo $(OBJS)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(EXE) $(OBJS) imgui.ini
