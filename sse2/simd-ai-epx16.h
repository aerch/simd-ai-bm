#ifndef __SIMD_SSE2_AI_EPX16_BM_H__
#define __SIMD_SSE2_AI_EPX16_BM_H__

const uint8_t sse2_ai_epx16_cnt = 10;

const char *sse2_ai_epx16_instructions[ sse2_ai_epx16_cnt + 1 ] = {
	"SIMD SSE2 16-bit Integer Arithmetic Instructions with 128-bit vectors ...",
	"paddw  \t_mm_add_epi16()    ",
	"paddsw \t_mm_adds_epi16()   ",
	"paddusw\t_mm_adds_epu16()   ",
	"pmaddwd\t_mm_madd_epi16()   ",
	"pmulhw \t_mm_mulhi_epi16()  ",
	"pmulhuw\t_mm_mulhi_epu16()  ",
	"pmullw \t_mm_mullo_epi16()  ",
	"psubw  \t_mm_sub_epi16()    ",
	"psubsw \t_mm_subs_epi16()   ",
	"psubusw\t_mm_subs_epu16()   "
};

inline void sse2_ai_epx16_bm( thread_data_t *td,  pc_data_t *pc, int16_t *si16 ) {
	int64_t i;
	int16_t *si16_start __attribute__((aligned(16))) = si16;
	__m128i wi;
	__m128i bi = _mm_set_epi16( 8, 7, 6, 5, 4, 3, 2, 1 );

	while ( td->thread_active ) {

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		si16 = si16_start;

		switch ( td->instruction ) {

			case 1: // add vectors of 8 16-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)si16 );
					wi = _mm_add_epi16( wi, bi );
					_mm_store_si128( (__m128i *)si16, wi );
				}
				break;

			case 2: // adds vectors of 8 16-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)si16 );
					wi = _mm_adds_epi16( wi, bi );
					_mm_store_si128( (__m128i *)si16, wi );
				}
				break;

			case 3: // adds vectors of 8 16-bit unsigned integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)si16 );
					wi = _mm_adds_epu16( wi, bi );
					_mm_store_si128( (__m128i *)si16, wi );
				}
				break;

			case 4: // madd vectors of 8 16-bit unsigned integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)si16 );
					wi = _mm_madd_epi16( wi, bi );
					_mm_store_si128( (__m128i *)si16, wi );
				}
				break;

			case 5: // mulhi vectors of 8 16-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)si16 );
					wi = _mm_mulhi_epi16( wi, bi );
					_mm_store_si128( (__m128i *)si16, wi );
				}
				break;

			case 6: // mulhi vectors of 8 16-bit unsigned integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)si16 );
					wi = _mm_mulhi_epu16( wi, bi );
					_mm_store_si128( (__m128i *)si16, wi );
				}
				break;

			case 7: // mullo vectors of 8 16-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)si16 );
					wi = _mm_mullo_epi16( wi, bi );
					_mm_store_si128( (__m128i *)si16, wi );
				}
				break;

			case 8: // sub vectors of 8 16-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)si16 );
					wi = _mm_sub_epi16( wi, bi );
					_mm_store_si128( (__m128i *)si16, wi );
				}
				break;

			case 9: // subs vectors of 8 16-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)si16 );
					wi = _mm_subs_epi16( wi, bi );
					_mm_store_si128( (__m128i *)si16, wi );
				}
				break;

			case 10:// subs vectors of 8 16-bit unsigned integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)si16 );
					wi = _mm_subs_epu16( wi, bi );
					_mm_store_si128( (__m128i *)si16, wi );
				}
				break;

			default:
				printf( "sse2_ai_epx16_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		evaluating_threads--;
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	return;
}

void* sse2_ai_epx16_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 8;

	sprintf( td->name, "sse2_aiep16th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( ST_BM_CYCLES_PER_TIME > MT_BM_CYCLES_PER_TIME ? ST_BM_CYCLES_PER_TIME : MT_BM_CYCLES_PER_TIME ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( int16_t );
	int16_t *si16 __attribute__((aligned(16))) = (int16_t*)aligned_alloc( 16, alloc_size );
	if ( !si16 ) perror( "aligned_alloc() error" );

	sse2_ai_epx16_bm( td, &pc[ DSP_PC ], si16 );

	if ( si16 ) free( si16 );

	return NULL;
}

void* sse2_ai_epx16_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 0;

	sprintf( td->name, "sse2caiep16th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	int16_t si16[ 8 ] __attribute__((aligned(16))) = { 8, 7, 6, 5, 4, 3, 2, 1 };

	sse2_ai_epx16_bm( td, &pc[ CPU_PC ], si16 );

	return NULL;
}

#endif // !__SIMD_SSE2_AI_EPX16_BM_H__