add_executable(cfs-edac.it-test.steps
    cfs/edac/features/step_definitions/ErrorsTestSteps
)

target_link_libraries(cfs-edac.it-test.steps
    PUBLIC
        cfs-edac.main
        cfs-edac.test
        CUCUMBER-CPP::CUCUMBER-CPP
	##PUBLIC BENCHMARK::BENCHMARK
)

add_custom_target(start-cucumber-wireserver
    COMMAND cppbdd101.it-test.steps --port 3902  >/dev/null &
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Start cucumber's wireserver."
)

add_custom_target(cppbdd101.integration-test
    COMMAND cppbdd101.it-test.steps --port 3902  >/dev/null &
    COMMAND cucumber --format progress --backtrace --format html --color --out
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/cfs-edac-cucumber-report.html --strict ${CMAKE_CURRENT_SOURCE_DIR}/cfs/com/features
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Start wire server and run integration test."
)

