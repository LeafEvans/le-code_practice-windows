cmake_minimum_required(VERSION 3.19)

project(AeroplaneWars VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找并包含Qt6，特别指定Widgets和Multimedia组件
find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)

set(PROJECT_SOURCES WIN32
        main.cpp
        mainscene.cpp
        mainscene.h
        config.h
        Map.h
        Map.cpp
        HeroPlane.h
        HeroPlane.cpp
        Bullet.h
        Bullet.cpp
        EnemyPlane.h
        EnemyPlane.cpp
        Bomb.h
        Bomb.cpp
        ${TS_FILES}
        logo.rc
)

# 使用qt_add_executable创建可执行文件，确保包含Multimedia模块
qt_add_executable(AeroplaneWars
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        res.qrc
)

# Android平台的特定属性
if(ANDROID)
        set_property(TARGET AeroplaneWars APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
                ${CMAKE_CURRENT_SOURCE_DIR}/android)
        set_target_properties(AeroplaneWars PROPERTIES
                MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
                MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
                MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
                MACOSX_BUNDLE TRUE
                WIN32_EXECUTABLE TRUE
        )
endif()

# 链接到Widgets和Multimedia模块
target_link_libraries(AeroplaneWars PRIVATE Qt6::Widgets Qt6::Multimedia)

# 设置iOS/macOS平台的属性
if(APPLE)
        set(BUNDLE_ID "com.example.AeroplaneWars") # 明确的bundle标识符
        set_target_properties(AeroplaneWars PROPERTIES
                MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
                MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
                MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
                MACOSX_BUNDLE TRUE
                WIN32_EXECUTABLE TRUE
        )
endif()

# 在设置完所有属性后最终化目标
qt_finalize_target(AeroplaneWars)

include(GNUInstallDirs)
install(TARGETS AeroplaneWars
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)