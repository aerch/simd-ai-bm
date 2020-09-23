#ifndef __SIMD_AVX2_AI_EPX16_BM_H__
#define __SIMD_AVX2_AI_EPX16_BM_H__

const uint8_t avx2_ai_epx16_cnt = 17;

const char *avx2_ai_epx16_instructions[ avx2_ai_epx16_cnt + 1 ] = {
	"SIMD AVX2 16-bit Integer Arithmetic Instructions with 256-bit vectors ...",
	"vpaddw\t_mm256_add_epi16()",
	"vpaddsw\t_mm256_adds_epi16()",
	"vpaddusw\t_mm256_adds_epu16()",
	"vphaddw\t_mm256_hadd_epi16()",
	"vphaddsw\t_mm256_hadds_epi16()",
	"vpmaddwd\t_mm256_madd_epi16()",
	"vpmaddubsw\t_mm256_maddubs_epi16()",
	"vpsubw\t_mm256_sub_epi16()",
	"vpsubsw\t_mm256_subs_epi16()",
	"vpsubusw\t_mm256_subs_epu16()",
	"vphsubw\t_mm256_hsub_epi16()",
	"vphsubsw\t_mm256_hsubs_epi16()",
	"vpmulhw\t_mm256_mulhi_epi16()",
	"vpmullw\t_mm256_mullo_epi16()",
	"vpmulhrsw\t_mm256_mulhrs_epi16()",
	"vpmulhuw\t_mm256_mulhi_epu16()",
	"vpsignw\t_mm256_sign_epi16()"
};

void* avx2_ai_epx16_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	uint64_t i, _vi_;
	char name[ 25 ];

	sprintf( name, "avx2_aiep16th%u", td->tid );
	prctl( PR_SET_NAME, name );

	vector_capacity = 16;
	uint64_t alloc_length = MT_BM_CYCLES_PER_TIME * vector_capacity;
	uint64_t alloc_size = alloc_length * sizeof( int16_t );
	int16_t *si16 __attribute__((aligned(32))) = (int16_t*)aligned_alloc( 32, alloc_size );
	if ( !si16 ) perror( "aligned_alloc() error" );

	ai = _mm256_set_epi16( 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 );

	pthread_mutex_lock( &lock );
	while ( (td->instruction == 0) && td->thread_active )
		pthread_cond_wait( &start, &lock );
	pthread_mutex_unlock( &lock );

	while ( td->thread_active ) {

		pc_get( td->cycles_count );

		if ( !td->thread_active ) break;

		switch ( td->instruction ) {

			case 1: // add vectors of 16 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si16[_vi_] );
					vi = _mm256_add_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)&si16[_vi_], vi );
				}
				break;

			case 2: // adds vectors of 16 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si16[_vi_] );
					vi = _mm256_adds_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)&si16[_vi_], vi );
				}
				break;

			case 3: // adds vectors of 16 16-bit unsigned integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si16[_vi_] );
					vi = _mm256_adds_epu16( vi, ai );
					_mm256_store_si256( (__m256i *)&si16[_vi_], vi );
				}
				break;

			case 4: // hadd vectors of 16 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si16[_vi_] );
					vi = _mm256_hadd_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)&si16[_vi_], vi );
				}
				break;

			case 5: // hadds vectors of 16 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si16[_vi_] );
					vi = _mm256_hadds_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)&si16[_vi_], vi );
				}
				break;

			case 6: // madd vectors of 16 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si16[_vi_] );
					vi = _mm256_madd_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)&si16[_vi_], vi );
				}
				break;

			case 7: // maddubs vectors of 16 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si16[_vi_] );
					vi = _mm256_maddubs_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)&si16[_vi_], vi );
				}
				break;

			case 8: // sub vectors of 16 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si16[_vi_] );
					vi = _mm256_sub_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)&si16[_vi_], vi );
				}
				break;

			case 9: // subs vectors of 16 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si16[_vi_] );
					vi = _mm256_subs_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)&si16[_vi_], vi );
				}
				break;

			case 10:// subs vectors of 16 16-bit unsigned integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si16[_vi_] );
					vi = _mm256_subs_epu16( vi, ai );
					_mm256_store_si256( (__m256i *)&si16[_vi_], vi );
				}
				break;

			case 11:// hsub vectors of 16 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si16[_vi_] );
					vi = _mm256_hsub_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)&si16[_vi_], vi );
				}
				break;

			case 12:// hsubs vectors of 16 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si16[_vi_] );
					vi = _mm256_hsubs_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)&si16[_vi_], vi );
				}
				break;

			case 13:// mulhi vectors of 16 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si16[_vi_] );
					vi = _mm256_mulhi_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)&si16[_vi_], vi );
				}
				break;

			case 14:// mullo vectors of 16 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si16[_vi_] );
					vi = _mm256_mullo_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)&si16[_vi_], vi );
				}
				break;

			case 15:// mulhrs vectors of 16 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si16[_vi_] );
					vi = _mm256_mulhrs_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)&si16[_vi_], vi );
				}
				break;

			case 16:// mulhi vectors of 16 16-bit unsigned integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si16[_vi_] );
					vi = _mm256_mulhi_epu16( vi, ai );
					_mm256_store_si256( (__m256i *)&si16[_vi_], vi );
				}
				break;

			case 17:// sign vectors of 16 16-bit signed integers at cycle
				for ( i = 0, _vi_ = 0; i < td->cycles_count; i++, _vi_ += vector_capacity ) {
					vi = _mm256_load_si256( (const __m256i *)&si16[_vi_] );
					vi = _mm256_sign_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)&si16[_vi_], vi );
				}
				break;

			default:
				printf( "avx2_ai_epx16_bm_thread%u havn't instruction\n", td->tid );

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

#endif // !__SIMD_AVX2_AI_EPX16_BM_H__