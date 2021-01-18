project(Couch)

file(GLOB shaders *.vert *.frag)
list(
  TRANSFORM shaders
  APPEND .h
  OUTPUT_VARIABLE shader_header_files)

add_custom_target(shader_headers
  BYPRODUCTS ${shader_header_files}
  COMMAND perl "${CMAKE_CURRENT_SOURCE_DIR}/makeheaders.pl"
  DEPENDS ${shaders} ${CMAKE_CURRENT_SOURCE_DIR}/makeheaders.pl)

add_dependencies(couch shader_headers)
