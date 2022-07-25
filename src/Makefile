CC 				:=		gcc
CFLAGS 			:=		-Wall -Werror -Wextra -pedantic -std=c11 

TARGET  		:=    	s21_calc.a

MODULES 		:=    	$(shell find . -type d | grep -v -E "test") 

SRC				:=	  	$(notdir $(shell find $(MODULES) -maxdepth 1 -name "*.c"))
INC 			:=    	$(shell find $(MODULES) -maxdepth 1 -name "*.h")
OBJS			:=	  	$(SRC:%.c=%.o)
OBJS_DIR    	:=    	./objs

vpath %.c 		$(MODULES)
vpath %.o 		$(OBJS_DIR)

all				: $(TARGET)

$(TARGET)		: $(OBJS)
					ar -rcs $(TARGET) $(addprefix $(OBJS_DIR)/, $(OBJS))
					ranlib $(TARGET)

%.o 			: %.c $(INC) $(OBJS_DIR)
					$(CC) $(CFLAGS) -o $(addprefix $(OBJS_DIR)/, $@) -c $<

$(OBJS_DIR) 	:
					mkdir -p $(OBJS_DIR)

.PHONY: test
test			:
					$(MAKE) -f test.mk

debug			:
					$(info SRC = $(SRC))
					$(info INC = $(INC))
					$(info OBJS = $(OBJS))
					$(info TARGET = $(TARGET))
					$(info MODULES = $(MODULES))

clean			:
					rm -rf $(OBJS_DIR)
					rm -rf $(TARGET)
fclean			:
					$(MAKE) -f test.mk clean

.PHONY: all install uninstall clean dvi dist tests gcov_report re
