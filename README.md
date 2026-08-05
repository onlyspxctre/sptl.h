# sptl.h

Recreational, header-only, macro-implemented library that provides elegant yet pragmatic implementations of common utilities and data structures not present by default in the C standard library.

> [!WARNING]
> This library is extremely experimental and should only be used for recreational purposes only!

## Features

- Macro-implemented data structures (type safe, generic)
    - Data structures heap allocate data on first push and dynamically resize
    - **You** are responsible for freeing structures (call the data structure's respective free)
- Implemented data structures: 
    - Dynamic Array (`Sp_Dynamic_Array`)
    - Linked List (`Sp_Linked_List`)
    - Hash Table (`Sp_Hash_Table`)
    - Heap (`Sp_Heap`)
- Quality-of-life string manipulation structures:
    - String Builder (`Sp_String_Builder`)
    - String View (`Sp_String_View`)
- Quality-of-life macros:
    - `sp_cstr()`: compound literal of type `const char *const *`
    - `SPExtern`: primarily used for Windows support and generating DLLs
    - `sp_unreachable()`: marking unreachable code (binds to `__builtin_unreachable()`)
    - `sp_swap()`: generic implementation to swap two variables
- Logging system w/ multiple log levels
    - Prefixed with `[LOG_LEVEL]`
    - Info is printed to `stdout`, warnings & errors are printed to `stderr`
    - Automatically newlined
    - Verbose logs with `-DSP_VERBOSE_LOGS` and the `SP_VERBOSE` log level

## Usage

> [!NOTE]
> This library uses non-standard extensions that may not be available in all C compilers. Ensure that your compiler:
> - Supports `__typeof__` **AND** is a C11 compliant compiler.
> - **OR** Is a C23 compliant compiler.

> For the sake of compatibility and maintainability, only GCC and Clang are officially supported.


### `Sp_Dynamic_Array`

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
