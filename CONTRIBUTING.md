# Contributing Guidelines

We welcome contributions to our University Rating System! Please review this document before submitting changes.

## Table of Contents

1. [Development Environment Setup](#development)
2. [Contribution Workflow](#workflow)
3. [Testing Guidelines](#testing)
4. [Code Style](#code-style)
5. [Documentation](#docs)
6. [CI/CD Checks](#ci)
7. [Reporting Issues](#issues)
8. [License](#license)

## Development Environment Setup

### Prerequisites

- C++17 compatible compiler (GCC 9+ or Clang 10+)
- SQLite 3.35+
- Make 4.0+
- clang-format 12+

### Installation

```sh
git clone https://github.com/crissyro/system-for-evaluating-teachers-and-courses.git
cd system-for-evaluating-teachers-and-courses

sudo apt-get update && sudo apt-get install -y g++ make sqlite3 libsqlite3-dev clang-format

make build
```

## Contribution Workflow

1. **Create a Branch**  
   Branch naming pattern:

   ```
   feature/[short-description]
   fix/[issue-number]
   ```

2. **Commit Changes**  
   Follow [Conventional Commits](https://www.conventionalcommits.org/):

   ```
   feat: add new rating calculation algorithm
   fix: resolve database connection leaks
   docs: update contribution guidelines
   ```

3. **Submit Pull Request**
   - Target `main` branch
   - Reference related issues (#123)
   - Include test coverage
   - Ensure CI checks pass

## Testing Guidelines

### Running Tests

```sh
make test
```

### Writing Tests

- Place tests in `tests/` directory
- Follow GTest conventions
- Cover positive/negative scenarios
- Use transaction rollbacks

### Coverage Reports

```sh
make gcov_report
# Open docs/coverage/index.html
```

## Code Style

### Formatting

```sh
make check-style  # Verify formatting
make format       # Auto-format code
```

### Best Practices

- RAII principles
- Smart pointers
- Const correctness
- Transaction validation
- Doxygen comments

## Documentation

1. Update Doxygen comments
2. Regenerate docs:

   ```sh
   make docs
   ```

3. Commit updated HTML in `docs/`

## CI/CD Checks

- Build validation (GCC/Clang)
- Unit tests (GTest)
- Code coverage (80%+)
- clang-format checks
- SQL schema verification

## Reporting Issues

Use GitHub [Issues](https://github.com/crissyro/system-for-evaluating-teachers-and-courses/issues) for:

- Bug reports
- Feature requests
- Security vulnerabilities

Include:

1. Environment details
2. Reproduction steps
3. Expected vs actual behavior
4. Relevant logs/screenshots

## License

By contributing, you agree to the project's [MIT License](https://opensource.org/licenses/MIT).

---

Thank you for helping improve our University Rating System! 🎓
