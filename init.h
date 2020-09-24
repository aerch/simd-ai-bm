#ifndef __INIT_H__
#define __INIT_H__

#include "pc.h"
#include "defs.h"
#include "vars.h"
#include "funcs.h"
#include "print.h"
#include "benchmarks.h"

inline void make_inits() {
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	printf( "\n" BLUE "SIMD Instructions Benchmark v" VERSION OFF "\n\n" );

	// try to get current processor name to file
	if ( system( "grep 'model name' /proc/cpuinfo | uniq | awk '/^model name/{$1=$2=$3=\"\";print $0}' > current_processor" ) != 0 )
		perror( "error due system call" );

	// try to read current processor name from file
	stream = fopen( "current_processor", "r" );
	if (stream == NULL) {
		perror("fopen: while reading the name of current processor");
		exit(EXIT_FAILURE);
	}
	if ((nread = getline(&line, &len, stream)) == -1) {
		perror("getline: while reading current processor name");
		exit(EXIT_FAILURE);
	}
	sprintf( current_path, "bmresults/%s", &line[3] );
	current_path[ strlen(current_path)-1 ] = 0;
	printf( BLUE "Saving to:" OFF WHITE " %s" OFF "\n\n", current_path );
	free(line);
	fclose(stream);
	stream = NULL;

	// removing no more needed file 'current_processor'
	remove("current_processor");

	available_processors = get_nprocs();
	printf( BLUE "Threads:   " OFF WHITE "This system has " BLUE "%d" OFF WHITE " processors configured and " BLUE "%d" OFF WHITE " processors available" OFF "\n\n", get_nprocs_conf(), available_processors );

	// writing machine config and cpu info to resulting file
	sprintf( _str_, "lscpu > \"%s\"; echo '' >> \"%s\"", current_path, current_path );
	if ( system( _str_ ) != 0 ) perror( "error due system call 0" );

	sprintf( _str_, "inxi -Sxx -c 0 >> \"%s\"; echo '' >> \"%s\"", current_path, current_path );
	if ( system( _str_ ) != 0 ) perror( "error due system call 1" );
	if ( system( "inxi -Sxx -c 2" ) != 0 ) perror( "error due system call 10" );

	printf("\n");

	sprintf( _str_, "inxi -Mxx -c 0 >> \"%s\"; echo '' >> \"%s\"", current_path, current_path );
	if ( system( _str_ ) != 0 ) perror( "error due system call 2" );
	if ( system( "inxi -Mxx -c 2" ) != 0 ) perror( "error due system call 20" );

	printf("\n");

	sprintf( _str_, "inxi -Cfx -y 160 -c 0 >> \"%s\"; echo '' >> \"%s\"", current_path, current_path );
	if ( system( _str_ ) != 0 ) perror( "error due system call 3" );
	if ( system( "inxi -Cfx -y 160 -c 2" ) != 0 ) perror( "error due system call 30" );

	printf("\n");

	// open resulting file
	stream = fopen( current_path, "a+" );
	if (stream == NULL) {
		perror("fopen: while reading the name of current processor");
		exit(EXIT_FAILURE);
	}

	return;
}

inline void make_finits() {
	correlation = simd_ai_mt_bm / simd_ai_st_bm;

	fprintf( stream, "Correlation of SIMD AI Single- & Multi- Threaded Benchmark values\t\t\t\t\t\t\t      [ %5.2lf ]\n\n", correlation );
	printf( BLUE "Correlation of SIMD AI Single- & Multi- Threaded Benchmark values\t\t\t\t\t\t\t      [" WHITE " %5.2lf " OFF BLUE "]" OFF "\n\n", correlation );

	// close resulting file
	fclose(stream);

	return;
}

#endif // !__INIT_H__