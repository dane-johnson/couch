find_package(SWIG REQUIRED)
include(UseSWIG)
set_property(SOURCE couch.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE couch.i PROPERTY USE_TARGET_INCLUDE_DIRECTORIES ON)

if (LUA_ENABLED)
  swig_add_library(couchlua
    TYPE STATIC
    LANGUAGE lua
    SOURCES couch.i lua/helpers.i)

  target_include_directories(couchlua PRIVATE "${PROJECT_SOURCE_DIR}/core")

  swig_link_libraries(couchlua
    PRIVATE
    couchlib
    ${LUA_LIBRARIES})
endif ()

if (GUILE_ENABLED)
  swig_add_library(couchguile
    TYPE STATIC
    LANGUAGE guile
    SOURCES couch.i)

  target_include_directories(couchguile PRIVATE "${PROJECT_SOURCE_DIR}/core")

  swig_link_libraries(couchguile
    PRIVATE
    couchlib
    ${GUILE_LIBRARIES})
endif ()
