set(QZTEST_SOURCES
        qztest.h
        testjlcompress.h
        testquachecksum32.h
        testquagzipfile.h
        testquaziodevice.h
        testquazip.h
        testquazipdir.h
        testquazipfile.h
        testquazipfileinfo.h
        testquazipnewinfo.h
        qztest.cpp
        testjlcompress.cpp
        testquachecksum32.cpp
        testquagzipfile.cpp
        testquaziodevice.cpp
        testquazip.cpp
        testquazipdir.cpp
        testquazipfile.cpp
        testquazipfileinfo.cpp
        testquazipnewinfo.cpp
)

add_executable(qztest ${QZTEST_SOURCES} qztest.qrc)
set_target_properties(qztest PROPERTIES AUTORCC ON)
target_include_directories(qztest PRIVATE ${QUAZIP_INC})
target_link_libraries(qztest
    ${QUAZIP_TEST_QT_LIBRARIES}
    QuaZip::QuaZip
)

add_test(NAME qztest_test COMMAND qztest)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose DEPENDS qztest)

# Copy all Qt dlls to qztest bin so we can run it in CI
if (WIN32)
	install(FILES $<TARGET_RUNTIME_DLLS:qztest> TYPE BIN)

	message(STATUS "QUAZIP_BINARY_DIR is ${QUAZIP_BINARY_DIR}")
	add_custom_command(TARGET qztest POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:quazip> $<TARGET_FILE_DIR:qztest>
			COMMAND_EXPAND_LISTS
	)

	if (DEFINED VCPKG_INSTALLED_DIR)
		message(STATUS "Copy .dll from vcpkg")
		add_custom_command(TARGET qztest POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/bin/bz2.dll" $<TARGET_FILE_DIR:qztest>
				COMMAND_EXPAND_LISTS
		)
	endif()

	message(STATUS "Setting up windeployqt")
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
	include(windeployqt)
	windeployqt(qztest)
endif()