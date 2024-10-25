#pragma once

#define INT16_SWAP( n ) \
    ( ( (((uint16_t)n) << 8 ) & 0xFF00 ) | \
      ( (((uint16_t)n) >> 8 ) & 0x00FF ) )

#define CHANNELS_MAX 12
#define PAT_SIZE(CH) (uint32_t)(CH*4*64)

typedef struct pmod_player_sample
{
    uint8_t   	name[22];
    uint16_t    length;
    uint8_t   	finetune;
    uint8_t   	volume;
    uint16_t	reppnt;
    uint16_t	replen;
} pmod_player_sample;

typedef struct pmod_player_note
{
    uint8_t	sampperiod;
    uint8_t	period;
    uint8_t	sampeffect;
    uint8_t	effect;
} pmod_player_note;

typedef struct pmod_player_module
{
    uint8_t   	title[20];
    uint8_t   	_samples[930]; //sample samples[31];
    uint8_t  	length;
    uint8_t   	protracker;
    uint8_t  	patterntable[128];
    uint8_t   	signature[4];
    pmod_player_sample*	samples[31];
} pmod_player_module;

#define SF_ANTICLICK   1
#define SF_SPORTAMENTO 2
#define SF_DISTORTION  4
#define SF_CUTOFF      8
#define SF_RESONANCE   16
#define SF_WAHWAH      32

typedef struct pmod_player_channel {
    int spec_effects;
    int old_volume;   //ANTICLICK    'A'
    int new_delta;    //SPORTAMENTO  'S'
    int ddelta;       //...
    int dist;         //DISTORTION   'D'
    int cutoff;       //CUTOFF       'C' ( 0 - max; 256 - min )
    int cold_volume;  //...
    int res_volume;   //RESONANCE    'R' ( 0 - max; 8 - min )
    int res_delta;    //...
    int res_ptr;      //...
    int wah_offset;   //WAHWAH       'W' ( 0 ... 256<<16 )
    int wah_add;      //...
    int wah_amp;      //...

    int pitch;        //pitch delta (0 - off)
    uint32_t pitch_ticks; //pitch ticks

    int anticlick;       //0 ... 255
    int anticlick_start; //start sample value
    int previous_value;

    int echo_volume;

    //int add_sounds; //number of additional tones
    //int add_period[8];
    //int add_ticks[8];

    int8_t * 	sampdata;
    int   	period;
    uint32_t   	delta;
    uint32_t   	ticks;
    int  	new_period;

    uint16_t    sampnum;
    uint16_t    length;
    uint16_t    reppnt;
    uint16_t    replen;
    uint16_t  	rep;
    int16_t  	p_delta; //period delta.
    int16_t   	p_olddelta;
    uint16_t  	p_up;
    uint16_t 	p_down;

    uint16_t   	v_up;
    uint16_t   	v_down;
    uint16_t   	global_volume_l;
    uint16_t   	global_volume_r;
    uint16_t   	summar_volume;
    uint16_t 	temp;
    int8_t   	volume;
} pmod_player_channel;

typedef struct pmod_player_s {
    int file_is_open;
    FILE* out_file;

    void* record_buf;
    int record_pos;

    void* echo_buffer;
    int echo_size;
    int echo_pointer;
    int echo_flange_delay;
    int echo_vol;

    uint8_t reverb_offset[ 10 ];
    int reverb_cnt;

    int8_t *rec_pointer;
    int rec_count;
    int rec_add;

    pmod_player_channel channels[ CHANNELS_MAX ];
    pmod_player_channel channels2[ 2 ]; //For the single channel play
    int patternticks;
    int onetick;
    uint32_t sp;
    uint32_t speed;
    uint32_t bpm;
    pmod_player_note *patterndata[64];
    pmod_player_module song;
    int8_t *_buffer;
    uint32_t sampleticksconst;
    int8_t periods[1900];
    int8_t *sampledata[31];
    int i2, size;
    uint32_t _update;
    uint16_t tablepos;
    uint16_t patternpos;
    uint16_t playrate;
    uint16_t _buffer_size;
    uint16_t CHANNELS;
    uint16_t VOLUME;
    int8_t _scope[60];
    int8_t status; //0-pause; 1-one sample mode; 2-play; 3-one pattern play;
    bool stop_at_the_end;
} pmod_player_s;

#ifdef __cplusplus
extern "C" {
#endif

int pmod_player_init( pmod_player_s* P, int sample_rate );
void pmod_player_deinit( pmod_player_s* P );
int pmod_player_load( pmod_player_s* P, const char* filename );
void pmod_player_show_info( pmod_player_s* P );
void pmod_player_play( pmod_player_s* P );
uint32_t pmod_player_render( pmod_player_s* P, int16_t* buffer, uint32_t buffer_size );

#ifdef __cplusplus
}; //extern "C"
#endif
