project(Couch)

macro(add_shader shaderfile)
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${shaderfile}.h
    COMMAND perl "${CMAKE_CURRENT_SOURCE_DIR}/makeheaders.pl" ${CMAKE_CURRENT_SOURCE_DIR}/${shaderfile} ${CMAKE_CURRENT_BINARY_DIR}/${shaderfile}.h
    DEPENDS ${shaderfile} makeheaders.pl
    )
endmacro()

add_shader(flat.vert)
add_shader(flat.frag)
add_shader(screen.vert)
add_shader(screen.frag)

add_custom_target(shader_headers
  DEPENDS flat.vert.h flat.frag.h screen.vert.h screen.frag.h
  COMMENT "Generated shaders headers.")
