cmake_minimum_required(VERSION 3.4.1)

add_definitions(-DGL_GLEXT_PROTOTYPES -DANDROID_BUILD)

file(GLOB SOURCES
    "../../../neon/core/engine/main.cpp"
    "../../../neon/core/engine/engine.cpp"
    "../../../neon/core/engine/common.cpp"
    "../../../neon/core/engine/camera_base.cpp"
    "../../../neon/core/engine/camera.cpp"
    "../../../neon/core/engine/orbit_camera.cpp"

    "../../../neon/core/interface/neon_interface.cpp"
    "../../../neon/core/interface/sdl2_interface.cpp"

    "../../../neon/core/renderer/renderer.cpp"
    "../../../neon/core/renderer/model.cpp"
    "../../../neon/core/renderer/model_manager.cpp"
    "../../../neon/core/renderer/shader.cpp"
    "../../../neon/core/renderer/texture.cpp"

    "../../../neon/sandbox/application.cpp"
    "../../../neon/sandbox/test_objects.cpp"
    "../../../neon/sandbox/test_lighting.cpp"

)

file(GLOB SOIL_SOURCES
    "../../../neon/external/soil/src/*.c"
)



file(GLOB SDL_SOURCES
    "src/main/cpp/SDL2/src/*.c"
    "src/main/cpp/SDL2/src/audio/*.c"
    "src/main/cpp/SDL2/src/audio/android/*.c"
    "src/main/cpp/SDL2/src/audio/dummy/*.c"
    "src/main/cpp/SDL2/src/atomic/SDL_atomic.c"
    "src/main/cpp/SDL2/src/atomic/SDL_spinlock.c"
    "src/main/cpp/SDL2/src/core/android/*.c"
    "src/main/cpp/SDL2/src/cpuinfo/*.c"
    "src/main/cpp/SDL2/src/dynapi/*.c"
    "src/main/cpp/SDL2/src/events/*.c"
    "src/main/cpp/SDL2/src/file/*.c"
    "src/main/cpp/SDL2/src/haptic/*.c"
    "src/main/cpp/SDL2/src/haptic/dummy/*.c"
    "src/main/cpp/SDL2/src/joystick/*.c"
    "src/main/cpp/SDL2/src/joystick/android/*.c"
    "src/main/cpp/SDL2/src/loadso/dlopen/*.c"
    "src/main/cpp/SDL2/src/power/*.c"
    "src/main/cpp/SDL2/src/power/android/*.c"
    "src/main/cpp/SDL2/src/filesystem/android/*.c"
    "src/main/cpp/SDL2/src/render/*.c"
    "src/main/cpp/SDL2/src/render/*/*.c"
    "src/main/cpp/SDL2/src/stdlib/*.c"
    "src/main/cpp/SDL2/src/thread/*.c"
    "src/main/cpp/SDL2/src/thread/pthread/*.c"
    "src/main/cpp/SDL2/src/timer/*.c"
    "src/main/cpp/SDL2/src/timer/unix/*.c"
    "src/main/cpp/SDL2/src/video/*.c"
    "src/main/cpp/SDL2/src/video/android/*.c"
    "src/main/cpp/SDL2/src/main/android/SDL_android_main.c"


)


include_directories(../../../neon/core)
include_directories(../../../neon/external/soil)
include_directories(../../../neon/external/sdl2/include)
include_directories(../../../neon/external/glm)

add_library(
             native-lib
             SHARED

             ${SOURCES}
             ${SDL_SOURCES}
             ${SOIL_SOURCES}

             )

#find_library( log-lib  log )

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       log
                       dl
                       GLESv1_CM
                       EGL
                       GLESv2
                       GLESv3
                       android

                       )