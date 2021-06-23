# image2inl

Utility that converts a given image into an array of RGBA bytes that can
be easily included on C/C++ applications.

This utility was specially created to generate the .inl file used for the
lite-xl editor since I didn't found anything public to do so and was
curious about how this worked.

## Compiling

```sh
gcc -lm -o image2inl image2inl.c
```

## Usage

When using it with lite-xl make sure to generate a 64x64 png image from
the projects icon.svg file since that size is the one that lite uses on
the `SDL_CreateRGBSurfaceFrom` call to assign the icon to the application.

After that then just run:
```sh
image2inl icon.png icon.inl
```

## References

* https://wiki.wxwidgets.org/Embedding_PNG_Images-Bin2c_In_C
* https://wiki.libsdl.org/SDL_CreateRGBSurfaceFrom
* https://github.com/nothings/stb
