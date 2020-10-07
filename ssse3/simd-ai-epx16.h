#ifndef __SIMD_SSSE3_AI_EPX16_BM_H__
#define __SIMD_SSSE3_AI_EPX16_BM_H__

const uint8_t ssse3_ai_epx16_cnt = 14;

const char *ssse3_ai_epx16_instructions[ ssse3_ai_epx16_cnt + 1 ] = {
	"SIMD SSSE3 16-bit Integer Arithmetic Instructions with 64-bit & 128-bit vectors ...",
	"phaddw\t_mm_hadd_epi16()      ",
	"phaddsw\t_mm_hadds_epi16()    ",
	"phsubw\t_mm_hsub_epi16()      ",
	"phsubsw\t_mm_hsubs_epi16()    ",
	"pmaddubsw\t_mm_maddubs_epi16()",
	"pmulhrsw\t_mm_mulhrs_epi16()  ",
	"psignw\t_mm_sign_epi16()      ",
	"phaddw\t_mm_hadd_pi16()       ",
	"phaddsw\t_mm_hadds_pi16()     ",
	"phsubw\t_mm_hsub_pi16()       ",
	"phsubsw\t_mm_hsubs_pi16()     ",
	"pmaddubsw\t_mm_maddubs_pi16() ",
	"pmulhrsw\t_mm_mulhrs_pi16()   ",
	"psignw\t_mm_sign_pi16()       "
};

inline void ssse3_ai_epx16_bm( thread_data_t *td,  pc_data_t *pc, int16_t *si16, int32_t vector_offset ) {
	int64_t i;
	int16_t *p __attribute__((aligned(16)));
	__m128i wi;
	__m128i bi = _mm_set_epi16( 8, 7, 6, 5, 4, 3, 2, 1 );
	__m64 xi;
	__m64 ci = _mm_set_si64_epi16( 4, 3, 2, 1 );

	while ( td->thread_active ) {

		p = si16;

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		switch ( td->instruction ) {

			case 1: // add vectors of 8 16-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)p );
					wi = _mm_hadd_epi16( wi, bi );
					_mm_store_si128( (__m128i *)p, wi );
				}
				break;

			case 2: // adds vectors of 8 16-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)p );
					wi = _mm_hadds_epi16( wi, bi );
					_mm_store_si128( (__m128i *)p, wi );
				}
				break;

			case 3: // adds vectors of 8 16-bit unsigned integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)p );
					wi = _mm_hsub_epi16( wi, bi );
					_mm_store_si128( (__m128i *)p, wi );
				}
				break;

			case 4: // hadd vectors of 8 16-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)p );
					wi = _mm_hsubs_epi16( wi, bi );
					_mm_store_si128( (__m128i *)p, wi );
				}
				break;

			case 5: // hadds vectors of 8 16-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)p );
					wi = _mm_maddubs_epi16( wi, bi );
					_mm_store_si128( (__m128i *)p, wi );
				}
				break;

			case 6: // madd vectors of 8 16-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)p );
					wi = _mm_mulhrs_epi16( wi, bi );
					_mm_store_si128( (__m128i *)p, wi );
				}
				break;

			case 7: // maddubs vectors of 8 16-bit signed integers at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					wi = _mm_load_si128( (const __m128i *)p );
					wi = _mm_sign_epi16( wi, bi );
					_mm_store_si128( (__m128i *)p, wi );
				}
				break;

			case 8: // add vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = *((const __m64*)p);
					xi = _mm_hadd_pi16( xi, ci );
					*((__m64 *)p) = xi;
				}
				break;

			case 9: // adds vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = *((const __m64*)p);
					xi = _mm_hadds_pi16( xi, ci );
					*((__m64 *)p) = xi;
				}
				break;

			case 10:// adds vectors of 4 16-bit unsigned integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = *((const __m64*)p);
					xi = _mm_hsub_pi16( xi, ci );
					*((__m64 *)p) = xi;
				}
				break;

			case 11:// hadd vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = *((const __m64*)p);
					xi = _mm_hsubs_pi16( xi, ci );
					*((__m64 *)p) = xi;
				}
				break;

			case 12:// hadds vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = *((const __m64*)p);
					xi = _mm_maddubs_pi16( xi, ci );
					*((__m64 *)p) = xi;
				}
				break;

			case 13:// madd vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = *((const __m64*)p);
					xi = _mm_mulhrs_pi16( xi, ci );
					*((__m64 *)p) = xi;
				}
				break;

			case 14:// maddubs vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = *((const __m64*)p);
					xi = _mm_sign_pi16( xi, ci );
					*((__m64 *)p) = xi;
				}
				break;

			default:
				printf( "ssse3_ai_epx16_bm_thread%u havn't instruction\n", td->tid );

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

void* ssse3_ai_epx16_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 8;

	sprintf( td->name, "ssse3_aiep16th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( ST_BM_CYCLES_PER_TIME > MT_BM_CYCLES_PER_TIME ? ST_BM_CYCLES_PER_TIME : MT_BM_CYCLES_PER_TIME ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( int16_t );
	int16_t *si16 __attribute__((aligned(16))) = (int16_t*)aligned_alloc( 16, alloc_size );
	if ( !si16 ) perror( "aligned_alloc() error" );

	ssse3_ai_epx16_bm( td, &pc[ DSP_PC ], si16, 8 );

	if ( si16 ) free( si16 );

	return NULL;
}

void* ssse3_ai_epx16_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 0;

	sprintf( td->name, "ssse3caiep16th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	int16_t si16[ 8 ] __attribute__((aligned(16))) = { 8, 7, 6, 5, 4, 3, 2, 1 };

	ssse3_ai_epx16_bm( td, &pc[ CPU_PC ], si16, 0 );

	return NULL;
}

#endif // !__SIMD_SSSE3_AI_EPX16_BM_H__