#ifndef __SIMD_MMX_AI_EPX8_BM_H__
#define __SIMD_MMX_AI_EPX8_BM_H__

const uint8_t mmx_ai_epx8_cnt = 12;

const char *mmx_ai_epx8_instructions[ mmx_ai_epx8_cnt + 1 ] = {
	"SIMD MMX 8-bit Integer Arithmetic Instructions with 64-bit vectors ...",
	"paddb\t_mm_add_pi8        ",
	"paddsb\t_mm_adds_pi8      ",
	"paddusb\t_mm_adds_pu8     ",
	"psubb\t_mm_sub_pi8        ",
	"psubsb\t_mm_subs_pi8      ",
	"psubusb\t_mm_subs_pu8     ",
	"paddb\t_m_paddb           ",
	"paddsb\t_m_paddsb         ",
	"paddusb\t_m_paddusb       ",
	"psubb\t_m_psubb           ",
	"psubsb\t_m_psubsb         ",
	"psubusb\t_m_psubusb       "
};

void* mmx_ai_epx8_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	uint64_t i, _vi_;
	char name[ 25 ];

	sprintf( name, "mmx_aiep8th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 8;
	uint64_t alloc_length = MT_BM_CYCLES_PER_TIME * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( int8_t );
	int8_t *si8 __attribute__((aligned(16))) = (int8_t*)aligned_alloc( 16, alloc_size );
	if ( !si8 ) perror( "aligned_alloc() error" );

	ci = _mm_set_si64_epi8( 8, 7, 6, 5, 4, 3, 2, 1 );

	pthread_mutex_lock( &lock );
	while ( (td->instruction == 0) && td->thread_active )
		pthread_cond_wait( &start, &lock );
	pthread_mutex_unlock( &lock );

	while ( td->thread_active ) {

		pc_get( td->cycles_count );

		if ( !td->thread_active ) break;

		switch ( td->instruction ) {

			case 1: // paddb vectors of 8 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si8[_vi_] );
					xi = _mm_add_pi8( xi, ci );
					_mm_store_si64( (__m64 *)&si8[_vi_], xi );
				}
				break;

			case 2: // paddsb vectors of 8 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si8[_vi_] );
					xi = _mm_adds_pi8( xi, ci );
					_mm_store_si64( (__m64 *)&si8[_vi_], xi );
				}
				break;

			case 3: // paddusb vectors of 8 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si8[_vi_] );
					xi = _mm_adds_pu8( xi, ci );
					_mm_store_si64( (__m64 *)&si8[_vi_], xi );
				}
				break;

			case 4: // psubb vectors of 8 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si8[_vi_] );
					xi = _mm_sub_pi8( xi, ci );
					_mm_store_si64( (__m64 *)&si8[_vi_], xi );
				}
				break;

			case 5: // psubsb vectors of 8 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si8[_vi_] );
					xi = _mm_subs_pi8( xi, ci );
					_mm_store_si64( (__m64 *)&si8[_vi_], xi );
				}
				break;

			case 6: // psubusb vectors of 8 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si8[_vi_] );
					xi = _mm_subs_pu8( xi, ci );
					_mm_store_si64( (__m64 *)&si8[_vi_], xi );
				}
				break;

			case 7: // paddb vectors of 8 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si8[_vi_] );
					xi = _m_paddb( xi, ci );
					_mm_store_si64( (__m64 *)&si8[_vi_], xi );
				}
				break;

			case 8: // paddsb vectors of 8 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si8[_vi_] );
					xi = _m_paddsb( xi, ci );
					_mm_store_si64( (__m64 *)&si8[_vi_], xi );
				}
				break;

			case 9: // paddusb vectors of 8 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si8[_vi_] );
					xi = _m_paddusb( xi, ci );
					_mm_store_si64( (__m64 *)&si8[_vi_], xi );
				}
				break;

			case 10:// psubb vectors of 8 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si8[_vi_] );
					xi = _m_psubb( xi, ci );
					_mm_store_si64( (__m64 *)&si8[_vi_], xi );
				}
				break;

			case 11:// psubsb vectors of 8 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si8[_vi_] );
					xi = _m_psubsb( xi, ci );
					_mm_store_si64( (__m64 *)&si8[_vi_], xi );
				}
				break;

			case 12:// psubusb vectors of 8 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si8[_vi_] );
					xi = _m_psubusb( xi, ci );
					_mm_store_si64( (__m64 *)&si8[_vi_], xi );
				}
				break;

			default:
				printf( "mmx_ai_epx8_bm_thread%u havn't instruction\n", td->tid );

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

#endif // !__SIMD_MMX_AI_EPX8_BM_H__