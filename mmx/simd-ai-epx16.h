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

inline void mmx_ai_epx16_bm( thread_data_t *td,  pc_data_t *pc, int16_t *si16, int32_t vector_offset ) {
	int64_t i;
	int16_t *p __attribute__((aligned(16)));
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

			case 1: // paddw vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)p );
					xi = _mm_add_pi16( xi, ci );
					_mm_store_si64( (__m64 *)p, xi );
				}
				break;

			case 2: // paddsw vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)p );
					xi = _mm_adds_pi16( xi, ci );
					_mm_store_si64( (__m64 *)p, xi );
				}
				break;

			case 3: // paddusw vectors of 4 16-bit unsigned integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)p );
					xi = _mm_adds_pu16( xi, ci );
					_mm_store_si64( (__m64 *)p, xi );
				}
				break;

			case 4: // pmaddwd vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)p );
					xi = _mm_madd_pi16( xi, ci );
					_mm_store_si64( (__m64 *)p, xi );
				}
				break;

			case 5: // pmulhw vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)p );
					xi = _mm_mulhi_pi16( xi, ci );
					_mm_store_si64( (__m64 *)p, xi );
				}
				break;

			case 6: // pmullw vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)p );
					xi = _mm_mullo_pi16( xi, ci );
					_mm_store_si64( (__m64 *)p, xi );
				}
				break;

			case 7: // psubw vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)p );
					xi = _mm_sub_pi16( xi, ci );
					_mm_store_si64( (__m64 *)p, xi );
				}
				break;

			case 8: // psubsw vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)p );
					xi = _mm_subs_pi16( xi, ci );
					_mm_store_si64( (__m64 *)p, xi );
				}
				break;

			case 9: // psubusw vectors of 4 16-bit unsigned integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)p );
					xi = _mm_subs_pu16( xi, ci );
					_mm_store_si64( (__m64 *)p, xi );
				}
				break;

			case 10:// paddsw vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)p );
					xi = _m_paddsw( xi, ci );
					_mm_store_si64( (__m64 *)p, xi );
				}
				break;

			case 11:// paddusw vectors of 4 16-bit unsigned integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)p );
					xi = _m_paddusw( xi, ci );
					_mm_store_si64( (__m64 *)p, xi );
				}
				break;

			case 12:// paddw vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)p );
					xi = _m_paddw( xi, ci );
					_mm_store_si64( (__m64 *)p, xi );
				}
				break;

			case 13:// psubsw vectors of 4 16-bit unsigned integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)p );
					xi = _m_psubsw( xi, ci );
					_mm_store_si64( (__m64 *)p, xi );
				}
				break;

			case 14:// psubusw vectors of 4 16-bit unsigned integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)p );
					xi = _m_psubusw( xi, ci );
					_mm_store_si64( (__m64 *)p, xi );
				}
				break;

			case 15:// psubw vectors of 4 16-bit unsigned integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)p );
					xi = _m_psubw( xi, ci );
					_mm_store_si64( (__m64 *)p, xi );
				}
				break;

			case 16:// pmaddwd vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)p );
					xi = _m_pmaddwd( xi, ci );
					_mm_store_si64( (__m64 *)p, xi );
				}
				break;

			case 17:// pmulhw vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)p );
					xi = _m_pmulhw( xi, ci );
					_mm_store_si64( (__m64 *)p, xi );
				}
				break;

			case 18:// pmullw vectors of 4 16-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					xi = _mm_load_si64( (const __m64 *)p );
					xi = _m_pmullw( xi, ci );
					_mm_store_si64( (__m64 *)p, xi );
				}
				break;

			default:
				printf( "mmx_ai_epx16_bm_thread%u havn't instruction\n", td->tid );

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

void* mmx_ai_epx16_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 4;

	sprintf( td->name, "mmx_aiep16th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( ST_BM_CYCLES_PER_TIME > MT_BM_CYCLES_PER_TIME ? ST_BM_CYCLES_PER_TIME : MT_BM_CYCLES_PER_TIME ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( int16_t );
	int16_t *si16 __attribute__((aligned(16))) = (int16_t*)aligned_alloc( 16, alloc_size );
	if ( !si16 ) perror( "aligned_alloc() error" );

	mmx_ai_epx16_bm( td, &pc[ DSP_PC ], si16, 4 );

	if ( si16 ) free( si16 );

	return NULL;
}

void* mmx_ai_epx16_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 0;

	sprintf( td->name, "mmxcaiep16th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	int16_t si16[ 4 ] __attribute__((aligned(16))) = { 8, 7, 6, 5 };

	mmx_ai_epx16_bm( td, &pc[ CPU_PC ], si16, 0 );

	return NULL;
}

#endif // !__SIMD_MMX_AI_EPX16_BM_H__