# Cmake 最低版本要求
cmake_minimum_required(VERSION 3.16)
# 设置项目名称和版本
project(EyeTracking VERSION 0.1 LANGUAGES CXX)
# 设置自动处理 Qt 的 UI、MOC 和 RCC 文件
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 查找 Qt 库
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
# 查找 OpenCV 库
find_package(OpenCV REQUIRED)
# 添加源文件和头文件
set(PROJECT_SOURCES
    src/main.cpp
    src/widget.cpp
    include/widget.h
    src/widget.ui
)
# 创建可执行文件
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(EyeTracking
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Qt 6 自动处理 iOS 和 macOS 的 bundle 设置
else()
    if(ANDROID)
        add_library(EyeTracking SHARED
            ${PROJECT_SOURCES}
        )
# iOS 和 macOS 平台使用 MACOSX_BUNDLE 选项
    else()
        add_executable(EyeTracking
            ${PROJECT_SOURCES}
        )
    endif()
endif()
# 链接 Qt 库
target_link_libraries(EyeTracking PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
# 链接 OpenCV 库
target_link_libraries(EyeTracking PRIVATE ${OpenCV_LIBS})
# 设置包含目录
target_include_directories(EyeTracking PRIVATE include)
# 设置应用程序的 bundle 属性（仅适用于 macOS）
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.EyeTracking)
endif()
set_target_properties(EyeTracking PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
# 安装目标
include(GNUInstallDirs)
install(TARGETS EyeTracking
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
# Finalize the executable for Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(EyeTracking)
endif()