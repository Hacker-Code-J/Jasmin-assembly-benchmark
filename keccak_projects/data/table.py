import pandas as pd
import matplotlib.pyplot as plt

# ─── 1) Load the three CSVs ────────────────────────────────────────────────────
baseline = pd.read_csv('c_xkcp.csv')
xkcp     = pd.read_csv('x86_64_xkcp.csv')
libjade  = pd.read_csv('x86_64_libjade.csv')

# ─── 2) Define the SHA-3 variants ─────────────────────────────────────────────
variants = ['SHA3-256', 'SHA3-384', 'SHA3-512']

# ─── 3) Compute improvement rates ─────────────────────────────────────────────
#    throughput: (new/old - 1)*100  ↑ better when larger
#    latency & cycles: (old/new - 1)*100  ↑ better when larger
impr = pd.DataFrame({'Message Size': baseline['Message Size']})
for v in variants:
    thr = f'{v}(MB/s)'
    lat = f'{v} Latency(ms)'
    cyc = f'{v} Cycles/byte'
    impr[f'{v} Thr XKCP (%)']       = (xkcp[thr]       / baseline[thr] - 1) * 100
    impr[f'{v} Thr LibJade (%)']    = (libjade[thr]    / baseline[thr] - 1) * 100
    impr[f'{v} Lat XKCP (%)']       = (baseline[lat]   / xkcp[lat]    - 1) * 100
    impr[f'{v} Lat LibJade (%)']    = (baseline[lat]   / libjade[lat] - 1) * 100
    impr[f'{v} Cyc XKCP (%)']       = (baseline[cyc]   / xkcp[cyc]    - 1) * 100
    impr[f'{v} Cyc LibJade (%)']    = (baseline[cyc]   / libjade[cyc] - 1) * 100

# ─── 4) Print a nice table of improvements ──────────────────────────────────
print("Improvement rates over C/XKCP baseline (in %):\n")
print(impr.to_string(index=False, float_format='%.2f'))

# ─── 5) Plotting improvements ────────────────────────────────────────────────
sizes = impr['Message Size'] // 1024
labels = [f"{sz} KiB" for sz in sizes]
x = list(range(len(labels)))

colors = {'XKCP': 'orange', 'LibJade': 'green'}

fig, axes = plt.subplots(3, 3, figsize=(15, 12), sharex=True)
for row, v in enumerate(variants):
    # Throughput subplot
    ax = axes[row, 0]
    ax.plot(x, impr[f'{v} Thr XKCP (%)'],    color=colors['XKCP'], marker='o', label='XKCP')
    ax.plot(x, impr[f'{v} Thr LibJade (%)'], color=colors['LibJade'], marker='s', label='LibJade')
    if row == 0: ax.set_title('Throughput improvement (%)', pad=12)
    ax.set_ylabel(v, rotation=0, labelpad=40, va='center')
    ax.grid(True, linestyle=':', linewidth=0.5)

    # Latency subplot
    ax = axes[row, 1]
    ax.plot(x, impr[f'{v} Lat XKCP (%)'],    color=colors['XKCP'], marker='o')
    ax.plot(x, impr[f'{v} Lat LibJade (%)'], color=colors['LibJade'], marker='s')
    if row == 0: ax.set_title('Latency improvement (%)', pad=12)
    ax.grid(True, linestyle=':', linewidth=0.5)

    # Cycles subplot
    ax = axes[row, 2]
    ax.plot(x, impr[f'{v} Cyc XKCP (%)'],    color=colors['XKCP'], marker='o')
    ax.plot(x, impr[f'{v} Cyc LibJade (%)'], color=colors['LibJade'], marker='s')
    if row == 0: ax.set_title('Cycles/byte improvement (%)', pad=12)
    ax.grid(True, linestyle=':', linewidth=0.5)

# ─── 6) X-axis labels only on bottom row ────────────────────────────────────
for ax in axes[:-1, :].flatten():
    ax.set_xticks([])
for ax in axes[-1, :]:
    ax.set_xticks(x)
    ax.set_xticklabels(labels, rotation=45, ha='right')

# ─── 7) Shared legend at bottom ─────────────────────────────────────────────
handles, _ = axes[0,0].get_legend_handles_labels()
fig.legend(handles, ['XKCP', 'LibJade'],
           title='Implementation',
           loc='lower center',
           ncol=2,
           frameon=False,
           fontsize=12)

plt.tight_layout(rect=(0, 0.05, 1, 1))
plt.savefig('sha3_improvement_3x3.png', dpi=300)
plt.show()

