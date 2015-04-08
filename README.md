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

3. Click "Show All Files" in Solution Explorer. Select and right-click the following files and folders, then click "Include in
Project".

  * `src`
  * `lib/glad/src/glad.c`
  * `lib/glad/include/glad/glad.h`
  * `lib/glad/include/KHR/khrplatform.h`

4. Open `lib/glad/src/glad.c` and replace all occurrences of `sscanf` with `sscanf_s`.

5. Download [GLFW](http://sourceforge.net/projects/glfw/files/glfw/3.1.1/glfw-3.1.1.bin.WIN32.zip/download). Unzip it into a
folder called `lib/glfw` in your project directory.

6. Download [glad](https://github.com/Dav1dde/glad/archive/c.zip). Unzip it into a folder called `lib/glad` in your project
directory.

7. In Visual Studio, open your project property pages, set the configuration to "All Configurations", and go to Configuration
Properties.

  * Under VC++ Directories, add `src;lib/glfw/include;lib/glad/include;` to the beginning of "Include Directories".

8. Go to Linker.

  * Under General, set "Additional Library Directories" to `lib/glfw/lib-vc2013`.
  * Under Input, add `opengl32.lib;glfw3.lib;` to the beginning of "Additional Dependencies".

9. (Optional) To prevent creation of a console window in Release configuration, set the configuration to "Release".

  * Under System, set "SubSystem" to `Windows (/SUBSYSTEM:WINDOWS)`.
  * Under Advanced, set "Entry Point" to `mainCRTStartup`.
