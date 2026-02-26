add_executable(run_tests
    main_test.cpp
    TestElfParser.cpp
    TestElfBuilder.cpp
    TestBuilderComponents.cpp
    TestPlugins.cpp
)

target_include_directories(run_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(run_tests PRIVATE libelfparser)
