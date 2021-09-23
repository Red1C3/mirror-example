# Mirror-Example
A simple mirror example using OpenGL 3.3 with C++.
## Theory
It basically constructs a camera at the mirror location, by determining its view direction, and that's by reflecting the observer to mirror vector using the mirror normal, also the FOV of the mirror's capturing camera is determined by the observer's distance from the mirror.
## Usage
Make sure the executable is in the same directory as the Assets folder (not inside of it), and run the executable, WASD navigation is working.
## Building
Using Meson, or without if you know how you do it...
### Required dependencies:
- [SFML](sfml-dev.org/) (Window module at least)
- [GLEW](http://glew.sourceforge.net/)
- [Assimp](https://github.com/assimp/assimp)
- [GLM](https://github.com/g-truc/glm)

## License 
Under MIT, check [License](./LICENSE)

### Made with escaping-out-the-mirror kittens
