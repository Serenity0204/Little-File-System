cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(Project_Name)

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



#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
#   Grab all cpp files from includes folder
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
set(INCLUDES_FOLDER includes)
set(LIB_FOLDER lib)
set(APP_FOLDER app)

FILE(GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}   "${INCLUDES_FOLDER}/*.cpp" )
FILE(GLOB_RECURSE LIB_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}   "${LIB_FOLDER}/*.cpp" )
FILE(GLOB_RECURSE APP_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}   "${APP_FOLDER}/*.cpp" )
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

ADD_EXECUTABLE(test_lib_app
    _tests/_test_files/test_lib_app.cpp
    ${SOURCE_FILES}
    ${LIB_FILES}
    ${APP_FILES}
)


ADD_EXECUTABLE(test_file_folder_io
    _tests/_test_files/test_file_folder_io.cpp
    ${SOURCE_FILES}
    ${LIB_FILES}
    ${APP_FILES}
)


ADD_EXECUTABLE(main
    main.cpp
    ${SOURCE_FILES}
    ${LIB_FILES}
    ${APP_FILES}
)

ADD_EXECUTABLE(remove_root_dir
    remove_root_dir.cpp
    ${SOURCE_FILES}
    ${LIB_FILES}
    ${APP_FILES}
)





TARGET_LINK_LIBRARIES(test_lib_app gtest)
TARGET_LINK_LIBRARIES(test_file_folder_io gtest)
TARGET_LINK_LIBRARIES(remove_root_dir gtest)
## copy resources file to build
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(main ${SFML_LIBRARIES})
    target_link_libraries(test_lib_app ${SFML_LIBRARIES})
    target_link_libraries(test_file_folder_io ${SFML_LIBRARIES})
    target_link_libraries(remove_root_dir ${SFML_LIBRARIES})
endif()

