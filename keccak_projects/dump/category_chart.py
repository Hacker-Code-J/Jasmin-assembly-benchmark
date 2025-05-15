#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np

# Categorizing instructions into predefined categories
CATEGORIES = {
    "Data-move": ["mov", "push", "pop", "lea", "xchg", "movq", "movd", "movdqu"],
    "Bitwise/Logic": ["xor", "and", "or", "not", "test", "bt", "bts", "btr", "bts", "bsf", "bsr"],
    "Rotate/Shift": ["shl", "shr", "rol", "ror", "sal", "sar", "shld", "shrd"],
    "Arithmetic": ["add", "sub", "mul", "div", "inc", "dec", "neg", "cmp"],
    "Control-flow": ["jmp", "je", "jne", "jg", "jl", "call", "ret", "loop", "jz", "jnz", "jz", "jo", "jno", "ja", "jb"],
    "Other": []  # Placeholder for instructions that don't fit in any category
}

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

def categorize_instructions(freq):
    """
    Categorizes instructions into predefined categories and counts occurrences.
    """
    category_count = {category: 0 for category in CATEGORIES}
    
    # Loop over instructions and categorize them
    for instruction, count in freq.items():
        categorized = False
        for category, keywords in CATEGORIES.items():
            if any(inst in instruction.lower() for inst in keywords):
                category_count[category] += count
                categorized = True
                break
        if not categorized:
            category_count["Other"] += count  # Add to 'Other' if no category matches
    
    return category_count

def plot_category_comparison(category_counts, labels, title):
    """
    Plots a bar chart comparing instruction categories across datasets with pastel colors.
    """
    # Prepare data for plotting
    categories = list(category_counts[0].keys())
    n_categories = len(categories)
    
    # Set up the positions for the bars
    x = np.arange(n_categories)
    width = 0.2  # Width of the bars
    
    # Define pastel colors using RGB values
    pastel_colors = [
        "#ffb3ba",  # Light Pink
        "#ffdfba",  # Light Orange
        "#ffffba",  # Light Yellow
        "#baffc9",  # Light Green
        "#c4e3f3"   # Light Blue
    ]
    
    # Create figure and axis
    fig, ax = plt.subplots(figsize=(12, 7))
    
    # Plot the bars for each dataset using pastel colors and adding edge lines
    for i, (category_count, label) in enumerate(zip(category_counts, labels)):
        bars = ax.bar(x + i * width, list(category_count.values()), width, label=label, color=pastel_colors[i], edgecolor='black', linewidth=1.5)
        
        # Annotate each bar with its value
        for bar in bars:
            height = bar.get_height()
            ax.annotate(f'{height}',
                        xy=(bar.get_x() + bar.get_width() / 2, height),
                        xytext=(0, 3),  # 3 points vertical offset
                        textcoords="offset points",
                        ha='center', va='bottom', fontsize=10,
                        bbox=dict(boxstyle="round,pad=0.2", fc="white", alpha=0.7), weight='bold')

    # Adding labels and titles
    ax.set_xlabel('Instruction Categories', fontsize=14)
    ax.set_ylabel('Frequency', fontsize=14)
    ax.set_title(title, fontsize=16)
    ax.set_xticks(x + width * (len(labels) - 1) / 2)  # Position x-ticks in the center of each group
    ax.set_xticklabels(categories, rotation=45, ha='right', fontsize=12)
    ax.legend(title="Datasets", fontsize=12)
    
    # Add gridlines for clarity
    ax.grid(True, axis='y', linestyle='--', alpha=0.7)

    # Display the chart
    plt.tight_layout()
    plt.show()

if __name__ == '__main__':
    # Load frequency data for each architecture
    freq_avx2 = load_freq_data('KeccakP-1600-AVX2.dump_freq.txt')  # AVX2
    freq_avx2_jazz = load_freq_data('KeccakP-1600-AVX2-jazz.dump_freq.txt')  # AVX2-Jazz
    freq_x86_64 = load_freq_data('KeccakP-1600-x86-64.dump_freq.txt')  # x86_64
    freq_x86_64_jazz = load_freq_data('KeccakP-1600-x86-64-jazz.dump_freq.txt')  # x86_64-Jazz

    # Categorize instructions for each architecture
    category_avx2 = categorize_instructions(freq_avx2)
    category_avx2_jazz = categorize_instructions(freq_avx2_jazz)
    category_x86_64 = categorize_instructions(freq_x86_64)
    category_x86_64_jazz = categorize_instructions(freq_x86_64_jazz)

    # Labels for the datasets
    # labels = ["AVX2", "AVX2-Jazz", "x86_64", "x86_64-Jazz"]
    labels = ["x86_64", "x86_64-Jazz", "AVX2", "AVX2-Jazz"]
    
    # Category counts for each dataset
    category_counts = [category_x86_64, category_x86_64_jazz, category_avx2, category_avx2_jazz]

    # Plot the category comparison chart
    plot_category_comparison(category_counts, labels, "Instruction Category Frequency Comparison")
