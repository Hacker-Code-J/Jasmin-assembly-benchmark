# Jasmin-assembly-benchmark

Benchmark suite for assessing the performance and correctness of assembly code produced by the `jasmin-lang` compiler.

## Features

- Categorized benchmarks under:
  - `blockcipher/` (AES, DES…)
  - `hash/` (SHA-256, MD5…)
  - `mac/` (HMAC…)
  - `streamcipher/` (RC4…)
- Automatic discovery of `.jasm` sources
- Two-step pipeline:
  1. **Compile** `.jasm` → `.s` via `jasmc`  
  2. **Assemble & link** `.s` → native executable via `gcc` or `clang`  
- Simple `make build` / `make clean` workflow

## Prerequisites

- [`jasmin-lang` compiler](https://github.com/jasmin-lang/jasmin) (`jasmc` on your `$PATH`)  
- GNU Make  
- A native assembler & linker (e.g. `gcc` or `clang`)  

Verify tools are installed:
```sh
$ which jasmc
/usr/local/bin/jasmc

$ which gcc
/usr/bin/gcc
```

## Repository layout

```
Jasmin-assembly-benchmark/
├── src/
│   ├── blockcipher/
│   │   ├── aes.jasm
│   │   └── des.jasm
│   ├── hash/
│   │   ├── sha256.jasm
│   │   └── md5.jasm
│   ├── mac/
│   │   └── hmac.jasm
│   └── streamcipher/
│       └── rc4.jasm
├── build/
│   ├── blockcipher/
│   ├── hash/
│   ├── mac/
│   └── streamcipher/
├── Makefile
└── README.md
```

- Place your `.jasm` benchmarks in `src/<category>/`.
- Build artifacts (`.s` and executables) appear under the mirrored `build/` tree.

## Usage

```sh
# Build all benchmarks:
make build

# Clean & rebuild from scratch:
make rebuild

# Remove all build artifacts:
make clean
```

After `make build`, each benchmark can be run directly.  
Example:
```sh
# Run the AES block‐cipher benchmark
./build/blockcipher/aes

# Run the SHA-256 hash benchmark
./build/hash/sha256
```

## Adding new benchmarks

1. Drop your new `foo.jasm` into the appropriate `src/<category>/` folder.  
2. Ensure it defines a `_start` or `main` entry point as per `jasmin-lang` conventions.  
3. Re-run `make build` — your new benchmark will be compiled & linked automatically.

## License

Distributed under the MIT License. See [LICENSE](LICENSE) for details.



