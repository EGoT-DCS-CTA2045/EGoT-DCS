# cpp-seed
This will be a starting point for C++ projects which will auto include gtest and boost libs

## Debian Buster (OS)
The requirements are:

* CMake 3.11 or better;
* A C++11 compatible compiler
* Boost Libraries
* Git

```bash
sudo apt-get update -y \
  && apt-get install -y build-essential git cmake libboost-all-dev \
  && mkdir build docs \
  && cmake -S . -B build \
  && cmake --build build
```

To configure (must be done first):

```bash
cmake -S . -B build
```

To build:

```bash
cmake --build build
```

To test:

```bash
./build/tests/all-tests
```

To run:

```bash
./build/src/app
```
## Docker
If you wish to develop on a different system that has docker installed I have provided a dockerfile to setup the same development environment within a container. 

To build:
``` bash
docker build -f Dockerfile.buster -t cppseed .
```

To run tests:

```bash
docker container run -i cppseed
```

To run app:

```bash
docker container run -i cppseed ./build/src/app
```

To run and attach terminal for troubleshooting:

```bash
docker container run -it cppseed /bin/bash
```

To cleanup all docker containers, images, and volumnes that are unused:

```bash
docker system prune -a
```
