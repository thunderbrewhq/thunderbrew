file(GLOB PRIVATE_SOURCES
    "*.cpp"
    "internal/*.cpp"
)

if(WHOA_SYSTEM_WIN)
    file(GLOB WIN_SOURCES
        "win/*.cpp")

    list(APPEND PRIVATE_SOURCES ${WIN_SOURCES})
endif()

if(WHOA_SYSTEM_MAC)
    file(GLOB MAC_SOURCES
        "mac/*.mm")

    set_source_files_properties(${MAC_SOURCES}
        PROPERTIES COMPILE_FLAGS "-x objective-c++"
    )

    list(APPEND PRIVATE_SOURCES ${MAC_SOURCES})
endif()

if(WHOA_SYSTEM_LINUX)
    file(GLOB LINUX_SOURCES
        "linux/*.cpp")

    list(APPEND PRIVATE_SOURCES ${LINUX_SOURCES})
endif()

if(WHOA_BUILD_GLSDL)
    file(GLOB SDL_SOURCES
        "sdl/*.cpp")

    list(APPEND PRIVATE_SOURCES ${SDL_SOURCES})
endif()

add_library(os STATIC
    ${PRIVATE_SOURCES}
)

target_include_directories(os
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(os
    PUBLIC
        storm
        common
)

if(WHOA_BUILD_GLSDL)
    target_link_libraries(os
        PRIVATE
            SDL3::SDL3-static
        )
endif()
