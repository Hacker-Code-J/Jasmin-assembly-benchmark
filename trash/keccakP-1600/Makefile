# Makefile for compiling KeccakP-1600 benchmark with assembly for AVX2, x86_64, Jazz x86_64, and C reference

# Compiler and flags
CC       := gcc
CFLAGS   := -std=c99 -O3 -Wall -Wextra # Default to 64-bit architecture for x86_64

# Paths for avx2, jazz_x86_64, x86_64, and c_ref
AVX2_DIR       := avx2
JAZZ_X86_64_DIR := jazz_x86_64
X86_64_DIR     := x86_64
C_REF_DIR      := c_ref

# Build targets for AVX2, Jazz, x86_64, and C reference
.PHONY: rebuild avx2 jazz_x86_64 x86 c_ref clean run-avx2 run-jazz_x86_64 run-x86 run-c_ref

# Default target for rebuilding the project
rebuild: clean avx2 jazz_x86_64 x86 c_ref

# Build for AVX2
avx2: CFLAGS += -mavx2 -fPIE # Add AVX2 flag to CFLAGS for avx2 build
avx2: $(AVX2_DIR)/benchmark_liboqs_avx2.c $(AVX2_DIR)/KeccakP-1600-AVX2.s
	$(CC) $(CFLAGS) $(AVX2_DIR)/benchmark_liboqs_avx2.c $(AVX2_DIR)/KeccakP-1600-AVX2.s -o $(AVX2_DIR)/benchmark_liboqs_avx2 -lm -pthread

# Build for Jazz x86-64 (with assembly from jazz_x86_64)
jazz_x86_64: CFLAGS += -m64  # Add 64-bit flag for Jazz x86-64 build
jazz_x86_64: $(JAZZ_X86_64_DIR)/benchmark_jasmin_x86-64.c $(JAZZ_X86_64_DIR)/keccackP-1600_jazz_ref.s
	$(CC) $(CFLAGS) $(JAZZ_X86_64_DIR)/benchmark_jasmin_x86-64.c $(JAZZ_X86_64_DIR)/keccackP-1600_jazz_ref.s -o $(JAZZ_X86_64_DIR)/benchmark_jasmin_x86-64 -lm -pthread -no-pie

# Build for x86-64 (with assembly from x86_64)
x86: CFLAGS += -m64  # Default flag for x86-64
x86: $(X86_64_DIR)/benchmark_liboqs_x86-64.c $(X86_64_DIR)/KeccakP-1600-x86-64-gas.s
	$(CC) $(CFLAGS) $(X86_64_DIR)/benchmark_liboqs_x86-64.c $(X86_64_DIR)/KeccakP-1600-x86-64-gas.s -o $(X86_64_DIR)/benchmark_liboqs_x86-64 -lm -pthread -no-pie

# Build for C reference (with C-based reference implementation)
c_ref: CFLAGS += -m64  # Ensure we compile with 64-bit flag
c_ref: $(C_REF_DIR)/benchmark_liboqs_c_ref.c $(C_REF_DIR)/KeccakP-1600-compact64.c $(C_REF_DIR)/KeccakP-1600-SnP.h $(C_REF_DIR)/SnP-Relaned.h $(C_REF_DIR)/brg_endian.h
	$(CC) $(CFLAGS) $(C_REF_DIR)/benchmark_liboqs_c_ref.c $(C_REF_DIR)/KeccakP-1600-compact64.c -o $(C_REF_DIR)/benchmark_liboqs_c_ref -lm -pthread

# Run the AVX2 benchmark
run-avx2: avx2
	./$(AVX2_DIR)/benchmark_liboqs_avx2

# Run the Jazz x86-64 benchmark
run-jazz_x86_64: jazz_x86_64
	./$(JAZZ_X86_64_DIR)/benchmark_jasmin_x86-64

# Run the x86-64 benchmark
run-x86: x86
	./$(X86_64_DIR)/benchmark_liboqs_x86-64

# Run the C reference benchmark
run-c_ref: c_ref
	./$(C_REF_DIR)/benchmark_liboqs_c_ref

# Clean up the build artifacts
clean:
	rm -f $(AVX2_DIR)/benchmark_liboqs_avx2 $(X86_64_DIR)/benchmark_liboqs_x86-64 $(JAZZ_X86_64_DIR)/benchmark_jasmin_x86-64 $(C_REF_DIR)/benchmark_liboqs_c_ref

