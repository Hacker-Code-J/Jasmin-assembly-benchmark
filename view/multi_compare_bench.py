#!/usr/bin/env python3
#python3 compare_bench.py bench_aes_c.csv "openssl_aes_c" bench_aes_aesni.csv "openssl_aesni"   
#python3 compare_bench.py bench_aes_aesni.csv "openssl_aesni" bench_aes_jasmin.csv "jasmin_aes_asm"                      

#!/usr/bin/env python3
import pandas as pd
import matplotlib.pyplot as plt
import re, sys, os, io
from matplotlib.ticker import ScalarFormatter

def load_summary(path):
    with open(path,'r') as f:
        lines = f.readlines()
    for idx, L in enumerate(lines):
        if L.startswith("size,mbps_mean"):
            hdr  = lines[idx]
            body = [L for L in lines[idx+1:] if re.match(r'^\s*\d', L)]
            return pd.read_csv(io.StringIO(hdr + "".join(body)))
    raise RuntimeError(f"Summary section not found in {path}")

def compare_multi_plot(summaries, labels, out_dir):
    # pick N distinct colors once
    base_colors = plt.rcParams['axes.prop_cycle'].by_key()['color']
    # map each label → a unique color
    label_to_color = {lbl: base_colors[i % len(base_colors)]
                      for i, lbl in enumerate(labels)}

    # — Throughput —
    fig, ax = plt.subplots(figsize=(8,6))
    for df, label in zip(summaries, labels):
        c = label_to_color[label]
        x    = df['size']/1024
        y    = df['mbps_mean']
        yerr = df['mbps_stddev']

        ax.plot  (x, y, marker='o', linestyle='-', color=c, label=label)
        ax.fill_between(x, y-yerr, y+yerr, color=c, alpha=0.2)
        for xi, yi in zip(x, y):
            ax.annotate(f"{yi:.1f}", xy=(xi,yi), xytext=(0,8),
                        textcoords="offset points", ha='center',
                        fontsize=8, color=c,
                        bbox=dict(facecolor='white', edgecolor=c,
                                  pad=1, alpha=0.7))

    ax.set_xscale('log')
    ax.set_xlabel('Buffer Size (KiB)')
    ax.set_ylabel('Throughput (MB/s)')
    ax.set_title('AES-128 Throughput Comparison')
    ax.grid(which='both', linestyle='--', linewidth=0.4)
    ax.legend()
    ax.yaxis.set_major_formatter(ScalarFormatter(useOffset=False))
    ax.ticklabel_format(style='plain', axis='y')
    fig.tight_layout()
    fig.savefig(os.path.join(out_dir, 'compare_throughput.png'), dpi=300)
    plt.close(fig)

    # — Cycles per Byte —
    fig, ax = plt.subplots(figsize=(8,6))
    for df, label in zip(summaries, labels):
        c = label_to_color[label]
        x    = df['size']/1024
        y    = df['cpb_mean']
        yerr = df['cpb_stddev']

        ax.plot  (x, y, marker='s', linestyle='--', color=c, label=label)
        ax.fill_between(x, y-yerr, y+yerr, color=c, alpha=0.2)
        for xi, yi in zip(x, y):
            ax.annotate(f"{yi:.2f}", xy=(xi,yi), xytext=(0,8),
                        textcoords="offset points", ha='center',
                        fontsize=8, color=c,
                        bbox=dict(facecolor='white', edgecolor=c,
                                  pad=1, alpha=0.7))

    ax.set_xscale('log')
    ax.set_xlabel('Buffer Size (KiB)')
    ax.set_ylabel('Cycles per Byte')
    ax.set_title('AES-128 Efficiency Comparison')
    ax.grid(which='both', linestyle='--', linewidth=0.4)
    ax.legend()
    ax.yaxis.set_major_formatter(ScalarFormatter(useOffset=False))
    ax.ticklabel_format(style='plain', axis='y')
    fig.tight_layout()
    fig.savefig(os.path.join(out_dir, 'compare_cycles.png'), dpi=300)
    plt.close(fig)

def main():
    args = sys.argv[1:]
    if len(args)<4 or len(args)%2!=0:
        print("Usage: compare_bench.py <csv1> <label1> <csv2> <label2> [...]", file=sys.stderr)
        sys.exit(1)

    pairs = list(zip(args[0::2], args[1::2]))
    summaries = [load_summary(csv) for csv,_ in pairs]
    labels    = [lbl for _,lbl in pairs]

    out_dir = os.path.dirname(os.path.abspath(__file__))
    os.makedirs(out_dir, exist_ok=True)
    compare_multi_plot(summaries, labels, out_dir)
    print("Saved:")
    print("  ", os.path.join(out_dir, "compare_throughput.png"))
    print("  ", os.path.join(out_dir, "compare_cycles.png"))

if __name__=="__main__":
    main()
