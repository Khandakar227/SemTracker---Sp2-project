cmake_minimum_required(VERSION 3.5)

project(semTracker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES semTracker_bn_BD.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        questionstruct.h
        ${TS_FILES}
)
# App logo
set(APP_ICON_RESOURCE_WINDOWS "${PROJECT_SOURCE_DIR}/app_logo.ico")
set(CMAKE_RC_FLAGS "${CMAKE_RC_FLAGS} -i${APP_ICON_RESOURCE_WINDOWS} -O coff -o app_logo.res")

set(APP_ICON_RESOURCE_LINUX "${PROJECT_SOURCE_DIR}/app_logo.png")
set_source_files_properties(${APP_ICON_RESOURCE_LINUX} PROPERTIES
    HEADER_FILE_ONLY TRUE)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(semTracker
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET semTracker APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(semTracker SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(semTracker
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(semTracker PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_sources(semTracker PRIVATE ${APP_ICON_RESOURCE_LINUX})

set_target_properties(semTracker PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS semTracker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(semTracker)
endif()
