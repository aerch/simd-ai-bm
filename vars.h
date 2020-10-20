#ifndef __VARS_H__
#define __VARS_H__

typedef enum instructions { _MMX_, _SSE_, _SSE2_, _SSE3_, _SSSE3_, _SSE4_1_, _AVX_, _AVX2_, _FMA3_ } instructions_e;

const char *instructions_s[ 9 ] = { "MMX", "SSE", "SSE2", "SSE3", "SSSE3", "SSE4_1", "AVX", "AVX2", "FMA3" };

typedef struct thread_data {

	int32_t		vector_offset;
	int64_t		cycles_count;
	uint8_t		instruction;
	bool		thread_active;

	uint16_t	tid;

	pthread_t	th;
	pthread_t	cpu_th;

	char		name[ 25 ];

} thread_data_t;

int32_t		result;
FILE		*stream = NULL;
char		_str_[ 16384 ];

char		brand_string[ 50 ];
char		current_path[ PATH_MAX ];

uint64_t	cycles_count = CYCLES_COUNT;		// 1,000,000,000 - 10,000,000,000
uint32_t	st_bm_cpt = ST_BM_CYCLES_PER_TIME;	//
uint32_t	mt_bm_cpt = MT_BM_CYCLES_PER_TIME;	//

uint8_t 	available_processors;		// system's available processor threads
uint8_t 	vector_capacity;		// simd vector's capacity
uint16_t 	threads_count;			// threads number
uint16_t	active_threads;			// active threads number
uint16_t	evaluating_threads;		// evaluating threads number

double		total_time;
double		total_tps;
double		cpu_time;

double		simd_ai_st_bm;
double		simd_ai_mt_bm;
double		simd_ai_mt_bm_rate;

pthread_mutex_t	lock;
pthread_cond_t	stop;
pthread_cond_t	finish;

thread_data_t	td[ 2 ][ MAX_THR_CNT ];
pc_data_t	pc[ 2 ];

#endif // !__VARS_H__