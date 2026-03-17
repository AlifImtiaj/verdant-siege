cmake_minimum_required(VERSION 3.15)

project(Siege)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC_FILE src/*.cpp)
file (GLOB IMGUI_SRC vendor/imgui/include/*.cpp)

# add_executable(${PROJECT_NAME} WIN32 main.cpp ${SRC_FILE} icon.rc)
add_executable(${PROJECT_NAME} main.cpp ${SRC_FILE} ${IMGUI_SRC} icon.rc)

target_include_directories(${PROJECT_NAME} PRIVATE
${CMAKE_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/vendor/sfml/include
${CMAKE_SOURCE_DIR}/vendor/imgui/include
)

target_link_directories(${PROJECT_NAME} PRIVATE
${CMAKE_SOURCE_DIR}/vendor/sfml/lib
)

target_link_libraries(${PROJECT_NAME}
opengl32
sfml-window
sfml-graphics
sfml-system
)