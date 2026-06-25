cmake_minimum_required(VERSION 3.16)
project(MultiChannelMonitor LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 Graphs)

qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)

qt_add_executable(MultiChannelMonitor
        src/main.cpp
)

target_include_directories(MultiChannelMonitor PRIVATE src)


set_target_properties(MultiChannelMonitor PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
)

set_source_files_properties(qml/Style.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(MultiChannelMonitor
        URI MultiChannelMonitor
        VERSION 1.0
        QML_FILES
        qml/Style.qml
        qml/Main.qml
        qml/ChannelCard.qml
        qml/ControlBar.qml
        qml/MultiChannelChart.qml
        qml/Notification.qml
        SOURCES
        src/measurementchannel.h
        src/measurementchannel.cpp
        src/acquisitionengine.h
        src/acquisitionengine.cpp
        src/acquisitionworker.cpp
        src/acquisitionworker.h
        src/NotificationsModel.cpp
        src/NotificationsModel.h
)

target_link_libraries(MultiChannelMonitor PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        Qt6::QuickControls2
        Qt6::Graphs
)