find_package(Qt6 REQUIRED COMPONENTS Test)

set(CORE_SOURCES
        ${CMAKE_SOURCE_DIR}/src/measurement_channel.cpp
        ${CMAKE_SOURCE_DIR}/src/measurement_channel.h
        ${CMAKE_SOURCE_DIR}/src/acquisition_engine.cpp
        ${CMAKE_SOURCE_DIR}/src/acquisition_engine.h
        ${CMAKE_SOURCE_DIR}/src/acquisition_worker.cpp
        ${CMAKE_SOURCE_DIR}/src/acquisition_worker.h
        ${CMAKE_SOURCE_DIR}/src/notifications_model.cpp
        ${CMAKE_SOURCE_DIR}/src/notifications_model.h
)

function(add_monitor_test test_name)
    qt_add_executable(${test_name} ${test_name}.cpp ${CORE_SOURCES})
    target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR}/src)
    target_link_libraries(${test_name} PRIVATE
            Qt6::Core
            Qt6::Qml
            Qt6::Test
    )
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

add_monitor_test(tst_measurementchannel)
add_monitor_test(tst_notificationsmodel)
add_monitor_test(tst_acquisitionworker)
