# Ford-Johnson Merge-Insert Sort

### Overview

**PmergeMe** is a C++98 program that implements the **Ford-Johnson merge-insertion sort algorithm** (also known as merge-insertion sort) to efficiently sort positive integer sequences. The program demonstrates the algorithm using two different STL containers (`std::vector` and `std::deque`) and compares their performance.

This is Exercise 02 from C++ Module 09, focused on practical application of STL containers and advanced sorting algorithms.

## Exercise Requirements

### Constraints
- **Input**: Positive integer sequence as command-line arguments
- **Algorithm**: Ford-Johnson merge-insertion sort (from _The Art of Computer Programming, Vol.3_, Page 184)
- **Containers**: Must use at least two different STL containers
- **Capacity**: Must handle at least 3000 different integers
- **Standard**: C++98 compliant

### Output Format
The program displays:
1. **Before**: The unsorted integer sequence
2. **After**: The sorted integer sequence
3. **Time (Container 1)**: Processing time with first container (std::vector)
4. **Time (Container 2)**: Processing time with second container (std::deque)

### Error Handling
- Invalid inputs (negative numbers, non-integers, overflow) display "Error" to stderr
- Duplicate handling is implementation-specific



## The Ford-Johnson Algorithm


The **Ford-Johnson algorithm** (merge-insertion sort) is a comparison-based sorting algorithm that minimizes the number of comparisons needed to sort a sequence. It was designed by L. R. Ford Jr. and Selmer M. Johnson in 1959.

### Algorithm Overview

1. **Pairing Phase**: Divide the sequence into pairs and sort each pair (larger element first)
2. **Recursive Sort**: Recursively sort the larger elements (first elements of pairs)
3. **Main Chain**: The sorted larger elements form the main chain
4. **Insertion Phase**: Insert the smaller elements (second elements of pairs) into the main chain using binary search
5. **Jacobsthal Sequence**: Insert elements in a specific order determined by the Jacobsthal sequence to minimize comparisons

### Why Jacobsthal Sequence?

The Jacobsthal sequence (1, 1, 3, 5, 11, 21, 43, 85, 171, 341, ...) determines the optimal insertion order. Each number is defined as:
```
J(n) = J(n-1) + 2 × J(n-2)
```

Inserting elements in reverse order within each Jacobsthal range ensures:
- Maximum search space is minimized for each insertion
- Fewer comparisons overall
- Optimal balance between comparison count and data movement

---

## Implementation Details

### Dual Container Approach

The implementation provides **separate implementations** for `std::vector` and `std::deque`:

#### std::vector Implementation
- **Best for**: Random access, cache-friendly operations
- **Files**: `FordJohnsonSort.cpp`, `FordJohnsonInsert.cpp`
- **Performance**: Generally faster for small to medium datasets due to better cache locality

#### std::deque Implementation
- **Best for**: Insertions at both ends
- **Files**: `FordJohnsonSort_deque.cpp`, `FordJohnsonInsert_deque.cpp`
- **Performance**: May be faster for certain insertion patterns

## Compilation and Usage

### Compilation

```bash
make
```

This compiles with:
- Compiler: `c++`
- Flags: `-Wall -Wextra -Werror -std=c++98`
- Output: `PmergeMe` executable

### Usage

```bash
./PmergeMe [positive integers...]
```

### Examples

#### Small Sequence
```bash
$ ./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::vector : 12 us
Time to process a range of 5 elements with std::deque : 15 us
```

#### Large Random Sequence (Linux)
```bash
$ ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " " | xargs`
Before: 45231 78923 12456 98234 ...
After: 45 123 234 456 ...
Time to process a range of 3000 elements with std::vector : 62143 us
Time to process a range of 3000 elements with std::deque : 69272 us
```

#### Large Random Sequence (macOS)
```bash
$ ./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' ' | xargs`
Before: 45231 78923 12456 98234 ...
After: 45 123 234 456 ...
Time to process a range of 3000 elements with std::vector : 62143 us
Time to process a range of 3000 elements with std::deque : 69272 us
```

#### Error Cases
```bash
$ ./PmergeMe -1 2
Error

$ ./PmergeMe 2147483648
Error

$ ./PmergeMe abc
Error

$ ./PmergeMe
Program needs a minimum of 1 argument
```

### Makefile Targets

- `make` or `make all` - Compile the program
- `make clean` - Remove object files
- `make fclean` - Remove object files and executable
- `make re` - Recompile everything

---

## Performance Testing

### Verification

The program automatically verifies correctness by comparing the result with `std::sort`:
```cpp
t_vector_ints computerSorted(input);
std::sort(computerSorted.begin(), computerSorted.end());
testMatch(ordered, computerSorted);  // Prints "MATCH!" if correct
```

### Benchmarking Different Sizes

```bash
# 10 elements
./PmergeMe `jot -r 10 1 10000 | tr '\n' ' ' | xargs`

# 100 elements
./PmergeMe `jot -r 100 1 10000 | tr '\n' ' ' | xargs`

# 1000 elements
./PmergeMe `jot -r 1000 1 100000 | tr '\n' ' ' | xargs`

# 3000 elements (required capacity)
./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' ' | xargs`

# 5000 elements (stress test)
./PmergeMe `jot -r 5000 1 100000 | tr '\n' ' ' | xargs`
```

### Expected Performance Characteristics

- **Small sequences (< 100)**: Both containers perform similarly, overhead dominates
- **Medium sequences (100-1000)**: `std::vector` typically faster due to cache locality
- **Large sequences (> 1000)**: Performance gap may widen based on insertion patterns
- **Very large sequences (> 5000)**: Deque may become competitive due to reduced data movement

---

## Algorithm Complexity

### Time Complexity

- **Best/Average Case**: O(n log n) comparisons (approximately **n log n - 1.4n** comparisons)
- **Worst Case**: O(n log n)
- The Ford-Johnson algorithm minimizes comparisons but may perform more data movements than other algorithms

### Space Complexity

- **Recursive space**: O(log n) for recursive calls
- **Additional storage**: O(n) for pairs and temporary sequences
- **Total**: O(n) auxiliary space

### Comparison Count

The Ford-Johnson algorithm is **optimal** in terms of comparison count for small sequences:
- For n ≤ 11, it uses the minimum possible number of comparisons
- For larger n, it remains highly competitive (within 1-2% of theoretical minimum)

### Practical Performance

While Ford-Johnson minimizes comparisons, modern algorithms like **quicksort** or **mergesort** often perform better in practice due to:
- Better cache locality
- Fewer data movements
- Simpler implementation with less overhead

This implementation serves as an educational example of:
- Advanced sorting algorithm design
- STL container usage and comparison
- Recursive algorithm implementation
- Performance measurement and optimization

---

## Additional Notes

### Design Decisions

1. **Separate implementations**: Following the exercise recommendation, separate implementations for each container avoid generic function overhead
2. **Precision timing**: Microsecond precision using `gettimeofday` allows clear performance comparison
3. **Strict validation**: Safe integer parsing with overflow detection prevents undefined behavior
4. **Automatic testing**: Built-in correctness verification against `std::sort`

### Edge Cases Handled

- Single element: Returns immediately
- Two elements: Direct comparison and swap
- Odd number of elements: Last element inserted separately using binary search
- Integer overflow: Detected during parsing
- Invalid input: Caught and reported as "Error"

### Limitations

- **duplicate detection**: Duplicates are allowed and preserved
- **Positive integers only**: As per exercise requirements
- **32-bit integers**: Limited to `INT_MAX` (2147483647)
- **C++98 compliance**: No modern C++ features (auto, range-based loops, etc.)

---

## References

- Knuth, Donald E. _The Art of Computer Programming, Volume 3: Sorting and Searching_ (2nd ed.), Section 5.3.1: Minimum-Comparison Sorting, pp. 180-187.
- Ford, L. R., Jr.; Johnson, S. M. (1959). "A Tournament Problem". _American Mathematical Monthly_, 66 (5): 387-389.

---

**Author**: Implementation by khaldoun Ahanawi  
**Date**: 2026  
**Standard**: C++98  
**Module**: CPP Module 09_ex02
