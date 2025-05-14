#!/usr/bin/env python3
import matplotlib.pyplot as plt

# Function to load frequency data from text files
def load_freq_data(file_path):
    """
    Reads frequency data from a file and returns a dictionary
    mapping mnemonics to their frequency counts.
    """
    freq = {}
    with open(file_path, 'r') as f:
        for line in f:
            if line.strip():  # Skip empty lines
                mnemonic, count = line.split(": ")  # Split mnemonic and count
                freq[mnemonic] = int(count)
    return freq

# Function to plot instruction frequencies
def plot_instruction_frequencies(freq_1, freq_2, label_1, label_2, title):
    """
    Compares the instruction frequencies from two datasets and plots them
    as horizontal bar charts without overlap.
    """
    # Sorting the frequencies in descending order
    sorted_1 = sorted(freq_1.items(), key=lambda x: -x[1])
    sorted_2 = sorted(freq_2.items(), key=lambda x: -x[1])

    # Prepare data for plotting
    instructions_1, counts_1 = zip(*sorted_1)
    instructions_2, counts_2 = zip(*sorted_2)

    # Number of bars to plot
    num_bars = min(20, len(instructions_1), len(instructions_2))  # Adjust based on the data size

    # Create subplots to compare the two architectures
    fig, ax = plt.subplots(figsize=(14, 10))

    # The width of each bar in the grouped bar chart
    bar_width = 0.35

    # Set the positions of the bars
    x = range(num_bars)

    # Define pastel colors and add edge lines for distinctness
    pastel_colors_1 = 'deepskyblue'  # Light pink for the first dataset (AVX2)
    pastel_colors_2 = 'orchid'  # Light orange for the second dataset (AVX2-Jazz)

    # Plotting bars with distinct colors for comparison (side by side)
    bars_1 = ax.barh([i - bar_width/2 for i in x], counts_1[:num_bars], bar_width, color=pastel_colors_1, label=label_1, edgecolor='black')  # Light pink bars for the first dataset
    bars_2 = ax.barh([i + bar_width/2 for i in x], counts_2[:num_bars], bar_width, color=pastel_colors_2, label=label_2, edgecolor='black')  # Light orange bars for the second dataset

    # Adding frequency count labels to bars
    for bar in bars_1:
        width = bar.get_width()  # Get the width of each bar
        ax.text(width, bar.get_y() + bar.get_height() / 2,  # Position text slightly outside the bar
                str(int(width)), va='center', ha='left', color='dodgerblue', fontsize=12, weight='bold')  # Black text

    for bar in bars_2:
        width = bar.get_width()  # Get the width of each bar
        ax.text(width, bar.get_y() + bar.get_height() / 2,  # Position text slightly outside the bar
                str(int(width)), va='center', ha='left', color='palevioletred', fontsize=12, weight='bold')  # Black text

    # Adding axis labels and title
    ax.set_xlabel('Frequency', fontsize=14)
    ax.set_title(title, fontsize=16)
    ax.invert_yaxis()  # Invert the y-axis to have the highest frequencies at the top
    ax.set_yticks(x)  # Set the y-ticks to correspond to the instructions
    ax.set_yticklabels(instructions_1[:num_bars])  # Show the instruction names

    # Adding a legend
    ax.legend()

    # Display the chart
    plt.tight_layout()
    plt.show()

if __name__ == '__main__':
    # Load the frequency data from the frequency text files
    freq_avx2 = load_freq_data('KeccakP-1600-AVX2.dump_freq.txt')  # AVX2
    freq_avx2_jazz = load_freq_data('KeccakP-1600-AVX2-jazz.dump_freq.txt')  # AVX2-Jazz

    freq_x86_64 = load_freq_data('KeccakP-1600-x86-64.dump_freq.txt')  # x86_64
    freq_x86_64_jazz = load_freq_data('KeccakP-1600-x86-64-jazz.dump_freq.txt')  # x86_64-Jazz

    # Plot the comparison charts
    plot_instruction_frequencies(freq_avx2, freq_avx2_jazz, "AVX2", "AVX2-Jazz", "AVX2 vs AVX2-Jazz Instruction Frequency Comparison")
    plot_instruction_frequencies(freq_x86_64, freq_x86_64_jazz, "x86_64", "x86_64-Jazz", "x86_64 vs x86_64-Jazz Instruction Frequency Comparison")
