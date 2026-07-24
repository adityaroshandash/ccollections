# Project status report


---

# C Collections (`ccollections`)

A lightweight, modular, and efficient collections framework for C, designed to provide reusable, type-agnostic data structures with custom memory management and clear APIs.

---

## 📌 Project Status Overview

| Status | Data Structure / Feature | Description |
| --- | --- | --- |
| **Completed** | **LinkedList** | Full implementation (`linkedList.c`, `linkedList.h`) with recent structural updates. |
| **Completed** | **ArrayList** | Added and integrated into the repository structure. |
| **Completed** | **Build Pipeline** | Configured with `CMakeLists.txt` and `Makefile` for cross-platform compilation. |
| **In Progress** | **Testing Suite** | Testing guide drafted (`ccollections_testing_guide.pdf`); full automated test coverage pending. |
| **Pending** | **Additional Collections** | Stacks, Queues, Hash Maps, Trees, and Sets to be implemented. |

---

## 🛠️ Project Structure

```text
ccollections/
├── include/              # Header files for public interfaces
├── src/                  # Source files for data structure implementations
├── CMakeLists.txt        # CMake build configuration
├── Makefile              # Build automation script
├── linkedList.h / .c     # Initial implementations (migrated/refactored)
└── ccollections_testing_guide.pdf # Initial testing guide and documentation

```

---

## 🚀 Work Done

### 1. **Core Data Structures**

* **Linked List Implementation:**
* Implemented header (`linkedList.h`) and source file (`linkedList.c`).
* Structured for seamless integration into dynamic C applications.


* **ArrayList Integration:**
* Added initial implementation for dynamic contiguous arrays under `include/` and `src/`.



### 2. **Build & Compilation Setup**

* Configured `CMakeLists.txt` for clean, modular multi-platform builds.
* Maintained legacy/standalone `Makefile` support for direct `make` execution.
* Verified multi-file compilation stability across project subdirectories (`src/`, `include/`).

### 3. **Testing & Guidelines**

* Authored `ccollections_testing_guide.pdf` outlining test strategy and manual test executions.

---

## ⏳ Work Pending (Roadmap)

### 1. **Expanded Data Structures**

* [ ] **Stack & Queue:** Implement array-backed and node-backed dynamic stacks and queues.
* [ ] **Hash Map / Dictionary:** Implement key-value mappings with customizable hash functions and collision resolution (chaining or open addressing).
* [ ] **Binary Search Tree / AVL Tree:** Self-balancing search trees for sorted data access.
* [ ] **Set:** Hash-based or tree-based unique collections.

### 2. **Refactoring & Standardization**

* [ ] Move top-level `linkedList.h` and `linkedList.c` completely into `include/` and `src/` to strictly align with clean C library design patterns.
* [ ] Standardize function naming conventions (e.g., `cc_list_add()`, `cc_arraylist_get()`).
* [ ] Introduce `void*` generic payload support with custom dynamic memory callbacks (e.g., `free_fn`, `copy_fn`).

### 3. **Testing & Documentation**

* [ ] Implement an automated unit testing framework (e.g., Unity, CTest, or Criterion).
* [ ] Add Valgrind memory leak checks to CI pipeline scripts.
* [ ] Expand dynamic usage examples directly within the `README.md`.

---

## ⚙️ How to Build

### Using CMake

```bash
mkdir build && cd build
cmake ..
make

```

### Using Makefile

```bash
make

```

---

## 📄 License

This project is licensed under the [MIT License](https://github.com/adityaroshandash/ccollections/blob/main/LICENSE).
