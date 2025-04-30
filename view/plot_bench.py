#!/usr/bin/env python3
import pandas as pd
import matplotlib.pyplot as plt
import re, sys, os, io

def load_csv_only(path):
    with open(path, 'r') as f:
        lines = f.readlines()
    header = lines[0]
    data_lines = [L for L in lines[1:] if re.match(r'^\s*\d', L)]
    return pd.read_csv(io.StringIO(header + ''.join(data_lines)))

def summarize(df):
    grp = df.groupby('size')
    return grp.agg(
        mbps_mean=('mbps', 'mean'),
        mbps_std =('mbps', 'std'),
        mbps_med =('mbps', 'median'),
        cpb_mean =('cpb', 'mean'),
        cpb_std  =('cpb', 'std'),
        cpb_med  =('cpb', 'median'),
    ).reset_index()

def plot_throughput(summary, out_dir):
    x    = summary['size'] / 1024
    y    = summary['mbps_mean']
    yerr = summary['mbps_std']
    ymed = summary['mbps_med']

    plt.figure(figsize=(8,6))
    plt.errorbar(x, y, yerr=yerr, fmt='o-', capsize=5,
                 color='tab:cyan', label='Mean ± σ')
    plt.fill_between(x, y-yerr, y+yerr, color='tab:cyan', alpha=0.2)
    plt.scatter(x, ymed, marker='s', color='tab:blue', label='Median')

    # annotate every mean point
    for xi, yi in zip(x, y):
        plt.annotate(f"{yi:.1f}", (xi, yi),
                     textcoords="offset points", xytext=(0, 8), ha='center',
                     fontsize=8, color='tab:cyan')

    # annotate every median point
    for xi, ymi in zip(x, ymed):
        plt.annotate(f"{ymi:.1f}", (xi, ymi),
                     textcoords="offset points", xytext=(0, -12), ha='center',
                     fontsize=8, color='tab:blue')

    plt.xscale('log')
    plt.xlabel('Buffer Size (KiB)')
    plt.ylabel('Throughput (MB/s)')
    plt.title('AES-128 ECB Throughput')
    plt.grid(which='both', linestyle='--', linewidth=0.4)
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(out_dir, 'throughput_annotated.png'), dpi=300)
    plt.close()

def plot_efficiency(summary, out_dir):
    x    = summary['size'] / 1024
    y    = summary['cpb_mean']
    yerr = summary['cpb_std']
    ymed = summary['cpb_med']

    plt.figure(figsize=(8,6))
    plt.errorbar(x, y, yerr=yerr, fmt='s--', capsize=5,
                 color='tab:purple', label='Mean ± σ')
    plt.fill_between(x, y-yerr, y+yerr, color='tab:purple', alpha=0.2)
    plt.scatter(x, ymed, marker='o', color='tab:red', label='Median')

    # annotate every mean point
    for xi, yi in zip(x, y):
        plt.annotate(f"{yi:.2f}", (xi, yi),
                     textcoords="offset points", xytext=(0, 8), ha='center',
                     fontsize=8, color='tab:purple')

    # annotate every median point
    for xi, ymi in zip(x, ymed):
        plt.annotate(f"{ymi:.2f}", (xi, ymi),
                     textcoords="offset points", xytext=(0, -12), ha='center',
                     fontsize=8, color='tab:red')

    plt.xscale('log')
    plt.xlabel('Buffer Size (KiB)')
    plt.ylabel('Cycles per Byte')
    plt.title('AES-128 ECB Efficiency')
    plt.grid(which='both', linestyle='--', linewidth=0.4)
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(out_dir, 'cycles_annotated.png'), dpi=300)
    plt.close()

def main():
    data_file = sys.argv[1] if len(sys.argv)>1 else 'bench_results.csv'
    out_dir   = os.path.dirname(os.path.abspath(__file__))
    os.makedirs(out_dir, exist_ok=True)

    df      = load_csv_only(data_file)
    summary = summarize(df)

    plot_throughput(summary, out_dir)
    plot_efficiency(summary, out_dir)
    print(f"Saved: {out_dir}/throughput_annotated.png, {out_dir}/cycles_annotated.png")

if __name__ == "__main__":
    main()
