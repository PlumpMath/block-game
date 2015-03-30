# BlockGame

A C++ OpenGL game that involves blocks.

## Setup instructions (Visual Studio 2013)

1. Clone this repository to your machine. I have not personally tested this, but I remember reading that you should not place
the project in a location with whitespace in the path.

2. In Visual Studio, create a new Visual C++ Empty Project, with the correct location and name according to what you did in the
previous step. Be sure to leave the "Create directory for solution" box unchecked.

3. Download [GLEW](http://sourceforge.net/projects/glew/files/glew/1.12.0/glew-1.12.0-win32.zip/download) and
[GLFW](http://sourceforge.net/projects/glfw/files/glfw/3.1.1/glfw-3.1.1.bin.WIN32.zip/download). Unzip them somewhere outside of
your project directory.

4. In your project directory, create directories `lib/glew` and `lib/glfw`.
