file(GLOB PRIVATE_SOURCES "*.cpp")

add_library(gameui STATIC
    ${PRIVATE_SOURCES}
)

target_include_directories(gameui
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(gameui
    PRIVATE
        client
        clientobject
        console
        event
        glue
        gx
        math
        model
        ui
        util
    PUBLIC
        common
        storm
        tempest
)
