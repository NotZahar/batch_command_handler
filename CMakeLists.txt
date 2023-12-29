cmake_minimum_required(VERSION 3.21)

set(PATCH_VERSION 1 CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project("bulk" VERSION ${PROJECT_VESRION})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_subdirectory(libs)

add_executable(${PROJECT_NAME})
add_executable(bulk_tests
    tests/bulk.cpp
)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.cpp
)

target_include_directories(bulk_tests 
    PRIVATE 
        ${GTEST_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        BatchCommandHandler)
target_link_libraries(bulk_tests 
    PRIVATE 
        ${GTEST_BOTH_LIBRARIES} BatchCommandHandler)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -pedantic)
    target_compile_options(bulk_tests PRIVATE -Wall -Wextra -Werror -pedantic)
endif()

# generate deb
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()
add_test(NAME bulk_tests COMMAND bulk_tests)