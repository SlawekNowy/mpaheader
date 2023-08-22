cmake_minimum_required(VERSION 3.16)

project(mpaheader)

set (INCLUDES
"include/mpafile.hpp"
"include/id3v1tag.hpp"
"include/lametag.hpp"
"include/lyrics3tag.hpp"
"include/xingheader.hpp"
"include/id3v2tag.hpp"
"include/mpastream.hpp"
"include/musicmatchtag.hpp"
"include/tag.hpp"
"include/tags.hpp"
"include/vbrheader.hpp"
"include/apetag.hpp"
"include/mpaheader.hpp"
"include/vbriheader.hpp"
"include/mpaframe.hpp"
"include/mpaexception.hpp"
"include/mpaendoffileexception.hpp"
"src/helper.hpp"
"src/pch.hpp"
)



set (SOURCES
"src/id3v2tag.cpp"
"src/lametag.cpp"
"src/mpaexception.cpp"
"src/tags.cpp"
"src/id3v1tag.cpp"
"src/mpaheader.cpp"
"src/lyrics3tag.cpp"
"src/vbriheader.cpp"
"src/tag.cpp"
"src/mpaendoffileexception.cpp"
"src/musicmatchtag.cpp"
"src/apetag.cpp"
"src/xingheader.cpp"
"src/mpastream.cpp"
"src/mpafile.cpp"
"src/vbrheader.cpp"
"src/mpaframe.cpp"
"src/helper.cpp"
)

if(WIN32)
set(INCLUDES ${INCLUDES}
"src/mpafilestream_win32.hpp")
set(SOURCES ${SOURCES}
"src/mpafilestream_win32.cpp")
endif()

if(UNIX)
set(INCLUDES ${INCLUDES}
"src/mpafilestream_posix.hpp")
set(SOURCES ${SOURCES}
"src/mpafilestream_posix.cpp")
endif()

add_library(mpaheader SHARED ${SOURCES} ${INCLUDES})
target_compile_definitions(mpaheader PUBLIC MPAH_DLL)
target_include_directories(mpaheader PUBLIC "include")
target_precompile_headers(mpaheader PRIVATE "src/pch.hpp")
