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

set_source_files_properties(qml/GlobalStyle.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(MultiChannelMonitor
        URI MultiChannelMonitor
        VERSION 1.0
        QML_FILES
        qml/GlobalStyle.qml
        qml/Main.qml
        qml/ChannelCard.qml
        qml/ControlBar.qml
        qml/MultiChannelChart.qml
        qml/Notification.qml
        qml/ThresholdEditor.qml
        qml/ThresholdRow.qml
        SOURCES
        src/measurement_channel.h
        src/measurement_channel.cpp
        src/acquisition_engine.h
        src/acquisition_engine.cpp
        src/acquisition_worker.cpp
        src/acquisition_worker.h
        src/notifications_model.cpp
        src/notifications_model.h
)

target_link_libraries(MultiChannelMonitor PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        Qt6::QuickControls2
        Qt6::Graphs
)

enable_testing()
add_subdirectory(tests)