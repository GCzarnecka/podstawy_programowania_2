add_executable (template main.cpp)

add_custom_target(run_template DEPENDS template
    COMMAND
        ${CMAKE_CURRENT_BINARY_DIR}/template
)