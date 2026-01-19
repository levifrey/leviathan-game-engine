# graphics
practicing creating simple graphics program

How to create a basic game on Levi's engine:
Development is all done within a c++ file, and external files for components and behaviors

# start game file
- In the header, include <glm/glm.hpp> and "Engine.h", this is all you should need 
- create a .cpp file with a main function:
- create a Game object using desired pixel width, height

# create camera
- create a PlayerCamera object, passing in a pointer to the game object
- add the camera object to the game with game.addObject(&camera)
- set current game camera with game.setCamera(camera.getComponent<Camera>());

# shaders
- create a Shader object passing in the .vert, .frag file locations
- If the texture uses textures, use .reserve(texture name, #id)

# game objects
- create a game object using GameObject(&game)
- add desired components, recommended Transform and Renderer
- call game.addGameObject(&go) for every object

# start game
- call game.Loop() to begin


- 
