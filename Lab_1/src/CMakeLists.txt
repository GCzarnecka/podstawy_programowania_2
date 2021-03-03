add_executable (lab_1 main.cpp)

add_custom_target(run_lab_1 DEPENDS lab_1
    COMMAND
        ${CMAKE_CURRENT_BINARY_DIR}/lab_1
)