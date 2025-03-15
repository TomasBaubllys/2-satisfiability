CC = g++
CFLAGS = -Wall
CSTD = -std=c++11
TARGET = 2sat
SRC_DIR = src
OBJ_DIR = objs

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(CSTD) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CSTD) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

clean_objs:
	rm -f $(OBJS)
