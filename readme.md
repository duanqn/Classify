# Classify [![Build Status](https://travis-ci.org/duanqn/Classify.svg?branch=master)](https://travis-ci.org/duanqn/Classify) [![Build Status](https://dev.azure.com/q7duan/q7duan/_apis/build/status/duanqn.Classify)](https://dev.azure.com/q7duan/q7duan/_build/latest?definitionId=1) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/21082f135b764fa5938892489c764c31)](https://app.codacy.com/app/duanqn_own_1/Classify?utm_source=github.com&utm_medium=referral&utm_content=duanqn/Classify&utm_campaign=Badge_Grade_Settings)
## Description
A tool for arranging students into classes.

## How to use
### Compiling
With GCC/Make:
```bash
$ ./make
```

With MSVC/NMAKE:
```
> nmake /F Makefile.win
```

### Running
```bash
$ ./build/classify
```
The program will execute interactively.

## Targets
* The numbers of male and female students in each class should be as close as possible.
* The numbers of students in each class should be as close as possible.
* Average scores of each subject in different classes should be as close as possible.
* The overall average scores of each class should be as close as possible.

## Features
### Current
* **Multithread**

The program spawns 8 threads, and each of them runs SA algorithm. The number of threads is hard-coded,
which could cause a problem, and should be fixed in the future.

### Future
* **GUI**

Right now I'm thinking of using Windows native APIs to build the graphical interface, because
they are well supported and do not require any 3rd party software in runtime.

## Open source code
utf8.h and utf8.c are copied from [lytsing/gbk-utf8][1]. Both files have been modified.

stringsplitter.h and stringsplitter.cpp are copied from [tobbez/string-splitting][2].
The original author is [Cheers and hth. - Alf from Stack Overflow][3]
Both files have been modified.

N.B. The code on Stack Overflow will skip empty segments.

[1]: https://github.com/lytsing/gbk-utf8
[2]: https://github.com/tobbez/string-splitting/blob/master/split6.cpp
[3]: https://stackoverflow.com/questions/9378500/why-is-splitting-a-string-slower-in-c-than-python/9379203#9379203

## Contribution
All contribution are welcome, from reporting bugs to implementing new features.

A short to-do list:
* Check for memory leakage (I know there will be some)
* Build GUI
* Replace hard-coded configuration with interactive prompts
* Detect the number of CPUs before spawning threads
* Make it easy-to-deploy, easy-to-use
* Write a user manual
