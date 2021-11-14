find_package(QT NAMES Qt6 COMPONENTS Test REQUIRED)
find_package(Qt6 COMPONENTS Test REQUIRED)

set(PROJECT_SOURCES
        ../../src/Game.cpp
        ../../src/Game.hpp
        gameFinished.cpp
)

qt_add_executable(gameFinished MANUAL_FINALIZATION ${PROJECT_SOURCES})

target_link_libraries(gameFinished PRIVATE Qt6::Test)

qt_finalize_executable(gameFinished)

add_test("gameFinished" gameFinished)
