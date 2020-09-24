#ifndef __SIMD_MMX_AI_EPX16_BM_H__
#define __SIMD_MMX_AI_EPX16_BM_H__

const uint8_t mmx_ai_epx16_cnt = 18;

const char *mmx_ai_epx16_instructions[ mmx_ai_epx16_cnt + 1 ] = {
	"SIMD MMX 16-bit Integer Arithmetic Instructions with 64-bit vectors ...",
	"paddw\t_mm_add_pi16       ",
	"paddsw\t_mm_adds_pi16     ",
	"paddusw\t_mm_adds_pu16    ",
	"pmaddwd\t_mm_madd_pi16    ",
	"pmulhw\t_mm_mulhi_pi16    ",
	"pmullw\t_mm_mullo_pi16    ",
	"psubw\t_mm_sub_pi16       ",
	"psubsw\t_mm_subs_pi16     ",
	"psubusw\t_mm_subs_pu16    ",
	"paddsw\t_m_paddsw         ",
	"paddusw\t_m_paddusw       ",
	"paddw\t_m_paddw           ",
	"psubsw\t_m_psubsw         ",
	"psubusw\t_m_psubusw       ",
	"psubw\t_m_psubw           ",
	"pmaddwd\t_m_pmaddwd       ",
	"pmulhw\t_m_pmulhw         ",
	"pmullw\t_m_pmullw         "
};

void* mmx_ai_epx16_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	uint64_t i, _vi_;
	char name[ 25 ];

	sprintf( name, "mmx_aiep16th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 4;
	uint64_t alloc_length = MT_BM_CYCLES_PER_TIME * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( int16_t );
	int16_t *si16 __attribute__((aligned(16))) = (int16_t*)aligned_alloc( 16, alloc_size );
	if ( !si16 ) perror( "aligned_alloc() error" );

	ci = _mm_set_si64_epi16( 4, 3, 2, 1 );

	pthread_mutex_lock( &lock );
	while ( (td->instruction == 0) && td->thread_active )
		pthread_cond_wait( &start, &lock );
	pthread_mutex_unlock( &lock );

	while ( td->thread_active ) {

		pc_get( td->cycles_count );

		if ( !td->thread_active ) break;

		switch ( td->instruction ) {

			case 1: // paddw vectors of 4 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _mm_add_pi16( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 2: // paddsw vectors of 4 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _mm_adds_pi16( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 3: // paddusw vectors of 4 16-bit unsigned integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _mm_adds_pu16( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 4: // pmaddwd vectors of 4 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _mm_madd_pi16( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 5: // pmulhw vectors of 4 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _mm_mulhi_pi16( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 6: // pmullw vectors of 4 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _mm_mullo_pi16( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 7: // psubw vectors of 4 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _mm_sub_pi16( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 8: // psubsw vectors of 4 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _mm_subs_pi16( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 9: // psubusw vectors of 4 16-bit unsigned integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _mm_subs_pu16( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 10:// paddsw vectors of 4 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _m_paddsw( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 11:// paddusw vectors of 4 16-bit unsigned integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _m_paddusw( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 12:// paddw vectors of 4 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _m_paddw( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 13:// psubsw vectors of 4 16-bit unsigned integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _m_psubsw( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 14:// psubusw vectors of 4 16-bit unsigned integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _m_psubusw( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 15:// psubw vectors of 4 16-bit unsigned integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _m_psubw( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 16:// pmaddwd vectors of 4 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _m_pmaddwd( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 17:// pmulhw vectors of 4 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _m_pmulhw( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			case 18:// pmullw vectors of 4 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si16[_vi_] );
					xi = _m_pmullw( xi, ci );
					_mm_store_si64( (__m64 *)&si16[_vi_], xi );
				}
				break;

			default:
				printf( "mmx_ai_epx16_bm_thread%u havn't instruction\n", td->tid );

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

#endif // !__SIMD_MMX_AI_EPX16_BM_H__