file(GLOB_RECURSE av_stream_hal_srcs av_stream_hal/*.c)
set(COMPONENT_SRCS av_stream.c ${av_stream_hal_srcs})
set(COMPONENT_ADD_INCLUDEDIRS . av_stream_hal ../audio_board)

set(COMPONENT_REQUIRES audio_board audio_stream esp_peripherals esp-adf-libs esp_timer)

if(IDF_TARGET STREQUAL "esp32s3")
    list(APPEND COMPONENT_REQUIRES usb_stream)
endif()

register_component()
