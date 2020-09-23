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
	uint64_t i, _vi_;
	char name[ 25 ];

	sprintf( name, "ssse3_aiep32th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 4;
	uint64_t alloc_length = MT_BM_CYCLES_PER_TIME * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( int32_t );
	int32_t *si32 __attribute__((aligned(16))) = (int32_t*)aligned_alloc( 16, alloc_size );
	if ( !si32 ) perror( "aligned_alloc() error" );

	bi = _mm_set_epi32( 4, 3, 2, 1 );
	ci = _mm_set_si64_epi32( 2, 1 );

	pthread_mutex_lock( &lock );
	while ( (td->instruction == 0) && td->thread_active )
		pthread_cond_wait( &start, &lock );
	pthread_mutex_unlock( &lock );

	while ( td->thread_active ) {

		pc_get( td->cycles_count );

		if ( !td->thread_active ) break;

		switch ( td->instruction ) {

			case 1: // add vectors of 4 32-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si32[_vi_] );
					wi = _mm_hadd_epi32( wi, bi );
					_mm_store_si128( (__m128i *)&si32[_vi_], wi );
				}
				break;

			case 2: // hadd vectors of 4 32-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si32[_vi_] );
					wi = _mm_hsub_epi32( wi, bi );
					_mm_store_si128( (__m128i *)&si32[_vi_], wi );
				}
				break;

			case 3: // sub vectors of 4 32-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si32[_vi_] );
					wi = _mm_sign_epi32( wi, bi );
					_mm_store_si128( (__m128i *)&si32[_vi_], wi );
				}
				break;

			case 4: // hsub vectors of 2 32-bit signed integers at cycle
				vector_capacity = 2;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si32[_vi_] );
					xi = _mm_hadd_pi32( xi, ci );
					_mm_store_si64( (__m64 *)&si32[_vi_], xi );
				}
				break;

			case 5: // mul vectors of 2 32-bit signed integers at cycle
				vector_capacity = 2;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si32[_vi_] );
					xi = _mm_hsub_pi32( xi, ci );
					_mm_store_si64( (__m64 *)&si32[_vi_], xi );
				}
				break;

			case 6: // mul vectors of 2 32-bit unsigned integers at cycle
				vector_capacity = 2;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si32[_vi_] );
					xi = _mm_sign_pi32( xi, ci );
					_mm_store_si64( (__m64 *)&si32[_vi_], xi );
				}
				break;

			default:
				printf( "ssse3_ai_epx32_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( si32 )
		free( si32 );

	return NULL;
}

#endif // !__SIMD_SSSE3_AI_EPX32_BM_H__