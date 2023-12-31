# Dungeons & Dragons Initiative Tracker
Commandline tool to track initiative for Dungeons and Dragons 5e combat encounters.

## Requirements
To build this software you require the following tools
- [CMake](https://cmake.org) Version 3.10 or higher

## Build
Run the following commands to build the project
```
$ cmake -B bld
$ cmake --build bld
```

## Testing
For unit tests this project relies on [GoogleTest](https://github.com/google/googletest) in version 1.14.0. To execute the unit tests run the following commands
```
$ cmake -B bld
$ cmake --build bld
$ ctest --test-dir bld/test
```

## Usage
To use the software run
```
$ ./bld/src/dnd-initiative-tracker
```
