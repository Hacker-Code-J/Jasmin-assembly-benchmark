### STEP 1.
```bash
wc -l keccak1600-avx2.S keccak1600-x86_64.S sha3_256_avx2.S sha3_256_ref.S 
```
```
  600 keccak1600-avx2.S
  527 keccak1600-x86_64.S
 1889 sha3_256_avx2.S
 1790 sha3_256_ref.S
 4806 total
```

### STEP 2.
```bash
ls -lh keccak1600-avx2.S keccak1600-x86_64.S sha3_256_avx2.S sha3_256_ref.S
```
```
-rw-rw-r-- 1 hacker-code-j hacker-code-j  16K May  7 17:11 keccak1600-avx2.S
-rw-rw-r-- 1 hacker-code-j hacker-code-j 8.3K May  7 17:11 keccak1600-x86_64.S
-rw-r--r-- 1 hacker-code-j hacker-code-j  27K May  7 17:11 sha3_256_avx2.S
-rw-r--r-- 1 hacker-code-j hacker-code-j  30K May  7 17:11 sha3_256_ref.S
```

### STEP 3.
```bash
gcc -c -mavx2 keccak1600-avx2.S -o keccak1600-avx2.o
gcc -c -march=x86-64 keccak1600-x86_64.S -o keccak1600-x86_64.o
gcc -c -mavx2 sha3_256_avx2.S -o sha3_256_avx2.o
gcc -c -march=x86-64 sha3_256_ref.S -o sha3_256_ref.o
objdump -d keccak1600-avx2.o > keccak1600-avx2.dump
objdump -d keccak1600-x86_64.o > keccak1600-x86_64.dump
objdump -d sha3_256_avx2.o > sha3_256_avx2.dump
objdump -d sha3_256_ref.o > sha3_256_ref.dump
```

### STEP 4.
```bash
python3 opcode_freq.py > result.txt
python3 opcode_chart.py
```

### STEP 5.
```bash
rm *.txt
rm *.dump
rm *.o
```


