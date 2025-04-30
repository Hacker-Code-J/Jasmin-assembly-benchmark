#!/usr/bin/env python3
#python3 compare_bench.py bench_results1.csv "Baseline" bench_results2.csv "Optimized"                      
import pandas as pd
import matplotlib.pyplot as plt
import re, sys, os, io

def load_csv(path):
    with open(path, 'r') as f:
        lines = f.readlines()
    header = lines[0]
    data = [L for L in lines[1:] if re.match(r'^\s*\d', L)]
    return pd.read_csv(io.StringIO(header + ''.join(data)))

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

def compare_plot(summary1, summary2, label1, label2, out_dir):
    # Throughput comparison
    plt.figure(figsize=(8,6))
    for df, label, color in [(summary1, label1, 'tab:blue'), (summary2, label2, 'tab:orange')]:
        x = df['size']/1024
        y = df['mbps_mean']
        yerr = df['mbps_std']
        plt.errorbar(x, y, yerr=yerr, fmt='o-', capsize=5,
                     color=color, label=label)
    plt.xscale('log')
    plt.xlabel('Buffer Size (KiB)')
    plt.ylabel('Throughput (MB/s)')
    plt.title('AES-128 ECB Throughput Comparison')
    plt.grid(which='both', linestyle='--', linewidth=0.4)
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(out_dir, 'compare_throughput.png'), dpi=300)
    plt.close()

    # Cycles-per-byte comparison
    plt.figure(figsize=(8,6))
    for df, label, color in [(summary1, label1, 'tab:green'), (summary2, label2, 'tab:red')]:
        x = df['size']/1024
        y = df['cpb_mean']
        yerr = df['cpb_std']
        plt.errorbar(x, y, yerr=yerr, fmt='s--', capsize=5,
                     color=color, label=label)
    plt.xscale('log')
    plt.xlabel('Buffer Size (KiB)')
    plt.ylabel('Cycles per Byte')
    plt.title('AES-128 ECB Efficiency Comparison')
    plt.grid(which='both', linestyle='--', linewidth=0.4)
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(out_dir, 'compare_cycles.png'), dpi=300)
    plt.close()

def main():
    if len(sys.argv) != 5:
        print("Usage: compare_bench.py <csv1> <label1> <csv2> <label2>")
        sys.exit(1)
    csv1, label1, csv2, label2 = sys.argv[1:]
    out_dir = os.path.dirname(os.path.abspath(__file__))
    os.makedirs(out_dir, exist_ok=True)

    df1 = load_csv(csv1)
    df2 = load_csv(csv2)

    s1 = summarize(df1)
    s2 = summarize(df2)

    compare_plot(s1, s2, label1, label2, out_dir)
    print(f"Saved comparison plots in {out_dir}:")
    print("  compare_throughput.png")
    print("  compare_cycles.png")

if __name__ == "__main__":
    main()
