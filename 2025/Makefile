# Compiler settings
CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -O2

# Default target
.PHONY: all clean help

all:
	@echo "Usage: make run DAY=<day> PART=<part>"
	@echo "Example: make run DAY=2 PART=1"
	@echo "Or: make 2/1"

# Help target
help:
	@echo "Available targets:"
	@echo "  make run DAY=<day> PART=<part>  - Compile and run specific day/part"
	@echo "  make <day>/<part>               - Compile and run (e.g., make 2/1)"
	@echo "  make clean                       - Remove all compiled binaries"
	@echo ""
	@echo "Examples:"
	@echo "  make run DAY=2 PART=1"
	@echo "  make 2/1"
	@echo "  make 4/2"

# Pattern rule for day/part format (e.g., make 2/1)
%/1:
	@$(MAKE) run DAY=$* PART=1

%/2:
	@$(MAKE) run DAY=$* PART=2

# Main compilation and run target
run: check-params
	@DAY_PADDED=$$(printf "%02d" $(DAY)); \
	PART_NAME=part_$(shell if [ "$(PART)" = "1" ]; then echo "one"; else echo "two"; fi); \
	SRC_FILE=$${DAY_PADDED}/$${PART_NAME}.cpp; \
	BIN_FILE=$${DAY_PADDED}/$${PART_NAME}; \
	if [ ! -f "$${SRC_FILE}" ]; then \
		echo "Error: Source file $${SRC_FILE} not found"; \
		exit 1; \
	fi; \
	echo "Compiling $${SRC_FILE}..."; \
	$(CXX) $(CXXFLAGS) $${SRC_FILE} -o $${BIN_FILE}; \
	if [ $$? -eq 0 ]; then \
		echo "Successfully compiled to $${BIN_FILE}"; \
		echo "Running $${BIN_FILE}..."; \
		echo ""; \
		./$${BIN_FILE}; \
	else \
		echo "Compilation failed"; \
		exit 1; \
	fi

# Check if DAY and PART are provided
check-params:
ifndef DAY
	@echo "Error: DAY parameter is required"
	@echo "Usage: make run DAY=<day> PART=<part>"
	@exit 1
endif
ifndef PART
	@echo "Error: PART parameter is required"
	@echo "Usage: make run DAY=<day> PART=<part>"
	@exit 1
endif

# Clean target
clean:
	@echo "Cleaning compiled binaries..."
	@find . -type f -name "part_one" -delete
	@find . -type f -name "part_two" -delete
	@echo "Clean complete"
