# C++ Container Testing

A simple program that runs a series of tests on C++ standard containers. The tests are not designed to be rigorous but rather simple experimentation of the relative performance of C++ containers.

## Contents

- [C++ Container Testing](#c-container-testing)
  - [Contents](#contents)
  - [Tests](#tests)
  - [Dependencies](#dependencies)
  - [Running Tests](#running-tests)
  - [License](#license)
  - [Acknowledgments](#acknowledgments)

## Tests

The tests include:

- Push Back
- Push Front
- Linear Search
- Random Insert w/ Linear Search
- Destruction
- Sort
- Incremental Sorted Insert

The results of the tests are store in the [`data/`](./data) directory. Graphs of the data are stored in the [`images`](./images) directory.

Currently, only the following containers are tested.

- `std::vector`
- `std::deque`
- `std::list`

## Dependencies

Current this project needs matplot++ as an external dependency. You can obtain it from Homebrew using the following command.

```sh
brew install matplotplusplus
```

## Running Tests

To run the tests simply run the following command in the root of the project.

```sh
sudo ln -s /home/linuxbrew/.linuxbrew/include/matplot /usr/local/include
sudo mdkir /usr/local/lib/matplot 
sudo ln -s /home/linuxbrew/.linuxbrew/lib/libmatplot.so /usr/local/lib/matplot/libmatplot.so
chmod +x ./makedb-new.sh
chmod +x ./run.sh

./run <debug | release>
```

## License

MIT License

## Acknowledgments

- Inspired by blog post by Baptiste Wicht - [C++ benchmark – std::vector VS std::list VS std::deque](https://baptiste-wicht.com/posts/2012/12/cpp-benchmark-vector-list-deque.html)
- Built with [Poac](https://poac.dev/)
