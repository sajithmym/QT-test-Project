cmake_minimum_required(VERSION 3.16)
project(QtLearningApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

# Enable Qt5 MOC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/TextEditor.cpp
    src/AboutDialog.cpp
    src/PreferencesDialog.cpp
)

set(HEADERS
    src/MainWindow.h
    src/TextEditor.h
    src/AboutDialog.h
    src/PreferencesDialog.h
)

set(UI_FILES
    ui/MainWindow.ui
    ui/AboutDialog.ui
    ui/PreferencesDialog.ui
)

set(RESOURCES
    resources/resources.qrc
)

add_executable(QtLearningApp ${SOURCES} ${HEADERS} ${RESOURCES})

target_link_libraries(QtLearningApp Qt5::Core Qt5::Widgets)

# Set output directory
set_target_properties(QtLearningApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)