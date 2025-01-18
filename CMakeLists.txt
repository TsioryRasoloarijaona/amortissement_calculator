cmake_minimum_required(VERSION 3.19)
project(amortissement_app LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Sql)

qt_standard_project_setup()

qt_add_executable(amortissement_app
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    head/materiel.h source/materiel.cpp
    head/db_manager.h source/db_manager.cpp
    head/amortissement_lineaire.h source/amortissement_lineaire.cpp
    head/amortissement_degressif.h source/amortissement_degressif.cpp
    icons/img.qrc
)

qt_add_resources(PROJECT_RESOURCES icons/img.qrc)
target_sources(amortissement_app PRIVATE ${PROJECT_RESOURCES})


target_link_libraries(amortissement_app
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
)

include(GNUInstallDirs)

install(TARGETS amortissement_app
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET amortissement_app
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})


