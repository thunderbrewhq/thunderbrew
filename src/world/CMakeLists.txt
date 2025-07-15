file(GLOB PRIVATE_SOURCES
    "daynight/*.cpp"
    "map/*.cpp"
    "*.cpp"
)

add_library(world STATIC
    ${PRIVATE_SOURCES}
)

target_include_directories(world
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(world
    PRIVATE
        gx
        model
    PUBLIC
        bc
        common
        storm
        tempest
)
