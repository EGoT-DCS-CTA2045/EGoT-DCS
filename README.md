RASPI CONTROL - SSH DEVELOPMENT - DCM implementation for raspberry pi zero w 
# ssh-dev, branched from raspi-control for development using remote-ssh toolchains 
This is a branch of raspi-control specifically meant to share common source between desktop and remote (pi) environments, using a remote toolchain in CLion.
Executable app for epri-dev sample2 program refactored into src/DCM.cpp, compiling in cmake-remote-repo-3 

## Debian Buster (OS)
The requirements are:

* CMake 3.14 or better;
* A C++11 compatible compiler
* Boost Libraries
* Git

### Updated configuration instructions 

All at once (delete the `mkdir ~/temp` and `cd ~/temp` commands if ~/temp already exists):
`sudo apt-get update -y && sudo apt-get install -y wget pkg-config build-essential git cmake libssl-dev libboost-all-dev -y && sudo apt-get upgrade -y && sudo reboot` The last command will reboot the pi. Re- login and enter: ` mkdir ~/temp && cd ~/temp && wget https://github.com/Kitware/CMake/releases/download/v3.18.4/cmake-3.18.4.tar.gz && tar -xf cmake-3.18.4.tar.gz && cd cmake-3.18.4 && cmake . && make && sudo make install`

Step by step: 

`sudo apt-get update -y `

`sudo apt-get install -y wget pkg-config build-essential git cmake libssl-dev libboost-all-dev`

`sudo apt-get upgrade`

`mkdir ~/temp`

`cd ~/temp `

`wget https://github.com/Kitware/CMake/releases/download/v3.18.4/cmake-3.18.4.tar.gz `

` tar -xf cmake-3.18.4.tar.gz `

`cd cmake-3.18.4 `

`cmake . `

`make `

`make install`

### From within the repo root directory
After you clone this directory, if you want to work with raspi-config, you must manually switch branches (clone automatically grabs main).
So from the directory where you cloned this repo, change directories into the repo: ```cd EGoT-DCS/```
To see all branches: ```git branch -a``` 
To switch branches: ```git checkout ssh-dev```

Now to configure (must be done first):

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
