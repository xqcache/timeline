set(PRIVATE_SOURCES
    timelineview.h
    timelineview.cpp
    timelinescene.h
    timelinescene.cpp
    timelineaxis.h
    timelineaxis.cpp
    timelinerow.h
    timelinerow.cpp
)

target_sources(${TARGET_NAME} PRIVATE ${PRIVATE_SOURCES})