Samples                         {#examples}
=======

We have created a few examples to help you get started. All current examples were created with GLFW3.

In the *effects* folder you can find a few useful Shader Effects that are used with these examples, and can be reused with your own projects. Note that these Effects don't depend on the window manager.
The current samples comprise:

- a simple mesh viewer with a Phong Shader

- a simple texture loader (exibits the texture only)

- an image processing application that uses an FBO to sequentially apply multiple filters, such as: Mean and Gradient Filter

- some other rendering examples (such as toon and oren-nayar), mostly to exaplify the GUI features. A SSAO is also under development to complete this sample soon.


## Compiling the samples

*CMake* files are available to compile the samples.

To compile the examples with *cmake*, first make sure you have a recent version of it (2.8.12+) installed on your system.

Then create a `build` directory inside the tucano directory, cd into it, then run *cmake* in the standard way, described below:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
cd tucano/    # top-level directory of tucano
mkdir build/  # build directory
cd build/
cmake ..
make
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This will compile all tucano examples at once, placing them under the `bin/` folder, inside the tucano top-level directory.
