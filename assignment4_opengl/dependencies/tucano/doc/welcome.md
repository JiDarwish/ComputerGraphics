Tucano
======

### Welcome to Tucano, a Library for rapid prototyping with modern OpenGL and GLSL.

Tucano encapsulates many common OpenGL/GLSL features in C++ classes, saving a lot of coding and allowing the developer to concentrate on the core of the application and the Shader codes.

By keeping the code **clean** and **compact**, Tucano also renders the code **less bug prone**.

## For the Computer Graphics Course

The framework will do most of the technical repetitive work for you regarding the basic setting up of a window and OpenGL context, you will mostly be working with one C++ class file and shaders. You are, nevertheless, more than welcome to look inside Tucano and see how it works internally.

## Other Interesting Features

* easily create and use Textures, FBOs, Shader Programs, Textures, modern OpenGL buffers...

* common classes used in most applications, such as Mesh, Camera, Trackball, and much more

* basic shapes, such as spheres, cylinder, arrows ...

* automatic texture unit assignment when binding textures, no need to worry about keeping track of ids

* uniforms, textures, and attributes are linked with the shaders in a simple and transparent way (no need to manually set locations)

* wrapper for Eigen Geometry, e.g. directly pass an *Eigen Matrix4f* to a GLSL Shader *mat4*

* use it with Qt, Glut, Glfw, or any other window manager that supports OpenGL


## Requirements

Tucano has only two library dependencies, but for the practicals you all need to install a windows manager, we will use GLFW3. Make sure you have a recent version of each library.

* Eigen : http://eigen.tuxfamily.org/
* GLEW : http://glew.sourceforge.net/
* GLFW3 : https://www.glfw.org/
  

## OpenGL version

Note that to use all the functionalities of Tucano you need an OpenGL driver that supports at least version 4.3.
The same goes for the GLSL version.

If you are using a computer or laptop without a dedicated graphics card it should work nevertheless. You will probably
have the Mesa driver installed. Many times the Mesa driver does not support by default OpenGL 4, but you can enforce it by running your program with the following prefix

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MESA_GL_VERSION_OVERRIDE=4.3 program-name
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## Using

You do not need to compile Tucano, it is designed as include file only to make compilation easier. However, it also means slower compilation time unfortunately.

## Documentation

The documentation can be found online at http://graphics.tudelft.nl/~marroquim/tucano
or you can just open the index.html file in your doc/html local folder (distributed with the assignments).

## First steps

Follow the [Compiling Tutorial](@ref compiling)