
inline void avx2_simd_ai_epx16_bm() {
	uint64_t i;

	fprintf( stream, "\n\tSIMD Arithmetic instructions with 256-bit vectors of 16-bit integers (measured by %i MCycles)\n", (int32_t)(cycles_count/1e6) );
	printf( "\n\tSIMD Arithmetic instructions with 256-bit vectors of 16-bit integers (measured by %i MCycles)\n", (int32_t)(cycles_count/1e6) );

	int16_t ALIGN32 wi[ 16 ] = { 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 };
	int16_t ALIGN32 wa[ 16 ] = { 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8 };

	// add vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)wa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		v = _mm256_add_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpaddw\t_mm256_add_epi16()", 16, cycles_count, total_time );
	// print_results_epi16( "vpaddw\t_mm256_add_epi16()", 16, wi, cycles_count, total_time );

	// adds vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)wa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		v = _mm256_adds_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpaddsw\t_mm256_adds_epi16()", 16, cycles_count, total_time );
	// print_results_epi16( "vpaddsw\t_mm256_adds_epi16()", 16, wi, cycles_count, total_time );

	// adds vectors of 16 16-bit unsigned integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)wa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		v = _mm256_adds_epu16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpaddusw\t_mm256_adds_epu16()", 16, cycles_count, total_time );
	// print_results_epi16( "vpaddusw\t_mm256_adds_epu16()", 16, wi, cycles_count, total_time );

	// hadd vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)wa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		v = _mm256_hadd_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vphaddw\t_mm256_hadd_epi16()", 16, cycles_count, total_time );
	// print_results_epi16( "vphaddw\t_mm256_hadd_epi16()", 16, wi, cycles_count, total_time );

	// hadds vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)wa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		v = _mm256_hadds_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vphaddsw\t_mm256_hadds_epi16()", 16, cycles_count, total_time );
	// print_results_epi16( "vphaddsw\t_mm256_hadds_epi16()", 16, wi, cycles_count, total_time );

	// madd vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)wa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		v = _mm256_madd_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpmaddwd\t_mm256_madd_epi16()", 16, cycles_count, total_time );
	// print_results_epi16( "vpmaddwd\t_mm256_madd_epi16()", 16, wi, cycles_count, total_time );

	// maddubs vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)wa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		v = _mm256_maddubs_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpmaddubsw\t_mm256_maddubs_epi16()", 16, cycles_count, total_time );
	// print_results_epi16( "vpmaddubsw\t_mm256_maddubs_epi16()", 16, wi, cycles_count, total_time );

	// sub vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)wa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		v = _mm256_sub_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpsubw\t_mm256_sub_epi16()", 16, cycles_count, total_time );
	// print_results_epi16( "vpsubw\t_mm256_sub_epi16()", 16, wi, cycles_count, total_time );

	// subs vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)wa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		v = _mm256_subs_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpsubsw\t_mm256_subs_epi16()", 16, cycles_count, total_time );
	// print_results_epi16( "vpsubsw\t_mm256_subs_epi16()", 16, wi, cycles_count, total_time );

	// subs vectors of 16 16-bit unsigned integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)wa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		v = _mm256_subs_epu16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpsubusw\t_mm256_subs_epu16()", 16, cycles_count, total_time );
	// print_results_epi16( "vpsubusw\t_mm256_subs_epu16()", 16, wi, cycles_count, total_time );

	// hsub vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)wa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		v = _mm256_hsub_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vphsubw\t_mm256_hsub_epi16()", 16, cycles_count, total_time );
	// print_results_epi16( "vphsubw\t_mm256_hsub_epi16()", 16, wi, cycles_count, total_time );

	// hsubs vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)wa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		v = _mm256_hsubs_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vphsubsw\t_mm256_hsubs_epi16()", 16, cycles_count, total_time );
	// print_results_epi16( "vphsubsw\t_mm256_hsubs_epi16()", 16, wi, cycles_count, total_time );

	// mulhi vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)wa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		v = _mm256_mulhi_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpmulhw\t_mm256_mulhi_epi16()", 16, cycles_count, total_time );
	// print_results_epi16( "vpmulhw\t_mm256_mulhi_epi16()", 16, wi, cycles_count, total_time );

	// mullo vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)wa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		v = _mm256_mullo_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpmullw\t_mm256_mullo_epi16()", 16, cycles_count, total_time );
	// print_results_epi16( "vpmullw\t_mm256_mullo_epi16()", 16, wi, cycles_count, total_time );

	// mulhrs vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)wa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		v = _mm256_mulhrs_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpmulhrsw\t_mm256_mulhrs_epi16()", 16, cycles_count, total_time );
	// print_results_epi16( "vpmulhrsw\t_mm256_mulhrs_epi16()", 16, wi, cycles_count, total_time );

	// mulhi vectors of 16 16-bit unsigned integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)wa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		v = _mm256_mulhi_epu16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpmulhuw\t_mm256_mulhi_epu16()", 16, cycles_count, total_time );
	// print_results_epi16( "vpmulhuw\t_mm256_mulhi_epu16()", 16, wi, cycles_count, total_time );

	// sign vectors of 16 16-bit signed integers at a cycle
	_BMARK_ON_;
	a = _mm256_load_si256( (const __m256i *)wa );
	for ( i = 0; i < cycles_count; i++ ) {
		v = _mm256_load_si256( (const __m256i *)wi );
		v = _mm256_sign_epi16( v, a );
		_mm256_store_si256( (__m256i *)wi, v );
	}
	_BMARK_OFF( total_time );
	print_results( "vpsignw\t_mm256_sign_epi16()", 16, cycles_count, total_time );
	// print_results_epi16( "vpsignw\t_mm256_sign_epi16()", 16, wi, cycles_count, total_time );

	return;
}
