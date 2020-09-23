#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

inline __m64 _mm_set_si64_epi8( int8_t v0, int8_t v1, int8_t v2, int8_t v3, int8_t v4, int8_t v5, int8_t v6, int8_t v7 ) {
	static __m64 tmp;
	static int8_t _v[8] = { v0, v1, v2, v3, v4, v5, v6, v7 };
	memcpy( &tmp, _v, sizeof(__m64) );
	return tmp;
}

inline __m64 _mm_set_si64_epi16( int16_t v0, int16_t v1, int16_t v2, int16_t v3 ) {
	static __m64 tmp;
	static int16_t _v[4] = { v0, v1, v2, v3 };
	memcpy( &tmp, _v, sizeof(__m64) );
	return tmp;
}

inline __m64 _mm_set_si64_epi32( int32_t v0, int32_t v1 ) {
	static __m64 tmp;
	static int32_t _v[2] = { v0, v1 };
	memcpy( &tmp, _v, sizeof(__m64) );
	return tmp;
}

inline __m64 _mm_load_si64( const __m64 *v ) {
	static __m64 tmp;
	memcpy( &tmp, v, sizeof(__m64) );
	return tmp;
}

inline void _mm_store_si64( __m64 *d, const __m64 v ) {
	memcpy( d, &v, sizeof(__m64) );
	return;
}

#endif // !__FUNCTIONS_H__