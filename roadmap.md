# Couch, the Last Bastion of Interactive Arts Co-operation

## Technical Specifications
- OpenGL is the only officially supported backend
- GLEW to wrangle extensions
- GLFW3 for handling windows and whatnot
- Targets Windows, Linux
- ~~Guile with GOOPS as scripting language~~ ~~Lua is the scripting language with Guile as a stretch goal~~
- Python?
- No editor planned

## Roadmap
### Programmable Balls
I want my balls to be programmable, I need to create a few key classes
1. Balls, duh
2. Transforms, which represent position (of my balls)
3. Camera, to look at my balls
4. Shaders, to render my balls
### Programmable Balls Postmortem
Everything seems to work, but we need a system of what goes in the scene
I think a scene tree like the one in Godot would be cool

I keep switching scripting languages, can I make it so it's programmable in many languages, switchable via command line?
