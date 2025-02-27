# cppLib
A collection of c++ functions and data structures. The minimum C++ version is C++20

Subjects that this library covers:
- arrays & vectors
- math
- strings
- data structures

Arrays & Vectors:
- utilities to manipulate arrays & vectors
- search

Math:
- general math functions
- integration methods
- root finding methods
- vector operations
- fast fourier transform
- complex numbers
- dual numbers

Strings:
- utilities to manipulate strings
- search
- edit distance

Data Structures:
- binary heap
- doubly linked list

# Build and Run Tests
## Native
```bash
g++ -std=c++23 -Wall ./tests/*.cpp ./src/*.cpp -o ./test.exe
./test.exe
```

## Make
```bash
make
./test.exe
```

## Docker or Podman
### Docker
```bash
docker build -t cpplib_image .
docker run --replace --name cpplib_container cpplib_image
```

### Podman
```bash
podman build -t cpplib_image .
podman run --replace --name cpplib_container cpplib_image
```
