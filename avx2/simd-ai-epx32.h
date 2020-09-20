#ifndef __SIMD_AVX2_AI_EPX32_BM_H__
#define __SIMD_AVX2_AI_EPX32_BM_H__

const uint8_t avx2_ai_epx32_cnt = 8;

const char *avx2_ai_epx32_instructions[ avx2_ai_epx32_cnt + 1 ] = {
	"SIMD AVX2 32-bit Integer Arithmetic Instructions with 256-bit vectors ...",
	"vpaddd\t_mm256_add_epi32()",
	"vphaddd\t_mm256_hadd_epi32()",
	"vpsubd\t_mm256_sub_epi32()",
	"vphsubd\t_mm256_hsub_epi32()",
	"vpmuldq\t_mm256_mul_epi32()",
	"vpmuludq\t_mm256_mul_epu32()",
	"vpmulld\t_mm256_mullo_epi32()",
	"vpsignd\t_mm256_sign_epi32()"
};

void* avx2_ai_epx32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	char name[ 25 ];
	uint64_t i;

	sprintf( name, "avx2_aiep32th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 8;
	int32_t ALIGN32 di[ vector_capacity ] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	int32_t ALIGN32 da[ vector_capacity ] = { 1, 2, 3, 4, 5, 6, 7, 8 };

	while ( td->thread_active ) {

		pthread_mutex_lock( &lock );
		while ( (td->instruction == 0) && td->thread_active )
			pthread_cond_wait( &start, &lock );
		pthread_mutex_unlock( &lock );

		if ( !td->thread_active ) break;

		ai = _mm256_load_si256( (const __m256i *)da );

		switch ( td->instruction ) {

			case 1: // add vectors of 8 32-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)di );
					vi = _mm256_add_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)di, vi );
				}
				break;

			case 2: // hadd vectors of 8 32-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)di );
					vi = _mm256_hadd_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)di, vi );
				}
				break;

			case 3: // sub vectors of 8 32-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)di );
					vi = _mm256_sub_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)di, vi );
				}
				break;

			case 4: // hsub vectors of 8 32-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)di );
					vi = _mm256_hsub_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)di, vi );
				}
				break;

			case 5: // mul vectors of 8 32-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)di );
					vi = _mm256_mul_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)di, vi );
				}
				break;

			case 6: // mul vectors of 8 32-bit unsigned integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)di );
					vi = _mm256_mul_epu32( vi, ai );
					_mm256_store_si256( (__m256i *)di, vi );
				}
				break;

			case 7: // mullo vectors of 8 32-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)di );
					vi = _mm256_mullo_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)di, vi );
				}
				break;

			case 8: // sign vectors of 8 32-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)di );
					vi = _mm256_sign_epi32( vi, ai );
					_mm256_store_si256( (__m256i *)di, vi );
				}
				break;

			default:
				printf( "avx2_ai_epx32_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		td->instruction = 0;
		SET_BIT( active_threads_flag, td->tid, 0 );
		if ( !active_threads_flag )
			pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	return NULL;
}

#endif // !__SIMD_AVX2_AI_EPX32_BM_H__