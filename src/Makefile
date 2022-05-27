CC:=gcc
LIB:=$(shell pkg-config --cflags --libs gtk4)
TARGET:=hello_world_gtk

SRC:=$(shell find . -maxdepth 1 -name "*.c")
OBJS:=$(SRC:%c=%.o)

all: $(TARGET)

$(TARGET): $(SRC) 
	$(CC) -o $(TARGET) $(SRC) $(LIB)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(TARGET)
