import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import ScalarFormatter
import re

# Configuration: number of top opcodes to display
TOP_N = 20

# List of section headers corresponding to implementations
bases = [
    'keccak1600-avx2',
    'keccak1600-x86_64',
    'sha3_256_avx2',
    'sha3_256_ref'
]

# Parse result.txt into a dict of dicts: {base: {opcode: count}}
freq_map = {base: {} for base in bases}
current = None
header_re = re.compile(r"^---\s*(.+?)\s*---")

with open('result.txt') as f:
    for line in f:
        line = line.strip()
        if not line:
            continue
        m = header_re.match(line)
        if m:
            current = m.group(1)
            continue
        if current:
            op, cnt = line.split(':', 1)
            freq_map[current][op.strip()] = int(cnt.strip())

# Build DataFrame: rows are opcodes, columns are implementations
all_ops = sorted({op for fm in freq_map.values() for op in fm})
df = pd.DataFrame({
    base: [freq_map[base].get(op, 0) for op in all_ops]
    for base in bases
}, index=all_ops)

# Compute total frequency across implementations and select top N
df['total'] = df.sum(axis=1)
top_ops = df['total'].sort_values(ascending=False).head(TOP_N).index
df_top = df.loc[top_ops].drop(columns='total')

# Plot settings
n_bases = len(bases)
x = np.arange(len(df_top))
total_width = 0.8
width = total_width / n_bases
cmap = plt.get_cmap('tab10')
colors = [cmap(i) for i in range(n_bases)]

fig, ax = plt.subplots(figsize=(12, 6))

# Plot grouped bars for top opcodes only
for i, base in enumerate(bases):
    bars = ax.bar(x - total_width/2 + i*width + width/2,
                  df_top[base], width, label=base, color=colors[i])
    # Annotate each bar with its value
    for bar in bars:
        h = bar.get_height()
        ax.annotate(f'{h}',
                    xy=(bar.get_x() + bar.get_width()/2, h),
                    xytext=(0, 3), textcoords='offset points',
                    ha='center', va='bottom', fontsize=8,
                    bbox=dict(boxstyle='round,pad=0.2', fc='white', alpha=0.6))

# Axis formatting
ax.set_xticks(x)
ax.set_xticklabels(df_top.index, rotation=45, ha='right')
ax.yaxis.set_major_formatter(ScalarFormatter(useOffset=False))
ax.ticklabel_format(style='plain', axis='y')

# Grid & labels
ax.grid(which='both', axis='y', linestyle='--', linewidth=0.4, alpha=0.7)
ax.set_xlabel('Opcode')
ax.set_ylabel('Frequency')
ax.set_title(f'Top {TOP_N} Opcode Frequency Comparison')
ax.legend()

plt.tight_layout()
plt.show()
