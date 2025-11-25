OpenGL Shader Viewer
This project is a simple OpenGL application that allows you to view and switch between various fragment shaders. It's designed to render a fullscreen quad and apply a GLSL fragment shader to it, making it ideal for viewing shaders from platforms like Shadertoy.

Prerequisites
To build and run this project, you'll need the following libraries:

SDL2: A cross-platform development library for C and C++ that provides low-level access to audio, keyboard, mouse, and graphics hardware via OpenGL and Direct3D.

GLEW: The OpenGL Extension Wrangler Library. GLEW provides a convenient way to load and use OpenGL extensions on different operating systems.

You can typically install these via your system's package manager. For example:

On Ubuntu: sudo apt-get install libsdl2-dev libglew-dev

On macOS (with Homebrew): brew install sdl2 glew

On Windows: You'll need to download the development libraries from the SDL and GLEW websites and configure your IDE to link against them.


https://github.com/user-attachments/assets/693c4586-992d-40b8-839a-597c6551a714

![Untitled](https://github.com/user-attachments/assets/a0815260-fd75-4705-95b3-c2054c531232)

Building the Project
This project includes two C++ source files, loader.cpp and Main.cpp. A simple build command using g++ would look like this:

g++ -o shader_viewer Main.cpp loader.cpp -lSDL2 -lGLEW -lGL

This command compiles the source files, creates an executable named shader_viewer, and links the necessary SDL2, GLEW, and OpenGL libraries.

Usage
Place Shaders: After compiling, place your GLSL fragment shader files in the same directory as the executable. The program is configured to look for files named sh1.frag, sh2.frag, sh3.frag, and so on, as defined in Main.cpp.

Run the Application: Execute the compiled program: ./shader_viewer

Controls:

Right Arrow or Spacebar: Switch to the next shader in the list.

Left Arrow: Switch to the previous shader.

ESC or Close Window: Exit the application.

Code Structure
loader.cpp: Contains a single utility function, loadFile, which reads the contents of a text file into a C++ string.

Main.cpp: This is the main application file. It handles:

Initialization: Sets up an SDL window and an OpenGL context.

Shader Management: Includes functions to compile and link a GLSL shader program from a source string. It also defines a simple vertex shader for a fullscreen quad.

Rendering Loop: The main while loop handles user input, updates uniforms (iResolution and iTime), and draws the fullscreen quad with the active shader.

Shader Switching: The code manages a list of shader filenames and allows the user to switch between them by pressing the left or right arrow keys or the spacebar.

Cleanup: Properly cleans up all SDL and OpenGL resources before exiting.
