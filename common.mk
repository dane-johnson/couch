CXX := g++
CXXFLAGS := `pkg-config --cflags gl glew glfw3 lua` -fPIC -g
LIBS := `pkg-config --libs gl glew glfw3 lua`
