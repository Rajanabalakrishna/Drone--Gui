cmake_minimum_required(VERSION 3.16)

project(trial1 VERSION 0.1 LANGUAGES CXX)

# Enable Qt's automatic features
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt and required modules
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Charts Multimedia MultimediaWidgets Positioning Sensors)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts Multimedia MultimediaWidgets Positioning Sensors )

# Source files
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    speedometer.h
    speedometer.cpp
    speed.h
    speed.cpp
)

# Add the executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(trial1
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}


    )
else()
    if(ANDROID)
        add_library(trial1 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(trial1
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Link the required Qt libraries
target_link_libraries(trial1 PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Charts
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::MultimediaWidgets
    Qt${QT_VERSION_MAJOR}::Sensors
)

# macOS/iOS bundle settings
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.trial1)
endif()

set_target_properties(trial1 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Installation rules
include(GNUInstallDirs)
install(TARGETS trial1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize the executable for Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(trial1)
endif()
