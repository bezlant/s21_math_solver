CC 			:=		gcc
CFLAGS 		:=		-Wall -Werror -Wextra -pedantic -std=c11 -fanalyzer

TARGET  	:=    	s21_calc.a

MODULES 	:=    	$(shell find . -type d | grep -v -E "tests") 

SRC			:=	  	$(notdir $(shell find $(MODULES) -maxdepth 1 -name "*.c"))
INC 		:=    	$(shell find $(MODULES) -maxdepth 1 -name "*.h")
OBJS		:=	  	$(SRC:%.c=%.o)
OBJS_DIR    :=    	./objs

vpath %.c 	$(MODULES)
vpath %.o 	$(OBJS_DIR)

all			: $(TARGET)

$(TARGET)	: $(OBJS)
				ar -vrcs $(TARGET) $(addprefix $(OBJS_DIR)/, $(OBJS))
				ranlib $(TARGET)

%.o 		: %.c $(INC)
				mkdir -p $(OBJS_DIR)
				$(CC) $(CFLAGS) -o $(addprefix $(OBJS_DIR)/, $@) -c $<


debug		:
				$(info SRC = $(SRC))
				$(info INC = $(INC))
				$(info OBJS = $(OBJS))
				$(info TARGET = $(TARGET))
				$(info MODULES = $(MODULES))

test		:
				$(MAKE) -f test.mk

clean		:
				rm -rf $(OBJS_DIR)

fclean		: clean
				rm -rf $(TARGET)
