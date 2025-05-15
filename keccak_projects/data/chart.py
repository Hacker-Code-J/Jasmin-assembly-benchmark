#!/usr/bin/env python3
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
from collections import OrderedDict

# ─── 1) map your CSV filenames in the exact order you want them plotted ───────
files = OrderedDict([
    ('[XKCP] SHA3 (C)'        , 'c_xkcp.csv'),
    ('[XKCP] SHA3 (x86_64)'   , 'x86_64_xkcp.csv'),
    ('[XKCP] SHA3 (AVX2)'     , 'avx2_xkcp.csv'),
    # ('[Libjade] SHA3 (x86_64)', 'x86_64_libjade.csv'),
    # ('[Libjade] SHA3 (AVX2)'  , 'avx2_libjade.csv'),
])

# ─── 2) load them all into DataFrames (preserves our ordering) ───────────────
dfs = {label: pd.read_csv(path) for label, path in files.items()}

# ─── 3) SHA-3 variants and their column‐name patterns ─────────────────────────
variants = ['SHA3-256', 'SHA3-384', 'SHA3-512']
thr_cols = {v: f'{v}(MB/s)'       for v in variants}
lat_cols = {v: f'{v} Latency(ms)' for v in variants}
cyc_cols = {v: f'{v} Cycles/byte'  for v in variants}

# ─── 4) build our x‐axis: 0…N−1 with KiB labels ───────────────────────────────
sizes = dfs[next(iter(dfs))]['Message Size'].astype(int).tolist()
x     = list(range(len(sizes)))
x_lbl = [f"{sz//1024} KiB" for sz in sizes]

# ─── 5) assign one color per implementation, one linestyle per variant ──────────
impls      = list(files.keys())            # guarantees desired order
colors     = plt.cm.tab10.colors           # a palette of ≥5 distinct colors
impl_color = {impl: colors[i] for i, impl in enumerate(impls)}
linestyles = {
    'SHA3-256': '-',
    'SHA3-384': '--',
    'SHA3-512': ':',
}

# ─── 6) set up a 3×3 grid: rows=variant, cols=metric ──────────────────────────
metrics = [
    ('Throughput (MB/s)', thr_cols),
    ('Latency (ms)'      , lat_cols),
    ('Cycles / Byte'     , cyc_cols),
]
fig, axes = plt.subplots(3, 3, figsize=(12, 9), sharex=True)

# ─── 7) plot each cell ────────────────────────────────────────────────────────
for row, var in enumerate(variants):
    for col, (title, cmap) in enumerate(metrics):
        ax = axes[row, col]
        for impl in impls:
            y = dfs[impl][cmap[var]].astype(float)
            ax.plot(
                x, y,
                color     = impl_color[impl],
                linestyle = linestyles[var],
                marker    = 'o',
                markersize= 4,
                label     = impl if (row, col) == (0, 0) else "_nolegend_"
            )
        if row == 0:
            ax.set_title(title, pad=12)
        ax.grid(True, linestyle=':', linewidth=0.5)

# ─── 8) only bottom row shows x‐axis ticks & labels ────────────────────────────
for ax in axes[:-1, :].flatten():
    ax.set_xticks([])

for ax in axes[-1, :]:
    ax.set_xticks(x)
    ax.set_xticklabels(x_lbl, rotation=45, ha='right')

# ─── 9) big variant labels down the left margin ───────────────────────────────
for row, var in enumerate(variants):
    ax = axes[row, 0]
    ax.text(
        -0.25, 0.5, var,
        transform=ax.transAxes,
        va='center', ha='center',
        rotation='vertical',
        fontsize=14
    )

# ─── 10) shared legend at bottom, in our specified order ──────────────────────
proxies = [
    Line2D([0], [0], color=impl_color[impl], lw=2)
    for impl in impls
]
fig.legend(
    proxies, impls,
    title='Implementation',
    loc='lower center',
    ncol=len(impls),
    frameon=False,
    fontsize=10
)

# ─── 11) tighten & save ───────────────────────────────────────────────────────
plt.tight_layout(rect=(0, 0.05, 1, 1))  # leave space at bottom for legend
fig.savefig('sha3_3x3_grid.png', dpi=300)
print("sha3_3x3_grid.png written.")



# import pandas as pd
# import matplotlib.pyplot as plt
# from matplotlib.lines import Line2D

# # ─── 1) map your CSVs ──────────────────────────────────────────────────────────
# files = {
#     '[XKCP] SHA3 (C)':         'c_xkcp.csv',
#     '[XKCP] SHA3 (x86_64)':    'x86_64_xkcp.csv',
#     '[XKCP] SHA3 (AVX2)':      'avx2_xkcp.csv',
#     '[Libjade] SHA3 (x86_64)': 'x86_64_libjade.csv',
#     '[Libjade] SHA3 (AVX2)':   'avx2_libjade.csv',
# }

# # ─── 2) load data ─────────────────────────────────────────────────────────────
# dfs = {lbl: pd.read_csv(path) for lbl, path in files.items()}

# # ─── 3) SHA-3 variants & column maps ─────────────────────────────────────────
# variants = ['SHA3-256','SHA3-384','SHA3-512']
# thr_cols = {v: f'{v}(MB/s)'       for v in variants}
# lat_cols = {v: f'{v} Latency(ms)' for v in variants}
# cyc_cols = {v: f'{v} Cycles/byte'  for v in variants}

# # ─── 4) build KiB x-axis labels ──────────────────────────────────────────────
# sizes       = dfs[next(iter(dfs))]['Message Size'].astype(int)
# kb_labels   = [f"{size//1024} KiB" for size in sizes]
# x_pos       = list(range(len(kb_labels)))

# # ─── 5) colors & linestyles ─────────────────────────────────────────────────
# impls       = list(dfs.keys())
# colors      = plt.cm.tab10.colors
# impl_color  = {lbl: colors[i] for i, lbl in enumerate(impls)}
# linestyles  = {'SHA3-256':'-', 'SHA3-384':'--', 'SHA3-512':':'}

# # ─── 6) metrics grid setup ──────────────────────────────────────────────────
# metrics = [
#     ('Throughput (MB/s)', thr_cols),
#     ('Latency (ms)',       lat_cols),
#     ('Cycles / Byte',      cyc_cols),
# ]

# fig, axes = plt.subplots(3, 3, figsize=(12,9), sharex=True)

# # ─── 7) plot each cell ──────────────────────────────────────────────────────
# for r, var in enumerate(variants):
#     for c, (mname, cmap) in enumerate(metrics):
#         ax = axes[r][c]
#         for impl in impls:
#             y = dfs[impl][cmap[var]].astype(float)
#             ax.plot(x_pos, y,
#                     color=impl_color[impl],
#                     linestyle=linestyles[var],
#                     marker='o', markersize=4)
#         # only the top row gets the column title
#         if r==0:
#             ax.set_title(mname, pad=12)
#         # make a little grid
#         ax.grid(linestyle=':', linewidth=0.5)

# # ─── 8) hide internal x-ticks ────────────────────────────────────────────────
# for ax in axes[:-1].flatten():
#     ax.set_xticks([])

# # ─── 9) bottom row gets our KiB labels ──────────────────────────────────────
# for ax in axes[-1]:
#     ax.set_xticks(x_pos)
#     ax.set_xticklabels(kb_labels, rotation=45, ha='right')

# # ─── 10) big variant labels on the left ─────────────────────────────────────
# for r, var in enumerate(variants):
#     ax = axes[r][0]
#     ax.text(-0.25, 0.5, var,
#             transform=ax.transAxes,
#             va='center', ha='center',
#             rotation='vertical',
#             fontsize=14)

# # ─── 11) shared legend at bottom ─────────────────────────────────────────────
# proxies = [Line2D([0],[0],
#                   color=impl_color[impl],
#                   lw=2)
#            for impl in impls]
# fig.legend(proxies, impls,
#            title='Implementation',
#            loc='lower center',
#            ncol=len(impls),
#            frameon=False,
#            fontsize=10)

# # ─── 12) final touches ───────────────────────────────────────────────────────
# plt.tight_layout(rect=(0.1,0.08,1,1))
# fig.savefig('sha3_3x3_grid.png', dpi=300)
# print("Saved sha3_3x3_grid.png")







# import pandas as pd
# import matplotlib.pyplot as plt

# # ─── CONFIG ─────────────────────────────────────────────────────────────────────

# FILES = {
#     'AVX2 – LibJade':   'avx2_libjade.csv',
#     'AVX2 – XKCP':      'avx2_xkcp.csv',
#     'C – XKCP':         'c_xkcp.csv',
#     'x86_64 – LibJade': 'x86_64_libjade.csv',
#     'x86_64 – XKCP':    'x86_64_xkcp.csv',
# }

# VARIANTS = ['SHA3-256', 'SHA3-384', 'SHA3-512']
# # column names as they appear in the CSV
# THR_COL = {v: f'{v}(MB/s)'       for v in VARIANTS}
# LAT_COL = {v: f'{v} Latency(ms)' for v in VARIANTS}
# CYC_COL = {v: f'{v} Cycles/byte' for v in VARIANTS}

# LINESTYLES = {'SHA3-256':'-', 'SHA3-384':'--', 'SHA3-512':':'}
# COLORS      = plt.cm.tab10.colors  # up to 10 distinct colors

# # ─── LOAD & NORMALIZE ───────────────────────────────────────────────────────────

# dfs = {}
# for label, fname in FILES.items():
#     df = pd.read_csv(fname)

#     # ensure each variant has its throughput/latency/cycles column,
#     # even if the CSV omitted it
#     for v in VARIANTS:
#         if THR_COL[v] not in df.columns:
#             df[THR_COL[v]] = pd.NA
#         if LAT_COL[v] not in df.columns:
#             df[LAT_COL[v]] = pd.NA
#         if CYC_COL[v] not in df.columns:
#             df[CYC_COL[v]] = pd.NA

#     # turn "Message Size" (bytes) into an integer and keep for plotting
#     df['SizeBytes'] = df['Message Size'].astype(int)
#     dfs[label] = df

# # grab the list of sizes from any one frame (they all share the same)
# SIZES = dfs[next(iter(dfs))]['SizeBytes'].tolist()
# # categorical x positions
# POS   = list(range(len(SIZES)))
# # human-friendly tick labels in KiB
# XLABELS = [f"{b//1024} KiB" for b in SIZES]


# # ─── PLOT ONE FIGURE PER VARIANT ────────────────────────────────────────────────

# for v in VARIANTS:
#     fig, axes = plt.subplots(1, 3, figsize=(18,5))
#     panels = [
#         ('Throughput (MB/s)', THR_COL[v]),
#         ('Latency (ms)'    , LAT_COL[v]),
#         ('Cycles/byte'     , CYC_COL[v]),
#     ]

#     for ax, (title, col) in zip(axes, panels):
#         for idx, (label, df) in enumerate(dfs.items()):
#             y = df[col].astype(float)
#             ax.plot(POS, y,
#                     color=COLORS[idx],
#                     linestyle=LINESTYLES[v],
#                     marker='o',
#                     label=label)
#             # annotate every point with its value
#             for x, yv in zip(POS, y):
#                 ax.text(x, yv, f"{yv:.1f}",
#                         color=COLORS[idx],
#                         fontsize=6,
#                         ha='center', va='bottom')

#         ax.set_title(f"{v} – {title}")
#         ax.set_xticks(POS)
#         ax.set_xticklabels(XLABELS, rotation=45, ha='right')
#         ax.set_xlabel("Message Size")
#         ax.set_ylabel(title)
#         ax.grid(True)

#     # one combined legend (implementations) on the rightmost panel
#     handles, labels = axes[-1].get_legend_handles_labels()
#     axes[-1].legend(handles, labels,
#                     title="Implementation",
#                     loc='upper left',
#                     bbox_to_anchor=(1.05,1))

#     plt.tight_layout()
#     outname = v.replace('-', '') + "_by_variant.png"
#     plt.savefig(outname, dpi=300)
#     plt.close(fig)
#     print("Saved", outname)