# Big Systems OS


## Prerequisites (For Build)
* GCC
* NASM
* make
* VM Software (such as QEMU)
* Linux, WSL or Docker...
* ntools 

## How to Build
Thes commands must be run in a linux shell (WSL, Docker...etc) should work
```bash
$ cd BigSystemsOS
$ make build-x86_64
```

## Emulate
Note that both of these commands are set up with QEMU
### Linux
```bash
$ make run
```

### Windows
run the file `src/kernel/src/run2.bat`
