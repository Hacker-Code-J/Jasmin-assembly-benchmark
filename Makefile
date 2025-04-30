# Top‐level Makefile for standalone OpenSSL AES

# — Directory configuration —
INC_DIR      := include
SRC_DIR      := src/blockcipher
TEST_DIR     := tests
BENCH_DIR    := benchmark
VIEW_DIR     := view
OBJ_DIR      := obj

# — Compiler settings —
CC           := gcc
CFLAGS       := -O2 -Wall \
                 -I$(INC_DIR) -I$(INC_DIR)/openssl \
                 -MMD -MP
ASFLAGS      := -m64 -march=x86-64 -O2 -Wall

# — Source discovery —
SRC_C        := $(wildcard $(SRC_DIR)/*.c)
TEST_C       := $(wildcard $(TEST_DIR)/*.c)
BENCH_C      := $(wildcard $(BENCH_DIR)/*.c)

# — Objects & dependencies —
AES_OBJS     := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_C))
TEST_OBJS    := $(patsubst %.c,$(OBJ_DIR)/%.o,$(TEST_C))
BENCH_OBJS   := $(patsubst %.c,$(OBJ_DIR)/%.o,$(BENCH_C))
OBJS         := $(AES_OBJS) $(TEST_OBJS) $(BENCH_OBJS)
DEPS         := $(OBJS:.o=.d)

# — Outputs —
LIB          := libossl_aes.a
TEST_EXE     := $(TEST_DIR)/test_ossl_aes
BENCH_EXE    := $(BENCH_DIR)/bench_ossl_aes
CSV_FILE     := $(VIEW_DIR)/bench_results.csv
PLOT_SCRIPT  := $(VIEW_DIR)/plot_bench.py

.PHONY: all clean test bench plot compare

# — Default: build library, test and bench executables —
all: $(LIB) $(TEST_EXE) $(BENCH_EXE)

# — Build AES static library —
$(LIB): $(AES_OBJS)
	ar rcs $@ $^

# — Build test executable —
$(TEST_EXE): $(AES_OBJS) $(OBJ_DIR)/$(TEST_EXE).o
	$(CC) $(CFLAGS) $^ -L. -lossl_aes -o $@

# — Build benchmark executable —
$(BENCH_EXE): $(AES_OBJS) $(OBJ_DIR)/$(BENCH_EXE).o
	$(CC) $(CFLAGS) $^ -L. -lossl_aes -lm -o $@

# — Produce the CSV by running the benchmark —
$(CSV_FILE): $(BENCH_EXE)
	@echo "Running benchmark to generate $@..."
	@./$(BENCH_DIR)/bench_ossl_aes > $@

# — Invoke your Python plot script in view/ —  
plot: $(CSV_FILE) $(PLOT_SCRIPT)
	@echo "Generating plots via $(PLOT_SCRIPT)…"
	@python3 $(PLOT_SCRIPT) $(CSV_FILE)

compare: bench_results1.csv bench_results2.csv
	@python3 $(VIEW_DIR)/compare_bench.py \
	    bench_results1.csv "Baseline" \
	    bench_results2.csv "Optimized"

# — Run the self-tests —
test: $(TEST_EXE)
	@echo "Running AES self-tests..."
	@./$(TEST_EXE)

# — Run the benchmark —
bench: $(BENCH_EXE)
	@echo "Running AES benchmark..."
	@./$(BENCH_EXE)

# — Clean all build artifacts —
clean:
	rm -rf $(OBJ_DIR) $(LIB) \
	       $(TEST_EXE) $(BENCH_EXE) \
		   $(VIEW_DIR)/*.csv
	@echo "Cleaned up all build artifacts."

# -- Rebuild all targets --
rebuild: clean all
	@echo "Rebuilding all targets..."
	@echo "[*] Rebuild complete."
	@echo "[1] Run 'make test' to run the self-tests."
	@echo "[2] Run 'make bench' to run the benchmark."
	@echo "[3] Run 'make plot' to generate plots from the benchmark results."
# — Clean up object files and dependencies —
clean-obj:
	rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d
	@echo "Cleaned up object files and dependencies."
	@echo "Run 'make clean' to remove all build artifacts."

# — Generic compile rule + auto-deps —
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)









# ###############################################################################
# # Makefile for Jasmin-assembly-benchmark
# # Source files under src/, organized by category (blockcipher, hash, etc.)
# # Targets:
# #   all     - alias for build
# #   build   - compile .jasm -> .j, assemble .j -> .class
# #   rebuild - clean then build
# #   clean   - remove entire build directory
# ###############################################################################

# # Directories
# SRC_DIR   := src
# BUILD_DIR := build

# # Find all .jasm under SRC_DIR
# JASM_SRCS    := $(shell find $(SRC_DIR) -name '*.jasm')
# # Corresponding .j and .class targets in BUILD_DIR
# J_FILES      := $(patsubst $(SRC_DIR)/%.jasm,$(BUILD_DIR)/%.j,$(JASM_SRCS))
# CLASS_FILES  := $(patsubst $(BUILD_DIR)/%.j,$(BUILD_DIR)/%.class,$(J_FILES))

# # Phony targets
# .PHONY: all build rebuild clean

# # Default
# all: build

# # Build: compile & assemble
# build: $(CLASS_FILES)
# 	@echo "[BUILD] Finished all benchmarks."

# # Rebuild: clean + build
# rebuild: clean build

# # Clean: remove build directory
# clean:
# 	rm -rf $(BUILD_DIR)
# 	@echo "[CLEAN] Removed $(BUILD_DIR)/"

# # Rule: .jasm -> .j
# $(BUILD_DIR)/%.j: $(SRC_DIR)/%.jasm
# 	@mkdir -p $(dir $@)
# 	@echo "[COMPILE] $< -> $@"
# 	jasmc $< -o $@

# # Rule: .j -> .class
# $(BUILD_DIR)/%.class: $(BUILD_DIR)/%.j
# 	@mkdir -p $(dir $@)
# 	@echo "[ASSEMBLE] $< -> $@"
# 	jasmin $< -o $@
# 	@echo "[ASSEMBLE] Generated $@"
