# Compiler
CC      := gcc
CFLAGS  := -O0 -g
BUILD   := build
BIN_DIR := $(BUILD)/bin

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

# Memory check with valgrind for a specific module
# Usage: make mem-check MODULE=<module>
mem-check:
	@if [ -z "$(MODULE)" ]; then \
		echo "Usage: make mem-check MODULE=<module>"; exit 1; \
	fi
	$(MAKE) $(BIN_DIR)/$(MODULE)
	valgrind --leak-check=full --track-origins=yes $(BIN_DIR)/$(MODULE)

# Convenience form: make mem-check-<module>
mem-check-%:
	$(MAKE) $(BIN_DIR)/$*
	valgrind --leak-check=full --track-origins=yes $(BIN_DIR)/$*

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


clean:
	rm -rf $(BUILD)

.PHONY: all clean mem-check mem-check-% run run-% tests test test-% test-bins build-test build-test-%
