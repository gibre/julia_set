project(julia_set)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(./src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.1 REQUIRED system window graphics)
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
