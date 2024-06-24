FILE ( GLOB TCP_SOURCES *.cpp *.h )
LIST ( SORT TCP_SOURCES )

add_library(
    TCP STATIC
    ${TCP_SOURCES}
)
