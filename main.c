#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <signal.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define sleep(sec) Sleep(1000*(sec))
#else
    #include <unistd.h> //sleep()
#endif

#include "psytexx_mod_engine.h"
#include "psytexx_audio.h"

int g_sample_rate = 44100;
int g_bufsize = 1024;
pmod_player_s g_player;
paudio_struct g_audio;

int g_exit_request = 0;
void int_handler( int param )
{
    g_exit_request = 1;
}

void render_piece_of_sound( paudio_struct* s, void* buf, int frames )
{
    pmod_player_s* P = (pmod_player_s*)s->userdata;
    pmod_player_render( P, (int16_t*)buf, frames );
}

int main( int argc, char **argv )
{
    int out_mode = 0; //0 - SDL; 1 - WAV EXPORT;
    const char* out_file_name = NULL;

    signal( SIGINT, int_handler );
    printf( "PsyTexx1 MOD Player by Alexander Zolotov / WarmPlace.ru\n" );
    printf( "(build " __DATE__ "; " __TIME__ ")\n" );
    char* name = NULL;
    if( argc > 1 )
    {
	for( int a = 1; a < argc; a++ )
	{
	    char* arg = argv[ a ];
	    if( strcmp( arg, "-o" ) == 0 )
	    {
		out_mode = 1;
		a++;
		out_file_name = argv[ a ];
		continue;
	    }
	    if( name == NULL )
	    {
		name = argv[ 1 ];
	    }
	}
    }
    else
    {
    	printf( "\
Usage examples:\n\
 psyplayer file.mod\n\
 psyplayer file.pdb\n\
 psyplayer file.mod -o filename.wav\n\
\n" );
    	return 0;
    }

    pmod_player_init( &g_player, g_sample_rate );

    int err = pmod_player_load( &g_player, name );
    if( err )
    {
	printf( "Loading ERROR %d\n", err );
	return 0;
    }
    pmod_player_show_info( &g_player );
    pmod_player_play( &g_player );

    printf( "Press CTRL+C to exit\n" );
    paudio_init( &g_audio, out_file_name, PAUDIO_SMPTYPE_INT16, g_sample_rate, 2, g_bufsize, &g_player, render_piece_of_sound );
    while( !g_exit_request )
    {
	if( out_file_name )
	{
	    g_player.stop_at_the_end = 1;
	    paudio_render( &g_audio, 256 );
	    if( g_player.status == 0 ) break;
	}
	else
	{
    	    sleep( 1 );
    	}
    }
    paudio_deinit( &g_audio );

    pmod_player_deinit( &g_player );

    return 0;
}
