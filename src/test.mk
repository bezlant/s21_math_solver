CC				:=	  	gcc
GCOV_FLAGS  	:= 		-fprofile-arcs -ftest-coverage 
ASAN			:=		-g -fsanitize=address
CFLAGS			:=		-Wall -Werror -Wextra -std=c11 -pedantic $(GCOV_FLAGS) #$(ASAN)
LDFLAGS 		:= 		$(shell pkg-config --libs --cflags check) -lm -lpcre

TARGET			:= 		tests
TARGET_LIB  	:=		s21_calc_test.a 

MODULES			:= 		$(shell find . -type d | grep -E "stack|credit_calc|deposit_calc|lexer|shunting_yard|calc|validation")
TEST_MODULES	:= 		$(shell find . -type d | grep -E "test")

SRC				:= 		$(notdir $(shell find $(MODULES) -maxdepth 1 -name "*.c"))
INC				:=		$(shell find $(MODULES) -maxdepth 1 -name "*.h")
OBJS			:=		$(SRC:%.c=%.o)
OBJS_DIR		:= 		./objs

TEST_SRC		:= 		$(notdir $(shell find $(TEST_MODULES) -maxdepth 1 -name "*.c"))
TEST_INC		:= 		$(shell find $(TEST_MODULES) -maxdepth 1 -name "*.h")
TEST_OBJS		:=		$(TEST_SRC:%.c=%.o)

vpath %.c 	$(MODULES) : $(TEST_MODULES)
vpath %.o 	$(OBJS_DIR)	

all				: $(TARGET) 

$(TARGET)		: $(TARGET_LIB) $(TEST_OBJS)
					$(CC) $(CFLAGS) -o $@  $(addprefix $(OBJS_DIR)/, $(TEST_OBJS)) $(TARGET_LIB) $(LDFLAGS) 
					./tests
				
%.o 			: %.c $(INC) $(OBJS_DIR)
					$(CC) $(CFLAGS) -o $(addprefix $(OBJS_DIR)/, $@) -c $<
$(OBJS_DIR) 	:
				mkdir -p $(OBJS_DIR)

$(TARGET_LIB)	: $(OBJS)
					ar -vrcs $(TARGET_LIB) $(addprefix $(OBJS_DIR)/, $(OBJS))
					ranlib $(TARGET_LIB)
	

gcov: $(TARGET)
	gcov $(TEST_SRC) $(SRC)

coverage.info: gcov
	lcov --capture --directory ./objs --output-file coverage.info

gcov_report: coverage.info
	genhtml coverage.info --output-directory coverage

open:
	open coverage/index.html

debug			:
					$(info TARGET = $(TARGET))
					$(info MODULES = $(MODULES))
					$(info SRC = $(SRC))
					$(info INC = $(INC))
					$(info OBJS = $(OBJS))
					$(info TARGET_LIB = $(TARGET_LIB))
					$(info TEST_MODULES = $(TEST_MODULES))
					$(info TEST_SRC = $(TEST_SRC))
					$(info TEST_INC = $(TEST_INC))
					$(info TEST_OBJS = $(TEST_OBJS))

clean			:
					rm -rf $(OBJS_DIR)
					rm -rf $(TARGET_LIB)
					rm -rf $(TARGET)
					rm -rf coverage*

re: clean $(TARGET)

.PHONY: tests test all gcov_report re clean debug 
