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

### Windows Compatible
I want to be able to build this for Windows
- I have no clue what that entails
- CMake?
- How to run SWIG on windows?

### Windows Compatible Postmortem
Pretty brittle as a result of needing to download Windows binaries, but it works
Eventually, we might need to include the source files as submodules, and build them all with CMake
For now, what we've got is good

### Better error messages
Okay, now I want a message other than "main.lua not found!" if the lua file fucks up.
Also, I want Lua errors to kill the program with an error message and a stack trace.

### Added model importing
I did this without writing about it in the roadmap. I still want to add a way to get multiple meshes on the same model, but 
I'll save skeletal animation until we have a working physics system

### Refactoring pass
I want to clean things up and see if some of the code can be combined into multiple files.
Also, I want a better user experience, so I might wind up removeing the %includes from the 
swig files and customizing the interface by hand. I also want to add a whole mess of constants
so that I don't have to test for keypresses. Lastly, I want to test if a function exists before
calling it from the lua file, so stubs aren't necessary to prevent a crash

- [x] Combine files
- [x] Better interface
- [x] Constants for keys and the like
- [x] No crash on calling non-existant scripting hooks

## Lighting
I'm a bit happier with the system now, I think it's time I started the lighting.
We're going to use a pretty basic Phong lighting system, with 
Flat and Garourd shaders available (This was all that was available on the PSX!)

## Bump in the road (1/23/21)
Not sure where to go next. I changed to using OBJ files for meshes, which I might need 
to revert (shitty animation support). There are a number of systems I want to add next
- GUI (dearimgui or Nuklear) (Maybe expose a raw opengl context for these?)
- Physics engine (Bullet)
- Animation system
- General code cleanup
- Scene editor
- Rest of lighting engine (point lights, spotlights)
- Audio engine

## Physics
Yeah sure let's do physics
- [x] Static, Kinematic and Rigidbodies
- [x] Collision areas
- [ ] Ray tracing
- [x] Axis pinning

## Great Refactor
Things are starting to smell, here's what I need to do
- [ ] Replace all public attributes with accessors (on classes)
- [x] Seperate prefabs from instances
- [ ] Combine related files (shaders)
- [ ] ~~Create a testing suite~~ Let's be real here...
- [x] Have exceptions thrown to Lua if generated from a user program

## More lights
The great refactor continues, and I will incrementally make progress, 
but this project is going to die on the vine if I don't get motivated, and
motivation comes from new features.
- [x] Point Light
- [ ] ~~Spot Light~~ Ehhh who cares...
- [ ] Shadows

## Fix the damn Windows
- [x] Compiles for windows
DLL Hell is still an issue, I have to distribute like 30 of them. Might go back to 
simply including them in the package.
