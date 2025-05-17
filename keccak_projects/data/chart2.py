import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.lines import Line2D

# 1) map labels → CSVs
files = {
    'XKCP-x86_64':    'x86_64_xkcp.csv',
    'LibJade-x86_64': 'x86_64_libjade.csv',
}
baseline_csv = 'c_xkcp.csv'

# 2) load
base_df = pd.read_csv(baseline_csv)
dfs     = {lbl: pd.read_csv(path) for lbl, path in files.items()}

# 3) x‐axis: message sizes → KiB labels
sizes    = base_df['Message Size'].astype(int).tolist()
x        = list(range(len(sizes)))
x_labels = [f"{sz//1024} KiB" for sz in sizes]

# 4) variants & column‐name maps
variants = ['SHA3-256','SHA3-384','SHA3-512']
thr_cols = {v: f'{v}(MB/s)'       for v in variants}
lat_cols = {v: f'{v} Latency(ms)' for v in variants}
cyc_cols = {v: f'{v} Cycles/byte'  for v in variants}

# 5) styling
impls      = list(dfs.keys())
colors     = {'XKCP-x86_64':'orange','LibJade-x86_64':'green'}
linestyles = {'SHA3-256':'-','SHA3-384':'--','SHA3-512':':'}

# 6) build figure
fig, axes = plt.subplots(1, 3, figsize=(15,5), sharex=True)
metrics = [
    ('Throughput Improvement (%)', thr_cols, 'higher_better'),
    ('Latency Improvement (%)',    lat_cols, 'lower_better'),
    ('Cycles/byte Improvement (%)',cyc_cols, 'lower_better'),
]

# 7) compute & plot
for ax, (title, colmap, mode) in zip(axes, metrics):
    for impl in impls:
        other = dfs[impl]
        for var in variants:
            A = base_df[colmap[var]].astype(float)
            B = other [colmap[var]].astype(float)
            if mode=='higher_better':
                # pct = (B - A)/A*100.0
                pct = B/A
            else:
                # pct = (A - B)/A*100.0
                pct = B/A
            ax.plot(x, pct,
                    color     = colors[impl],
                    linestyle = linestyles[var],
                    marker    = 'o',
                    label     = var if impl==impls[0] else "_nolegend_")
    ax.set_title(title, pad=12)
    ax.set_xticks(x)
    ax.set_xticklabels(x_labels, rotation=45, ha='right')
    ax.set_ylabel('Improvement (%)')
    ax.grid(True, linestyle=':', linewidth=0.5)

# ─── 8) legends ───────────────────────────────────────────────────────────────
# (a) Implementation legend just above the axes
imp_handles = [Line2D([0],[0], color=colors[impl], lw=2)
               for impl in impls]
fig.legend(imp_handles, impls,
           title='Implementation',
           loc='upper center',
           bbox_to_anchor=(0.5, 1.1),  # fine
           ncol=len(impls),
           title_fontproperties={'weight': 'bold', 'size': 16},
    fontsize=14,
           frameon=False)

# (b) Variant legend just below the axes
var_handles = [Line2D([0],[0], color='black', lw=2, linestyle=linestyles[v])
               for v in variants]
fig.legend(var_handles, variants,
           title='Variant',
           loc='lower center',
           bbox_to_anchor=(0.5, -0.075), # push a little lower
           ncol=len(variants),
           title_fontproperties={'weight': 'bold', 'size': 16},
    fontsize=14,
           frameon=False)

# ─── 9) layout & save ────────────────────────────────────────────────────────
# give more bottom-margin (20% of the height) so that your -0.10 anchor
# actually shows up, and leave top-margin for the impl legend too
plt.subplots_adjust(top=0.88, bottom=0.20)

# `bbox_inches='tight'` will automatically expand the saved area so
# nothing is clipped, even if it sits outside the nominal subplot box.
plt.savefig('sha3_diff_analysis.png', dpi=300, bbox_inches='tight')
print("Done: saved sha3_diff_analysis.png")






# import pandas as pd
# import matplotlib.pyplot as plt

# # ─── 1) Map labels to your CSV filenames ───────────────────────────────────────
# files = {
#     'C XKCP (Baseline)'       : 'c_xkcp.csv',
#     'x86_64 XKCP'             : 'x86_64_xkcp.csv',
#     'x86_64 Libjade'          : 'x86_64_libjade.csv',
# }

# # ─── 2) Load the datasets ───────────────────────────────────────────────────────
# dfs = {label: pd.read_csv(path) for label, path in files.items()}

# # ─── 3) Define SHA-3 variants and column mappings ───────────────────────────────
# variants = ['SHA3-256','SHA3-384','SHA3-512']
# thr_cols = {v: f'{v}(MB/s)'         for v in variants}
# lat_cols = {v: f'{v} Latency(ms)'   for v in variants}
# cyc_cols = {v: f'{v} Cycles/byte'    for v in variants}

# baseline_label = 'C XKCP (Baseline)'
# baseline = dfs[baseline_label]
# impls = [lbl for lbl in dfs if lbl != baseline_label]

# # ─── 4) Prepare the x-axis (KiB) ─────────────────────────────────────────────────
# sizes_kb = baseline['Message Size'] / 1024  # convert bytes to KiB

# # ─── 5) Compute percent improvements over baseline ───────────────────────────────
# improvements = {}
# for impl in impls:
#     df_imp = pd.DataFrame({'Message Size (KiB)': sizes_kb})
#     for v in variants:
#         thr_imp = (dfs[impl][thr_cols[v]] - baseline[thr_cols[v]]) / baseline[thr_cols[v]] * 100
#         lat_imp = (baseline[lat_cols[v]] - dfs[impl][lat_cols[v]]) / baseline[lat_cols[v]] * 100
#         cyc_imp = (baseline[cyc_cols[v]] - dfs[impl][cyc_cols[v]]) / baseline[cyc_cols[v]] * 100
#         df_imp[f'{v} Throughput Δ%'] = thr_imp
#         df_imp[f'{v} Latency Δ%']    = lat_imp
#         df_imp[f'{v} Cycles Δ%']     = cyc_imp
#     improvements[impl] = df_imp

# # ─── 6) Plot settings ───────────────────────────────────────────────────────────
# linestyles = {'SHA3-256':'-','SHA3-384':'--','SHA3-512':':'}
# colors     = ['tab:blue','tab:orange']

# # ─── 7) Plot throughput improvement ──────────────────────────────────────────────
# plt.figure(figsize=(8,5))
# for i, impl in enumerate(impls):
#     df_imp = improvements[impl]
#     for v in variants:
#         plt.plot(df_imp['Message Size (KiB)'],
#                  df_imp[f'{v} Throughput Δ%'],
#                  color=colors[i],
#                  linestyle=linestyles[v],
#                  marker='o',
#                  label=f'{impl} {v}')
# plt.xlabel('Message Size (KiB)')
# plt.ylabel('Throughput Improvement (%)')
# plt.title('SHA-3 Throughput Improvement vs C XKCP')
# plt.grid(True)
# plt.legend(loc='best')
# plt.tight_layout()
# plt.savefig('sha3_throughput_improvement.png', dpi=300)

# # ─── 8) Plot latency improvement ─────────────────────────────────────────────────
# plt.figure(figsize=(8,5))
# for i, impl in enumerate(impls):
#     df_imp = improvements[impl]
#     for v in variants:
#         plt.plot(df_imp['Message Size (KiB)'],
#                  df_imp[f'{v} Latency Δ%'],
#                  color=colors[i],
#                  linestyle=linestyles[v],
#                  marker='o',
#                  label=f'{impl} {v}')
# plt.xlabel('Message Size (KiB)')
# plt.ylabel('Latency Improvement (%) (higher is better)')
# plt.title('SHA-3 Latency Improvement vs C XKCP')
# plt.grid(True)
# plt.legend(loc='best')
# plt.tight_layout()
# plt.savefig('sha3_latency_improvement.png', dpi=300)

# # ─── 9) Plot cycles-per-byte improvement ────────────────────────────────────────
# plt.figure(figsize=(8,5))
# for i, impl in enumerate(impls):
#     df_imp = improvements[impl]
#     for v in variants:
#         plt.plot(df_imp['Message Size (KiB)'],
#                  df_imp[f'{v} Cycles Δ%'],
#                  color=colors[i],
#                  linestyle=linestyles[v],
#                  marker='o',
#                  label=f'{impl} {v}')
# plt.xlabel('Message Size (KiB)')
# plt.ylabel('Cycles-per-byte Improvement (%)')
# plt.title('SHA-3 Cycles/byte Improvement vs C XKCP')
# plt.grid(True)
# plt.legend(loc='best')
# plt.tight_layout()
# plt.savefig('sha3_cycles_improvement.png', dpi=300)

# print("Done: saved three improvement plots.")
