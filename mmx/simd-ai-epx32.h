#ifndef __SIMD_MMX_AI_EPX32_BM_H__
#define __SIMD_MMX_AI_EPX32_BM_H__

const uint8_t mmx_ai_epx32_cnt = 4;

const char *mmx_ai_epx32_instructions[ mmx_ai_epx32_cnt + 1 ] = {
	"SIMD MMX 32-bit Integer Arithmetic Instructions with 64-bit vectors ...",
	"paddd\t__m64 _mm_add_pi32    ",
	"psubd\t__m64 _mm_sub_pi32    ",
	"paddd\t__m64 _m_paddd        ",
	"psubd\t__m64 _m_psubd        "
};

void* mmx_ai_epx32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	uint64_t i, _vi_;
	char name[ 25 ];

	sprintf( name, "mmx_aiep32th%u", td->tid );
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
				vector_capacity = 4;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si32[_vi_] );
					wi = _mm_add_epi32( wi, bi );
					_mm_store_si128( (__m128i *)&si32[_vi_], wi );
				}
				break;

			case 2: // mul vectors of 4 32-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si32[_vi_] );
					wi = _mm_mul_epu32( wi, bi );
					_mm_store_si128( (__m128i *)&si32[_vi_], wi );
				}
				break;

			case 3: // mul vectors of 2 32-bit signed integers at cycle
				vector_capacity = 2;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					xi = _mm_load_si64( (const __m64 *)&si32[_vi_] );
					xi = _mm_mul_su32( xi, ci );
					_mm_store_si64( (__m64 *)&si32[_vi_], xi );
				}
				break;

			case 4: // sub vectors of 4 32-bit signed integers at cycle
				vector_capacity = 4;
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					wi = _mm_load_si128( (const __m128i *)&si32[_vi_] );
					wi = _mm_sub_epi32( wi, bi );
					_mm_store_si128( (__m128i *)&si32[_vi_], wi );
				}
				break;

			default:
				printf( "mmx_ai_epx32_bm_thread%u havn't instruction\n", td->tid );

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

#endif // !__SIMD_MMX_AI_EPX32_BM_H__