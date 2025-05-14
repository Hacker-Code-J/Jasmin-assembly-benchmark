#!/usr/bin/env python3
import re

# List of dump files
files = [
    'KeccakP-1600-AVX2-jazz.dump',
    'KeccakP-1600-x86-64-jazz.dump',
    'KeccakP-1600-AVX2.dump',
    'KeccakP-1600-x86-64.dump'
]

# Regular expression to match objdump -d instruction lines
instr_re = re.compile(r"^\s*[0-9A-Fa-f]+:\s*(?:[0-9A-Fa-f]{2}\s+)+\s*([a-zA-Z0-9_]+)")

def freq_from_dump(dump_path):
    """
    Read an objdump -d assembly dump (.dump) file,
    extract instruction mnemonics from each line,
    and return a mapping of mnemonic -> occurrence count.
    """
    freq = {}
    with open(dump_path, 'r') as f:
        for line in f:
            match = instr_re.match(line)
            if match:
                mnemonic = match.group(1)
                freq[mnemonic] = freq.get(mnemonic, 0) + 1
    return freq

if __name__ == '__main__':
    # Process each file and count instructions
    for dump_file in files:
        print(f"Processing {dump_file}...")
        freq = freq_from_dump(dump_file)

        # Save the frequencies to a file
        output_file = f"{dump_file}_freq.txt"
        with open(output_file, 'w') as f:
            for op, cnt in sorted(freq.items(), key=lambda x: -x[1]):
                f.write(f"{op}: {cnt}\n")
        print(f"Frequency data saved to {output_file}")
