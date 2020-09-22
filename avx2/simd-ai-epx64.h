#ifndef __SIMD_AVX2_AI_EPX64_BM_H__
#define __SIMD_AVX2_AI_EPX64_BM_H__

const uint8_t avx2_ai_epx64_cnt = 2;

const char *avx2_ai_epx64_instructions[ avx2_ai_epx64_cnt + 1 ] = {
	"SIMD AVX2 64-bit Integer Arithmetic Instructions with 256-bit vectors ...",
	"vpaddq\t_mm256_add_epi64()",
	"vpsubq\t_mm256_sub_epi64()"
};

void* avx2_ai_epx64_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	char name[ 25 ];
	uint64_t i;

	sprintf( name, "avx2_aiep64th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 4;
	int64_t ALIGN32 qi[ vector_capacity ] = { 8, 7, 6, 5 };
	int64_t ALIGN32 qa[ vector_capacity ] = { 1, 2, 3, 4 };

	while ( td->thread_active ) {

		pthread_mutex_lock( &lock );
		while ( (td->instruction == 0) && td->thread_active )
			pthread_cond_wait( &start, &lock );
		pthread_mutex_unlock( &lock );

		if ( !td->thread_active ) break;

		ai = _mm256_load_si256( (const __m256i *)qa );

		switch ( td->instruction ) {

			case 1: // add vectors of 4 64-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)qi );
					vi = _mm256_add_epi64( vi, ai );
					_mm256_store_si256( (__m256i *)qi, vi );
				}
				break;

			case 2: // sub vectors of 4 64-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					vi = _mm256_load_si256( (const __m256i *)qi );
					vi = _mm256_sub_epi64( vi, ai );
					_mm256_store_si256( (__m256i *)qi, vi );
				}
				break;

			default:
				printf( "avx2_ai_epx64_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		td->instruction = 0;
		SET_BIT( active_threads, td->tid, 0 );
		if ( !active_threads )
			pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	return NULL;
}

#endif // !__SIMD_AVX2_AI_EPX64_BM_H__