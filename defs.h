#ifndef __DEFINES_H__
#define __DEFINES_H__

#define DSP_PC			0
#define CPU_PC			1

#define MAX_THR_CNT		128				// maximum value is 8192 threads

#define ST_BM_CYCLES_PER_TIME	8192				// 8192 - ST
#define MT_BM_CYCLES_PER_TIME	4096				// 4096 - MT

#define SINGLE_THREAD		1

#ifdef THREADSCOUNT
#define MULTIPLE_THREADS	2 * THREADSCOUNT		// 2 - 8192
#else
#define MULTIPLE_THREADS	MAX_THR_CNT
#endif

#ifdef THREADSCOUNT
#define CYCLES_COUNT		CYCLESCOUNT			// 1,000,000 - 10,000,000,000
#else
#define CYCLES_COUNT		1000000000
#endif

#define _BMARK_ON_ struct timespec t1, t2; clock_gettime(CLOCK_REALTIME, &t1);
#define _BMARK_OFF( cycle ) clock_gettime(CLOCK_REALTIME, &t2); cycle = (double)((double)t2.tv_sec + (double)t2.tv_nsec/1.0e9) - ((double)t1.tv_sec + (double)t1.tv_nsec/1.0e9);

#define BIT(b) (1<<(b))						///< битовый сдвиг влево на b позиций
#define TEST(n,b) (((n)&BIT(b))!=0)				///< проверка, что b-ый бит числа n - ненулевой
#define SET_BIT(n,b,value) (n) ^= ((-value)^(n)) & (BIT(b))	///< установка бита из позиции n в позицию b числа value
#define CHECK(n,b) (((n)&BIT(b))!=0)				///< проверка, что b-ый бит числа n - ненулевой

#define BLACK		"\033[30;1m"
#define BGBLACK		"\033[37;1;40m"
#define RED		"\033[31;1m"
#define BGRED		"\033[37;1;41m"
#define GREEN		"\033[32;1m"
#define BGGREEN		"\033[37;1;42m"
#define YELLOW		"\033[33;1m"
#define BGYELLOW	"\033[30;1;43m"
#define BLUE		"\033[34;1m"
#define BGBLUE		"\033[37;1;44m"
#define PURPLE		"\033[35;1m"
#define BGPURPLE	"\033[37;1;45m"
#define CYAN		"\033[36;1m"
#define BGCYAN		"\033[37;1;46m"
#define WHITE		"\033[37;1m"
#define THINW		"\033[38;1m"
#define WHITE_		"\033[39;1m"
#define BBLACK		"\033[40;1m"
#define BRED		"\033[41;1m"
#define BGREEN		"\033[42;1m"
#define BYELLOW		"\033[43;1m"
#define BBLUE		"\033[44;1m"
#define BPURPLE		"\033[45;1m"
#define BCYAN		"\033[46;1m"
#define BWHITE		"\033[47;1m"
#define BTHINW		"\033[48;1m"
#define BWHITE_		"\033[49;1m"
#define OFF		"\033[0m"

#endif // !__DEFINES_H__