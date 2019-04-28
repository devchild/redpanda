#
# Generate the parser using flex and bison
#
FIND_PACKAGE(FLEX REQUIRED)
SET(FlexOutput ${CMAKE_CURRENT_BINARY_DIR}/scanner.c)
SET(FlexOutputHeader ${CMAKE_CURRENT_BINARY_DIR}/scanner.h)

IF (FLEX_FOUND)
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
ENDIF ()
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/scanner.c PROPERTIES
        GENERATED TRUE)
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/scanner.h PROPERTIES
        GENERATED TRUE)

FIND_PACKAGE(BISON REQUIRED)
SET(BisonOutput ${CMAKE_CURRENT_BINARY_DIR}/parser.c)
SET(BisonOutputHeader ${CMAKE_CURRENT_BINARY_DIR}/parser.h)
IF (BISON_FOUND)
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
ENDIF ()
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/parser.c PROPERTIES
        GENERATED TRUE)
SET_SOURCE_FILES_PROPERTIES(${FlexOutput} PROPERTIES OBJECT_DEPENDS ${BisonOutputHeader})
SET_SOURCE_FILES_PROPERTIES(${FlexOutputHeader} PROPERTIES OBJECT_DEPENDS ${BisonOutputHeader})

SET(HEADER_FILES
        ../../include/redpanda.h
        ../../include/stack.h
        ../../include/ast_node.h
        ../../include/object.h
        ../../include/ast_compile_unit.h
        ../../include/ast_compile_unit_member_list.h
        ../../include/ast_node_list.h
        ../../include/ast_statement_list.h
        ../../include/ast_primitive_expression.h
        ../../include/ast_binary_expression.h
        ../../include/ast_return_statement.h
        ../../include/ast_method.h
        ../../include/ast_declaration.h
        ../../include/ast_selection_statement.h
        ../../include/ast_compound_statement.h
        ../../include/ast_while_statement.h ../../include/ast_node_visitor.h ../../include/ast_printer.h ../../include/code_generator.h)

set(PROJECT_FILES
        ${HEADER_FILES}
        ${BisonOutput}
        ${FlexOutput}
        redpanda.c
        ast_node.c
        object.c
        ast_primitive_expression.c
        ast_binary_expression.c
        ast_compile_unit.c
        ast_compile_unit_member_list.c
        ast_compound_statement.c
        ast_declaration.c
        ast_method.c
        ast_node_list.c
        ast_return_statement.c
        ast_selection_statement.c
        ast_statement_list.c
        ast_while_statement.c
        ast_node_visitor.c ast_printer.c code_generator.c)

add_library(libredpanda SHARED ${PROJECT_FILES})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} ../../include)
target_link_libraries(libredpanda ${GLib_LIBRARY} ${GObject_LIBRARY})


set_target_properties(libredpanda PROPERTIES
        LINKER_LANGUAGE C
        C_STANDARD 99
        MACOSX_RPATH TRUE
        INSTALL_NAME_DIR "@rpath"
        OUTPUT_NAME redpanda
        INSTALL_RPATH_USE_LINK_PATH TRUE
        )


