#ifndef __SIMD_SSE4_1_AI_EPX32_BM_H__
#define __SIMD_SSE4_1_AI_EPX32_BM_H__

const uint8_t sse4_1_ai_epx32_cnt = 2;

const char *sse4_1_ai_epx32_instructions[ sse4_1_ai_epx32_cnt + 1 ] = {
	"SIMD SSE4.1 32-bit Integer Arithmetic Instructions with 128-bit vectors ...",
	"pmuldq \t_mm_mul_epi32()    ",
	"pmulld \t_mm_mullo_epi32()    "
};

void* sse4_1_ai_epx32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	char name[ 25 ];
	uint64_t i;

	sprintf( name, "sse4.1_aiep32th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 4;
	int32_t ALIGN16 di[ vector_capacity ] = { 8, 7, 6, 5 };
	int32_t ALIGN16 da[ vector_capacity ] = { 1, 2, 3, 4 };

	while ( td->thread_active ) {

		pthread_mutex_lock( &lock );
		while ( (td->instruction == 0) && td->thread_active )
			pthread_cond_wait( &start, &lock );
		pthread_mutex_unlock( &lock );

		if ( !td->thread_active ) break;

		bi = _mm_load_si128( (const __m128i *)da );

		switch ( td->instruction ) {

			case 1: // add vectors of 8 32-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					wi = _mm_load_si128( (const __m128i *)di );
					wi = _mm_mul_epi32( wi, bi );
					_mm_store_si128( (__m128i *)di, wi );
				}
				break;

			case 2: // hadd vectors of 8 32-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					wi = _mm_load_si128( (const __m128i *)di );
					wi = _mm_mullo_epi32( wi, bi );
					_mm_store_si128( (__m128i *)di, wi );
				}
				break;

			default:
				printf( "sse4_1_ai_epx32_bm_thread%u havn't instruction\n", td->tid );

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

#endif // !__SIMD_SSE4_1_AI_EPX32_BM_H__