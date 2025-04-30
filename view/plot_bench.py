#!/usr/bin/env python3
import pandas as pd
import matplotlib.pyplot as plt
import re, sys, os, io
from matplotlib.ticker import ScalarFormatter

def load_sections(path):
    """
    Splits the file into two DataFrames:
    - df_runs:    detailed (size,run,elapsed_ns,mbps,cycles,cpb)
    - df_summary: precomputed summary 
        (size,mbps_mean,mbps_stddev,mbps_median,cpb_mean,cpb_stddev,cpb_median)
    """
    with open(path, 'r') as f:
        lines = f.readlines()

    # find where the summary header begins
    summary_idx = None
    for i, L in enumerate(lines):
        if L.startswith("size,mbps_mean"):
            summary_idx = i
            break
    if summary_idx is None:
        raise RuntimeError("Could not find summary header in file")

    # per-run lines are from line 0..summary_idx-1
    header_runs = lines[0]
    run_lines   = [L for L in lines[1:summary_idx] if re.match(r'^\s*\d', L)]
    df_runs     = pd.read_csv(io.StringIO(header_runs + "".join(run_lines)))

    # summary lines are from summary_idx..end
    header_sum  = lines[summary_idx]
    sum_lines   = [L for L in lines[summary_idx+1:] if re.match(r'^\s*\d', L)]
    df_summary  = pd.read_csv(io.StringIO(header_sum + "".join(sum_lines)))

    return df_runs, df_summary

def plot_throughput(summary, out_dir):
    x    = summary['size'] / 1024
    y    = summary['mbps_mean']
    yerr = summary['mbps_stddev']
    ymed = summary['mbps_median']

    fig, ax = plt.subplots(figsize=(8,6))
    ax.errorbar(x, y, yerr=yerr, fmt='o-', capsize=5,
                color='tab:cyan', label='Mean ± σ')
    ax.fill_between(x, y-yerr, y+yerr, color='tab:cyan', alpha=0.2)
    ax.scatter(x, ymed, marker='s', color='tab:blue', label='Median')

    # plain numbers on y-axis
    ax.yaxis.set_major_formatter(ScalarFormatter(useOffset=False))
    ax.ticklabel_format(style='plain', axis='y')

    # annotate every mean point
    for xi, yi in zip(x, y):
        ax.annotate(f"{yi:.1f}", xy=(xi, yi),
                    xytext=(0, 8), textcoords="offset points",
                    ha='center', va='bottom',
                    color='tab:cyan', fontsize=8,
                    bbox=dict(boxstyle='round,pad=0.2', fc='tab:cyan', alpha=0.2))
    # annotate every median point
    for xi, ymi in zip(x, ymed):
        ax.annotate(f"{ymi:.1f}", xy=(xi, ymi),
                    xytext=(0, -12), textcoords="offset points",
                    ha='center', va='top',
                    color='tab:blue', fontsize=8,
                    bbox=dict(boxstyle='round,pad=0.2', fc='tab:blue', alpha=0.2))

    ax.set_xscale('log')
    ax.set_xlabel('Buffer Size (KiB)')
    ax.set_ylabel('Throughput (MB/s)')
    ax.set_title('AES-128 ECB Throughput')
    ax.grid(which='both', linestyle='--', linewidth=0.4)
    ax.legend()
    fig.tight_layout()
    fig.savefig(os.path.join(out_dir, 'throughput_annotated.png'), dpi=300)
    plt.close(fig)

def plot_efficiency(summary, out_dir):
    x    = summary['size'] / 1024
    y    = summary['cpb_mean']
    yerr = summary['cpb_stddev']
    ymed = summary['cpb_median']

    fig, ax = plt.subplots(figsize=(8,6))
    ax.errorbar(x, y, yerr=yerr, fmt='s--', capsize=5,
                color='tab:purple', label='Mean ± σ')
    ax.fill_between(x, y-yerr, y+yerr, color='tab:purple', alpha=0.2)
    ax.scatter(x, ymed, marker='o', color='tab:red', label='Median')

    ax.yaxis.set_major_formatter(ScalarFormatter(useOffset=False))
    ax.ticklabel_format(style='plain', axis='y')

    for xi, yi in zip(x, y):
        ax.annotate(f"{yi:.2f}", xy=(xi, yi),
                    xytext=(0, 8), textcoords="offset points",
                    ha='center', va='bottom',
                    color='tab:purple', fontsize=8,
                    bbox=dict(boxstyle='round,pad=0.2', fc='tab:purple', alpha=0.2))
    for xi, ymi in zip(x, ymed):
        ax.annotate(f"{ymi:.2f}", xy=(xi, ymi),
                    xytext=(0, -12), textcoords="offset points",
                    ha='center', va='top',
                    color='tab:red', fontsize=8,
                    bbox=dict(boxstyle='round,pad=0.2', fc='tab:red', alpha=0.2))

    ax.set_xscale('log')
    ax.set_xlabel('Buffer Size (KiB)')
    ax.set_ylabel('Cycles per Byte')
    ax.set_title('AES-128 ECB Efficiency')
    ax.grid(which='both', linestyle='--', linewidth=0.4)
    ax.legend()
    fig.tight_layout()
    fig.savefig(os.path.join(out_dir, 'cycles_annotated.png'), dpi=300)
    plt.close(fig)

def main():
    data_file = sys.argv[1] if len(sys.argv)>1 else 'bench_results.csv'
    out_dir   = os.path.dirname(os.path.abspath(__file__))
    os.makedirs(out_dir, exist_ok=True)

    df_runs, summary = load_sections(data_file)

    # you can still inspect df_runs if you like,
    # but for plotting we use the pre-computed summary:
    plot_throughput(summary, out_dir)
    plot_efficiency(summary, out_dir)
    print(f"Saved: {out_dir}/throughput_annotated.png, {out_dir}/cycles_annotated.png")

if __name__ == "__main__":
    main()


# #!/usr/bin/env python3
# import pandas as pd
# import matplotlib.pyplot as plt
# import re, sys, os, io

# def load_csv_only(path):
#     with open(path, 'r') as f:
#         lines = f.readlines()
#     header = lines[0]
#     data_lines = [L for L in lines[1:] if re.match(r'^\s*\d', L)]
#     return pd.read_csv(io.StringIO(header + ''.join(data_lines)))

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

# def plot_throughput(summary, out_dir):
#     x    = summary['size'] / 1024
#     y    = summary['mbps_mean']
#     yerr = summary['mbps_std']
#     ymed = summary['mbps_med']

#     plt.figure(figsize=(8,6))
#     plt.errorbar(x, y, yerr=yerr, fmt='o-', capsize=5,
#                  color='tab:cyan', label='Mean ± σ')
#     plt.fill_between(x, y-yerr, y+yerr, color='tab:cyan', alpha=0.2)
#     plt.scatter(x, ymed, marker='s', color='tab:blue', label='Median')

#     # annotate every mean point
#     for xi, yi in zip(x, y):
#         plt.annotate(f"{yi:.1f}", (xi, yi),
#                      textcoords="offset points", xytext=(0, 8), ha='center',
#                      fontsize=8, color='tab:cyan')

#     # annotate every median point
#     for xi, ymi in zip(x, ymed):
#         plt.annotate(f"{ymi:.1f}", (xi, ymi),
#                      textcoords="offset points", xytext=(0, -12), ha='center',
#                      fontsize=8, color='tab:blue')

#     plt.xscale('log')
#     plt.xlabel('Buffer Size (KiB)')
#     plt.ylabel('Throughput (MB/s)')
#     plt.title('AES-128 ECB Throughput')
#     plt.grid(which='both', linestyle='--', linewidth=0.4)
#     plt.legend()
#     plt.tight_layout()
#     plt.savefig(os.path.join(out_dir, 'throughput_annotated.png'), dpi=300)
#     plt.close()

# def plot_efficiency(summary, out_dir):
#     x    = summary['size'] / 1024
#     y    = summary['cpb_mean']
#     yerr = summary['cpb_std']
#     ymed = summary['cpb_med']

#     plt.figure(figsize=(8,6))
#     plt.errorbar(x, y, yerr=yerr, fmt='s--', capsize=5,
#                  color='tab:purple', label='Mean ± σ')
#     plt.fill_between(x, y-yerr, y+yerr, color='tab:purple', alpha=0.2)
#     plt.scatter(x, ymed, marker='o', color='tab:red', label='Median')

#     # annotate every mean point
#     for xi, yi in zip(x, y):
#         plt.annotate(f"{yi:.2f}", (xi, yi),
#                      textcoords="offset points", xytext=(0, 8), ha='center',
#                      fontsize=8, color='tab:purple')

#     # annotate every median point
#     for xi, ymi in zip(x, ymed):
#         plt.annotate(f"{ymi:.2f}", (xi, ymi),
#                      textcoords="offset points", xytext=(0, -12), ha='center',
#                      fontsize=8, color='tab:red')

#     plt.xscale('log')
#     plt.xlabel('Buffer Size (KiB)')
#     plt.ylabel('Cycles per Byte')
#     plt.title('AES-128 ECB Efficiency')
#     plt.grid(which='both', linestyle='--', linewidth=0.4)
#     plt.legend()
#     plt.tight_layout()
#     plt.savefig(os.path.join(out_dir, 'cycles_annotated.png'), dpi=300)
#     plt.close()

# def main():
#     data_file = sys.argv[1] if len(sys.argv)>1 else 'bench_results.csv'
#     out_dir   = os.path.dirname(os.path.abspath(__file__))
#     os.makedirs(out_dir, exist_ok=True)

#     df      = load_csv_only(data_file)
#     summary = summarize(df)

#     plot_throughput(summary, out_dir)
#     plot_efficiency(summary, out_dir)
#     print(f"Saved: {out_dir}/throughput_annotated.png, {out_dir}/cycles_annotated.png")

# if __name__ == "__main__":
#     main()
