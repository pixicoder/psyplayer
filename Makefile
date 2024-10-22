all:
	gcc $(CFLAGS) -c main.c
	gcc $(CFLAGS) -c psytexx_mod_engine.c psytexx_audio.c
	gcc $(LDFLAGS) -o psyplayer main.o psytexx_mod_engine.o psytexx_audio.o $(LIBS)

clean:
	rm -f *.o *.so *.dylib psyplayer
