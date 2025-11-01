cmake_minimum_required(VERSION 3.15)
project(WarCardGame CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Main app ---
add_executable(WarGame
    MainDriver.cpp
    CardClass.cpp
    DeckClass.cpp
    StackClass.cpp
    GameClass.cpp
    OutputClass.cpp
)