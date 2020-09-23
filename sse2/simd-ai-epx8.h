#ifndef __SIMD_SSE2_AI_EPX8_BM_H__
#define __SIMD_SSE2_AI_EPX8_BM_H__

const uint8_t sse2_ai_epx8_cnt = 7;

const char *sse2_ai_epx8_instructions[ sse2_ai_epx8_cnt + 1 ] = {
	"SIMD SSE2 8-bit Integer Arithmetic Instructions with 128-bit vectors ...",
	"paddb  \t_mm_add_epi8    ",
	"paddsb \t_mm_adds_epi8   ",
	"paddusb\t_mm_adds_epu8   ",
	"psadbw \t_mm_sad_epu8    ",
	"psubb  \t_mm_sub_epi8    ",
	"psubsb \t_mm_subs_epi8   ",
	"psubusb\t_mm_subs_epu8   "
};

void* sse2_ai_epx8_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	uint64_t i, _vi_;
	char name[ 25 ];

	sprintf( name, "sse2_aiep8th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 16;
	uint64_t alloc_length = MT_BM_CYCLES_PER_TIME * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( int8_t );
	int8_t *si8 __attribute__((aligned(16))) = (int8_t*)aligned_alloc( 16, alloc_size );
	if ( !si8 ) perror( "aligned_alloc() error" );

	bi = _mm_set_epi8( 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 );

	pthread_mutex_lock( &lock );
	while ( (td->instruction == 0) && td->thread_active )
		pthread_cond_wait( &start, &lock );
	pthread_mutex_unlock( &lock );

	while ( td->thread_active ) {

		pc_get( td->cycles_count );

		if ( !td->thread_active ) break;

		switch ( td->instruction ) {

			case 1: // add vectors of 16 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si8[_vi_] );
					wi = _mm_add_epi8( wi, bi );
					_mm_store_si128( (__m128i *)&si8[_vi_], wi );
				}
				break;

			case 2: // adds vectors of 16 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si8[_vi_] );
					wi = _mm_adds_epi8( wi, bi );
					_mm_store_si128( (__m128i *)&si8[_vi_], wi );
				}
				break;

			case 3: // adds vectors of 16 8-bit unsigned integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si8[_vi_] );
					wi = _mm_adds_epu8( wi, bi );
					_mm_store_si128( (__m128i *)&si8[_vi_], wi );
				}
				break;

			case 4: // sad vectors of 16 8-bit unsigned integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si8[_vi_] );
					wi = _mm_sad_epu8( wi, bi );
					_mm_store_si128( (__m128i *)&si8[_vi_], wi );
				}
				break;

			case 5: // sub vectors of 16 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si8[_vi_] );
					wi = _mm_sub_epi8( wi, bi );
					_mm_store_si128( (__m128i *)&si8[_vi_], wi );
				}
				break;

			case 6: // subs vectors of 16 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si8[_vi_] );
					wi = _mm_subs_epi8( wi, bi );
					_mm_store_si128( (__m128i *)&si8[_vi_], wi );
				}
				break;

			case 7: // subs vectors of 16 8-bit unsigned integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si8[_vi_] );
					wi = _mm_subs_epu8( wi, bi );
					_mm_store_si128( (__m128i *)&si8[_vi_], wi );
				}
				break;

			default:
				printf( "sse2_ai_epx8_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( si8 )
		free( si8 );

	return NULL;
}

#endif // !__SIMD_SSE2_AI_EPX8_BM_H__