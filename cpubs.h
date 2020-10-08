#ifndef __CPU_ID_H__
#define __CPU_ID_H__

// correct method to get cpu brand string
void get_cpu_brand_string( char *brand_string ) {
	uint32_t *bs = (uint32_t*)brand_string;

	if ( !__get_cpuid_max( 0x80000004, NULL ) ) {
		perror("__get_cpuid_max(): feature not implemented");
		exit(EXIT_FAILURE);
	}

	__get_cpuid(0x80000002, bs+0x0, bs+0x1, bs+0x2, bs+0x3);
	__get_cpuid(0x80000003, bs+0x4, bs+0x5, bs+0x6, bs+0x7);
	__get_cpuid(0x80000004, bs+0x8, bs+0x9, bs+0xa, bs+0xb);
	brand_string[48] = 0;

	return;
}

// // bad straight method to get cpu brand string
// void get_cpu_brand_string( char *brand_string ) {
// 	char *line = NULL;
// 	size_t len = 0;
// 	ssize_t nread;

// 	// try to get current processor name to file
// 	if ( system( "grep 'model name' /proc/cpuinfo | uniq | awk '/^model name/{$1=$2=$3=\"\";print $0}' > current_processor" ) != 0 )
// 		perror( "error due system call" );

// 	// try to read current processor name from file
// 	stream = fopen( "current_processor", "r" );
// 	if (stream == NULL) {
// 		perror("fopen: while reading the name of current processor");
// 		exit(EXIT_FAILURE);
// 	}
// 	if ((nread = getline(&line, &len, stream)) == -1) {
// 		perror("getline: while reading current processor name");
// 		exit(EXIT_FAILURE);
// 	}
// 	sprintf( current_path, "bmresults/%s", &line[3] );
// 	current_path[ strlen(current_path)-1 ] = 0;
// 	printf( BLUE "Saving to:" OFF WHITE " %s" OFF "\n\n", current_path );
// 	free(line);
// 	fclose(stream);
// 	stream = NULL;

// 	// removing no more needed file 'current_processor'
// 	remove("current_processor");

// 	return;
// }

#endif // !__CPU_ID_H__