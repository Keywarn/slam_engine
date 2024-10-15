# slam_engine

![image](https://github.com/user-attachments/assets/b831df6b-dc0d-4c03-9db3-b0fccc8cdb54)

I have (sort of) structured the project in such a way that it is modular and easily extended, similar-ish in strucutre for something that might be used in say, a game engine. However, in its current form, it mostaly an OpenGL based renderer. This project is mostly a learning resource and as such does not follow any strict styles/format/rules and code might not be the tidiest.

# Installation
## Requirements
- Visual Studio 17 2022
- CMake 3.26 or newer

## Building
- To generate a solution, run `generate_vs2022.bat` from the root folder of the repo
- This will create a project structure in the `generated` folder. The solution can be found in `slam_engine\generated\vs2022`
- Set the `game_sample` project as the Startup Project from the solution view and build/run in either config
- The project builds out-of-source to a `build` folder. (You can clear the `build`/`generated` folder safely)

## Creating your own game (currently not much functionality)
- Files/code for your game should go in a game specific folder similar to the `game_sample` included in the repo
- You can add this this as a subdirectory in the `CMakeLists.txt` at the root of the repo
- I recommend copying the `game_sample` for a base structure or simply renaming it as needed (and editing the relevant line in the `CMakeLists.txt` to aid in folder/setup structure)

# How To
## Hotkeys

- `L` - toggle the wireframe rendering mode
- `C` - toggle cursor lock
- `Esc` - quit the application
