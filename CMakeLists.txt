cmake_minimum_required(VERSION 3.19)
project(Bank_App LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui sql Widgets)

qt_standard_project_setup()

qt_add_executable(Bank_App
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    initdb.h
    bankController.cpp
    bankController.h


)

target_link_libraries(Bank_App
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Sql
    Qt6::Widgets
)

include(GNUInstallDirs)

install(TARGETS Bank_App
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Bank_App
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
