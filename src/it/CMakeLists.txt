
set(FEATURE_TEST_FORMAT --format progress)  #--format pretty OR --format pretty --tags @wip OR ...
set(FEATURE_TEST_OPTION --backtrace --format html --color)


add_executable(cfs-edac.it-test.steps
    cfs/edac/features/step_definitions/ErrorsTestSteps
)

apply_style_targets_command(cfs-edac.it-test.steps ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(cfs-edac.it-test.steps
    PUBLIC
        cfs.edac.main
        #cfs-edac.test
        CUCUMBER-CPP::CUCUMBER-CPP
        ${Boost_LIBRARIES}
        #	    BENCHMARK::BENCHMARK
)

add_custom_target(cfs-edac.integration-test

    COMMAND
        ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/qa/test-result

    COMMAND
        ${CUCUMBER_BINARY} ${FEATURE_TEST_FORMAT} ${FEATURE_TEST_OPTION}
        --out ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/cfs-edac-cucumber-report.html
        --strict ${CMAKE_CURRENT_SOURCE_DIR}/cfs/edac/features

    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}

    DEPENDS
        cfs-edac.it-test.steps

    COMMENT
    "Running cfs-edac integration test."
)

add_custom_command(TARGET cfs-edac.integration-test
    PRE_BUILD
    COMMAND
        cfs-edac.it-test.steps --port 3902  >/dev/null &
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT
        "Start cucumber's wire server on port 3902."
)

add_custom_command(TARGET cfs-edac.integration-test
    POST_BUILD
    COMMAND
        fuser -k -n  tcp 3902 || true # kill -9 *.Seps which is using port 3902
#        # iptables -I INPUT -p tcp --dport 3902 -j DROP ;# need to be root for this command
         # # pkill -f ddspublisher #kill Publisher executable by name.
    COMMENT
        // check pro opened lsof -i -P -n | grep LISTEN
        "Killing process to close cucumber wire port. (bind: Address already in use)"
)

