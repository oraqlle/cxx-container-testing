# C++ Container Testing

A simple program that runs a series of tests on C++ standard containers. The tests are not designed to be rigorous but rather simple experimentation of the relative performance of C++ containers.

## Contents

- [C++ Container Testing](#c-container-testing)
  - [Contents](#contents)
  - [Tests](#tests)
  - [Running Tests](#running-tests)
    - [Listing Tests](#listing-tests)
    - [Selecting Tests](#selecting-tests)
  - [Plot Results](#plot-results)
  - [Acknowledgments](#acknowledgments)

## Tests

The tests include:

- Push Back
- Push Front
- Linear Search
- Random Insert w/ Linear Search
- Random Erase
- Random Remove + Erase
- Destruction
- Sort
- Random Sorted Insert

The results of the tests are store in the [`data/`](data/) directory. Graphs of the data are stored in the [`imgs/`](imgs/) directory.

Currently, only the following containers are tested.

- `std::list`
- `std::deque`
- `std::vector`
- Preallocated `std::vector`

Currently, only the following kinds of element types are tested with.

- Trivial [Sized Types]
  - 8 bytes
  - 64 bytes
  - 128 bytes
  - 1024 bytes
  - 4096 bytes
- Non Trivial and Movable
- Non Trivial, Movable and `noexcept`
- Non Trivial and Non Movable
- Non Trivial and Expensive to Copy and Move [32 bytes]

## Running Tests

To run the tests simply run the following command in the root of the project. The results are stored as `*.csv` in the [`data/`](data/) directory. This directory is split first by the test type and then the sized element used for that test.

```sh
cmake --preset=<linux|windows|macos>
cmake --build --preset=<linux|windows|macos>
./build/<linux|windows|macos>/release/cxx-container-testing --test=all
```

### Listing Tests

The available tests can be listed using the `--list` flag.

```sh
./build/<linux|windows|macos>/release/cxx-container-testing --list
```

### Selecting Tests

A specific test can be run using the `--test=<test-name>`. Multiple tests can be selected by repeating the `--test` flag.

```sh
# Run only `push-back` test
./build/<linux|windows|macos>/release/cxx-container-testing --test=push-back

# Run only `push-front` and `destroy` tests
./build/<linux|windows|macos>/release/cxx-container-testing --test=push-front --test=destroy
```

## Plot Results

To plot the results a small Go package has been included that is used to plot the results as `*.svg` into the [`imgs/`](imgs/) directory. The [`imgs/`](imgs/) directory mirrors the structure of the `data/` directory.

```sh
go build -o bin/plotter
bin/plotter
```

## Acknowledgments

Inspired by [C++ benchmark - std::vector VS std::list VS std::deque - Baptiste Wicht](https://baptiste-wicht.com/posts/2012/12/cpp-benchmark-vector-list-deque.html)
