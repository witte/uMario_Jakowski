cmake_minimum_required(VERSION 3.25)
project(uMario VERSION 1.0 LANGUAGES C CXX OBJC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/SetupDependencies.cmake)


# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
#if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
#	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
#	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
#	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
#elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
#	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
#		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
#	else()
#		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
#	endif()
#endif()

include_directories(uNext)

set(icon_file "${CMAKE_SOURCE_DIR}/uNext/files/images/ico.bmp")
file(GLOB_RECURSE images "${CMAKE_SOURCE_DIR}/uNext/files/images/*.bmp")
file(GLOB_RECURSE sounds "${CMAKE_SOURCE_DIR}/uNext/files/sounds/*.wav")

if (CMAKE_SYSTEM_NAME STREQUAL "iOS")
    set(RootResourcesFolder "")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(RootResourcesFolder "Resources")
endif()

foreach (FILE ${images})
    file(RELATIVE_PATH NEW_FILE "${CMAKE_SOURCE_DIR}/uNext" ${FILE})
    get_filename_component(NEW_FILE_PATH ${NEW_FILE} DIRECTORY)
    set_source_files_properties(${FILE}
        PROPERTIES
            MACOSX_PACKAGE_LOCATION "${RootResourcesFolder}/${NEW_FILE_PATH}"
    )
endforeach()

foreach (FILE ${sounds})
    file(RELATIVE_PATH NEW_FILE "${CMAKE_SOURCE_DIR}/uNext" ${FILE})
    get_filename_component(NEW_FILE_PATH ${NEW_FILE} DIRECTORY)
    set_source_files_properties(${FILE}
        PROPERTIES
            MACOSX_PACKAGE_LOCATION "${RootResourcesFolder}/${NEW_FILE_PATH}"
    )
endforeach()

file(GLOB_RECURSE uMario_SOURCES "uNext/*.cpp")
add_executable (uMario ${uMario_SOURCES}
    ${icon_file} ${images} ${sounds}
)

target_link_libraries(uMario SDL3::SDL3-static SDL3_image::SDL3_image-static SDL3_mixer::SDL3_mixer-static)

set_target_properties(uMario PROPERTIES
    BUNDLE True
    MACOSX_BUNDLE True
    MACOSX_BUNDLE_GUI_IDENTIFIER io.github.witte.uMario
    MACOSX_BUNDLE_BUNDLE_NAME UMario
    MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
)

set_source_files_properties(${icon_file}
    PROPERTIES
        MACOSX_PACKAGE_LOCATION "${RootResourcesFolder}/files/images"
)
