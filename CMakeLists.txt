cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(Little_File_System)

#. . . . . . . . . . . . . . . . . . . .
include(GNUInstallDirs)
if(MSVC)
    add_compile_options(/W4)
    add_link_options(/W4)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()


# place binaries and libraries according to GNU standards
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})



if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()
#. . . . . . . . . . . . . . . . . . . .

# ------------------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)
 
enable_testing() 


# ------------------------------------



# Define the SFML version to use
set(SFML_VERSION "2.5.1")

# Declare SFML as an external project
FetchContent_Declare(
  SFML
  URL https://www.sfml-dev.org/files/SFML-${SFML_VERSION}-sources.zip
)

# Build SFML as part of the project
FetchContent_MakeAvailable(SFML)



#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
#   Grab all cpp files from includes folder
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
set(INCLUDES_FOLDER includes)
set(LIB_FOLDER lib)
set(APP_FOLDER app)

FILE(GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}   "${INCLUDES_FOLDER}/*.cpp")
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 



ADD_EXECUTABLE(test_file_folder_io
    _tests/_test_files/test_file_folder_io.cpp
    ${SOURCE_FILES}
)


ADD_EXECUTABLE(main
    main.cpp
    ${SOURCE_FILES}
)

ADD_EXECUTABLE(remove_root_dir
    remove_root_dir.cpp
    ${SOURCE_FILES}
)

ADD_EXECUTABLE(test_parser
    _tests/_test_files/test_parser.cpp
    ${SOURCE_FILES}
)

ADD_EXECUTABLE(test_directory_tree
    _tests/_test_files/test_directory_tree.cpp
    ${SOURCE_FILES}
)




## gtest
TARGET_LINK_LIBRARIES(main gtest)
TARGET_LINK_LIBRARIES(test_file_folder_io gtest)
TARGET_LINK_LIBRARIES(test_parser gtest)
TARGET_LINK_LIBRARIES(test_directory_tree gtest)
TARGET_LINK_LIBRARIES(remove_root_dir gtest)

## sfml
TARGET_LINK_LIBRARIES(main sfml-graphics sfml-window sfml-system)
TARGET_LINK_LIBRARIES(test_file_folder_io sfml-graphics sfml-window sfml-system)
TARGET_LINK_LIBRARIES(test_parser sfml-graphics sfml-window sfml-system)
TARGET_LINK_LIBRARIES(test_directory_tree sfml-graphics sfml-window sfml-system)
TARGET_LINK_LIBRARIES(remove_root_dir sfml-graphics sfml-window sfml-system)

## copy resources file to build
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})





