# Block Game

A game that involves blocks.

## Supported platforms

The following platforms are "officially" supported by this project. If you are using a different platform that you would like
this project to support, create a pull request with at least the appropriate addition to this section of the README, and I'll
work with you to add support for that platform.

* Visual Studio 2013

## Setup instructions

### Visual Studio 2013

1. Clone this repository to your machine.

2. In Visual Studio, create a new Visual C++ Empty Project, with the correct location and name according to the previous step.
Be sure to leave the "Create directory for solution" box unchecked.

3. Click "Show All Files" in Solution Explorer. Right-click `src`, then click "Include In Project".

4. Download [GLEW](http://sourceforge.net/projects/glew/files/glew/1.12.0/glew-1.12.0-win32.zip/download) and
[GLFW](http://sourceforge.net/projects/glfw/files/glfw/3.1.1/glfw-3.1.1.bin.WIN32.zip/download). Unzip them somewhere outside of
your project directory.

5. Copy `bin/Release/Win32/glew32.dll` from your unzipped GLEW directory to your project root directory.

6. In your project directory, create directories `lib/GL` and `lib/GLFW`.

7. Copy these files from your unzipped GLEW directory to `lib/GL`:

  * All files in `include/GL`
  * `lib/Release/Win32/glew32.lib`

8. Copy these files from your unzipped GLFW directory to `lib/GLFW`:

  * All files in `include/GLFW`
  * `lib-vc2013/glfw3.lib`

9. In Visual Studio, open your project property pages, set the configuration to "All Configurations", and go to Configuration
Properties.

  * Under VC++ Directories, add `src;lib;` to the beginning of "Include Directories".

10. Go to Linker.

  * Under General, set "Additional Library Directories" to `lib/GL;lib/GLFW`.
  * Under Input, add `opengl32.lib;glew32.lib;glfw3.lib;` to the beginning of "Additional Dependencies".

11. (Optional) To prevent creation of a console window in Release configuration, set the configuration to "Release".

  * Under System, set "SubSystem" to `Windows (/SUBSYSTEM:WINDOWS)`.
  * Under Advanced, set "Entry Point" to `mainCRTStartup`.
