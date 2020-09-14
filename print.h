
inline void print_results( const char* str, int32_t vecsz, uint64_t cycles_count, double total_time ) {
	double tpc = total_time / (double)cycles_count;
	double tps = (double)vecsz / (tpc * 1.0e9);
	total_tps += tps;
	fprintf( stream, "\t   %s\t%15.12lf sec\t~%8.2e sec\t~%5.1lf GT/sec\n", str, total_time, tpc, tps );
	printf("\t   %s\t%15.12lf sec\t~%8.2e sec\t~%5.1lf GT/sec\n", str, total_time, tpc, tps );
	return;
}

// inline void print_results_epi8( const char* str, int32_t vecsz, int8_t *si, uint64_t cycles_count, double total_time ) {
// 	// sprintf( _str_, "%s\t{", str );
// 	// for ( int32_t i = 0; i < vecsz; i++ )
// 	// 	sprintf( _str_, "%s %+11d", _str_, si[i] );
// 	// sprintf( _str_, "%s }\n", _str_ );
// 	print_results( str, vecsz, cycles_count, total_time );
// 	return;
// }

// inline void print_results_epi16( const char* str, int32_t vecsz, int16_t *si, uint64_t cycles_count, double total_time ) {
// 	// sprintf( _str_, "%s\t{", str );
// 	// for ( int32_t i = 0; i < vecsz; i++ )
// 	// 	sprintf( _str_, "%s %+11d", _str_, si[i] );
// 	// sprintf( _str_, "%s }\n", _str_ );
// 	print_results( str, vecsz, cycles_count, total_time );
// 	return;
// }

// inline void print_results_epi32( const char* str, int32_t vecsz, int32_t *si, uint64_t cycles_count, double total_time ) {
// 	// sprintf( _str_, "%s\t{", str );
// 	// for ( int32_t i = 0; i < vecsz; i++ )
// 	// 	sprintf( _str_, "%s %+11i", _str_, si[i] );
// 	// sprintf( _str_, "%s }\n", _str_ );
// 	print_results( str, vecsz, cycles_count, total_time );
// 	return;
// }

// inline void print_results_epi64( const char* str, int32_t vecsz, int64_t *si, uint64_t cycles_count, double total_time ) {
// 	// sprintf( _str_, "%s\t{", str );
// 	// for ( int32_t i = 0; i < vecsz; i++ )
// 	// 	sprintf( _str_, "%s %+15li", _str_, si[i] );
// 	// sprintf( _str_, "%s }\n", _str_ );
// 	print_results( str, vecsz, cycles_count, total_time );
// 	return;
// }
