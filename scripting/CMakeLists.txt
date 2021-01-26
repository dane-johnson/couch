include(UseSWIG)
set_property(SOURCE couch.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE couch.i PROPERTY USE_TARGET_INCLUDE_DIRECTORIES ON)

if (NOT WIN32)
swig_add_library(couchlua
  TYPE SHARED
  LANGUAGE lua
  SOURCES couch.i lua/helpers.i)
else()
  swig_add_library(couchlua
  TYPE STATIC
  LANGUAGE lua
  SOURCES couch.i lua/helpers.i)
endif()

target_include_directories(couchlua PRIVATE "${PROJECT_SOURCE_DIR}/core")

swig_link_libraries(couchlua
  PRIVATE
  couchlib
  ${LUA_LIBRARIES})
