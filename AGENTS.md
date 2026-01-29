# AGENTS.md - Coding Guidelines for ipsuip

## Build System
- **Build Tool**: CMake 3.23+
- **Compiler**: GCC 12.1+
- **Dependencies**: Boost 1.82, Qt6 (Core, Widgets)
- **Build Command**:
  ```bash
  mkdir -p build && cd build
  cmake .. -DCMAKE_CXX_STANDARD=20
  make
  ```
- **Clean Build**:
  ```bash
  rm -rf build && mkdir -p build && cd build
  cmake .. -DCMAKE_CXX_STANDARD=20
  make
  ```

## Testing
- **Test Framework**: None currently implemented. Add tests using Catch2 or Google Test.
- **Running Tests**: N/A (implement test targets in CMakeLists.txt)
- **Single Test Execution**: N/A

## Code Style Guidelines

### Formatting
- **Indentation**: 4 spaces (no tabs)
- **Braces**: K&R style (opening brace on same line)
- **Line Length**: 100 characters max
- **Clang-Format**: Use the default LLVM style with these adjustments:
  ```yaml
  IndentWidth: 4
  ColumnLimit: 100
  AllowShortIfStatementsOnASingleLine: false
  IndentCaseLabels: true
  ```

### Imports/Includes
- **Order**: Standard library → Third-party → Local headers
- **Grouping**: Separate groups with a blank line
- **Example**:
  ```cpp
  #include <vector>
  #include <string>

  #include <boost/asio.hpp>
  #include <QtCore/QObject>

  #include "functions.h"
  #include "http_client_sync_ssl.h"
  ```

### Naming Conventions
- **Variables**: `snake_case` (e.g., `ip_address`, `file_name`)
- **Functions**: `snake_case` (e.g., `validate_ip`, `save_to_file`)
- **Classes/Structs**: `PascalCase` (e.g., `HumanReadable`, `MainWindow`)
- **Constants**: `UPPER_SNAKE_CASE` (e.g., `MAX_RETRIES`, `DEFAULT_TIMEOUT`)
- **Namespaces**: `lowercase` (e.g., `ipsuip`)
- **Macros**: `UPPER_SNAKE_CASE` (avoid unless necessary)
- **Template Parameters**: `PascalCase` (e.g., `Iterator`, `T`)

### Types
- **Use `auto`**: For complex types or when the type is obvious (e.g., `auto it = vec.begin()`)
- **Primitive Types**: Use fixed-width types (e.g., `uint32_t`, `int64_t`) where precision matters
- **Enums**: Use `enum class` (e.g., `enum class TYPEPARSING { CONTINENT, COUNTRY }`)
- **Structs vs Classes**: Use `struct` for POD, `class` for objects with invariants

### Error Handling
- **Exceptions**: Use for exceptional cases (e.g., file I/O failures, network errors)
- **Error Codes**: Use for expected failures (e.g., invalid user input)
- **Assertions**: Use `assert` for internal invariants (disable in release builds)
- **Qt Signals/Slots**: Use for GUI error reporting
- **Example**:
  ```cpp
  try {
      std::ofstream file("output.txt");
      if (!file) throw std::runtime_error("File creation failed");
      file << data;
  } catch (const std::exception& e) {
      std::cerr << "Error: " << e.what() << std::endl;
      throw; // Re-throw if recovery is impossible
  }
  ```

### Memory Management
- **RAII**: Prefer stack allocation and smart pointers (`std::unique_ptr`, `std::shared_ptr`)
- **Raw Pointers**: Avoid unless interfacing with Qt or C libraries
- **Qt Objects**: Use parent-child ownership (e.g., `QObject` hierarchy)

### Concurrency
- **Threads**: Use `std::thread` or Qt's `QThread` for parallelism
- **Atomic Operations**: Use `std::atomic` for shared data
- **Mutexes**: Use `std::mutex` or `QMutex` for synchronization
- **Example**:
  ```cpp
  std::vector<std::thread> threads(num_threads - 1);
  for (auto& t : threads) {
      t = std::thread([&] { /* work */ });
  }
  for (auto& t : threads) t.join();
  ```

### Qt-Specific Guidelines
- **Signals/Slots**: Use the new syntax (`connect(sender, &Sender::signal, receiver, &Receiver::slot)`)
- **UI Files**: Prefer `.ui` files for GUI layouts (use `uic` to generate headers)
- **String Literals**: Use `tr()` for user-facing strings (e.g., `tr("Error: File not found")`)
- **Resource Files**: Use `.qrc` for embedded resources

### Documentation
- **Comments**: Use `//` for single-line, `/* */` for multi-line
- **Function Docs**: Use Doxygen-style comments:
  ```cpp
  /**
   * @brief Validates an IP address string
   * @param ip The IP address to validate
   * @return true if valid, false otherwise
   */
  bool validate_ip(const std::string& ip);
  ```
- **File Headers**: Include a brief description and copyright:
  ```cpp
  /**
   * @file functions.h
   * @brief Core functionality for IP address parsing and processing
   * @copyright Made by I'm Pancake
   */
  ```

### Performance
- **Move Semantics**: Use `std::move` for large objects (e.g., `std::vector`)
- **Pass by Value**: For small, copyable types (e.g., `int`, `std::string_view`)
- **Pass by Reference**: For large or non-copyable types (e.g., `const std::vector&`)
- **Avoid Copies**: Use `emplace_back` instead of `push_back` where possible

### Modern C++ Features
- **Use**: `std::optional`, `std::variant`, `std::filesystem`, range-based for loops, structured bindings
- **Avoid**: Raw loops (use algorithms), C-style casts, manual memory management
- **Example**:
  ```cpp
  for (const auto& [key, value] : map) {
      std::cout << key << ": " << value << "\n";
  }
  ```

### Testing Guidelines
- **Unit Tests**: Test individual functions (e.g., `validate_ip`, `range_boundaries_to_cidr`)
- **Integration Tests**: Test interactions between components (e.g., `parsing_site` + `save_to_file`)
- **Mocking**: Use dependency injection for external services (e.g., HTTP client)
- **Test Coverage**: Aim for 80%+ coverage of critical paths

### Git Workflow
- **Commits**: Atomic changes with descriptive messages (e.g., "Fix IP validation for edge cases")
- **Branches**: Use feature branches (e.g., `feature/parallel-downloads`)
- **Pull Requests**: Include a summary of changes and testing steps

### Example Code
```cpp
// Good:
std::vector<std::string> parse_ips(const std::vector<std::string>& raw_data) {
    std::vector<std::string> ips;
    ips.reserve(raw_data.size());

    for (const auto& line : raw_data) {
        if (validate_ip(line)) {
            ips.emplace_back(line);
        }
    }
    return ips;
}

// Bad:
void parse(std::vector<std::string> d, std::vector<std::string>* o) {
    for (int i = 0; i < d.size(); i++) {
        if (validateIP(d[i])) {
            o->push_back(d[i]);
        }
    }
}
```

---
**Note**: This file is intended for agentic coding tools. Follow these guidelines strictly to maintain consistency.