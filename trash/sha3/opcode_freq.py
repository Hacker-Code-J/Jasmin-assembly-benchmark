#!/usr/bin/env python3
import re
import sys

# List the base names (without extension) of your dump files
bases = [
    'keccak1600-avx2',
    'keccak1600-x86_64',
    'sha3_256_avx2',
    'sha3_256_ref'
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
            if not match:
                continue
            mnemonic = match.group(1)
            freq[mnemonic] = freq.get(mnemonic, 0) + 1
    return freq

if __name__ == '__main__':
    # For each implementation, parse its .dump file and print all mnemonics with counts
    for base in bases:
        dump_file = f"{base}.dump"
        print(f"--- {base} ---")
        freq = freq_from_dump(dump_file)
        # Sort by count descending
        for op, cnt in sorted(freq.items(), key=lambda x: -x[1]):
            print(f"{op}: {cnt}")
        print()