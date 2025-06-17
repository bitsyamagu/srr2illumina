# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2025-06-17

### Added
- Initial release of srr2illumina
- Convert SRA format FastQ headers to Illumina format
- Support for gzipped input files
- Automatic detection of read number from filename (_R1/_R2)
- Removal of /1 and /2 suffixes from read names
- Addition of index sequences to Illumina headers
- Command-line interface with proper error handling
- Makefile for easy compilation
- Comprehensive documentation

### Features
- Processes compressed FastQ files (.fastq.gz) directly using zlib
- Converts headers from SRA format to proper Illumina format
- Handles lines up to 1000 characters
- Outputs uncompressed FastQ to stdout
- Cross-platform compatibility (Linux, macOS, Unix)

### Technical Details
- Written in C99-compliant C
- Uses zlib for gzip decompression
- Memory-efficient processing (line-by-line)
- Robust error handling
