/*
    PsyTexx simple audio output library
    by Alexander Zolotov <nightradio@gmail.com>
    WarmPlace.ru
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "psytexx_audio.h"

#ifdef PAUDIO_SDL
static void sdl_audio_callback( void* udata, Uint8* stream, int len )
{
    paudio_struct* s = (paudio_struct*)udata;
    s->cb( s, stream, len / 4 );
}
#endif

int paudio_init(
    paudio_struct* s,
    const char* out_file_name,
    paudio_smptype stype,
    int sample_rate,
    int channels,
    int bufsize,
    void* userdata,
    paudio_callback_t cb )
{
    int rv = -1;
    memset( s, 0, sizeof( paudio_struct ) );
    s->sample_rate = sample_rate;
    s->channels = channels;
    s->bufsize = bufsize;
    s->userdata = userdata;
    s->cb = cb;

    switch( stype )
    {
	case PAUDIO_SMPTYPE_INT16: s->sample_size = 2; break;
	case PAUDIO_SMPTYPE_FLOAT32: s->sample_size = 4; break;
    }

    while( out_file_name )
    {
	//Export to WAV:
	s->f = fopen( out_file_name, "wb" );
        if( !s->f ) break;
        printf( "Exporting to WAV...\n" );
        s->wav_out_buf_size = 256;
        s->wav_out_buf = malloc( s->wav_out_buf_size * s->sample_size * s->channels );
        int val;
        //WAV header:
        fwrite( (void*)"RIFF", 1, 4, s->f );
        val = 4 + 24 + 8 + s->wav_out_bytes;
        s->wav_fixup1 = ftell( s->f );
        fwrite( &val, 4, 1, s->f );
        fwrite( (void*)"WAVE", 1, 4, s->f );
        //WAV FORMAT:
        fwrite( (void*)"fmt ", 1, 4, s->f );
        val = 16; fwrite( &val, 4, 1, s->f );
        val = 1;
        if( stype == PAUDIO_SMPTYPE_FLOAT32 ) val = 3; //Float 32-bit
        fwrite( &val, 2, 1, s->f ); //format
        val = s->channels; fwrite( &val, 2, 1, s->f ); //channels
        val = s->sample_rate; fwrite( &val, 4, 1, s->f ); //frames per second
        val = s->sample_rate * s->channels * s->sample_size; fwrite( &val, 4, 1, s->f ); //bytes per second
        val = s->channels * s->sample_size; fwrite( &val, 2, 1, s->f ); //block align
        val = s->sample_size * 8; fwrite( &val, 2, 1, s->f ); //bits per sample
        //WAV DATA:
        fwrite( (void*)"data", 1, 4, s->f );
        s->wav_fixup2 = ftell( s->f );
        fwrite( &s->wav_out_bytes, 4, 1, s->f );
	rv = 0;
	break;
    }

#ifdef PAUDIO_SDL
    while( rv == -1 )
    {
	SDL_Init( 0 );
	SDL_AudioSpec a;
	a.freq = sample_rate;
	a.format = AUDIO_S16;
	if( stype == PAUDIO_SMPTYPE_FLOAT32 )
	    a.format = AUDIO_F32;
	a.channels = 2;
	a.samples = bufsize;
	a.callback = sdl_audio_callback;
	a.userdata = s;
	if( SDL_OpenAudio( &a, NULL ) < 0 )
	{
    	    printf( "SDL: Couldn't open audio: %s\n", SDL_GetError() );
    	    break;
	}
	SDL_PauseAudio( 0 );
	s->sdl_initialized = 1;
	rv = 0;
	break;
    }
#endif

    return rv;
}

void paudio_deinit( paudio_struct* s )
{
    if( s->f )
    {
        int val;
        if( s->wav_out_bytes & 1 ) fputc( 0, s->f );
	fseek( s->f, s->wav_fixup1, SEEK_SET ); val = 4 + 24 + 8 + s->wav_out_bytes; fwrite( &val, 4, 1, s->f );
        fseek( s->f, s->wav_fixup2, SEEK_SET ); val = s->wav_out_bytes; fwrite( &val, 4, 1, s->f );
        fclose( s->f );
        free( s->wav_out_buf );
        s->f = 0;
        s->wav_out_buf = NULL;
    }

#ifdef PAUDIO_SDL
    if( s->sdl_initialized )
    {
	SDL_CloseAudio();
	SDL_Quit();
    }
#endif
}

void paudio_render( paudio_struct* s, int frames )
{
    if( s->f )
    {
	while( frames > 0 )
	{
	    int size = frames;
	    if( size > s->wav_out_buf_size )
		size = s->wav_out_buf_size;
	    s->cb( s, s->wav_out_buf, size );
	    s->wav_out_bytes += fwrite( s->wav_out_buf, 1, size * s->channels * s->sample_size, s->f );
	    frames -= size;
	}
    }
}
