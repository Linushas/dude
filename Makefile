# Variables
CC = gcc
CFLAGS = -lncurses
SRC = src/main.c
OUT = dude
INSTALL_DIR = /usr/local/bin

# Default target
all: $(OUT)

# Compile the program
$(OUT): $(SRC)
	@echo "Building..."
	$(CC) $(SRC) $(CFLAGS) -o $(OUT)

# Install the program
install: $(OUT)
	@echo "Installing $(OUT) to $(INSTALL_DIR)..."
	sudo cp $(OUT) $(INSTALL_DIR)
	@echo "Installation complete."

# Clean the build
clean:
	@echo "Cleaning up..."
	rm -f $(OUT)
	@echo "Clean complete."

# Uninstall the program
uninstall:
	@echo "Removing $(OUT) from $(INSTALL_DIR)..."
	sudo rm -f $(INSTALL_DIR)/$(OUT)
	@echo "Uninstall complete."
