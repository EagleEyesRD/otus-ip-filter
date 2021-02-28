cmake_minimum_required(VERSION 3.5)

if($ENV{TRAVIS_BUILD_NUMBER})
    project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(ip_filter VERSION 0.0.1)
endif()

configure_file(basefuncs.h basefuncs.h)
configure_file(version.h.in version.h)

add_executable(ip_filter_cli main.cpp)
add_library(ip_filter lib.cpp)
add_executable(test_version test_version.cpp) 
set_target_properties(ip_filter_cli ip_filter test_version  PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)
set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(ip_filter_cli PRIVATE
    ip_filter
)
target_link_libraries(test_version
    ${Boost_LIBRARIES}
    ip_filter
)
 


if (MSVC)
    target_compile_options(ip_filter_cli PRIVATE
        /W4
    )
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(test_version PRIVATE
        /W4
    ) 
else ()
    target_compile_options(ip_filter_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    
endif()



install(TARGETS ip_filter RUNTIME DESTINATION bin)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_GENERATOR DEB)

set(CPACK_SET_DESTDIR ON)
set(CPACK_PACKAGE_CONTACT mkubyshkin@internet.ru)

include(CPack)
enable_testing()

add_test(test_version test_version) 

