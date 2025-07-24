cmake_minimum_required(VERSION 3.10)

project(BowlingGame
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
set(SOURCES
    src/frame_base.cpp
    src/regular_frame.cpp
    src/tenth_frame.cpp
    src/score_calculator.cpp
    src/bowling_game.cpp
    src/file_reader.cpp
    src/game_controller.cpp
)
add_executable(${PROJECT_NAME}
    main.cpp
    ${SOURCES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

add_definitions(-DDATA_PATH="${CMAKE_SOURCE_DIR}/data")