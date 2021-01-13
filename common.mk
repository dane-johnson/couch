CXX = g++
CXXFLAGS = `pkg-config --cflags gl glew glfw3 guile-2.2` -g
LIBS = `pkg-config --libs gl glew glfw3 guile-2.2`
