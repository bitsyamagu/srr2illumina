# Contributing to srr2illumina

Thank you for your interest in contributing to srr2illumina! We welcome contributions from everyone.

## How to Contribute

1. **Fork the Repository**: Create a fork of this repository on GitHub.

2. **Clone Your Fork**: Clone your forked repository to your local machine.
   ```bash
   git clone https://github.com/yourusername/srr2illumina.git
   cd srr2illumina
   ```

3. **Create a Branch**: Create a new branch for your feature or bug fix.
   ```bash
   git checkout -b feature/your-feature-name
   ```

4. **Make Changes**: Make your changes to the code.

5. **Test**: Ensure your changes work correctly by testing with sample FastQ files.
   ```bash
   make clean && make
   ./srr2illumina test_input.fastq.gz > output.fastq
   ```

6. **Commit**: Commit your changes with a descriptive commit message.
   ```bash
   git commit -m "Add feature: description of your changes"
   ```

7. **Push**: Push your changes to your fork.
   ```bash
   git push origin feature/your-feature-name
   ```

8. **Pull Request**: Create a pull request from your fork to the main repository.

## Code Style

- Use clear, descriptive variable names
- Add comments for complex logic
- Follow existing code formatting
- Ensure compatibility with standard C99

## Reporting Issues

If you find a bug or have a feature request, please create an issue on GitHub with:
- A clear description of the problem
- Steps to reproduce (for bugs)
- Expected vs actual behavior
- Sample input files (if applicable)

## Types of Contributions

- Bug fixes
- Performance improvements
- New features
- Documentation improvements
- Test cases

Thank you for contributing!
