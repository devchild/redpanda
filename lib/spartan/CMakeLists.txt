#
# Generate the parser using flex and bison
#
FIND_PACKAGE(FLEX REQUIRED)
SET(FlexOutput ${CMAKE_CURRENT_BINARY_DIR}/scanner.c)
SET(FlexOutputHeader ${CMAKE_CURRENT_BINARY_DIR}/scanner.h)

IF(FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
      OUTPUT ${FlexOutput}
      COMMAND ${FLEX_EXECUTABLE}
	          --nounistd
              --outfile=${FlexOutput}
	      --header-file=${FlexOutputHeader}
              ${CMAKE_CURRENT_SOURCE_DIR}/scanner.l
      COMMENT "Generating scanner.c"
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/scanner.l
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
ENDIF()
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/scanner.c PROPERTIES
	GENERATED TRUE
	C_STANDARD 99)
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/scanner.h PROPERTIES
	GENERATED TRUE
	C_STANDARD 99)

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
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/parser.c PROPERTIES 
	GENERATED TRUE
	C_STANDARD 99)
SET_SOURCE_FILES_PROPERTIES(${FlexOutput} PROPERTIES OBJECT_DEPENDS ${BisonOutputHeader})
SET_SOURCE_FILES_PROPERTIES(${FlexOutputHeader} PROPERTIES OBJECT_DEPENDS ${BisonOutputHeader})

SET(HEADER_FILES
  ../../include/ast.h
)

set(PROJECT_FILES
	${HEADER_FILES}
	${PROJECT_FILES}
	${BisonOutput}
	${FlexOutput}
	spartan.c
	ast.c
	)

include_directories(
	../../include
	${CMAKE_CURRENT_BINARY_DIR}
	)

add_library(libspartan SHARED ${PROJECT_FILES})

set_target_properties(libspartan PROPERTIES
	LINKER_LANGUAGE C
	MACOSX_RPATH TRUE
	INSTALL_NAME_DIR "@rpath"
	OUTPUT_NAME snowball
	INSTALL_RPATH_USE_LINK_PATH TRUE
	)


