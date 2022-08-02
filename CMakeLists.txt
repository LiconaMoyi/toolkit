cmake_minimum_required(VERSION 3.5)

project(toolkit VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools sql statemachine)

set(TS_FILES toolkit_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp
        widget.h
        widget.cpp
        qtcookbook.h
        qtcookbook.cpp
        moyi-ui/lib/moyitheme.h
        moyi-ui/lib/moyitheme_p.h
        moyi-ui/lib/moyitheme.cpp
        moyi-ui/lib/moyistyle.h
        moyi-ui/lib/moyistyle.cpp
        moyi-ui/lib/moyistyle_p.h
        moyi-ui/lib/moyioverlaywidget.h
        moyi-ui/lib/moyioverlaywidget.cpp
        moyi-ui/lib/moyistatetransitionevent.h
        moyi-ui/lib/moyistatetransition.h
        moyi-ui/lib/moyistatetransition.cpp
        moyi-ui/moyislider_p.h
        moyi-ui/moyislider_internal.h
        moyi-ui/moyislider_internal.cpp
        moyi-ui/moyislider.h
        moyi-ui/moyislider.cpp
        moyi-ui/moyicircularprogress_p.h
        moyi-ui/moyicircularprogress_internal.h
        moyi-ui/moyicircularprogress_internal.cpp
        moyi-ui/moyicircularprogress.h
        moyi-ui/moyicircularprogress.cpp
        moyi-ui/moyipushbutton.h
        moyi-ui/moyipushbutton.cpp
        image.qrc
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(toolkit
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET toolkit APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(toolkit SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(toolkit
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(toolkit PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(toolkit PRIVATE Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(toolkit PRIVATE Qt${QT_VERSION_MAJOR}::StateMachine)

set_target_properties(toolkit PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(toolkit)
endif()
