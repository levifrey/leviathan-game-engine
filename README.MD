Leviathan Game Engine:

Description: 
A personally developed project Game Engine that can be easily interfaced through C++.
Following the steps from https://learnopengl.com/ but consolidated to make a useful tool.

# features:
 - OpenGL Rendering
 - custom models
 - custom textures
 - custom shaders
 - render effects
 - custom game object behaviors
 - keyboard, mouse input handling
 - 4 types of lights

# Requirements:
 - cmake 3.5+
 - OpenGL 4.6
 - assimp

# Build 
 > bash build.sh

(run sample program)
 > ./build/sample

(run custom program)
 - Write program as FILENAME .cpp in games folder
 > ./build/FILENAME

(to remake)
 - will recompile all games
 > bash make.sh

 - will recompile and run (recommended)
 > bash run.sh FILENAME



