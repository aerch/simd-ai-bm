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

void* ssse3_ai_epx16_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	uint64_t i, _vi_;
	char name[ 25 ];

	sprintf( name, "ssse3_aiep16th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 8;
	uint64_t alloc_length = MT_BM_CYCLES_PER_TIME * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( int16_t );
	int16_t *si16 __attribute__((aligned(16))) = (int16_t*)aligned_alloc( 16, alloc_size );
	if ( !si16 ) perror( "aligned_alloc() error" );

	bi = _mm_set_epi16( 8, 7, 6, 5, 4, 3, 2, 1 );
	ci = _mm_set_si64_epi16( 4, 3, 2, 1 );

	pthread_mutex_lock( &lock );
	while ( (td->instruction == 0) && td->thread_active )
		pthread_cond_wait( &start, &lock );
	pthread_mutex_unlock( &lock );

	while ( td->thread_active ) {

		pc_get( td->cycles_count );

		if ( !td->thread_active ) break;

		switch ( td->instruction ) {

			case 1: // add vectors of 8 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si16[_vi_] );
					wi = _mm_hadd_epi16( wi, bi );
					_mm_store_si128( (__m128i *)&si16[_vi_], wi );
				}
				break;

			case 2: // adds vectors of 8 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si16[_vi_] );
					wi = _mm_hadds_epi16( wi, bi );
					_mm_store_si128( (__m128i *)&si16[_vi_], wi );
				}
				break;

			case 3: // adds vectors of 8 16-bit unsigned integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si16[_vi_] );
					wi = _mm_hsub_epi16( wi, bi );
					_mm_store_si128( (__m128i *)&si16[_vi_], wi );
				}
				break;

			case 4: // hadd vectors of 8 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si16[_vi_] );
					wi = _mm_hsubs_epi16( wi, bi );
					_mm_store_si128( (__m128i *)&si16[_vi_], wi );
				}
				break;

			case 5: // hadds vectors of 8 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si16[_vi_] );
					wi = _mm_maddubs_epi16( wi, bi );
					_mm_store_si128( (__m128i *)&si16[_vi_], wi );
				}
				break;

			case 6: // madd vectors of 8 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si16[_vi_] );
					wi = _mm_mulhrs_epi16( wi, bi );
					_mm_store_si128( (__m128i *)&si16[_vi_], wi );
				}
				break;

			case 7: // maddubs vectors of 8 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si16[_vi_] );
					wi = _mm_sign_epi16( wi, bi );
					_mm_store_si128( (__m128i *)&si16[_vi_], wi );
				}
				break;

			case 8: // add vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _mm_hadd_pi16( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 9: // adds vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _mm_hadds_pi16( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 10:// adds vectors of 4 16-bit unsigned integers at cycle
				vector_capacity = 4;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _mm_hsub_pi16( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 11:// hadd vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _mm_hsubs_pi16( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 12:// hadds vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _mm_maddubs_pi16( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 13:// madd vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _mm_mulhrs_pi16( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 14:// maddubs vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _mm_sign_pi16( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			default:
				printf( "ssse3_ai_epx16_bm_thread%u havn't instruction\n", td->tid );

		}

		pthread_mutex_lock( &lock );
		pthread_cond_signal( &stop );
		pthread_mutex_unlock( &lock );

	}

	pthread_mutex_lock( &lock );
	active_threads--;
	pthread_cond_signal( &finish );
	pthread_mutex_unlock( &lock );

	if ( si16 )
		free( si16 );

	return NULL;
}

#endif // !__SIMD_SSSE3_AI_EPX16_BM_H__