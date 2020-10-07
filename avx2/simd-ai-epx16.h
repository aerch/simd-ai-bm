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

inline void avx2_ai_epx16_bm( thread_data_t *td,  pc_data_t *pc, int16_t *si16 ) {
	int64_t i;
	int16_t *si16_start __attribute__((aligned(32))) = si16;
	__m256i vi;
	__m256i ai = _mm256_set_epi16( 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 );

	while ( td->thread_active ) {

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		si16 = si16_start;

		switch ( td->instruction ) {

			case 1: // add vectors of 16 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)si16 );
					vi = _mm256_add_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)si16, vi );
				}
				break;

			case 2: // adds vectors of 16 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)si16 );
					vi = _mm256_adds_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)si16, vi );
				}
				break;

			case 3: // adds vectors of 16 16-bit unsigned integers at cycle
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)si16 );
					vi = _mm256_adds_epu16( vi, ai );
					_mm256_store_si256( (__m256i *)si16, vi );
				}
				break;

			case 4: // hadd vectors of 16 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)si16 );
					vi = _mm256_hadd_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)si16, vi );
				}
				break;

			case 5: // hadds vectors of 16 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)si16 );
					vi = _mm256_hadds_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)si16, vi );
				}
				break;

			case 6: // madd vectors of 16 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)si16 );
					vi = _mm256_madd_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)si16, vi );
				}
				break;

			case 7: // maddubs vectors of 16 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)si16 );
					vi = _mm256_maddubs_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)si16, vi );
				}
				break;

			case 8: // sub vectors of 16 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)si16 );
					vi = _mm256_sub_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)si16, vi );
				}
				break;

			case 9: // subs vectors of 16 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)si16 );
					vi = _mm256_subs_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)si16, vi );
				}
				break;

			case 10:// subs vectors of 16 16-bit unsigned integers at cycle
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)si16 );
					vi = _mm256_subs_epu16( vi, ai );
					_mm256_store_si256( (__m256i *)si16, vi );
				}
				break;

			case 11:// hsub vectors of 16 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)si16 );
					vi = _mm256_hsub_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)si16, vi );
				}
				break;

			case 12:// hsubs vectors of 16 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)si16 );
					vi = _mm256_hsubs_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)si16, vi );
				}
				break;

			case 13:// mulhi vectors of 16 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)si16 );
					vi = _mm256_mulhi_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)si16, vi );
				}
				break;

			case 14:// mullo vectors of 16 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)si16 );
					vi = _mm256_mullo_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)si16, vi );
				}
				break;

			case 15:// mulhrs vectors of 16 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)si16 );
					vi = _mm256_mulhrs_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)si16, vi );
				}
				break;

			case 16:// mulhi vectors of 16 16-bit unsigned integers at cycle
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)si16 );
					vi = _mm256_mulhi_epu16( vi, ai );
					_mm256_store_si256( (__m256i *)si16, vi );
				}
				break;

			case 17:// sign vectors of 16 16-bit signed integers at cycle
				for ( i = 0; i < td->cycles_count; i++, si16 += td->vector_offset ) {
					vi = _mm256_load_si256( (const __m256i *)si16 );
					vi = _mm256_sign_epi16( vi, ai );
					_mm256_store_si256( (__m256i *)si16, vi );
				}
				break;

			default:
				printf( "avx2_ai_epx16_bm_thread%u havn't instruction\n", td->tid );

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

void* avx2_ai_epx16_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 16;

	sprintf( td->name, "avx2_aiep16th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( ST_BM_CYCLES_PER_TIME > MT_BM_CYCLES_PER_TIME ? ST_BM_CYCLES_PER_TIME : MT_BM_CYCLES_PER_TIME ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( int16_t );
	int16_t *si16 __attribute__((aligned(32))) = (int16_t*)aligned_alloc( 32, alloc_size );
	if ( !si16 ) perror( "aligned_alloc() error" );

	avx2_ai_epx16_bm( td, &pc[ DSP_PC ], si16 );

	if ( si16 ) free( si16 );

	return NULL;
}

void* avx2_ai_epx16_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 0;

	sprintf( td->name, "avx2caiep16th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	int16_t si16[ 16 ] __attribute__((aligned(32))) = { 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3, 2, 1 };

	avx2_ai_epx16_bm( td, &pc[ CPU_PC ], si16 );

	return NULL;
}

#endif // !__SIMD_AVX2_AI_EPX16_BM_H__