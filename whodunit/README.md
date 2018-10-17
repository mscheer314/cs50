# Questions

## What's `stdint.h`?

`stdint.h` is a header file that includes typedefs for exact-width integer types.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

`uint8_t`, `uint32_t`, and `uint16-t` are unsigned integers of 8, 32, and 16 bits respectively. Having these declared explicitly shows what your intent is with the variable.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

`BYTE` = 8, `DWORD` = 32, `LONG` = 32, `WORD` = 16

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

ASCII - BM, DECIMAL - 66 77, HEXADECIMAL - 0x42 0x4D

## What's the difference between `bfSize` and `biSize`?

`bfSize` is a `WORD` or 16 bytes, while `biSize` is a `DWORD` or 32 bytes.

## What does it mean if `biHeight` is negative?

If `biHeight` is negative, the bitmap is a top-down DIB (device independent bitmap) and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

`biBitCount`

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

At line 24, if the file provided doesn't exist or couldn't be located. At 32, if the file creation couldn't be completed due to disk space or

## Why is the third argument to `fread` always `1` in our code?

The third argument is the count of files to be read. In this code, it is always 1 file. [fread info](http://www.cplusplus.com/reference/cstdio/fread/)

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

`int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;`
(4 - (3 * 3) % 4) % 4
(4 - 9 % 4) % 4
(-5 % 4) % 4
3 % 4
3

## What does `fseek` do?

skip over padding, if it exists

## What is `SEEK_CUR`?

the current position of the file pointer [SEEK_CUR](https://www.tutorialspoint.com/c_standard_library/c_function_fseek.htm)

## Whodunit?

It was Professor Plum with the candlestick in the library.