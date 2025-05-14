#!/usr/bin/env python3
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

def freq_from_dump(dump_path):
    # You can’t directly disassemble an objdump -d ASCII dump back into machine code bytes,
    # so you either need to strip out jump labels and convert to hex literals, or read the .o file directly.
    # Here’s an example of reading the .o file:
    with open(dump_path.replace('.dump', '.o'), 'rb') as f:
        code = f.read()

    # Initialize Capstone for 64-bit x86 disassembly
    md = Cs(CS_ARCH_X86, CS_MODE_64)

    # freq will hold a count of how many times each mnemonic appears
    freq = {}
    for insn in md.disasm(code, 0x0):
        # Increment the count for this instruction’s mnemonic
        freq[insn.mnemonic] = freq.get(insn.mnemonic, 0) + 1

    return freq

if __name__ == '__main__':
    # Compare instruction frequencies for two object files
    for base in ['aesni-x86_64', 'jasmin_aesni']:
        f = freq_from_dump(f'{base}.dump')
        print(f'--- {base} ---')
        # Print the top 10 most frequent opcodes
        for op, cnt in sorted(f.items(), key=lambda x: -x[1])[:10]:
            print(f'{op}: {cnt}')
