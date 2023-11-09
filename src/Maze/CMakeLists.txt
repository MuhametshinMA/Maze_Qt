cmake_minimum_required(VERSION 3.5)

project(Maze VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(
    ${CMAKE_SOURCE_DIR}/view
    ${CMAKE_SOURCE_DIR}/controller
    ${CMAKE_SOURCE_DIR}/model
    ${CMAKE_SOURCE_DIR}/canvas
)

set(PROJECT_SOURCES
        ${CMAKE_SOURCE_DIR}/main.cc
        ${CMAKE_SOURCE_DIR}/view/view.h
        ${CMAKE_SOURCE_DIR}/view/view.cc
        ${CMAKE_SOURCE_DIR}/view/view.ui
        ${CMAKE_SOURCE_DIR}/view/paintwidget.h
        ${CMAKE_SOURCE_DIR}/view/paintwidget.cc
        ${CMAKE_SOURCE_DIR}/canvas/figure.h
        ${CMAKE_SOURCE_DIR}/canvas/figurefactory.h        
        ${CMAKE_SOURCE_DIR}/canvas/figureparams.h
        ${CMAKE_SOURCE_DIR}/canvas/canvasmaze.h
        ${CMAKE_SOURCE_DIR}/canvas/canvasmaze.cc
        ${CMAKE_SOURCE_DIR}/canvas/painter.h        
        ${CMAKE_SOURCE_DIR}/canvas/canvascave.h
        ${CMAKE_SOURCE_DIR}/canvas/canvascave.cc
        ${CMAKE_SOURCE_DIR}/controller/icontroller.h
        ${CMAKE_SOURCE_DIR}/controller/controllermaze.h
        ${CMAKE_SOURCE_DIR}/controller/controllermaze.cc
        ${CMAKE_SOURCE_DIR}/controller/controllercave.h
        ${CMAKE_SOURCE_DIR}/controller/controllercave.cc
        ${CMAKE_SOURCE_DIR}/controller/controllerfactory.h
        ${CMAKE_SOURCE_DIR}/model/maze.h
        ${CMAKE_SOURCE_DIR}/model/maze.cc
        ${CMAKE_SOURCE_DIR}/model/generate_maze.cc
        ${CMAKE_SOURCE_DIR}/model/checkmaze.h
        ${CMAKE_SOURCE_DIR}/model/checkmaze.cc
        ${CMAKE_SOURCE_DIR}/model/position.h
        ${CMAKE_SOURCE_DIR}/model/position.cc
        ${CMAKE_SOURCE_DIR}/model/path.h
        ${CMAKE_SOURCE_DIR}/model/path.cc
        ${CMAKE_SOURCE_DIR}/model/filemanager.h
        ${CMAKE_SOURCE_DIR}/model/filemanager.cc
        ${CMAKE_SOURCE_DIR}/model/cave.h
        ${CMAKE_SOURCE_DIR}/model/cave.cc
        ${CMAKE_SOURCE_DIR}/model/cave_data.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Maze
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Maze APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Maze SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Maze
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Maze PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Maze PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Maze)
endif()
