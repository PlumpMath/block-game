# BlockGame

A C++ OpenGL game that involves blocks.

## Setup instructions (Visual Studio 2013)

1. Clone this repository to your machine. I have not personally tested this, but I remember reading that you should not place
the project in a location with whitespace in the path.

2. In Visual Studio, create a new Visual C++ Empty Project, with the correct location and name according to what you did in the
previous step. Be sure to leave the "Create directory for solution" box unchecked.

3. In Visual Studio, click "Show All Files" in Solution Explorer. Right click `src`, then click "Include In Project".

4. Download [GLEW](http://sourceforge.net/projects/glew/files/glew/1.12.0/glew-1.12.0-win32.zip/download) and
[GLFW](http://sourceforge.net/projects/glfw/files/glfw/3.1.1/glfw-3.1.1.bin.WIN32.zip/download). Unzip them somewhere outside of
your project directory.

5. In your project directory, create directories `lib/glew` and `lib/glfw`.

6. Copy these files from your unzipped GLEW directory to `lib/glew`:

  * All files in `include/GL`
  * `lib/Release/Win32/glew32.lib`

7. Copy these files from your unzipped GLFW directory to `lib/glfw`:

  * All files in `include/GLFW`
  * `lib-vc2013/glfw3.lib`

8. Copy `bin/Release/Win32/glew32.dll` from your unzipped GLEW directory to your project root directory.

9. In Visual Studio, open your project property pages, set the configuration to "All Configurations", and go to Configuration Properties.

  * Under Linker/General, set "Additional Library Directories" to `lib/glew;lib/glfw`.
  * Under Linker/Input, add `opengl32.lib;glu32.lib;glew32.lib;glfw3.lib;` to the beginning of "Additional Dependencies".
  * Under VC++ Directories, add `src;lib;` to the beginning of "Include Directories".
  * (Optional) Under Linker/System, set "SubSystem" to `Windows (/SUBSYSTEM:WINDOWS)`.
  * (Optional) Under Linker/Advanced, set "Entry Point" to `mainCRTStartup`.
