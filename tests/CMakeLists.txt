find_package(QT NAMES Qt6 COMPONENTS Test REQUIRED)
find_package(Qt6 COMPONENTS Test REQUIRED)

set(PROJECT_SOURCES
        ../src/Game.cpp
        ../src/Game.hpp
        matchDecision3x3.cpp
)

qt_add_executable(tests MANUAL_FINALIZATION ${PROJECT_SOURCES})

target_link_libraries(tests PRIVATE Qt6::Test)

qt_finalize_executable(tests)

add_test("tests" tests)
