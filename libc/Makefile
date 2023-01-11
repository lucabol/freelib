SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

TARGET := $(BIN_DIR)/libfslibc.a
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# -MMD -MP -> Generates the header dependencies included below
#  -flto   -> Enable link time optimization (i.e., not linking unused functions if compiled and linked with -Ox)
#  https://unix.stackexchange.com/questions/715899/do-c-compilers-discard-unused-functions-when-statically-linking-to-a-file
CPPFLAGS := -Iinclude -Iinclude/fslc -MMD -MP
CFLAGS   := -Wall -Wextra -Os -ffreestanding -flto
LDLIBS   := 
ARFLAGS  := rc

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ) | $(BIN_DIR)
	$(AR) $(ARFLAGS) $@ $+

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)
