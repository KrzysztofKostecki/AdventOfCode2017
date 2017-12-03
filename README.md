# AdventOfCode2017
Solutions for all days from 2017 Advent of Code

Best way to use it is to open repository folder in VS Code. Tasks are configured properly.

Steps to run:
- make "build" directory

  `$ mkdir build`
  
- generate Makefile with cmake:

  `$ cd build`
  
  `$ cmake -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Debug ..`
  
- run makefile(in "build" directory)

  `$ make -j 8`
