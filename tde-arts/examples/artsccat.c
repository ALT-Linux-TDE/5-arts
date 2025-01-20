    /*

    Copyright (C) 2001 Matthias Kretz
                       kretz@kde.org

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.
  
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.
   
    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.

    */

/*
 * This is another artscat written with aRts C API. It reads data from
 * stdin, and plays it via the aRts soundserver.
 * 
 * Compile programs using the aRts C API with
 * 
 *    cc -o artscdump artscdump.c `artsc-config --cflags` `artsc-config --libs`
 *
 * If you are using a makefile, it could look like this:
 *
 *    CFLAGS=`artsc-config --cflags`
 *    LDFLAGS=`artsc-config --libs`
 *
 *    artscdump: artscdump.c
 */
#include <artsc.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void exitUsage(const char *progname)
{
	fprintf(stderr,"usage: %s [ options ] [ <filename> ]\n",progname);
	fprintf(stderr,"-r <samplingrate>   set samplingrate to use\n");
	fprintf(stderr,"-b <bits>           set number of bits (8 or 16)\n");
	fprintf(stderr,"-c <channels>       set number of channels (1 or 2)\n");
	fprintf(stderr,"-h                  display this help and exit\n");
	exit(1);	
}

int main(int argc, char ** argv)
{
	int cfgSamplingRate = 44100;
	int cfgBits = 16;
	int cfgChannels = 2;
	FILE *infile = stdin;
	int pfd;
	int packetsize;
	char *buffer;
	int size = 1024;
	arts_stream_t stream;
	int optch;
	while((optch = getopt(argc,argv,"r:b:c:h")) > 0)
	{
		switch(optch)
		{
			case 'r': cfgSamplingRate = atoi(optarg);
				break;
			case 'b': cfgBits = atoi(optarg);
				break;
			case 'c': cfgChannels = atoi(optarg);
				break;
			case 'h':
			default: 
					exitUsage(argc?argv[0]:"artsccat");
				break;
		}
	}

	if (optind < argc)
    {
		if(argv[optind] != "-")
		{
			infile = fopen(argv[optind],"w");
			if(!infile)
			{
				fprintf( stderr, "Can't open file '%s'.\n", argv[optind] );
				exit(1);
			}
		}
	}

	pfd = fileno( infile );

	arts_init();
	stream = arts_play_stream( cfgSamplingRate, cfgBits, cfgChannels, "artsccat" );
	packetsize = arts_stream_get( stream, ARTS_P_PACKET_SIZE );
	buffer = malloc(packetsize);

	do {
		size = read( pfd, buffer, packetsize );
		size = arts_write( stream, buffer, size );
	} while( size > 0 );

	arts_close_stream( stream );
	arts_free();

	pclose( infile );
	free(buffer);

	return 0;
}