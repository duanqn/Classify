# Classify
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

## Targets
* The numbers of male and female students in each class should be as close as possible.
* The numbers of students in each class should be as close as possible.
* Average scores of each subject in different classes should be as close as possible.
* The overall average scores of each class should be as close as possible.

## Open source code
utf8.h and utf8.c are copied from [lytsing/gbk-utf8][1]. Both files have been modified.

stringsplitter.h and stringsplitter.cpp are copied from [tobbez/string-splitting][2].
The original author is [Cheers and hth. - Alf from Stack Overflow][3]
Both files have been modified.

N.B. The code on Stack Overflow will skip empty segments.

[1]: https://github.com/lytsing/gbk-utf8
[2]: https://github.com/tobbez/string-splitting/blob/master/split6.cpp
[3]: https://stackoverflow.com/questions/9378500/why-is-splitting-a-string-slower-in-c-than-python/9379203#9379203

