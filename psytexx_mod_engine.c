/*
PsyTexx MOD player engine
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "psytexx_mod_engine.h"

//#define ECHO_TYPE_NEW
#define ECHO_TYPE_OLD
#define INTERPOLATION
#define SPEC_EFFECTS_ON

uint16_t g_tab_finetune[ 16 * 60 ] = {

1712,1616,1524,1440,1356,1280,1208,1140,1076,1016,960,906,
856,808,762,720,678,640,604,570,538,508,480,453,
428,404,381,360,339,320,302,285,269,254,240,226,
214,202,190,180,170,160,151,143,135,127,120,113,
107,101,95,90,85,80,75,71,67,63,60,56,

1700,1604,1514,1430,1348,1274,1202,1134,1070,1010,954,900,
850,802,757,715,674,637,601,567,535,505,477,450,
425,401,379,357,337,318,300,284,268,253,239,225,
213,201,189,179,169,159,150,142,134,126,119,113,
106,100,94,89,84,79,75,71,67,63,59,56,

1688,1592,1504,1418,1340,1264,1194,1126,1064,1004,948,894,
844,796,752,709,670,632,597,563,532,502,474,447,
422,398,376,355,335,316,298,282,266,251,237,224,
211,199,188,177,167,158,149,141,133,125,118,112,
105,99,94,88,83,79,74,70,66,62,59,56,

1676,1582,1492,1408,1330,1256,1184,1118,1056,996,940,888,
838,791,746,704,665,628,592,559,528,498,470,444,
419,395,373,352,332,314,296,280,264,249,235,222,
209,198,187,176,166,157,148,140,132,125,118,111,
104,99,93,88,83,78,74,70,66,62,59,55,

1664,1570,1482,1398,1320,1246,1176,1110,1048,990,934,882,
832,785,741,699,660,623,588,555,524,495,467,441,
416,392,370,350,330,312,294,278,262,247,233,220,
208,196,185,175,165,156,147,139,131,124,117,110,
104,98,92,87,82,78,73,69,65,62,58,55,

1652,1558,1472,1388,1310,1238,1168,1102,1040,982,926,874,
826,779,736,694,655,619,584,551,520,491,463,437,
413,390,368,347,328,309,292,276,260,245,232,219,
206,195,184,174,164,155,146,138,130,123,116,109,
103,97,92,87,82,77,73,69,65,61,58,54,

1640,1548,1460,1378,1302,1228,1160,1094,1032,974,920,868,
820,774,730,689,651,614,580,547,516,487,460,434,
410,387,365,345,325,307,290,274,258,244,230,217,
205,193,183,172,163,154,145,137,129,122,115,109,
102,96,91,86,81,77,72,68,64,61,57,54,

1628,1536,1450,1368,1292,1220,1150,1086,1026,968,914,862,
814,768,725,684,646,610,575,543,513,484,457,431,
407,384,363,342,323,305,288,272,256,242,228,216,
204,192,181,171,161,152,144,136,128,121,114,108,
102,96,90,85,80,76,72,68,64,60,57,54,

1814,1712,1616,1524,1440,1356,1280,1208,1140,1076,1008,960,
907,856,808,762,720,678,640,604,570,538,504,480,
453,428,404,381,360,339,320,302,285,269,254,240,
226,214,202,190,180,170,160,151,143,135,127,120,
113,107,101,95,90,85,80,75,71,67,63,60,

1800,1700,1604,1514,1430,1350,1272,1202,1134,1070,1010,954,
900,850,802,757,715,675,636,601,567,535,505,477,
450,425,401,379,357,337,318,300,284,268,253,238,
225,212,200,189,179,169,159,150,142,134,126,119,
112,106,100,94,89,84,79,75,71,67,63,59,

1788,1688,1592,1504,1418,1340,1264,1194,1126,1064,1004,948,
894,844,796,752,709,670,632,597,563,532,502,474,
447,422,398,376,355,335,316,298,282,266,251,237,
223,211,199,188,177,167,158,149,141,133,125,118,
111,105,99,94,88,83,79,74,70,66,62,59,

1774,1676,1582,1492,1408,1330,1256,1184,1118,1056,996,940,
887,838,791,746,704,665,628,592,559,528,498,470,
444,419,395,373,352,332,314,296,280,264,249,235,
222,209,198,187,176,166,157,148,140,132,125,118,
111,104,99,93,88,83,78,74,70,66,62,59,

1762,1664,1570,1482,1398,1320,1246,1176,1110,1048,988,934,
881,832,785,741,699,660,623,588,555,524,494,467,
441,416,392,370,350,330,312,294,278,262,247,233,
220,208,196,185,175,165,156,147,139,131,123,117,
110,104,98,92,87,82,78,73,69,65,61,58,

1750,1652,1558,1472,1388,1310,1238,1168,1102,1040,982,926,
875,826,779,736,694,655,619,584,551,520,491,463,
437,413,390,368,347,338,309,292,276,260,245,232,
219,206,195,184,174,164,155,146,138,130,123,116,
109,103,97,92,87,82,77,73,69,65,61,58,

1736,1640,1548,1460,1378,1302,1228,1160,1094,1032,974,920,
868,820,774,730,689,651,614,580,547,516,487,460,
434,410,387,365,345,325,307,290,274,258,244,230,
217,205,193,183,172,163,154,145,137,129,122,115,
108,102,96,91,86,81,77,72,68,64,61,57,

1724,1628,1536,1450,1368,1292,1220,1150,1086,1026,968,914,
862,814,768,725,684,646,610,575,543,513,484,457,
431,407,384,363,342,323,305,288,272,256,242,228,
216,203,192,181,171,161,152,144,136,128,121,114,
108,101,96,90,85,80,76,72,68,64,60,57

};

uint8_t g_tab_sin[ 256 ] = {
0, 3, 6, 9, 12, 15, 18, 21, 25, 28, 31, 34, 37, 40, 43, 46,
49, 52, 56, 59, 62, 65, 68, 71, 74, 77, 80, 83, 86, 89, 92, 95,
97, 100, 103, 106, 109, 112, 115, 117, 120, 123, 126, 128, 131, 134, 136, 139,
142, 144, 147, 149, 152, 154, 157, 159, 162, 164, 167, 169, 171, 174, 176, 178,
180, 183, 185, 187, 189, 191, 193, 195, 197, 199, 201, 203, 205, 207, 209, 211,
212, 214, 216, 217, 219, 221, 222, 224, 225, 227, 228, 229, 231, 232, 233, 235,
236, 237, 238, 239, 240, 242, 243, 243, 244, 245, 246, 247, 248, 249, 249, 250,
251, 251, 252, 252, 253, 253, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 254, 253, 253, 252, 252, 251,
251, 250, 249, 249, 248, 247, 246, 245, 245, 244, 243, 242, 241, 240, 238, 237,
236, 235, 234, 232, 231, 230, 228, 227, 225, 224, 222, 221, 219, 218, 216, 214,
213, 211, 209, 207, 205, 203, 201, 200, 198, 196, 194, 191, 189, 187, 185, 183,
181, 179, 176, 174, 172, 169, 167, 165, 162, 160, 157, 155, 152, 150, 147, 145,
142, 139, 137, 134, 131, 129, 126, 123, 120, 118, 115, 112, 109, 106, 104, 101,
98, 95, 92, 89, 86, 83, 80, 77, 74, 71, 68, 65, 62, 59, 56, 53,
50, 47, 44, 41, 37, 34, 31, 28, 25, 22, 19, 16, 12, 9, 6, 3
};
#define SINTAB( V ) ( (int)g_tab_sin[ V ] - 128 )

static void pmod_player_effect( pmod_player_channel*, pmod_player_s* );
static void pmod_player_worknote( pmod_player_note*, pmod_player_channel*, pmod_player_s* );

int pmod_player_init( pmod_player_s* P, int sample_rate )
{
    P->playrate = sample_rate;

    int a;
    for( a = 0; a < 64; a++ )
    {
	size_t size = CHANNELS_MAX * 4 * 64;
        P->patterndata[ a ] = (pmod_player_note*)malloc( size );
        //memset( P->patterndata[ a ], 0, size );
    }
    for( a = 0; a < 31; a++ )
    {
	size_t size = 70000;
        P->sampledata[ a ] = (int8_t*)malloc( size );
        //memset( P->patterndata[ a ], 0, size );
    }
    P->echo_buffer = malloc( 128000 ); memset( P->echo_buffer, 0, 128000 );

    int8_t* pp = P->periods;
    pp[1712]=0;pp[1616]=1;pp[1524]=2;pp[1440]=3;pp[1356]=4;pp[1280]=5;
    pp[1208]=6;pp[1140]=7;pp[1076]=8;pp[1016]=9;pp[960]=10;pp[906]=11;
    pp[856]=12;pp[808]=13;pp[762]=14;pp[720]=15;pp[678]=16;pp[640]=17;
    pp[604]=18;pp[570]=19;pp[538]=20;pp[508]=21;pp[480]=22;pp[453]=23;
    pp[428]=24;pp[404]=25;pp[381]=26;pp[360]=27;pp[339]=28;pp[320]=29;
    pp[302]=30;pp[285]=31;pp[269]=32;pp[254]=33;pp[240]=34;pp[226]=35;
    pp[214]=36;pp[202]=37;pp[190]=38;pp[180]=39;pp[170]=40;pp[160]=41;
    pp[151]=42;pp[143]=43;pp[135]=44;pp[127]=45;pp[120]=46;pp[113]=47;
    pp[107]=48;pp[101]=49;pp[95]=50;pp[90]=51;pp[85]=52;pp[80]=53;
    pp[75]=54;pp[71]=55;pp[67]=56;pp[63]=57;pp[60]=58;pp[56]=59;

    P->reverb_cnt = 10;
    for( int r = 0; r < P->reverb_cnt; r++ )
    {
        P->reverb_offset[r] = (uint8_t)rand();
        P->reverb_offset[r] >>= 1;
        P->reverb_offset[r] <<= 1;
    }

    P->record_pos = 61000;
    P->rec_pointer = 0;
    P->rec_count = 0;
    P->rec_add = 0;

    P->VOLUME = 32;

    return 0;
}

void pmod_player_deinit( pmod_player_s* P )
{
    int a;
    for( a = 0; a < 64; a++ )
    {
        free( P->patterndata[ a ] );
    }
    for( a = 0; a < 31; a++ )
    {
        free( P->sampledata[ a ] );
    }
    free( P->echo_buffer );
}

static void pmod_player_channels_setup( pmod_player_s* P )
{
    uint32_t cc;
    int vol;
    P->CHANNELS = 4;
    if(P->song.signature[0]=='6') P->CHANNELS = 6;
    if(P->song.signature[0]=='8') P->CHANNELS = 8;
    if(P->song.signature[0]=='O') P->CHANNELS = 8;
    if(P->song.signature[0]=='C') P->CHANNELS = 12;
    if(P->song.signature[0]=='X') P->CHANNELS = 16;
    for( vol = 32, cc = 0; cc < P->CHANNELS>>1; cc ++, vol += (64/P->CHANNELS) )
    {
        P->channels[cc].global_volume_l = 64;
        P->channels[cc].global_volume_r = vol;
    }
    for( vol = 64, cc = P->CHANNELS>>1; cc < P->CHANNELS; cc ++, vol -= (64/P->CHANNELS) )
    {
        P->channels[cc].global_volume_l = (uint16_t)vol;
        P->channels[cc].global_volume_r = 64;
    }
}

static void pmod_player_channels_reset( pmod_player_s* P )
{
    uint16_t a;
    for( a = 0; a < P->CHANNELS; a++ )
    {
        P->channels[a].volume = 0;
        P->channels[a].period = 1;
        P->channels[a].echo_volume = 0;
        P->channels[a].pitch = 0;
        P->channels[a].spec_effects = 0;
        P->channels[a].cutoff = 255;
        P->channels[a].cold_volume = 0;
        P->channels[a].res_volume = 1;
        P->channels[a].res_ptr = 0;
        P->channels[a].res_delta = 255<<15;
        P->channels[a].wah_offset = 256<<16;
        P->channels[a].wah_amp = 1500;
        P->channels[a].wah_add = -1500;
        P->channels[a].p_delta=0;
        P->channels[a].v_up=0;
        P->channels[a].v_down=0;
        P->channels[a].anticlick = 0;
        P->channels[a].anticlick_start = 0;
        P->channels[a].previous_value = 0;

        P->channels[a].echo_volume = 0;
        P->channels[a].sampdata = 0;
        P->channels[a].length = 0;
        P->channels[a].replen = 0;
        P->channels[a].reppnt = 0;
        P->channels[a].delta = 0;
        P->channels[a].ticks = 0;
        P->channels[a].rep = 0;
    }
    for( a = 0; a < 2; a++ )
    {
        P->channels2[a].echo_volume = 0;
        P->channels2[a].pitch = 0;
        P->channels2[a].spec_effects = 0;
        P->channels2[a].cutoff = 255;
        P->channels2[a].cold_volume = 0;
        P->channels2[a].res_volume = 1;
        P->channels2[a].res_ptr = 0;
        P->channels2[a].res_delta = 255<<15;
        P->channels2[a].wah_offset = 256<<16;
        P->channels2[a].wah_amp = 1500;
        P->channels2[a].wah_add = -1500;
        P->channels2[a].p_delta=0;
        P->channels2[a].v_up=0;
        P->channels2[a].v_down=0;
        P->channels2[a].anticlick = 0;
        P->channels2[a].anticlick_start = 0;
        P->channels2[a].previous_value = 0;
    }
}

static void pmod_player_set_echo( pmod_player_s* P, int echo_volume, int size_in_ticks )
{
    P->echo_size = size_in_ticks;
    P->echo_vol = echo_volume;
    P->song.title[19] = (uint8_t)echo_volume;
    P->song.title[18] = (uint8_t)size_in_ticks;
    P->echo_pointer = 0;
}

static int pmod_player_load_opened_file( pmod_player_s* P, FILE* f )
{
    int rv = -1;

    fread( &P->song, 1084, 1, f ); //load header

    pmod_player_channels_setup( P );

    int maxp = 0;
    for( int i = 0; i < 128; i++ )
    {
        if( P->song.patterntable[ i ] > maxp )
            maxp = P->song.patterntable[ i ];
    }

    for( int i = 0; i <= maxp; i++ )
    {
        fread( P->patterndata[ i ], PAT_SIZE(P->CHANNELS), 1, f );
    }

    int8_t* ss = (int8_t*)&P->song._samples;
    for( int i = 0; i < 31; i++ )
    {
        P->song.samples[ i ] = (pmod_player_sample*)ss;
        ss += 30;
    }

    for( int i = 0; i < 31; i++ )
    {
        pmod_player_sample* sptr = P->song.samples[ i ];
        sptr->length = INT16_SWAP( sptr->length );
        sptr->replen = INT16_SWAP( sptr->replen );
        sptr->reppnt = INT16_SWAP( sptr->reppnt );
        sptr->length *= 2;
        sptr->reppnt *= 2;
        sptr->replen *= 2;
        if( sptr->length == 0 ) continue;
        fread( P->sampledata[ i ], sptr->length, 1, f );
        if( sptr->replen + sptr->reppnt > sptr->length )
            sptr->replen = sptr->length - sptr->reppnt;
    }

    uint32_t ECHO = P->song.title[19];
    uint32_t ECHOLEN = P->song.title[18];
    if( ECHOLEN > 24 ) ECHO = 24;
    if( ECHOLEN == 0 ) ECHOLEN = 24;
    if( ECHO == 0 ) ECHO = 100;

    pmod_player_channels_reset( P );
    pmod_player_set_echo( P, ECHO, ECHOLEN );

    rv = 0;
    return rv;
}

static int pmod_player_load_mod( pmod_player_s* P, const char* filename )
{
    int rv = -1;
    FILE* f = fopen( filename, "rb" );
    if( f )
    {
        rv = pmod_player_load_opened_file( P, f );
        fclose( f );
    }
    else printf( "Can't open %s\n", filename );
    return rv;
}

static int pmod_player_load_pdb( pmod_player_s* P, const char* filename )
{
    int rv = -1;
    FILE* f = fopen( filename, "rb" );
    if( f )
    {
        int c, c2;
        for(;;)
        {
            c = getc(f);
            c2 = getc(f);
            if( c == 'E' && c2 == 'N' )
            {
                c = getc(f);
                c2 = getc(f);
                if( c == 'D' ) break;
            }
        }
        rv = pmod_player_load_opened_file( P, f );
        fclose( f );
    }
    else printf( "Can't open %s\n", filename );
    return rv;
}

int pmod_player_load( pmod_player_s* P, const char* filename )
{
    int rv = -1;
    int name_len = strlen( filename );
    if( filename[ name_len - 3 ] == 'p' || filename[ name_len - 3 ] == 'P' )
    {
        printf( "Loading PalmOS PDB file: %s\n", filename );
        rv = pmod_player_load_pdb( P, filename );
    }
    else
    {
        printf( "Loading MOD file: %s\n", filename );
        rv = pmod_player_load_mod( P, filename );
    }
    return rv;
}

void pmod_player_show_info( pmod_player_s* P )
{
    printf( "Song name: " );
    for( int s = 0; s < 20; s++ )
    {
        uint8_t c = P->song.title[ s ];
        if( c < 32 || c > 126 ) c = ' ';
        printf( "%c", c );
    }
    printf( "\n" );
    printf( "Samples:\n" );
    for( int i = 0; i < 31; i++ )
    {
        printf( "%02d: ", i );
        for( int s = 0; s < 22; s++ )
        {
            uint8_t c = P->song.samples[ i ]->name[ s ];
            if( c < 32 || c > 126 ) c = ' ';
            printf( "%c", c );
        }
        printf( "\n" );
    }
}

void pmod_player_play( pmod_player_s* P )
{
    P->tablepos = 0;
    P->patternpos = 0;
    P->bpm = 125;
    P->onetick = (((uint32_t)P->playrate*25)<<8)/(P->bpm*10);
    P->patternticks = P->onetick + 1;
    P->speed = 6;
    P->sp = 2;
    P->sampleticksconst = (3546894UL / P->playrate)<<16;
    P->status = 2;
}

//Effects:
#define VOLUME_CONTROL(l) \
    if(l<-32765) l=-32765; \
    if(l>32765) l=32675;

//l,l2 >> 5 = 0..16k
//vol = 0..31
#define echo_accumulate( l, l2, vol ) \
    if( vol ) { \
	/*calculate current value from stereo values*/ \
	echo_res2 = (l+l2) >> 6; \
	echo_res += (echo_res2 * vol) >> 5; \
    }

#define echo_reset() echo_res = 0;

#define echo_send() \
    if( echo_buffer ) { \
	/*put current value to the echo-buffer*/ \
	echo_p1 = echo_pointer - 34; \
	if( echo_p1 < 0 ) echo_p1 += echo_size; \
	if( !(echo_p1&1) ) { \
	    echo_res += echo_buffer[ echo_p1>>1 ]; \
	    VOLUME_CONTROL( echo_res ); \
	    echo_buffer[ echo_p1>>1 ] = (int16_t)echo_res; \
	} \
    }

#define reverb_send( l, l2, vol ) \
    if( vol ) { \
	/*calculate current value from stereo values*/ \
	echo_res = (l+l2) >> 6; \
	echo_res = (echo_res * vol) >> 6; \
	/*put current value to the echo-buffer*/ \
	for( reverb_cur = 0; reverb_cur < reverb_cnt; reverb_cur++ ) \
	{ \
	    echo_p1 = echo_pointer + ((int)reverb_offset[reverb_cur]<<8); \
	    if( echo_p1 < 0 ) { echo_p1 += echo_size; \
	    	if( echo_p1 < 0 ) echo_p1 += echo_size; \
	    } \
	    if( echo_p1 >= echo_size ) { echo_p1 -= echo_size; \
	    	if( echo_p1 >= echo_size ) echo_p1 -= echo_size; \
	    } \
	    if( !(echo_p1&1) ) { \
	    	echo_res2 = echo_res + echo_buffer[ echo_p1>>1 ]; \
	    	VOLUME_CONTROL( echo_res2 ); \
	    	echo_buffer[ echo_p1>>1 ] = echo_res2; \
	    } \
	} \
    }

#ifdef ECHO_TYPE_OLD
#define echo_get( l, l2 ) \
    if( echo_buffer ) { \
	/*smooth old value*/ \
	if( !(echo_pointer&1) ) { \
	    echo_p1 = echo_pointer + 2; if( echo_p1 >= echo_size ) echo_p1 -= echo_size; \
	    echo_res = (int)echo_buffer[ echo_pointer>>1 ] + (int)echo_buffer[ echo_p1>>1 ]; \
	    echo_res = (echo_res * echo_vol) >> 8; \
	    VOLUME_CONTROL( echo_res ); \
	    echo_buffer[ echo_pointer>>1 ] = (int16_t)echo_res; \
	} \
	/*get old values*/ \
	echo_p2 = echo_pointer - 32; if( echo_p2 < 0 ) echo_p2 += echo_size; \
	l += (int)echo_buffer[ echo_pointer>>1 ] << 1; \
	l2 += (int)echo_buffer[ echo_p2>>1 ] << 1; \
	echo_pointer ++; \
	/*check for the echo bounds*/ \
	if( echo_pointer >= echo_size ) echo_pointer -= echo_size; \
    }
#endif

#ifdef ECHO_TYPE_NEW
#define echo_get( l, l2 ) \
    if( echo_buffer ) { \
	/*smooth old value*/ \
	if( !(echo_pointer&1) ) { \
	    echo_p1 = echo_pointer + 2; if( echo_p1 >= echo_size ) echo_p1 -= echo_size; \
	    echo_res = (int)echo_buffer[ echo_pointer>>1 ] + (int)echo_buffer[ echo_p1>>1 ]; \
	    echo_res = (echo_res * echo_vol) >> 8; \
	    VOLUME_CONTROL( echo_res ); \
	    echo_buffer[ echo_pointer>>1 ] = (int16_t)echo_res; \
	} \
	/*get old values*/ \
	echo_p2 = echo_pointer - 32; if( echo_p2 < 0 ) echo_p2 += echo_size; \
	l += (int)echo_buffer[ echo_pointer>>1 ] << 1; \
	l2 += (int)echo_buffer[ echo_p2>>1 ] << 1; \
	echo_pointer ++; \
	/*check for the echo bounds*/ \
	if( echo_pointer >= echo_size ) echo_pointer -= echo_size; \
    }
#endif

#ifdef SPEC_EFFECTS_ON
#define RESET_SPEC_EFFECTS \
    if( spec_effects = cptr->spec_effects ) \
    { \
	cptr->dist = 0; \
    }
#define SPEC_EFFECTS( v ) \
    if( spec_effects = cptr->spec_effects ) \
    { \
	if( (spec_effects & SF_CUTOFF) ) \
	{ \
	    if( (spec_effects & SF_WAHWAH) ) \
	    {\
	    	cptr->wah_offset += cptr->wah_add;\
	    	if( cptr->wah_offset < (1<<16) ) cptr->wah_add = cptr->wah_amp;\
	    	if( cptr->wah_offset > (255<<16) ) cptr->wah_add = -cptr->wah_amp;\
	    	cutoff = cptr->wah_offset>>16;\
	    }\
	    else cutoff = cptr->cutoff;\
	    click_delta = cptr->cold_volume - (v<<8);\
	    v = cptr->cold_volume - ((click_delta * cutoff)>>8);\
	    cptr->cold_volume = v;\
	    if( (spec_effects & SF_RESONANCE) ) \
	    {\
	    	cptr->res_ptr += cptr->res_delta;\
	    	resonance_wave = SINTAB( (cptr->res_ptr>>16) & 255 ) >> cptr->res_volume;\
	    	v += ( resonance_wave * click_delta ) >> 7;\
	    }\
	    v >>= 8;\
	} \
	if( (spec_effects & SF_ANTICLICK) ) \
	{ \
	    click_delta = cptr->old_volume - v;\
	    if( click_delta < 0 ) click_delta = -click_delta;\
	    if( click_delta > 32 ) v = ( cptr->old_volume + v ) >> 1;\
	    cptr->old_volume = v;\
	} \
	if( (spec_effects & SF_SPORTAMENTO) ) \
	{ \
	    if( (int)cptr->delta < cptr->new_delta ) \
	    {\
	    	cptr->delta += cptr->ddelta;\
	    	if( (int)cptr->delta > cptr->new_delta ) cptr->delta = cptr->new_delta;\
	    }\
	    if( (int)cptr->delta > cptr->new_delta ) \
	    {\
	    	cptr->delta -= cptr->ddelta;\
	    	if( (int)cptr->delta < cptr->new_delta ) cptr->delta = cptr->new_delta;\
	    }\
	} \
	if( (spec_effects & SF_DISTORTION) ) \
	{ \
	    cptr->dist += v;\
	    if( cptr->dist > 64 ) cptr->dist = 64;\
	    if( cptr->dist < -64 ) cptr->dist = -64;\
	    v = cptr->dist;\
	} \
    }
#else
#define SPEC_EFFECTS( v ) /*none*/ 
#define RESET_SPEC_EFFECTS /*none*/
#endif

#define ANTICLICK( v ) \
/* ANTICLICK FILTER : */\
    if( cptr->anticlick > 0 ) \
    { \
	v = ( (v * (255-cptr->anticlick)) + (cptr->anticlick_start * cptr->anticlick) ) >> 8; \
	cptr->anticlick -= 4; \
    }

#define START_ANTICLICK cptr->anticlick = 255; cptr->anticlick_start = cptr->previous_value;

uint32_t pmod_player_render( pmod_player_s* P, int16_t* buffer, uint32_t buffer_size )
{
    int j;
    uint32_t k;
    int i, l, l2, l3, i2, size, ostalos;
    int int1, int2; //for interpolation
    pmod_player_note* nptr;
    pmod_player_channel* cptr;
    int yy = 0;
    pmod_player_note** patterndata;
    pmod_player_module* song;
    uint8_t* _patterntable;

    int8_t* rec_buffer;
    int rec_count;
    int rec_res;
    int rec_add;
    int8_t* scope;
    uint16_t CHANNELS;
    uint16_t VOLUME;
    uint32_t cc; //cur_channel

    int16_t* echo_buffer;
    int echo_size;
    int echo_pointer;
    int echo_flange_delay;
    int echo_vol;
    int echo_p1;
    int echo_p2;
    int echo_res;
    int echo_res2;
    int8_t* reverb_offset;
    int reverb_cnt;
    int lval;
    int rval;

    int spec_effects;
    int click_delta;
    int resonance_wave;
    int cutoff;

    int8_t* record_buf;

    record_buf = (int8_t*)P->record_buf;
    if( P->record_pos < 60000 ) { //RECORDING FROM MICROPHONE:
	for (i = 0; i < buffer_size; i++) {
	    if( P->record_pos >= 60000 ) break;
	    l = buffer[i];l >>= 8;
	    record_buf[ P->record_pos ] = (int8_t)l;
	    P->record_pos ++;
	}
	return 0;
    }

    patterndata=P->patterndata;
    song=&P->song;
    _patterntable=song->patterntable;
    echo_buffer = (int16_t*)P->echo_buffer;
    echo_size = P->echo_size * (P->onetick>>8);
    echo_pointer = P->echo_pointer;
    echo_flange_delay = P->echo_flange_delay;
    echo_vol = P->echo_vol;
    reverb_offset = (int8_t*)P->reverb_offset;
    reverb_cnt = P->reverb_cnt;
    scope=P->_scope;
    CHANNELS = P->CHANNELS;
    VOLUME = P->VOLUME;

    if( P->status >= 2 )
    {
	for( i=0; i<buffer_size; i++ ) buffer[i]=0;
    	cptr = P->channels;
    	i2 = 0;
    	ostalos = buffer_size;
new_tick:
    	size = (P->onetick - P->patternticks) / 256; size++;
    	if( size < 0 ) size = 0;
    	if( size > ostalos ) size = ostalos;
    	for( i = (i2<<1); i < ((i2+size)<<1); i += 2 )
    	{
	    echo_reset();
	    RESET_SPEC_EFFECTS;
            for( j = l = l2 = 0, cptr; j < CHANNELS; j++, cptr++ )
            {
		lval = rval = 0;
		if( !cptr->sampdata ) continue;
		//Pitch: =======
		if( cptr->pitch )
		{
		    cptr->pitch_ticks += cptr->pitch;
		    k = cptr->pitch_ticks >> 16;
		    if (k >= (uint32_t)cptr->rep)
		    {
		        if(cptr->replen>2)
		        {
		    	    cptr->pitch_ticks = cptr->pitch_ticks - ((uint32_t)(cptr->replen)<<16);
			} else {
			    cptr->pitch_ticks = (uint32_t)(cptr->length)<<16;
			    cptr->sampdata = 0;
			}
		    }
		}
		//==============
                cptr->ticks += cptr->delta;
                k = cptr->ticks>>16;
#ifdef INTERPOLATION
		int1 = cptr->ticks & 0xFFFF; int2 = 0xFFFF - int1;
#endif
next_iteration:
                if( k >= cptr->rep )
                {
            	    if( cptr->replen > 2 )
                    {
                        cptr->ticks = cptr->ticks - ((uint32_t)(cptr->replen)<<16);
                        k = cptr->ticks>>16;
			if( k >= cptr->rep ) goto next_iteration;
#ifdef INTERPOLATION
			lval = (cptr->sampdata[k]*int2)>>16;
			uint32_t k2 = k + 1;
			if( k2 >= cptr->length ) k2 = k;
			lval += (cptr->sampdata[k2]*int1)>>16;
#else 
			lval = cptr->sampdata[k];
#endif
			SPEC_EFFECTS( lval );
			lval *= cptr->volume;
			ANTICLICK( lval );
			cptr->previous_value = lval;
			rval = lval;
			lval = lval * cptr->global_volume_l;
			rval = rval * cptr->global_volume_r;
		    } else {
            		cptr->ticks = (uint32_t)(cptr->length)<<16;
			if( !cptr->pitch ) cptr->sampdata = 0;
			cptr->previous_value = 0;
                    }
                } else {
#ifdef INTERPOLATION
		    lval = (cptr->sampdata[k]*int2)>>16;
		    if( k == (uint32_t)cptr->rep - 1 ) { //right sample bound:
		        if( cptr->replen > 2 ) { //loop
		    	    k = cptr->reppnt;
			    lval += (cptr->sampdata[k]*int1)>>16;
			}
		    } else lval += (cptr->sampdata[k+1]*int1)>>16; //just sample playing
#else 
		    lval = cptr->sampdata[k];
#endif
		    SPEC_EFFECTS( lval );
		    lval *= cptr->volume;
		    ANTICLICK( lval );
		    cptr->previous_value = lval;
		    rval = lval;
		    lval = lval * cptr->global_volume_l;
		    rval = rval * cptr->global_volume_r;
                }

                l += lval;
                l2 += rval;
		l3 = l >> 14;
		if( l3 < 0 ) l3 = -l3;
		cptr->summar_volume = l3;

    		//ECHO PROCESSING:
		echo_accumulate( lval, rval, cptr->echo_volume );
		//===============
	    }
	    //ECHO PROCESSING:
	    echo_send();
	    //===============
	    l>>=4;
	    l2>>=4;
	    //ECHO PROCESSING:
	    echo_get( l, l2 );
	    //===============
            l*=VOLUME; //volume = 0..256
	    l2*=VOLUME;
	    l>>=8;
	    l2>>=8;
	    VOLUME_CONTROL(l);
	    VOLUME_CONTROL(l2);
	    buffer[i] = l;
    	    buffer[i+1] = l2;
            cptr -= CHANNELS;
    	}
    	P->patternticks += (size*256);
        if( P->patternticks > P->onetick )
        {
    	    P->patternticks-=P->onetick;
            if( P->sp-- == 1 )
            {
                P->sp = P->speed;
                nptr = patterndata[_patterntable[P->tablepos]];
                nptr = nptr + P->patternpos;
                P->patternpos += CHANNELS;

                for(cc=0;cc<CHANNELS;cc++) pmod_player_worknote(nptr+cc, cptr+cc, P);

                if( P->patternpos == CHANNELS*64 )
                {
        	    if(P->status!=3)
            	    {
            	        P->tablepos++;
                        if( P->tablepos>=song->length )
                        {
                    	    if( P->stop_at_the_end )
                    	    {
                    		P->status = 0;
                    	    }
                    	    P->tablepos = 0;
                    	}
                    }
                    P->patternpos = 0;
                }
            }

            for( cc=0; cc<CHANNELS; cc++ ) pmod_player_effect(cptr+cc, P);
        }
    	i2 += size;
    	if(i2<buffer_size) { ostalos=buffer_size-i2; goto new_tick; }
    	goto end_mod;
    }
    if( P->status==1 )
    {
	cptr = P->channels2;
    	for( i = 0; i < (buffer_size<<1); i+=2 )
    	{
	    l = l2 = 0;
	    echo_reset();
	    RESET_SPEC_EFFECTS;
    	    cptr->ticks += cptr->delta;
            k = cptr->ticks>>16;
	    int1 = cptr->ticks & 0xFFFF; int2 = 0xFFFF - int1;
            if( k >= (uint32_t)cptr->rep )
            {
                if( cptr->replen > 2 )
                {
            	    cptr->ticks = cptr->ticks - ((uint32_t)(cptr->replen)<<16);
            	    k=cptr->ticks>>16;
		    l = (cptr->sampdata[k]*int2)>>16;
		    l += (cptr->sampdata[k+1]*int1)>>16;
		    SPEC_EFFECTS( l );
		    l2 = l;
		    l = l * cptr->volume * 64;
		    l2 = l2 * cptr->volume * 64;
                } else {
            	    cptr->ticks = (uint32_t)(cptr->length)<<16;
		    cptr->sampdata = 0;
		    l = 0;
		    l2 = 0;
                }
            } else {
	        l = (cptr->sampdata[k]*int2)>>16;
	        if( k == (uint32_t)cptr->rep - 1 ) { //right sample bound:
		    if( cptr->replen > 2 ) { //loop
		        k = cptr->reppnt; 
		        l += (cptr->sampdata[k]*int1)>>16;
		    }
		} else l += (cptr->sampdata[k+1]*int1)>>16; //just sample playing
		SPEC_EFFECTS( l );
		l2 = l;
		l = l * cptr->volume * 64;
		l2 = l2 * cptr->volume * 64;
            }
	    //ECHO PROCESSING:
	    echo_accumulate( l, l2, cptr->echo_volume );
	    echo_send();
	    //===============
	    l >>= 4;
	    l2 >>= 4;
	    //ECHO PROCESSING:
	    echo_get( l, l2 );
	    //===============
	    l *= VOLUME; //volume = 0..256
	    l2 *= VOLUME;
	    l >>= 8;
	    l2 >>= 8;
	    VOLUME_CONTROL(l);
	    VOLUME_CONTROL(l2);
	    buffer[i] = l;
	    buffer[i+1] = l2;
    	}
    	goto end_mod;
    }
    if( P->status == 0 )
    {
        for( i = 0; i < (buffer_size<<1); i+=2 )
        {
	    l = 0; l2 = 0;
	    //ECHO PROCESSING:
	    echo_get( l, l2 );
	    //===============
            l *= VOLUME; //volume = 0..256
	    l2 *= VOLUME;
	    l >>= 8;
	    l2 >>= 8;
	    VOLUME_CONTROL(l);
	    VOLUME_CONTROL(l2);
	    buffer[i] = l; buffer[i+1] = l2;
	}
    }
end_mod:

    //Record to the COPY buffer:
    if( P->rec_pointer != 0 && P->status >= 2 )
    {
	rec_buffer = (int8_t*)P->rec_pointer;
	rec_count = P->rec_count;
	rec_add = P->rec_add;
	for( i = 0; i < (buffer_size<<1); i+= (rec_add<<1) )
	{
	    if( rec_count > 60000 ) { P->rec_pointer = 0; break; }
    	    rec_res = buffer[i] >> 9;
	    rec_res += buffer[i+1] >> 9;
	    rec_buffer[ rec_count ] = (int8_t)rec_res;
	    rec_count ++;
	}
	P->rec_count = rec_count;
    }

    P->echo_pointer = echo_pointer;
    P->echo_flange_delay = echo_flange_delay;

    P->_update=1;
    return 0;
}

static void pmod_player_worknote( pmod_player_note* nptr, pmod_player_channel* cptr, pmod_player_s* P )
{
    uint16_t    sample, period, effect;

    pmod_player_module* song = &P->song;
    int8_t* periods = P->periods;
    int8_t** sampledata = P->sampledata;

    uint8_t* s_info;
    int a;

    sample = (nptr->sampperiod & 0xF0) | (nptr->sampeffect >> 4);
    period = ((nptr->sampperiod & 0xF) << 8) | nptr->period;
    effect = ((nptr->sampeffect & 0xF) << 8) | nptr->effect;

    if( sample != 0 )
    {
	if( sample != 0 ) cptr->sampnum = --sample;

	//Set spec-effects:=======
	s_info = song->samples[cptr->sampnum]->name;
	cptr->spec_effects = 0;
	if( s_info[ 0 ] == '@' )
	{
	    for( a = 1; a < 20; a++ )
	    {
		if( s_info[ a ] == '@' ) break;
		switch( s_info[ a ] )
		{
		    case 'A':
			cptr->spec_effects |= SF_ANTICLICK;
			break;
		    case 'S':
			cptr->spec_effects |= SF_SPORTAMENTO;
			break;
		    case 'D':
			cptr->spec_effects |= SF_DISTORTION;
			break;
		    case 'C':
			cptr->spec_effects |= SF_CUTOFF;
			break;
		    case 'R':
			cptr->spec_effects |= SF_RESONANCE;
			break;
		    case 'W':
			cptr->spec_effects |= SF_WAHWAH;
			break;
		}
	    }
	}
	//========================
	cptr->echo_volume = s_info[21]; //Echo volume;
	if(cptr->echo_volume > 32) cptr->echo_volume = 0; //Correct echo volume

	if(period) 
	{
	    cptr->new_period = g_tab_finetune[((song->samples[cptr->sampnum]->finetune*60)+periods[period])];
	}
        if( effect>>8!=3 )
        {
	    cptr->ddelta = 0;
            cptr->sampdata = sampledata[cptr->sampnum];
            cptr->length = song->samples[cptr->sampnum]->length;
            cptr->reppnt = song->samples[cptr->sampnum]->reppnt;
            cptr->replen = song->samples[cptr->sampnum]->replen;
            cptr->volume = song->samples[cptr->sampnum]->volume;
            if( period )
            {
		period = g_tab_finetune[((song->samples[cptr->sampnum]->finetune*60)+periods[period])];
                cptr->new_delta = cptr->delta = P->sampleticksconst/period;
                cptr->period = period;
                cptr->ticks = 0;
		cptr->wah_offset = 0;
		cptr->cutoff = 255;
		START_ANTICLICK;
	    }
            if( cptr->replen > 2 ) { cptr->rep = cptr->reppnt+cptr->replen; } else { cptr->rep = cptr->length; }
        }
    }
    cptr->p_delta=0;
    cptr->v_up=0;
    cptr->v_down=0;
    if( (effect >> 8) != 0x8 ) cptr->pitch = 0;
    switch( effect >> 8 )
    {
        case 0x1:
    	    if((int)(effect&0xFF)==0){
    		cptr->p_delta=cptr->p_olddelta;
	    } else {cptr->p_delta=-(int)(effect&0xFF);}
            cptr->p_up=1814;
            cptr->p_down=54;
            cptr->p_olddelta=cptr->p_delta;

	    cptr->new_delta = 0xFFFFFFF;
	    cptr->ddelta = -cptr->p_olddelta;
            break;
        case 0x2:
    	    if((int)(effect&0xFF)==0){
        	cptr->p_delta=cptr->p_olddelta;
            } else {cptr->p_delta=(int)(effect&0xFF);}
            cptr->p_up=1814;
            cptr->p_down=54;
            cptr->p_olddelta=cptr->p_delta;

	    cptr->new_delta = 128;
	    cptr->ddelta = cptr->p_olddelta;
            break;
        case 0x3:
    	    if(cptr->period!=cptr->new_period){
                if((effect&0xFF)==0){
            	    if(cptr->period>cptr->new_period){
                	cptr->p_delta=-cptr->p_olddelta;
			cptr->p_down=cptr->new_period;
			cptr->p_up=1900;
                    } else {cptr->p_delta=cptr->p_olddelta;cptr->p_up=cptr->new_period;cptr->p_down=10;}
                } else { if(cptr->period>cptr->new_period){
            	    cptr->p_delta=-(effect&0xFF);cptr->p_down=cptr->new_period;cptr->p_up=1900;
                } else {cptr->p_delta=(effect&0xFF);cptr->p_up=cptr->new_period;cptr->p_down=10;}
                    cptr->p_olddelta=(effect&0xFF);
                }
            }
	    cptr->new_delta = P->sampleticksconst/cptr->new_period;
	    cptr->ddelta = cptr->p_olddelta;
            break;
	case 0xA:
	    cptr->v_up = (effect&0xF0)>>4;
	    cptr->v_down = effect&0x0F;
	    break;
	case 0xE:
	    switch( (effect>>4)&15 ) {
		case 0x1:
		    cptr->period -= effect&15;
		    cptr->delta = P->sampleticksconst/cptr->period;
		    break;
		case 0x2:
		    cptr->period += effect&15;
		    cptr->delta = P->sampleticksconst/cptr->period;
		    break;
		case 0xA:
		    cptr->volume += effect&15; 
		    if( cptr->volume > 64 ) cptr->volume = 64;
		    break;
		case 0xB: cptr->volume -= effect&15;
		    if( cptr->volume < 0 ) cptr->volume = 0;
		    break;
	    }
	    break;
        case 0xF:
    	    if((uint32_t)(effect&0xFF)<=31){
		P->speed=(uint32_t)(effect&0xFF);P->sp=P->speed;
            } else {
                P->bpm=(uint32_t)(effect&0xFF);P->onetick=(((uint32_t)P->playrate*25)<<8)/(P->bpm*10);
            }
            break;
        case 0xD: P->patternpos = (effect & 0xFF) * 4; P->tablepos++; if(P->tablepos>=song->length){P->tablepos=0;} break;
        case 0xC: cptr->volume = (effect & 0xFF); break;
        case 0xB: P->tablepos = (effect & 0xFF); P->patternpos = 0; break;
	case 0x4: P->echo_vol = (uint32_t)(effect & 0xFF); break;
        case 0x9: cptr->ticks = ((effect & 0xFF) * 256) << 16; break;
	case 0x6: cptr->wah_amp = (effect & 0xFF) * 64; break;
    	case 0x7:
	    cptr->cutoff = effect & 0xFF; 
	    cptr->res_delta = cptr->cutoff<<17;
	    break;
	case 0x8: 
	    if( (effect&0xff) == 0xFF ) 
	    {
		cptr->pitch_ticks = 0; //RESET PITCH
		break;
	    }
	    if( cptr->pitch == 0 ) cptr->pitch_ticks = cptr->ticks;
	    if( cptr->period )
		cptr->pitch = P->sampleticksconst / g_tab_finetune[((song->samples[cptr->sampnum]->finetune*60)+(effect&0xff)+12)];
	    break;
    }
}

static void pmod_player_effect( pmod_player_channel* cptr, pmod_player_s* P )
{
    if( cptr->v_up!=0 )
    {
	cptr->volume += cptr->v_up;
	if( cptr->volume > 63 ) { cptr->volume = 63; cptr->v_up = 0; }
    }
    if( cptr->v_down != 0 )
    {
	cptr->volume -= cptr->v_down;
	if(cptr->volume < 0) { cptr->volume = 0; cptr->v_down = 0; }
    }
    if( cptr->p_delta!=0 && (cptr->spec_effects&SF_SPORTAMENTO)==0 )
    {
	cptr->period += cptr->p_delta;
	if( cptr->period >= cptr->p_up ) { cptr->period = cptr->p_up; cptr->p_delta = 0; }
	if( cptr->period <= cptr->p_down ) { cptr->period=cptr->p_down; cptr->p_delta = 0; }
	if( cptr->period != 0 )
	{
	    cptr->delta = P->sampleticksconst / cptr->period;
	}
    }
    if( cptr->pitch )
    {
	cptr->ticks = cptr->pitch_ticks;
	START_ANTICLICK;
    }
}
