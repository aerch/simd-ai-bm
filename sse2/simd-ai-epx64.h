#ifndef __SIMD_SSE2_AI_EPX64_BM_H__
#define __SIMD_SSE2_AI_EPX64_BM_H__

const uint8_t sse2_ai_epx64_cnt = 4;

const char *sse2_ai_epx64_instructions[ sse2_ai_epx64_cnt + 1 ] = {
	"SIMD SSE2 64-bit Integer Arithmetic Instructions with 64-bit & 128-bit vectors ...",
	"paddq\t_mm_add_epi64()   ",
	"paddq\t_mm_add_si64()    ",
	"psubq\t_mm_sub_epi64()   ",
	"psubq\t_mm_sub_si64()    "
};

void* sse2_ai_epx64_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	uint64_t i, _vi_;
	char name[ 25 ];

	sprintf( name, "sse2_aiep64th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 2;
	uint64_t alloc_length = MT_BM_CYCLES_PER_TIME * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( int64_t );
	int64_t *si64 __attribute__((aligned(16))) = (int64_t*)aligned_alloc( 16, alloc_size );
	if ( !si64 ) perror( "aligned_alloc() error" );

	si64[0] = 1;
	bi = _mm_set_epi64x( 2, 1 );
	ci = _mm_load_si64( (const __m64 *)si64 );

	pthread_mutex_lock( &lock );
	while ( (td->instruction == 0) && td->thread_active )
		pthread_cond_wait( &start, &lock );
	pthread_mutex_unlock( &lock );

	while ( td->thread_active ) {

		pc_get( td->cycles_count );

		if ( !td->thread_active ) break;

		switch ( td->instruction ) {

			case 1: // add vectors of 2 64-bit signed integers at cycle
				vector_capacity = 2;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si64[_vi_] );
					wi = _mm_add_epi64( wi, bi );
					_mm_store_si128( (__m128i *)&si64[_vi_], wi );
				}
				break;

			case 2: // add vectors of 1 64-bit signed integers at cycle
				vector_capacity = 1;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si64[_vi_] );
					xi = _mm_add_si64( xi, ci );
					_mm_store_si64( (__m64 *)&si64[_vi_], xi );
				}
				break;

			case 3: // sub vectors of 2 64-bit signed integers at cycle
				vector_capacity = 2;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si64[_vi_] );
					wi = _mm_sub_epi64( wi, bi );
					_mm_store_si128( (__m128i *)&si64[_vi_], wi );
				}
				break;

			case 4: // sub vectors of 1 64-bit signed integers at cycle
				vector_capacity = 1;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si64[_vi_] );
					xi = _mm_sub_si64( xi, ci );
					_mm_store_si64( (__m64 *)&si64[_vi_], xi );
				}
				break;

			default:
				printf( "sse2_ai_epx64_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( si64 )
		free( si64 );

	return NULL;
}

#endif // !__SIMD_SSE2_AI_EPX64_BM_H__