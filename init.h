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

	printf( "\n\t   " BLUE "SIMD Arithmetic Instructions Benchmark v" VERSION OFF "\n\n" );

	get_cpu_brand_string( brand_string );
	sprintf( current_path, "bmresults/%s", brand_string );
	printf( BLUE "Saving to:" OFF WHITE " %s" OFF "\n\n", current_path );

	available_processors = get_nprocs();
	printf( BLUE "Threads:   " OFF WHITE "This system has got " BLUE "%d" OFF WHITE " processors configured and " BLUE "%d" OFF WHITE " processors available" OFF "\n\n", get_nprocs_conf(), available_processors );

	// writing machine config and cpu info into resulting file
	sprintf( _str_, "lscpu > \"%s\"; echo '' >> \"%s\"", current_path, current_path );
	if ( system( _str_ ) != 0 ) perror( "error due system call 0" );

	sprintf( _str_, "inxi -SMICGfmsxxx -c 0 -t cm5 >> \"%s\"; echo '' >> \"%s\"", current_path, current_path );
	if ( system( _str_ ) != 0 ) perror( "error due system call 1" );
	if ( system( "inxi -SMICGfmsxxx -c 2 -t cm5" ) != 0 ) perror( "error due system call 10" );

	// open resulting file
	stream = fopen( current_path, "a+" );
	if ( stream == NULL ) {
		perror("fopen: while reading the brand name of the current processor");
		exit( EXIT_FAILURE );
	}

	fprintf( stream, "Measure:   by %i megacycles\n\n", (int32_t)(cycles_count / 1000000) );
	printf( "\n" BLUE "Measure:   " OFF WHITE "by %i megacycles" OFF "\n\n", (int32_t)(cycles_count / 1000000) );

	return;
}

inline void make_finits() {

	// print out final multi-threading rate
	make_finit_title();

	// close resulting file
	fclose( stream );

	return;
}

#endif // !__INIT_H__