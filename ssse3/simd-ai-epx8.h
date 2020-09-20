#ifndef __SIMD_SSSE3_AI_EPX8_BM_H__
#define __SIMD_SSSE3_AI_EPX8_BM_H__

const uint8_t ssse3_ai_epx8_cnt = 2;

const char *ssse3_ai_epx8_instructions[ ssse3_ai_epx8_cnt + 1 ] = {
	"SIMD SSSE3 8-bit Integer Arithmetic Instructions with 64-bit & 128-bit vectors ...",
	"psignb\t_mm_sign_epi8()     ",
	"psignb\t_mm_sign_pi8()      "
};

void* ssse3_ai_epx8_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	char name[ 25 ];
	uint64_t i;

	sprintf( name, "ssse3_aiep8th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 16;
	int8_t ALIGN16 _bi[ vector_capacity ] = { 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 };
	int8_t ALIGN16 _ba[ vector_capacity ] = { 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8 };

	while ( td->thread_active ) {

		pthread_mutex_lock( &lock );
		while ( (td->instruction == 0) && td->thread_active )
			pthread_cond_wait( &start, &lock );
		pthread_mutex_unlock( &lock );

		if ( !td->thread_active ) break;

		bi = _mm_load_si128( (const __m128i *)_ba );
		ci = _mm_load_si64( (const __m64 *)_ba );

		switch ( td->instruction ) {

			case 1: // add vectors of 16 8-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					wi = _mm_load_si128( (const __m128i *)_bi );
					wi = _mm_sign_epi8( wi, bi );
					_mm_store_si128( (__m128i *)_bi, wi );
				}
				break;

			case 2: // adds vectors of 8 8-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++ ) {
					xi = _mm_load_si64( (const __m64 *)_bi );
					xi = _mm_sign_pi8( xi, ci );
					_mm_store_si64( (__m64 *)_bi, xi );
				}
				break;

			default:
				printf( "ssse3_ai_epx8_bm_thread%u havn't instruction\n", td->tid );

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

#endif // !__SIMD_SSSE3_AI_EPX8_BM_H__