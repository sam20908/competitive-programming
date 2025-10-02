find_package(Python COMPONENTS Interpreter REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("../library/cpp")

function(add_library_test name)
    add_executable(${name}_program "program/${name}.cpp")
    add_executable(${name}_solution "solution/${name}.cpp")

    add_test(NAME ${name}
            COMMAND ${Python_EXECUTABLE} -m test.checker.${name} -p $<TARGET_FILE:${name}_program> -s $<TARGET_FILE:${name}_solution>
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        )
endfunction()

add_library_test("heavy_light_decomposition")
add_library_test("mo_array")
add_library_test("segment_tree")
add_library_test("segment_tree_lazy")
add_library_test("treap")
