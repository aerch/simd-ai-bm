#ifndef __SIMD_MMX_AI_EPX8_BM_H__
#define __SIMD_MMX_AI_EPX8_BM_H__

const uint8_t mmx_ai_epx8_cnt = 12;

const char *mmx_ai_epx8_instructions[ mmx_ai_epx8_cnt + 1 ] = {
	"SIMD MMX 8-bit Integer Arithmetic Instructions with 64-bit vectors ...",
	"paddb\t__m64 _mm_add_pi8     ",
	"paddsb\t__m64 _mm_adds_pi8   ",
	"paddusb\t__m64 _mm_adds_pu8  ",
	"psubb\t__m64 _mm_sub_pi8     ",
	"psubsb\t__m64 _mm_subs_pi8   ",
	"psubusb\t__m64 _mm_subs_pu8  ",
	"paddb\t__m64 _m_paddb        ",
	"paddsb\t__m64 _m_paddsb      ",
	"paddusb\t__m64 _m_paddusb    ",
	"psubb\t__m64 _m_psubb        ",
	"psubsb\t__m64 _m_psubsb      ",
	"psubusb\t__m64 _m_psubusb    "
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

			case 1: // add vectors of 8 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si8[_vi_] );
					xi = _m_psadbw( xi, ci );
					_mm_store_si64( (__m64 *)&si8[_vi_], xi );
				}
				break;

			case 2: // adds vectors of 8 8-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si8[_vi_] );
					xi = _mm_sad_pu8( xi, ci );
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