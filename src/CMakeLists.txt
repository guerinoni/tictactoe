find_package(QT NAMES Qt6 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        Game.cpp
        Game.hpp
)

qt_add_executable(tictactoe MANUAL_FINALIZATION ${PROJECT_SOURCES})

if(ANDROID)
    add_library(tictactoe SHARED ${PROJECT_SOURCES})
endif()

target_link_libraries(tictactoe PRIVATE Qt6::Core Qt6::Quick)

set_target_properties(tictactoe PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

qt_finalize_executable(tictactoe)
