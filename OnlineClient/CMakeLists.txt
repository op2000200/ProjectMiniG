# CMakeList.txt: проект CMake для Online; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Online")

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Online "Online.cpp"  "Game.h" "Game.cpp")
target_link_libraries(Online PRIVATE sfml-graphics)
target_compile_features(Online PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET Online
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Online>
        VERBATIM)
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Online PROPERTY CXX_STANDARD 20)
endif()


# TODO: Добавьте тесты и целевые объекты, если это необходимо.
