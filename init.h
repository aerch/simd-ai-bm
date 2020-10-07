#ifndef __INIT_H__
#define __INIT_H__

#include "pc.h"
#include "defs.h"
#include "vars.h"
#include "cpubs.h"
#include "funcs.h"
#include "print.h"
#include "benchmarks.h"

inline void make_inits() {
	// char *line = NULL;
	// size_t len = 0;
	// ssize_t nread;

	printf( "\n\t   " BLUE "SIMD Arithmetic Instructions Benchmark v" VERSION OFF "\n\n" );

	// // try to get current processor name to file
	// if ( system( "grep 'model name' /proc/cpuinfo | uniq | awk '/^model name/{$1=$2=$3=\"\";print $0}' > current_processor" ) != 0 )
	// 	perror( "error due system call" );

	// // try to read current processor name from file
	// stream = fopen( "current_processor", "r" );
	// if (stream == NULL) {
	// 	perror("fopen: while reading the name of current processor");
	// 	exit(EXIT_FAILURE);
	// }
	// if ((nread = getline(&line, &len, stream)) == -1) {
	// 	perror("getline: while reading current processor name");
	// 	exit(EXIT_FAILURE);
	// }
	// sprintf( current_path, "bmresults/%s", &line[3] );
	// current_path[ strlen(current_path)-1 ] = 0;
	// printf( BLUE "Saving to:" OFF WHITE " %s" OFF "\n\n", current_path );
	// free(line);
	// fclose(stream);
	// stream = NULL;

	// // removing no more needed file 'current_processor'
	// remove("current_processor");

	get_cpu_brand_string( brand_string );
	sprintf( current_path, "bmresults/%s", brand_string );
	printf( BLUE "Saving to:" OFF WHITE " %s" OFF "\n\n", current_path );

	available_processors = get_nprocs();
	printf( BLUE "Threads:   " OFF WHITE "This system has got " BLUE "%d" OFF WHITE " processors configured and " BLUE "%d" OFF WHITE " processors available" OFF "\n\n", get_nprocs_conf(), available_processors );

	// writing machine config and cpu info to resulting file
	sprintf( _str_, "lscpu > \"%s\"; echo '' >> \"%s\"", current_path, current_path );
	if ( system( _str_ ) != 0 ) perror( "error due system call 0" );

	sprintf( _str_, "inxi -SMICfmsxxx -c 0 -t cm5 >> \"%s\"; echo '' >> \"%s\"", current_path, current_path );
	if ( system( _str_ ) != 0 ) perror( "error due system call 1" );
	if ( system( "inxi -SMICfmsxxx -c 2 -t cm5" ) != 0 ) perror( "error due system call 10" );

	// open resulting file
	stream = fopen( current_path, "a+" );
	if (stream == NULL) {
		perror("fopen: while reading the name of current processor");
		exit(EXIT_FAILURE);
	}

	fprintf( stream, "Measure:   by %i megacycles\n\n", (int32_t)(cycles_count / 1e6) );
	printf( "\n" BLUE "Measure:   " OFF WHITE "by %i megacycles" OFF "\n\n", (int32_t)(cycles_count / 1e6) );

	return;
}

inline void make_finits() {

	// print out final multi-threading rate
	make_finit_title();

	// close resulting file
	fclose(stream);

	return;
}

#endif // !__INIT_H__