#ifndef __SIMD_SSE4_1_AI_EPX8_BM_H__
#define __SIMD_SSE4_1_AI_EPX8_BM_H__

const uint8_t sse4_1_ai_epx8_cnt = 1;

const char *sse4_1_ai_epx8_instructions[ sse4_1_ai_epx8_cnt + 1 ] = {
	"SIMD SSE4.1 8-bit Integer Arithmetic Instructions with 128-bit vectors ...",
	"mpsadbw\t_mm_mpsadbw_epu8()"
};

void* sse4_1_ai_epx8_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	char name[ 25 ];
	uint64_t i;

	sprintf( name, "sse4.1_aiep8th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 16;
	int8_t ALIGN16 bbi[ vector_capacity ] = { 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 };
	int8_t ALIGN16 bba[ vector_capacity ] = { 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8 };

	while ( td->thread_active ) {

		pthread_mutex_lock( &lock );
		while ( (td->instruction == 0) && td->thread_active )
			pthread_cond_wait( &start, &lock );
		pthread_mutex_unlock( &lock );

		if ( !td->thread_active ) break;

		bi = _mm_load_si128( (const __m128i *)bba );

		switch ( td->instruction ) {

			case 1: // mpsadbw vectors of 16 8-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					wi = _mm_load_si128( (const __m128i *)bbi );
					wi = _mm_mpsadbw_epu8( wi, bi, 0x0f );
					_mm_store_si128( (__m128i *)bbi, wi );
				}
				break;

			default:
				printf( "sse4_1_ai_epx8_bm_thread%u havn't instruction\n", td->tid );

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

#endif // !__SIMD_SSE4_1_AI_EPX8_BM_H__