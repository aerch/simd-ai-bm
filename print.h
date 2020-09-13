
inline void print_results_epi8( const char* str, int32_t vecsz, int8_t *si, uint64_t cycles_count, double total_time ) {
	char _str_[ 1024 ];
	memset( _str_, 0x00, sizeof(_str_) );
	sprintf( _str_, "%s\t{", str );
	for ( int32_t i = 0; i < vecsz; i++ )
		sprintf( _str_, "%s %+11d", _str_, si[i] );
	sprintf( _str_, "%s }\n", _str_ );
	double tpc = total_time / (double)cycles_count;
	double tps = (double)vecsz / (tpc * 1.0e9);
	printf("\t   %s\t%15.12lf sec\t~%8.2e sec\t~%5.1lf GT/sec\n", str, total_time, tpc, tps );
	return;
}

inline void print_results_epi16( const char* str, int32_t vecsz, int16_t *si, uint64_t cycles_count, double total_time ) {
	char _str_[ 1024 ];
	memset( _str_, 0x00, sizeof(_str_) );
	sprintf( _str_, "%s\t{", str );
	for ( int32_t i = 0; i < vecsz; i++ )
		sprintf( _str_, "%s %+11d", _str_, si[i] );
	sprintf( _str_, "%s }\n", _str_ );
	double tpc = total_time / (double)cycles_count;
	double tps = (double)vecsz / (tpc * 1.0e9);
	printf("\t   %s\t%15.12lf sec\t~%8.2e sec\t~%5.1lf GT/sec\n", str, total_time, tpc, tps );
	return;
}

inline void print_results_epi32( const char* str, int32_t vecsz, int32_t *si, uint64_t cycles_count, double total_time ) {
	char _str_[ 1024 ];
	memset( _str_, 0x00, sizeof(_str_) );
	sprintf( _str_, "%s\t{", str );
	for ( int32_t i = 0; i < vecsz; i++ )
		sprintf( _str_, "%s %+11i", _str_, si[i] );
	sprintf( _str_, "%s }\n", _str_ );
	double tpc = total_time / (double)cycles_count;
	double tps = (double)vecsz / (tpc * 1.0e9);
	printf("\t   %s\t%15.12lf sec\t~%8.2e sec\t~%5.1lf GT/sec\n", str, total_time, tpc, tps );
	return;
}

inline void print_results_epi64( const char* str, int32_t vecsz, int64_t *si, uint64_t cycles_count, double total_time ) {
	char _str_[ 1024 ];
	memset( _str_, 0x00, sizeof(_str_) );
	sprintf( _str_, "%s\t{", str );
	for ( int32_t i = 0; i < vecsz; i++ )
		sprintf( _str_, "%s %+15li", _str_, si[i] );
	sprintf( _str_, "%s }\n", _str_ );
	double tpc = total_time / (double)cycles_count;
	double tps = (double)vecsz / (tpc * 1.0e9);
	printf("\t   %s\t%15.12lf sec\t~%8.2e sec\t~%5.1lf GT/sec\n", str, total_time, tpc, tps );
	return;
}
