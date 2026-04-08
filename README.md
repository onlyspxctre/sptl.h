# sptl.h

Recreational header-only library for simple implementations of common utils and data structures not present by default in the C language.

> [!WARNING]
> This library is extremely experimental and should only be used for recreational purposes only!

> [!NOTE]
> Some macros in this library uses non-standard extensions that may not be available in all C compilers. For compatibility sakes, only the GCC and Clang compilers are supported.

## Features

- Macro-implemented data structures (type safe, generic)
- Currently implemented data structures: 
    - Dynamic Array
    - Linked List
    - Hash Table
- Logging system w/ multiple log levels
    - Prefixed with `[LOG_LEVEL]`
    - Info is printed to `stdout`, warnings & errors are printed to `stderr`
    - Automatically newlined
    - Verbose logs with `-DSP_VERBOSE_LOGS` and the `SP_VERBOSE` log level

## Usage

```c
#include "sptl.h"

int main(void) {
    Sp_Dynamic_Array(int) da = {0}; // initializes a dynamic array of type int

    sp_da_push(&da, 1);
    sp_da_push(&da, 2);
    sp_da_push(&da, 3);

    for (size_t i = 0; i < da.count; ++i) {
        da.data[i];
    }

    sp_da_free(&da); // structures must be manually freed
}
```

## References

[nob.h by Tsoding](https://github.com/tsoding/nob.h/), inspiration

## LICENSE
This project is licensed under the [MIT License](LICENSE).
