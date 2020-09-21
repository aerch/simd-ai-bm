#ifndef __VARS_H__
#define __VARS_H__

typedef struct thread_data {
	pthread_t	th;
	uint32_t	tid;
	uint8_t		instruction;
	bool		thread_active;
	uint64_t	cycles_count;
} thread_data_t;

double 		diff;
struct timespec t1, t2;

int32_t		result;
FILE		*stream = NULL;
char		_str_[ 1024 ];
char		current_path[ PATH_MAX ];

uint64_t	cycles_count = CYCLES_COUNT;	// 1,000,000,000 - 10,000,000,000

uint8_t 	available_processors;		// available processor threads in system
uint8_t 	threads_count;			// maximum value is 128 threads
uint8_t 	vector_capacity;		// simd vector's capacity

double		total_time;
double		total_tps;

__m256		as, vs;
__m256d		ad, vd;
__m256i		ai, vi;

__m128		bs, ws;
__m128d		bd, wd;
__m128i		bi, wi;

__m64		ci, xi;

__uint128_t	active_threads_flag;

pthread_mutex_t	lock;
pthread_cond_t	start;
pthread_cond_t	stop;

thread_data_t	td[ MAX_THR_CNT ];

#endif // !__VARS_H__