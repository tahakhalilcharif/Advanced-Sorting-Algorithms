# Advanced Sorting Algorithms Performance Analysis

## Project Overview

This C program provides a comprehensive performance comparison of advanced sorting algorithms, measuring their execution times across varying array sizes. The project focuses on four sophisticated sorting techniques:

- Merge Sort
- Counting Sort
- Quick Sort
- Radix Sort

## Key Features

- Dynamic array size generation
- Precise execution time measurement
- Random array generation
- CSV result logging
- Performance visualization support

## Prerequisites

- C Compiler (GCC recommended)
- Python 3.x (for visualization)
- Libraries:
  - Pandas
  - Matplotlib

## Compilation

Compile the C program using:

```bash
gcc -std=c99 -o sorting_benchmark sorting_algorithms.c
```

## Execution

1. Compile the program
2. Run the executable
3. Analyze results in `sorting_results.csv`

```bash
./sorting_benchmark
```

## Visualization Script

A Python script is provided for graphing performance:

```bash
python visualise.py
```

## Sorting Algorithm Characteristics

### Merge Sort
- **Time Complexity**: O(n log n)
- **Space Complexity**: O(n)
- Stable sorting algorithm
- Efficient for large datasets
- Consistent performance

### Counting Sort
- **Time Complexity**: O(n + k), where k is the range
- **Space Complexity**: O(k)
- Works best with integer ranges
- Extremely efficient for small, integer-based datasets
- Limited by range of input

### Quick Sort
- **Time Complexity**: 
  - Average: O(n log n)
  - Worst Case: O(n²)
- **Space Complexity**: O(log n)
- In-place sorting
- Performance depends on pivot selection
- Typically faster in practice

### Radix Sort
- **Time Complexity**: O(d * (n + k)), where d is number of digits
- **Space Complexity**: O(n + k)
- Works well for fixed-width integers
- Linear time complexity for certain inputs
- Stable sorting method

## Experimental Parameters

- Array sizes: 10,000 to 1,000,000 (increments of 10,000)
- Random integer generation range: 0-999
- Multiple iterations for statistical reliability

## Output Files

1. `sorting_results.csv`: Detailed timing data
2. `sorting_comparison_graph.png`: Performance visualization

## Limitations

- Uses pseudo-random number generation
- CPU time measurements can vary
- Designed for comparative analysis

## Potential Improvements

- Add more sorting algorithms
- Implement different input array types (sorted, reverse sorted)
- Create more detailed statistical analysis

## Requirements

- C99 or later standard
- Python 3.6+
- Matplotlib 3.x
- Pandas 1.x

## Contributing

Contributions, issues, and feature requests are welcome!

## Author

Charif Taha Khalil