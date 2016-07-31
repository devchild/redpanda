#
# Generate the parser using flex and bison
#
FIND_PACKAGE(FLEX REQUIRED)
SET(FlexOutput ${CMAKE_CURRENT_BINARY_DIR}/scanner.c)
IF(FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
      OUTPUT ${FlexOutput}
      COMMAND ${FLEX_EXECUTABLE}
              --outfile=${FlexOutput}
              ${CMAKE_CURRENT_SOURCE_DIR}/scanner.l
      COMMENT "Generating scanner.c"
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/scanner.l
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
ENDIF()
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/scanner.c GENERATED)

FIND_PACKAGE(BISON REQUIRED)
SET(BisonOutput ${CMAKE_CURRENT_BINARY_DIR}/parser.c)
SET(BisonOutputHeader ${CMAKE_CURRENT_BINARY_DIR}/parser.h)
IF(BISON_FOUND)
    ADD_CUSTOM_COMMAND(
      OUTPUT ${BisonOutput}
      COMMAND ${BISON_EXECUTABLE}
              --defines=${BisonOutputHeader}
              --output=${BisonOutput}
              ${CMAKE_CURRENT_SOURCE_DIR}/parser.y
      COMMENT "Generating parser.c"
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/parser.y
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
ENDIF()
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/parser.c GENERATED)
SET_SOURCE_FILES_PROPERTIES(${FlexOutput} PROPERTIES OBJECT_DEPENDS ${BisonOutputHeader})


set(PROJECT_FILES
	${PROJECT_FILES}
	${BisonOutput}
	${FlexOutput}
	)

add_library(libsnowball SHARED ${PROJECT_FILES})

set_target_properties(libsnowball PROPERTIES
	LINKER_LANGUAGE C
	MACOSX_RPATH TRUE
	INSTALL_NAME_DIR "@rpath"
	OUTPUT_NAME snowball
	INSTALL_RPATH_USE_LINK_PATH TRUE
	)


