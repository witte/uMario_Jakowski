include(FetchContent)


set(BUILD_SHARED_LIBS OFF)

set(SDL_SHARED OFF)
set(INTERFACE_SDL2_SHARED OFF)
set(SDL2MIXER_OPUS OFF)
set(SDL2MIXER_MOD OFF)
set(SDL2MIXER_MOD_XMP OFF)
set(SDL2MIXER_MIDI_FLUIDSYNTH OFF)
set(SDL2MIXER_WAVPACK OFF)
set(SDL2MIXER_MIDI_NATIVE OFF)
set(SDL2IMAGE_DEPS_SHARED OFF)

FetchContent_Declare(
    SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG main #release-2.30.7
    FIND_PACKAGE_ARGS NAMES SDL
    GIT_PROGRESS TRUE
)

FetchContent_Declare(
    SDL_Image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG main #release-2.8.2
    FIND_PACKAGE_ARGS NAMES SDL_Image
    GIT_PROGRESS TRUE
)

FetchContent_Declare(
    SDL_Mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG main #release-2.8.0
    FIND_PACKAGE_ARGS NAMES SDL_Mixer
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(SDL SDL_Image SDL_Mixer)
