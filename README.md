**PsyTexx1 Player** is a command line player for MOD files created in PsyTexx music tracker v1.x.

PsyTexx1 MOD format is based on the Amiga MOD and is almost identical to the original, but has some limitations and additional effects.  
Supported standard effects: 1, 2, 3, 9, A, B, C, D, F, E1, E2, EA, EB.

Description of special effects in the sample name: @ABC@  
where ABC are the codes for the following effects:
* A - anticlick;
* S - smooth portamento;
* D - distortion;
* C - low-pass filter;
* R - resonance;
* W - wah-wah?

Sample echo volume = sample_name[ 21 ] (from 0 to 32);  
Global echo volume = song_title[ 19 ] (from 0 to 100);  
Echo length (in ticks) = song_title[ 18 ] (from 1 to 24);  
yes, i know, it was a stupid way to store the echo parameters...

Non-standard effects (only available in PsyTexx1.x):
* 4 - set echo volume;
* 6 - set wah-wah amplitude;
* 7 - set filter cutoff;
* 8 - сhange pitch without changing duration;

Usage examples:
* psyplayer file.mod
* psyplayer file.pdb
* psyplayer file.mod -o filename.wav

At the moment, build scripts are only available for Linux and macOS. But this source code can be easily ported to any other system.

Please support my work:  
https://warmplace.ru/donate
