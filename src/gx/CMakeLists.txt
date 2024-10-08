file(GLOB GX_SOURCES
    "*.cpp"
    "buffer/*.cpp"
    "font/*.cpp"
    "shader/*.cpp"
    "texture/*.cpp"
)

if (WHOA_SYSTEM_WIN)
    file(GLOB D3D_SOURCES "d3d/*.cpp")
    list(APPEND GX_SOURCES ${D3D_SOURCES})
endif ()

if (WHOA_SYSTEM_MAC)
    file(GLOB GLL_SOURCES "gll/*.cpp" "gll/*.mm")
    set_source_files_properties(${GLL_SOURCES}
        PROPERTIES COMPILE_FLAGS "-x objective-c++"
    )
    list(APPEND GX_SOURCES ${GLL_SOURCES})
endif ()

# Build OpenGL/SDL graphics device if enabled
if (WHOA_BUILD_GLSDL)
    file(GLOB GLSDL_SOURCES "glsdl/*.cpp")
    list(APPEND GX_SOURCES ${GLSDL_SOURCES})
endif ()

add_library(gx STATIC ${GX_SOURCES})

target_include_directories(gx
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(gx
    PRIVATE
        event
        math
        model
        ui
        util
    PUBLIC
        bc
        freetype-2.0
        storm
        tempest
)

if (WHOA_SYSTEM_WIN)
    target_link_libraries(gx
        PRIVATE
            d3d9.lib
    )

    # MSVC includes DirectXMath by default
    if (NOT MSVC)
        target_link_libraries(gx
            PRIVATE
                DirectXMath
        )
    endif ()
endif ()

# Link SDL2 and GLEW for GLSDL
if (WHOA_BUILD_GLSDL)
    target_link_libraries(gx
        PRIVATE
            SDL2::SDL2-static
            libglew_static
        )
endif ()

if (WHOA_SYSTEM_MAC)
    target_link_libraries(gx
        PRIVATE
            "-framework AppKit"
            "-framework OpenGL"
    )
endif ()
