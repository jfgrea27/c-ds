# Compiler
CC      := gcc
CFLAGS  := -O0 -g
BUILD   := build
BIN_DIR := $(BUILD)/bin

# Platform detection
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    # macOS: use clang with AddressSanitizer for memory checking
    MEMCHECK_CC := clang
    MEMCHECK_CFLAGS := -fsanitize=address -fno-omit-frame-pointer
    MEMCHECK_LDFLAGS := -fsanitize=address
else
    # Linux: use valgrind (no special compiler needed)
    MEMCHECK_CC := $(CC)
    MEMCHECK_CFLAGS :=
    MEMCHECK_LDFLAGS :=
endif

# Include directories from all modules
INCLUDES := $(addprefix -I,$(wildcard src/*/include))

# Library sources: all module sources excluding per-module mains
LIB_SRCS := $(filter-out src/%/main.c,$(wildcard src/*/*.c))
LIB_OBJS := $(patsubst src/%.c,$(BUILD)/%.o,$(LIB_SRCS))

# Tests: discover test modules and define test binaries
TEST_SRCS := $(wildcard test/*/test_*.c)
TEST_DIRS := $(dir $(TEST_SRCS))
TEST_MODULES := $(notdir $(patsubst %/,%,$(TEST_DIRS)))
TEST_BINS := $(addprefix $(BIN_DIR)/test_,$(TEST_MODULES))

# Top-level main (optional)
TOP_MAIN := $(wildcard src/main.c)
TOP_OBJ  := $(patsubst src/%.c,$(BUILD)/%.o,$(TOP_MAIN))

# Modules are directories that contain a main.c
MODULE_MAINS := $(wildcard src/*/main.c)
MODULES := $(notdir $(patsubst src/%/main.c,%,$(MODULE_MAINS)))

# Final executables: top-level main (if present) and each module main
TARGETS := $(addprefix $(BIN_DIR)/,$(MODULES))
ifeq ($(strip $(TOP_MAIN)),)
else
TARGETS += $(BIN_DIR)/main
endif

all: $(TARGETS)

	@mkdir -p $(BIN_DIR)

# Top-level binary: link top-level main with all library objects
$(BIN_DIR)/main: $(TOP_OBJ) $(LIB_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Build test binaries (place before generic module rule to take precedence)
$(BIN_DIR)/test_%: test/%/test_%.c $(LIB_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Also materialize explicit rules for discovered test modules (helps some make versions)
define MAKE_TEST_RULE
$(BIN_DIR)/test_$(1): test/$(1)/test_$(1).c $(LIB_OBJS)
	@mkdir -p $(dir $$@)
	$(CC) $(CFLAGS) $(INCLUDES) -o $$@ $$^
endef

$(foreach m,$(TEST_MODULES),$(eval $(call MAKE_TEST_RULE,$(m))))

# Per-module binary: link module main with all library objects (static pattern to avoid matching tests)
$(addprefix $(BIN_DIR)/,$(MODULES)): $(BIN_DIR)/%: src/%/main.c $(LIB_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Compile .c -> .o
$(BUILD)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Memory check for a specific module
# Usage: make mem-check MODULE=<module>
# On macOS: uses AddressSanitizer (rebuilds with ASan)
# On Linux: uses valgrind
mem-check:
	@if [ -z "$(MODULE)" ]; then \
		echo "Usage: make mem-check MODULE=<module>"; exit 1; \
	fi
ifeq ($(UNAME_S),Darwin)
	@echo "Building $(MODULE) with AddressSanitizer..."
	@mkdir -p $(BIN_DIR)
	$(MEMCHECK_CC) $(CFLAGS) $(MEMCHECK_CFLAGS) $(INCLUDES) -o $(BIN_DIR)/$(MODULE)_asan src/$(MODULE)/main.c $(LIB_SRCS) $(MEMCHECK_LDFLAGS)
	@echo "Running with AddressSanitizer..."
	ASAN_OPTIONS=detect_leaks=0 $(BIN_DIR)/$(MODULE)_asan
	@echo ""
	@echo "=========================================="
	@echo "No memory errors detected (ASan passed)"
	@echo "=========================================="
else
	$(MAKE) $(BIN_DIR)/$(MODULE)
	valgrind --leak-check=full --track-origins=yes $(BIN_DIR)/$(MODULE)
endif

# Convenience form: make mem-check-<module>
mem-check-%:
ifeq ($(UNAME_S),Darwin)
	@echo "Building $* with AddressSanitizer..."
	@mkdir -p $(BIN_DIR)
	$(MEMCHECK_CC) $(CFLAGS) $(MEMCHECK_CFLAGS) $(INCLUDES) -o $(BIN_DIR)/$*_asan src/$*/main.c $(LIB_SRCS) $(MEMCHECK_LDFLAGS)
	@echo "Running with AddressSanitizer..."
	ASAN_OPTIONS=detect_leaks=0 $(BIN_DIR)/$*_asan
	@echo ""
	@echo "=========================================="
	@echo "No memory errors detected (ASan passed)"
	@echo "=========================================="
else
	$(MAKE) $(BIN_DIR)/$*
	valgrind --leak-check=full --track-origins=yes $(BIN_DIR)/$*
endif

# Run a specific module
# Usage: make run MODULE=<module>
run:
	@if [ -z "$(MODULE)" ]; then \
		echo "Usage: make run MODULE=<module>"; exit 1; \
	fi
	$(MAKE) $(BIN_DIR)/$(MODULE)
	$(BIN_DIR)/$(MODULE)

# Convenience form: make run-<module>
run-%:
	$(MAKE) $(BIN_DIR)/$*
	$(BIN_DIR)/$*

# Build and run all tests
tests: $(TEST_BINS)
	@set -e; \
	for t in $(TEST_BINS); do \
		echo "Running $$t"; \
		"$$t"; \
	done

# Build all test binaries (without running)
test-bins: $(TEST_BINS)

# Build and run a specific module's tests
# Usage: make test MODULE=<module>
test:
	@if [ -z "$(MODULE)" ]; then \
		echo "Usage: make test MODULE=<module>"; exit 1; \
	fi
	$(MAKE) $(BIN_DIR)/test_$(MODULE)
	$(BIN_DIR)/test_$(MODULE)

# Convenience form: make test-<module>
test-%:
	$(MAKE) $(BIN_DIR)/test_$*
	$(BIN_DIR)/test_$*

# Build a specific test binary (without running)
# Usage: make build-test MODULE=<module>
build-test:
	@if [ -z "$(MODULE)" ]; then \
		echo "Usage: make build-test MODULE=<module>"; exit 1; \
	fi
	$(MAKE) $(BIN_DIR)/test_$(MODULE)

# Convenience form: make build-test-<module>
build-test-%:
	$(MAKE) $(BIN_DIR)/test_$*

# Memory check for tests
# Usage: make mem-check-test MODULE=<module>
mem-check-test:
	@if [ -z "$(MODULE)" ]; then \
		echo "Usage: make mem-check-test MODULE=<module>"; exit 1; \
	fi
ifeq ($(UNAME_S),Darwin)
	@echo "Building test_$(MODULE) with AddressSanitizer..."
	@mkdir -p $(BIN_DIR)
	$(MEMCHECK_CC) $(CFLAGS) $(MEMCHECK_CFLAGS) $(INCLUDES) -o $(BIN_DIR)/test_$(MODULE)_asan test/$(MODULE)/test_$(MODULE).c $(LIB_SRCS) $(MEMCHECK_LDFLAGS)
	@echo "Running with AddressSanitizer..."
	ASAN_OPTIONS=detect_leaks=0 $(BIN_DIR)/test_$(MODULE)_asan
	@echo ""
	@echo "=========================================="
	@echo "No memory errors detected (ASan passed)"
	@echo "=========================================="
else
	$(MAKE) $(BIN_DIR)/test_$(MODULE)
	valgrind --leak-check=full --track-origins=yes $(BIN_DIR)/test_$(MODULE)
endif

# Convenience form: make mem-check-test-<module>
mem-check-test-%:
ifeq ($(UNAME_S),Darwin)
	@echo "Building test_$* with AddressSanitizer..."
	@mkdir -p $(BIN_DIR)
	$(MEMCHECK_CC) $(CFLAGS) $(MEMCHECK_CFLAGS) $(INCLUDES) -o $(BIN_DIR)/test_$*_asan test/$*/test_$*.c $(LIB_SRCS) $(MEMCHECK_LDFLAGS)
	@echo "Running with AddressSanitizer..."
	ASAN_OPTIONS=detect_leaks=0 $(BIN_DIR)/test_$*_asan
	@echo ""
	@echo "=========================================="
	@echo "No memory errors detected (ASan passed)"
	@echo "=========================================="
else
	$(MAKE) $(BIN_DIR)/test_$*
	valgrind --leak-check=full --track-origins=yes $(BIN_DIR)/test_$*
endif

clean:
	rm -rf $(BUILD)

.PHONY: all clean mem-check mem-check-% mem-check-test mem-check-test-% run run-% tests test test-% test-bins build-test build-test-%
