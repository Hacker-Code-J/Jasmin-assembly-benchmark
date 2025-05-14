import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import ScalarFormatter

# Load result.txt into a DataFrame
openssl = {}
jasmin = {}
current = None
with open('result.txt') as f:
    for line in f:
        line = line.strip()
        if not line:
            continue
        if line.startswith('---'):
            current = 'openssl' if 'aesni-x86_64' in line else 'jasmin'
            continue
        op, cnt = line.split(':', 1)
        if current == 'openssl':
            openssl[op.strip()] = int(cnt.strip())
        else:
            jasmin[op.strip()] = int(cnt.strip())

# Create DataFrame
ops = sorted(set(openssl.keys()) | set(jasmin.keys()))
df = pd.DataFrame({
    'opcode': ops,
    'OpenSSL AES-NI': [openssl.get(op, 0) for op in ops],
    'Jasmin AES-NI': [jasmin.get(op, 0) for op in ops]
})

# Plot setup
x = np.arange(len(df))
width = 0.35

fig, ax = plt.subplots(figsize=(12, 6))
bars1 = ax.bar(x - width/2, df['OpenSSL AES-NI'], width,
               color='tab:cyan', label='OpenSSL AES-NI')
bars2 = ax.bar(x + width/2, df['Jasmin AES-NI'], width,
               color='tab:purple', label='Jasmin AES-NI')

# Annotate values
for bar in bars1 + bars2:
    h = bar.get_height()
    ax.annotate(f'{h}',
                xy=(bar.get_x()+bar.get_width()/2, h),
                xytext=(0, 4), textcoords='offset points',
                ha='center', va='bottom', fontsize=8,
                bbox=dict(boxstyle='round,pad=0.2', fc='white', alpha=0.6))

# Axis formatting
ax.set_xticks(x)
ax.set_xticklabels(df['opcode'], rotation=45, ha='right')
ax.yaxis.set_major_formatter(ScalarFormatter(useOffset=False))
ax.ticklabel_format(style='plain', axis='y')

# Grid & labels
ax.grid(which='both', linestyle='--', linewidth=0.4, axis='y', alpha=0.7)
ax.set_xlabel('Opcode')
ax.set_ylabel('Frequency')
ax.set_title('Opcode Frequency Comparison: OpenSSL AES-NI vs Jasmin AES-NI')
ax.legend()

plt.tight_layout()
plt.show()
