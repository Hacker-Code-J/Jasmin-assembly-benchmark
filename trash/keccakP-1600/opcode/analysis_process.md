### STEP 1.
```bash
wc -l KeccakP-1600-AVX2-jazz.s KeccakP-1600-x86-64-jazz.s KeccakP-1600-AVX2.s KeccakP-1600-x86-64.s
```
```
  1879 KeccakP-1600-AVX2-jazz.s
  1780 KeccakP-1600-x86-64-jazz.s
  1103 KeccakP-1600-AVX2.s
  1196 KeccakP-1600-x86-64.s
  5958 total
```

### STEP 2.
```bash
ls -lh KeccakP-1600-AVX2-jazz.s KeccakP-1600-x86-64-jazz.s KeccakP-1600-AVX2.s KeccakP-1600-x86-64.s
```
```
-rw-rw-r-- 1 hacker-code-j hacker-code-j 27K May  9 11:29 KeccakP-1600-AVX2-jazz.s
-rw-rw-r-- 1 hacker-code-j hacker-code-j 30K May  9 11:26 KeccakP-1600-x86-64-jazz.s
-rw-rw-r-- 1 hacker-code-j hacker-code-j 42K May  9 11:30 KeccakP-1600-AVX2.s
-rw-rw-r-- 1 hacker-code-j hacker-code-j 33K May  9 11:30 KeccakP-1600-x86-64.s
```

### STEP 3.
```bash
gcc -c -O3 -mavx2 KeccakP-1600-AVX2-jazz.s -o KeccakP-1600-AVX2-jazz.o 
gcc -c -O3 -march=x86-64 KeccakP-1600-x86-64-jazz.s -o KeccakP-1600-x86-64-jazz.o
gcc -c -O3 -mavx2 KeccakP-1600-AVX2.s -o KeccakP-1600-AVX2.o
gcc -c -O3 -march=x86-64 KeccakP-1600-x86-64.s -o KeccakP-1600-x86-64.o

     
objdump -d KeccakP-1600-AVX2-jazz.o > KeccakP-1600-AVX2-jazz.dump
objdump -d KeccakP-1600-x86-64-jazz.o > KeccakP-1600-x86-64-jazz.dump
objdump -d KeccakP-1600-AVX2.o > KeccakP-1600-AVX2.dump
objdump -d KeccakP-1600-x86-64.o > KeccakP-1600-x86-64.dump
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


