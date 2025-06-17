# srr2illumina

FastQ file processor that converts SRA format to Illumina format with index sequences.

## Overview

This program processes compressed FastQ files (.fastq.gz) from SRA and converts them to Illumina format with proper index sequences. It transforms SRA-style headers to Illumina-style headers and outputs uncompressed FastQ to stdout.

## Requirements

- GCC compiler
- zlib library (usually pre-installed on most systems)

## Building

```bash
make
```

Or compile manually:
```bash
gcc -Wall -Wextra -O2 -std=c99 srr2illumina.c -o srr2illumina -lz
```

## Usage

```bash
./srr2illumina input.fastq.gz > output.fastq
```

## Example

Input SRA FastQ record:
```
@SRR33684863.1 A00609:257:H2VLKDSX2:1:1101:10004:10269/1 length=101
ACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGT
+
IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
```

Output Illumina FastQ record:
```
@A00609:257:H2VLKDSX2:1:1101:10004:10269 1:N:0:TCTTAACTGG+TTCAGGCCGA
ACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGT
+
IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
```

## Features

- Processes gzipped FastQ files directly
- Converts SRA format to proper Illumina format
- Removes /1 and /2 suffixes from read names
- Adds index sequences to Illumina headers (TCTTAACTGG+TTCAGGCCGA)
- Handles lines up to 1000 characters
- Outputs to stdout for easy piping
- Automatically detects read number from filename (_R1 or _R2)

## Make Targets

- `make` or `make all` - Build the program
- `make clean` - Remove compiled files
- `make install` - Install to /usr/local/bin
- `make uninstall` - Remove from /usr/local/bin
- `make check-deps` - Check for required dependencies
- `make help` - Show available targets and usage

## License

This is a utility program created for bioinformatics data processing.
