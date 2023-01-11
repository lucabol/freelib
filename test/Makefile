SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

SRC    := $(wildcard $(SRC_DIR)/*.c)
OBJ    := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET := $(OBJ:$(OBJ_DIR)/%.o=$(BIN_DIR)/%)
STUB   := ../stubs/stub.o

# -MMD -MP -> Generates the header dependencies included below
#  -flto   -> Enable link time optimization (i.e., not linking unused functions if compiled and linked with -Ox)
#  https://unix.stackexchange.com/questions/715899/do-c-compilers-discard-unused-functions-when-statically-linking-to-a-file
CPPFLAGS := -I../libc/include -MMD -MP -flto
CFLAGS   := -Wall -Wextra -O3 -ffreestanding
LDFLAGS  := -L../libc/bin -static -nostdlib -flto
LDLIBS   := -lfslibc 
ARFLAGS  := rc

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(STUB) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)
