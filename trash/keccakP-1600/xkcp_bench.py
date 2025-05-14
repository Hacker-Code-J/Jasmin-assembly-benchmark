import matplotlib.pyplot as plt
from matplotlib.ticker import ScalarFormatter

# Data parsing function for the given data
def parse_benchmark_data(data):
    sizes = []
    cycles = []

    # Process the data line by line
    for line in data.splitlines():
        # We only want lines containing cycles per byte
        if "cycles/byte" in line:
            parts = line.split(":")
            size = parts[0].strip()
            cycle_values = parts[1].split()

            # Extract cycles for each block size
            sizes.extend([16, 17, 21])  # Lane counts corresponding to 16, 17, 21
            cycles.extend([float(cycle) for cycle in cycle_values])

    return sizes, cycles

# Input data provided
avx2_data = """
Time for loop of KeccakP1600_AddBytes() and KeccakP1600_Permute_24rounds():
     laneCount:     16          17          21
       1 block:   1394         884         850
      10 blocks:  14654        9452        9248
     100 blocks:   95030       94927       93126
    1000 blocks:   950572      930920      933231
    cycles/byte:    8.79        6.87        5.48
"""

generic64_data = """
Time for loop of KeccakP1600_AddBytes() and KeccakP1600_Permute_24rounds():
     laneCount:     16          17          21
       1 block:    917         917         917
      10 blocks:   9145        9145        9179
     100 blocks:   91458       91391       91731
    1000 blocks:   914599      913817      916843
    cycles/byte:    7.15        6.72        5.46
"""

reference_data = """
Time for loop of KeccakP1600_AddBytes() and KeccakP1600_Permute_24rounds():
     laneCount:     16          17          21
       1 block:  16728       13430       13498
      10 blocks: 167892      134844      135320
     100 blocks: 1342592     1345754     1357042
    1000 blocks: 13467842    13485386    13535638
    cycles/byte:  114.75       99.05       80.53
"""

# Parse each dataset
avx2_sizes, avx2_cycles = parse_benchmark_data(avx2_data)
generic64_sizes, generic64_cycles = parse_benchmark_data(generic64_data)
reference_sizes, reference_cycles = parse_benchmark_data(reference_data)

# Create the plot with styling applied
plt.figure(figsize=(10, 6))

# Plot each dataset with appropriate style
plt.plot(avx2_sizes, avx2_cycles, label='AVX2', marker='o', linestyle='-', color='blue')
plt.plot(generic64_sizes, generic64_cycles, label='Generic64', marker='s', linestyle='-', color='green')
plt.plot(reference_sizes, reference_cycles, label='Reference', marker='^', linestyle='-', color='red')

# Adding labels, title, and style to the plot
plt.xlabel('Lane Count (Size)')
plt.ylabel('Cycles per Byte')
plt.title('Benchmark Comparison: AVX2, Generic64, Reference')
plt.legend()

# Apply log scale and formatting
plt.xscale('log')
plt.grid(True, which='both', linestyle='--', linewidth=0.4)
plt.ticklabel_format(style='plain', axis='y')
plt.gca().yaxis.set_major_formatter(ScalarFormatter(useOffset=False))

# Show the plot
plt.tight_layout()
plt.show()
