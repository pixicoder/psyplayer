#pragma once

#define PAUDIO_SDL

#ifdef PAUDIO_SDL
    #include "SDL2/SDL.h"
#endif

typedef enum
{
    PAUDIO_SMPTYPE_INT16,
    PAUDIO_SMPTYPE_FLOAT32
} paudio_smptype;

struct paudio_struct;
typedef void (*paudio_callback_t)( struct paudio_struct* ss, void* buf, int frames );
typedef struct paudio_struct
{
    int sample_rate;
    int sample_size;
    int channels;
    int bufsize;
    void* userdata;
    paudio_callback_t cb;

#ifdef PAUDIO_SDL
    bool sdl_initialized;
#endif

    FILE* f;
    int wav_fixup1;
    int wav_fixup2;
    int wav_out_bytes;
    void* wav_out_buf;
    int wav_out_buf_size; //in frames
} paudio_struct;

#ifdef __cplusplus
extern "C" {
#endif

int paudio_init(
    paudio_struct* s,
    const char* out_file_name,
    paudio_smptype stype,
    int sample_rate,
    int channels,
    int bufsize,
    void* userdata,
    paudio_callback_t cb );
void paudio_deinit( paudio_struct* s );
void paudio_render( paudio_struct* s, int frames );

#ifdef __cplusplus
}; //extern "C"
#endif
