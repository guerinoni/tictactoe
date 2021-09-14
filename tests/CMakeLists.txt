find_package(QT NAMES Qt6 Qt5 COMPONENTS Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test REQUIRED)

set(PROJECT_SOURCES
        ../src/Game.cpp
        ../src/Game.hpp
        matchDecision3x3.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tests
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(tests ${PROJECT_SOURCES})
endif()

target_link_libraries(tests PRIVATE Qt${QT_VERSION_MAJOR}::Test)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(tests)
endif()

add_test("tests" tests)
