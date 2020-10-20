#ifndef __SIMD_FMA3_AI_PS32_BM_H__
#define __SIMD_FMA3_AI_PS32_BM_H__

const uint8_t fma3_ai_ps32_cnt = 16;

const char *fma3_ai_ps32_instructions[ fma3_ai_ps32_cnt + 1 ] = {
	"SIMD FMA3 32-bit Single-Precision Arithmetic Instructions with 128-bit & 256-bit vectors ...",
	"vfmaddXps\t_mm_fmadd_ps         ",
	"vfmaddXss\t_mm_fmadd_ss         ",
	"vfmaddsubXps\t_mm_fmaddsub_ps   ",
	"vfmsubXps\t_mm_fmsub_ps         ",
	"vfmsubXss\t_mm_fmsub_ss         ",
	"vfmsubaddXps\t_mm_fmsubadd_ps   ",
	"vfnmaddXps\t_mm_fnmadd_ps       ",
	"vfnmaddXss\t_mm_fnmadd_ss       ",
	"vfnmsubXps\t_mm_fnmsub_ps       ",
	"vfnmsubXss\t_mm_fnmsub_ss       ",
	"vfmaddXps\t_mm256_fmadd_ps      ",
	"vfmaddsubXps\t_mm256_fmaddsub_ps",
	"vfmsubXps\t_mm256_fmsub_ps      ",
	"vfmsubaddXps\t_mm256_fmsubadd_ps",
	"vfnmaddXps\t_mm256_fnmadd_ps    ",
	"vfnmsubXps\t_mm256_fnmsub_ps    "
};

inline void fma3_ai_ps32_bm( thread_data_t *td,  pc_data_t *pc, float *ps32, int32_t vector_offset ) {
	int64_t i;
	float *p __attribute__((aligned(32)));
	__m128 ws;
	__m128 bs = _mm_set_ps( 3.33333f, 4.44444f, 1.11111f, 2.22222f );
	__m128 zs = _mm_set_ps( 1.11111f, 2.22222f, 3.33333f, 4.44444f );
	__m256 vs;
	__m256 as = _mm256_set_ps( 1.11111f, 2.22222f, 3.33333f, 4.44444f, 5.55555f, 6.66666f, 7.77777f, 8.88888f );
	__m256 ys = _mm256_set_ps( 5.55555f, 6.66666f, 7.77777f, 8.88888f, 1.11111f, 2.22222f, 3.33333f, 4.44444f );

	while ( td->thread_active ) {

		p = ps32;

		pc_get( pc, td->cycles_count );

		if ( !td->thread_active ) break;

		pthread_mutex_lock( &lock );
		evaluating_threads++;
		pthread_mutex_unlock( &lock );

		switch ( td->instruction ) {

			case 1: // vfmadd132ps vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					ws = _mm_load_ps( (const float *)p );
					ws = _mm_fmadd_ps( ws, bs, zs );
					_mm_store_ps( (float *)p, ws );
				}
				break;

			case 2: // vfmadd132ss vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					ws = _mm_load_ps( (const float *)p );
					ws = _mm_fmadd_ss( ws, bs, zs );
					_mm_store_ps( (float *)p, ws );
				}
				break;

			case 3: // vfmaddsub132ps vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					ws = _mm_load_ps( (const float *)p );
					ws = _mm_fmaddsub_ps( ws, bs, zs );
					_mm_store_ps( (float *)p, ws );
				}
				break;

			case 4: // vfmsub132ps vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					ws = _mm_load_ps( (const float *)p );
					ws = _mm_fmsub_ps( ws, bs, zs );
					_mm_store_ps( (float *)p, ws );
				}
				break;

			case 5: // vfmsub132ss vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					ws = _mm_load_ps( (const float *)p );
					ws = _mm_fmsub_ss( ws, bs, zs );
					_mm_store_ps( (float *)p, ws );
				}
				break;

			case 6: // vfmsubadd132ps vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					ws = _mm_load_ps( (const float *)p );
					ws = _mm_fmsubadd_ps( ws, bs, zs );
					_mm_store_ps( (float *)p, ws );
				}
				break;

			case 7: // vfnmadd132ps vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					ws = _mm_load_ps( (const float *)p );
					ws = _mm_fnmadd_ps( ws, bs, zs );
					_mm_store_ps( (float *)p, ws );
				}
				break;

			case 8: // vfnmadd132ss vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					ws = _mm_load_ps( (const float *)p );
					ws = _mm_fnmadd_ss( ws, bs, zs );
					_mm_store_ps( (float *)p, ws );
				}
				break;

			case 9: // vfnmsub132ps vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					ws = _mm_load_ps( (const float *)p );
					ws = _mm_fnmsub_ps( ws, bs, zs );
					_mm_store_ps( (float *)p, ws );
				}
				break;

			case 10:// vfnmsub132ss vectors of 4 32-bit singles at cycle
				vector_capacity = 4;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					ws = _mm_load_ps( (const float *)p );
					ws = _mm_fnmsub_ss( ws, bs, zs );
					_mm_store_ps( (float *)p, ws );
				}
				break;

			case 11:// vfmadd132ps vectors of 8 32-bit singles at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					vs = _mm256_load_ps( (const float *)p );
					vs = _mm256_fmadd_ps( vs, as, ys );
					_mm256_store_ps( (float *)p, vs );
				}
				break;

			case 12:// vfmaddsub132ps vectors of 8 32-bit singles at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					vs = _mm256_load_ps( (const float *)p );
					vs = _mm256_fmaddsub_ps( vs, as, ys );
					_mm256_store_ps( (float *)p, vs );
				}
				break;

			case 13:// vfmsub132ps vectors of 8 32-bit singles at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					vs = _mm256_load_ps( (const float *)p );
					vs = _mm256_fmsub_ps( vs, as, ys );
					_mm256_store_ps( (float *)p, vs );
				}
				break;

			case 14:// vfmsubadd132ps vectors of 8 32-bit singles at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					vs = _mm256_load_ps( (const float *)p );
					vs = _mm256_fmsubadd_ps( vs, as, ys );
					_mm256_store_ps( (float *)p, vs );
				}
				break;

			case 15:// vfnmadd132ps vectors of 8 32-bit singles at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					vs = _mm256_load_ps( (const float *)p );
					vs = _mm256_fnmadd_ps( vs, as, ys );
					_mm256_store_ps( (float *)p, vs );
				}
				break;

			case 16:// vfnmsub132ps vectors of 8 32-bit singles at cycle
				vector_capacity = 8;
				for ( i = 0; i < td->cycles_count; i++, p += vector_offset ) {
					vs = _mm256_load_ps( (const float *)p );
					vs = _mm256_fnmsub_ps( vs, as, ys );
					_mm256_store_ps( (float *)p, vs );
				}
				break;


			default:
				printf( "fma3_ai_ps32_bm_thread%u havn't instruction\n", td->tid );

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

void* fma3_ai_ps32_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 8;

	sprintf( td->name, "fma3_aips32th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	uint64_t alloc_length = ( st_bm_cpt > mt_bm_cpt ? st_bm_cpt : mt_bm_cpt ) * td->vector_offset;
	uint64_t alloc_size = alloc_length * sizeof( float );
	float *ps32 __attribute__((aligned(32))) = (float*)aligned_alloc( 32, alloc_size );
	if ( !ps32 ) perror( "aligned_alloc() error" );

	fma3_ai_ps32_bm( td, &pc[ DSP_PC ], ps32, 8 );

	if ( ps32 ) free( ps32 );

	return NULL;
}

void* fma3_ai_ps32_cpu_bm_thread( void *arg ) {
	thread_data_t *td = (thread_data_t*)arg;
	td->vector_offset = 0;

	sprintf( td->name, "fma3caips32th%u", td->tid );
	prctl( PR_SET_NAME, td->name );

	float ps32[ 8 ] __attribute__((aligned(32))) = { 8, 7, 6, 5, 4, 3, 2, 1 };

	fma3_ai_ps32_bm( td, &pc[ CPU_PC ], ps32, 0 );

	return NULL;
}

#endif // !__SIMD_FMA3_AI_PS32_BM_H__