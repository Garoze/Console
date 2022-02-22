# Fantasy Console

A 16 bit Fantasy console inspired by the NES and Gameboy written in C++

## Table of Contents

1. [Introduction](#introduction)
	- [How use the Project](#installation)
1. [Specs](#specs)
	- [Memory](#memory)
1. [License](#license)

## Introduction

To use this project you'll need a C/C++ compiler like [GCC](https://gcc.gnu.org/) or [Cland](https://clang.llvm.org/).

This project also uses the Imhui lib to draw the interface, you can check the project [here](https://github.com/ocornut/imgui)

## Installation

Please make sure you have all the dependecies listed [here](#introduction).
If you do, just run the commands below.

```bash
git clone https://github.com/Garoze/Console
cd Console
make config && make
```

To use the `Console` itself, just run

```bash
./console <rom_file>
```

## License

This project in under the [**MIT**](https://mit-license.org/) License terms. And you can check the file [here](https://github.com/Garoze/Console/blob/main/LICENSE).
