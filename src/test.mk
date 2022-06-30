CC				:=	  	gcc
GCOV_FLAGS  	:= 		-fprofile-arcs -ftest-coverage 
CFLAGS			:=		-Wall -Werror -Wextra -std=c11 -pedantic -fanalyzer $(GCOV_FLAGS)
ASAN			:=		-g -fsanitize=address
LDFLAGS 		:= 		$(shell pkg-config --libs --cflags check)

TARGET			:= 		test 
TARGET_LIB  	:=		s21_calc_test.a 

MODULES			:= 		$(shell find . -type d | grep -v -E "tests")
TEST_MODULES	:= 		$(shell find . -type d | grep -E "test")

SRC				:= 		$(notdir $(shell find $(MODULES) -maxdepth 1 -name "*.c"))
INC				:=		$(shell find $(MODULES) -maxdepth 1 -name "*.h")
OBJS			:=		$(SRC:%.c=%.o)
OBJS_DIR		:= 		./objs

TEST_SRC		:= 		$(notdir $(shell find $(TEST_MODULES) -maxdepth 1 -name "*.c"))
TEST_INC		:= 		$(shell find $(TEST_MODULES) -maxdepth 1 -name "*.h")
TEST_OBJS		:=		$(TEST_SRC:%.c=%.o)
TEST_OBJS_DIR	:= 		./objs

vpath %.c 	$(MODULES)  : $(TEST_MODULES)
vpath %.o 	$(OBJS_DIR)	: $(TEST_OBJS_DIR)

debug		:
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


all				: $(TARGET) 

$(TARGET)		: $(TARGET_LIB) $(TEST_OBJS)
					$(CC) $(CFLAGS) $(TEST_LIB) -o $@ $(TARGET_LIB) $(addprefix $(TEST_OBJS_DIR)/, $(TEST_OBJS)) $(LDFLAGS) 
					./test
				
%.o 			: %.c $(INC)
					mkdir -p $(OBJS_DIR)
					$(CC) $(CFLAGS) -o $(addprefix $(OBJS_DIR)/, $@) -c $<

$(TARGET_LIB)	: $(OBJS)
					ar -vrcs $(TARGET_LIB) $(addprefix $(OBJS_DIR)/, $(OBJS))
					ranlib $(TARGET_LIB)
	

# gcov: $(TARGET_TEST)
# 	gcov $(TEST_SRC) $(SRC)

# coverage.info: gcov
# 	lcov --capture --directory . --output-file coverage.info

# report: coverage.info
# 	genhtml coverage.info --output-directory coverage

# open:
# 	open coverage/index.html

clean			:
					rm -rf objs
					rm -rf $(TARGET_LIB)

# fclean: clean
# 	rm -rf $(TARGET_TEST) $(TARGET_TEST_LIB)

# re: fclean test

# .PHONY: all clean fclean open
