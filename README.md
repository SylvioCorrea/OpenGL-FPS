# OpenGL FPS template
In this Computer Graphics course assignment the goal was to create any kind of simple game or animation using OpenGL. I have chosen to build a first person shooter template of sorts to prove to myself that this could be done with basic trigonometry and linear algebra. 

It's as bare bones as you would expect! Physics update is tied to the framerate (I didn't know better then). OpenGL was setup for use on CodeBlocks so students wouldn't lose 95% of the assignment time trying to get it running. This uses "old " OpenGL, that is, the classic `begin`-`end` libraries that serious developers in the industry no longer use.

### Playing

TesteTemplate.exe opens the game (compiled for Windows).

Controls:

- **ESC** to quit at any time;
- **WASD keys** move around;
- **mouse** aims;
- **left mouse button** shoots at the blue objects.

Shooting blue objects turns then red and gives you points (number below your life bar on the top left). When shot, objects start behaving differently:

 - Spheres start chasing you;
 - Cubes target your current location and follow a curved path towards it, repeating once they reach their destination;
 - Octahedrons increase in size.

Fail condition is losing all your life. Your life bar is on the top left. You lose life when you touch any of the objects or step outside of the checkered floor. Losing all your life closes the game (lame, I know).

There's no winning condition.
