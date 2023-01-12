SRC_DIR :=.
OBJ_DIR :=.
BIN_DIR :=.

TARGET := $(BIN_DIR)/stub.o
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS :=
CFLAGS   := -Wall -Wextra -Os -ffreestanding
LDLIBS   := 
ARFLAGS  := rc

.PHONY: all clean check

all: $(TARGET)

$(TARGET): $(OBJ) | $(BIN_DIR)
	$(AR) $(ARFLAGS) $@ $+
	@$(RM) -rv $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

check:

clean:
	@$(RM) -rv $(OBJ) $(TARGET)
