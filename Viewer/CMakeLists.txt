cmake_minimum_required(VERSION 3.5)

project(CurrentViewer VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGL)

add_definitions(-DGL_SILENCE_DEPRECATION)


set(PROJECT_SOURCES
        main.cpp
        view/mainwindow.cpp
        view/mainwindow.h
        view/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CurrentViewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        QtGifImage/gifimage/qgifglobal.h
        QtGifImage/gifimage/qgifimage.cpp
        QtGifImage/gifimage/qgifimage.h
        QtGifImage/gifimage/qgifimage_p.h
        QtGifImage/giflib/dgif_lib.c
        QtGifImage/giflib/egif_lib.c
        QtGifImage/giflib/gif_err.c
        QtGifImage/giflib/gif_font.c
        QtGifImage/giflib/gif_hash.c
        QtGifImage/giflib/gif_hash.h
        QtGifImage/giflib/gif_lib.h
        QtGifImage/giflib/gif_lib_private.h
        QtGifImage/giflib/gifalloc.c
        QtGifImage/giflib/quantize.c
        myopenglwidget.h
        view/myopenglwidget.cpp
        controller/controller.h
        controller/controller.cc
        model/model.h
        model/affine.cc
        model/parser.cc
        memento/memento.h
        memento/memento.cc
        model/vertex.cc
        model/polygon.cc
        model/point.cc
        model/viewerSupport.cc
        command/command.h
        command/command.cc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CurrentViewer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CurrentViewer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CurrentViewer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CurrentViewer PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::OpenGL
    Qt${QT_VERSION_MAJOR}::OpenGLWidgets
    Qt${QT_VERSION_MAJOR}::Widgets
)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CurrentViewer)
endif()
set_target_properties(CurrentViewer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CurrentViewer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CurrentViewer)
endif()
