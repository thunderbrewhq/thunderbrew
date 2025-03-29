file(GLOB PRIVATE_SOURCES "*.cpp")

add_library(clientobject STATIC
    ${PRIVATE_SOURCES}
)

target_include_directories(clientobject
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(clientobject
    PRIVATE
        storm
        db
)
