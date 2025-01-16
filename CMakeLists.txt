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
    materiel.h materiel.cpp
    db_manager.h db_manager.cpp
    amortissement_lineaire.h amortissement_lineaire.cpp
    amortissement_degressif.h amortissement_degressif.cpp
    time.qrc
    stat.qrc
    barChart.qrc
    timer.qrc
    material.qrc
    calendar.qrc
    download.qrc
    titleIcon.qrc
    title_.qrc

    next.qrc
    right_.qrc

    list.qrc
    back.qrc



)



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
