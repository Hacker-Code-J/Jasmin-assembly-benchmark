#!/usr/bin/env python3
#python3 compare_bench.py bench_aes_c.csv "openssl_aes_c" bench_aes_aesni.csv "openssl_aesni"   
#python3 compare_bench.py bench_aes_aesni.csv "openssl_aesni" bench_aes_jasmin.csv "jasmin_aes_asm"                      

#!/usr/bin/env python3
import pandas as pd
import matplotlib.pyplot as plt
import re, sys, os, io
from matplotlib.ticker import ScalarFormatter

def load_summary(path):
    """
    Pulls out only the summary table at the bottom of your CSV file:
       size,mbps_mean,mbps_stddev,mbps_median,cpb_mean,cpb_stddev,cpb_median
    """
    with open(path, 'r') as f:
        lines = f.readlines()

    # find where the summary header begins
    for idx, L in enumerate(lines):
        if L.startswith("size,mbps_mean"):
            hdr = lines[idx]
            body = [L for L in lines[idx+1:] if re.match(r'^\s*\d', L)]
            return pd.read_csv(io.StringIO(hdr + "".join(body)))

    raise RuntimeError(f"Summary section not found in {path}")

def compare_plot(s1, s2, label1, label2, out_dir):
    # -- Throughput (MB/s) --
    fig, ax = plt.subplots(figsize=(8,6))
    for df, label, color in [
        (s1, label1, 'tab:blue'),
        (s2, label2, 'tab:orange'),
    ]:
        x    = df['size'] / 1024
        y    = df['mbps_mean']
        yerr = df['mbps_stddev']
        ax.errorbar(x, y, yerr=yerr, fmt='o-', capsize=5,
                    color=color, label=label)
        for xi, yi in zip(x, y):
            ax.annotate(f"{yi:.1f}", xy=(xi, yi),
                        xytext=(0, 8), textcoords="offset points",
                        ha='center', va='bottom',
                        fontsize=8, color=color,
                        bbox=dict(facecolor='white', edgecolor=color, pad=1, alpha=0.7))

    ax.set_xscale('log')
    ax.set_xlabel('Buffer Size (KiB)')
    ax.set_ylabel('Throughput (MB/s)')
    ax.set_title('AES-128 ECB Throughput Comparison')
    ax.grid(which='both', linestyle='--', linewidth=0.4)
    ax.legend()

    # plain‐number y‐axis
    ax.yaxis.set_major_formatter(ScalarFormatter(useOffset=False))
    ax.ticklabel_format(style='plain', axis='y')

    fig.tight_layout()
    fig.savefig(os.path.join(out_dir, 'compare_throughput.png'), dpi=300)
    plt.close(fig)

    # -- Cycles per Byte --
    fig, ax = plt.subplots(figsize=(8,6))
    for df, label, color in [
        (s1, label1, 'tab:green'),
        (s2, label2, 'tab:red'),
    ]:
        x    = df['size'] / 1024
        y    = df['cpb_mean']
        yerr = df['cpb_stddev']
        ax.errorbar(x, y, yerr=yerr, fmt='s--', capsize=5,
                    color=color, label=label)
        for xi, yi in zip(x, y):
            ax.annotate(f"{yi:.2f}", xy=(xi, yi),
                        xytext=(0, 8), textcoords="offset points",
                        ha='center', va='bottom',
                        fontsize=8, color=color,
                        bbox=dict(facecolor='white', edgecolor=color, pad=1, alpha=0.7))

    ax.set_xscale('log')
    ax.set_xlabel('Buffer Size (KiB)')
    ax.set_ylabel('Cycles per Byte')
    ax.set_title('AES-128 ECB Efficiency Comparison')
    ax.grid(which='both', linestyle='--', linewidth=0.4)
    ax.legend()

    ax.yaxis.set_major_formatter(ScalarFormatter(useOffset=False))
    ax.ticklabel_format(style='plain', axis='y')

    fig.tight_layout()
    fig.savefig(os.path.join(out_dir, 'compare_cycles.png'), dpi=300)
    plt.close(fig)

def main():
    if len(sys.argv) != 5:
        print("Usage: compare_bench.py <csv1> <label1> <csv2> <label2>")
        sys.exit(1)

    csv1, label1, csv2, label2 = sys.argv[1:]
    out_dir = os.path.dirname(os.path.abspath(__file__))
    os.makedirs(out_dir, exist_ok=True)

    s1 = load_summary(csv1)
    s2 = load_summary(csv2)

    compare_plot(s1, s2, label1, label2, out_dir)
    print(f"Saved comparison plots in {out_dir}:")
    print("  compare_throughput.png")
    print("  compare_cycles.png")

if __name__ == "__main__":
    main()


# #!/usr/bin/env python3
# import pandas as pd
# import matplotlib.pyplot as plt
# import re, sys, os, io

# def load_csv(path):
#     with open(path, 'r') as f:
#         lines = f.readlines()
#     header = lines[0]
#     data   = [L for L in lines[1:] if re.match(r'^\s*\d', L)]
#     return pd.read_csv(io.StringIO(header + ''.join(data)))

# def summarize(df):
#     grp = df.groupby('size')
#     return grp.agg(
#         mbps_mean=('mbps', 'mean'),
#         mbps_std =('mbps', 'std'),
#         mbps_med =('mbps', 'median'),
#         cpb_mean =('cpb', 'mean'),
#         cpb_std  =('cpb', 'std'),
#         cpb_med  =('cpb', 'median'),
#     ).reset_index()

# def compare_plot(s1, s2, label1, label2, out_dir):
#     # -- Throughput (MB/s) --
#     plt.figure(figsize=(8,6))
#     for df, label, color in [
#         (s1, label1, 'tab:blue'),
#         (s2, label2, 'tab:orange'),
#     ]:
#         x    = df['size'] / 1024
#         y    = df['mbps_mean']
#         yerr = df['mbps_std']
#         plt.errorbar(x, y, yerr=yerr, fmt='o-', capsize=5,
#                      color=color, label=label)
#         # annotate each point in the same color:
#         for xi, yi in zip(x, y):
#             plt.text(xi, yi, f"{yi:.1f}",
#                      color=color,
#                      ha='center', va='bottom',
#                      fontsize=8,
#                      bbox=dict(facecolor='white', edgecolor=color, pad=1, alpha=0.7))
#     plt.xscale('log')
#     plt.xlabel('Buffer Size (KiB)')
#     plt.ylabel('Throughput (MB/s)')
#     plt.title('AES-128 ECB Throughput Comparison')
#     plt.grid(which='both', linestyle='--', linewidth=0.4)
#     plt.legend()
#     plt.tight_layout()
#     plt.savefig(os.path.join(out_dir, 'compare_throughput.png'), dpi=300)
#     plt.close()

#     # -- Cycles per Byte --
#     plt.figure(figsize=(8,6))
#     for df, label, color in [
#         (s1, label1, 'tab:green'),
#         (s2, label2, 'tab:red'),
#     ]:
#         x    = df['size'] / 1024
#         y    = df['cpb_mean']
#         yerr = df['cpb_std']
#         plt.errorbar(x, y, yerr=yerr, fmt='s--', capsize=5,
#                      color=color, label=label)
#         # annotate each point:
#         for xi, yi in zip(x, y):
#             plt.text(xi, yi, f"{yi:.2f}",
#                      color=color,
#                      ha='center', va='bottom',
#                      fontsize=8,
#                      bbox=dict(facecolor='white', edgecolor=color, pad=1, alpha=0.7))
#     plt.xscale('log')
#     plt.xlabel('Buffer Size (KiB)')
#     plt.ylabel('Cycles per Byte')
#     plt.title('AES-128 ECB Efficiency Comparison')
#     plt.grid(which='both', linestyle='--', linewidth=0.4)
#     plt.legend()
#     plt.tight_layout()
#     plt.savefig(os.path.join(out_dir, 'compare_cycles.png'), dpi=300)
#     plt.close()

# def main():
#     if len(sys.argv) != 5:
#         print("Usage: compare_bench.py <csv1> <label1> <csv2> <label2>")
#         sys.exit(1)

#     csv1, label1, csv2, label2 = sys.argv[1:]
#     out_dir = os.path.dirname(os.path.abspath(__file__))
#     os.makedirs(out_dir, exist_ok=True)

#     df1 = load_csv(csv1)
#     df2 = load_csv(csv2)
#     s1  = summarize(df1)
#     s2  = summarize(df2)

#     compare_plot(s1, s2, label1, label2, out_dir)
#     print(f"Saved comparison plots in {out_dir}:")
#     print("  compare_throughput.png")
#     print("  compare_cycles.png")

# if __name__ == "__main__":
#     main()