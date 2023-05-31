# C++ Container Testing

A simple program that runs a series of tests on C++ standard containers. The tests are not designed to be rigorous but rather simple experimentation of the relative performance of C++ containers.

## Contents

- [C++ Container Testing](#c-container-testing)
  - [Contents](#contents)
  - [Tests](#tests)
  - [Running Tests](#running-tests)
  - [Plot Results](#plot-results)
  - [License](#license)
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
- Incremental Sorted Insert

The results of the tests are store in the [`data/`](data/) directory. Graphs of the data are stored in the [`imgs/`](imgs/) directory.

Currently, only the following containers are tested.

- `std::list`
- `std::deque`
- `std::vector`
- Preallocated `std::vector`

## Running Tests

To run the tests simply run the following command in the root of the project. The results are stored as `*.csv` in the [`data/`](data/) directory. This directory is split first by the test type and then the sized element used for that test.

```sh
poac build -r
./poac-out/release/cxx-container-testing --test=all
```

## Plot Results

To plot the results a small Go package has been included that is used to plot the results as `*.svg` into the [`imgs/`](imgs/) directory. The [`imgs/`](imgs/) directory mirrors the structure of the `data/` directory.

```sh
go build -o bin/plotter
bin/plotter
```

## License

MIT License

## Acknowledgments

- Inspired by blog post by Baptiste Wicht - [C++ benchmark – std::vector VS std::list VS std::deque](https://baptiste-wicht.com/posts/2012/12/cpp-benchmark-vector-list-deque.html)
- Built with [Poac - v0.6.0](https://poac.dev/)
