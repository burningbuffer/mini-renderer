# mini-renderer
Creating a renderer with SDL

<img src="https://github.com/burningbuffer/mini-renderer/raw/master/media/head.gif" width="450">

### Features
- 3D Projection
- OBJ loading
- Triangle Rasterization
- Backface Culling
- ...

### Todo
- Depth Sort
- Fix Perspective
- Lighting
- Texture Mapping

### Install

download dependencies:
- SDL
- k-math
   - Catch2

This project use my [k-math](https://github.com/burningbuffer/k-math) library
so try cloning with:

~~~{.bash}
$ git clone --recursive https://github.com/burningbuffer/mini-renderer
$ cd mini-renderer && mkdir build && cd build
$ cmake .. && make
~~~
