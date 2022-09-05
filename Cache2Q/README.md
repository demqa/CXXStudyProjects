# 2Q Cache Emulator

This will be my cache emulation in course of C++ in MIPT 2nd year (First task). There will be gradual development from C programming language to C++.

## Task

1. Functionality

   I will take input from stdin and give output to stdout.

   Input:

   * cache size
   * number of elements to test cache
   * elements to test cache (elements will be ints for simplicity)

   Output:

   * number of cache-hits

   Emulate cache use with 2Q algorithm. 

   I took information about 2Q Algorithm from [article from it's authors](https://www.vldb.org/conf/1994/P439.PDF).

2. Ideal Cache Emulation
   
   I have to compare results of 2Q cache with [ideal cache](https://www.youtube.com/watch?v=xDKnMXtZKq8&t=1598s).
   
   * determine when in the future will appear every element
   * drop the latest from all current elements in cache
   
   I have to make 2 algorithms:
   
   * the most optimal
   * least optimal (adequate)

3. End-to-end tests

## Build

```shell
mkdir build && cd build && cmake ..
```

## Usage

This paragraph will be improved in future versions.

```shell
./Cache2Q
```
