#ifndef __SIMD_SSSE3_AI_EPX32_BM_H__
#define __SIMD_SSSE3_AI_EPX32_BM_H__

const uint8_t ssse3_ai_epx32_cnt = 6;

const char *ssse3_ai_epx32_instructions[ ssse3_ai_epx32_cnt + 1 ] = {
	"SIMD SSSE3 32-bit Integer Arithmetic Instructions with 64-bit & 128-bit vectors ...",
	"phaddd\t_mm_hadd_epi32()",
	"phsubd\t_mm_hsub_epi32()",
	"psignd\t_mm_sign_epi32()",
	"phaddw\t_mm_hadd_pi32() ",
	"phsubd\t_mm_hsub_pi32() ",
	"psignd\t_mm_sign_pi32() "
};

void* ssse3_ai_epx32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	char name[ 25 ];
	uint64_t i;

	sprintf( name, "ssse3_aiep32th%u", td->tid );
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
		ci = _mm_load_si64( (const __m64 *)da );

		switch ( td->instruction ) {

			case 1: // add vectors of 4 32-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					wi = _mm_load_si128( (const __m128i *)di );
					wi = _mm_hadd_epi32( wi, bi );
					_mm_store_si128( (__m128i *)di, wi );
				}
				break;

			case 2: // hadd vectors of 4 32-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					wi = _mm_load_si128( (const __m128i *)di );
					wi = _mm_hsub_epi32( wi, bi );
					_mm_store_si128( (__m128i *)di, wi );
				}
				break;

			case 3: // sub vectors of 4 32-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++ ) {
					wi = _mm_load_si128( (const __m128i *)di );
					wi = _mm_sign_epi32( wi, bi );
					_mm_store_si128( (__m128i *)di, wi );
				}
				break;

			case 4: // hsub vectors of 2 32-bit signed integers at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++ ) {
					xi = _mm_load_si64( (const __m64 *)di );
					xi = _mm_hadd_pi32( xi, ci );
					_mm_store_si64( (__m64 *)di, xi );
				}
				break;

			case 5: // mul vectors of 2 32-bit signed integers at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++ ) {
					xi = _mm_load_si64( (const __m64 *)di );
					xi = _mm_hsub_pi32( xi, ci );
					_mm_store_si64( (__m64 *)di, xi );
				}
				break;

			case 6: // mul vectors of 2 32-bit unsigned integers at cycle
				vector_capacity = 2;
				for ( i = 0; i < td->cycles_count; i++ ) {
					xi = _mm_load_si64( (const __m64 *)di );
					xi = _mm_sign_pi32( xi, ci );
					_mm_store_si64( (__m64 *)di, xi );
				}
				break;

			default:
				printf( "ssse3_ai_epx32_bm_thread%u havn't instruction\n", td->tid );

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

#endif // !__SIMD_SSSE3_AI_EPX32_BM_H__