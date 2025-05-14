# Brainf\*ck Compiler in C

A simple Brainf\*ck compiler written in C. This projects generates a .c file that GCC then compiles to the native binary file of the OS.

## How It Works

1. Tokenizer reads the `.bf` file and converts the characters into tokens
2. Parser builds an abstract syntax tree (AST) with optimizations (e.g. consecutive `+` and `-` is summed up and becomes a single node)
3. Code Generator writes C code that mirrors the optimized AST
4. Compiler uses `gcc` to compile the generated `.c` code into an executable

## How to Build

### Prerequisites

-   `gcc`
-   `make`

### Build

```bash
make
```

### Clean Build Artifacts

```bash
make clean
```

## Usage

```bash
./brainf source.bf
```

This will compile `source.bf` to `output` (`output.exe` on Windows).

To specify the output file path, simply add:

```bash
./brainf source.bf -o program
```

And this will generate `program` / `program.exe`

## Run the Compiled Binary

```bash
./output
```
