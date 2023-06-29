# simd-ai-bm
SIMD Arithmetic Instructions Benchmark
(pure C-style writing)

build:
	make

start:
	sudo ./simd-ai-bm

results:
	./results.sh

SIMD Arithmetic Instructions Single-Thread Benchmark Intercomparison
-------------------------------------------------------------------
        4018.2		AMD Ryzen 7 7735HS with Radeon Graphics @ 4.83GHz DDR5 @ 4800MHz
        3262.2		AMD Ryzen 5 3600 6-Core Processor @ 3.60GHz DDR4 @ 3200MHz
        3129.4		AMD Ryzen 5 3600X 6-Core Processor @ 4.10GHz DDR4 @ 3200MHz
        2872.8		AMD Ryzen 5 3600X 6-Core Processor @ 4.00GHz DDR4 @ 3200MHz
        2554.2		Intel(R) Core(TM) i7-8700K CPU @ 4.90GHz DDR4 @ 3400MHz
        2554.0		AMD EPYC 7532 32-Core Processor @ 3.30GHz DDR4 @ 3200MHz
        2549.0		Intel(R) Core(TM) i7-8700K CPU @ 4.90GHz DDR4 @ 3600MHz
        2497.9		AMD Ryzen Threadripper 2990WX 32-Core Processor @ 3.00GHz DDR4 @ 2133MHz
        2464.0		Intel(R) Core(TM) i7-8700K CPU @ 4.70GHz DDR4 @ 3600MHz
        2131.7		Intel(R) Core(TM) i7-4770K CPU @ 4.50GHz DDR3 @ 2800MHz
        2119.5		Intel(R) Core(TM) i7-4770K CPU @ 4.40GHz DDR3 @ 2800MHz
        2115.9		Intel(R) Core(TM) i7-4770K CPU @ 4.50GHz DDR3 @ 2933MHz
        2085.4		Intel(R) Core(TM) i7-4770K CPU @ 4.40GHz DDR3 @ 2933MHz
        1992.0		Intel(R) Core(TM) i7-4770K CPU @ 4.20GHz DDR3 @ 2400MHz
        1972.0		Intel(R) Core(TM) i7-4770K CPU @ 4.20GHz DDR3 @ 2800MHz
        1874.5		Intel(R) Core(TM) i7-4770K CPU @ 4.20GHz DDR3 @ 2666MHz
        1795.8		Intel(R) Core(TM) i7-4770K CPU @ 4.00GHz DDR3 @ 2400MHz
        1768.8		Intel(R) Core(TM) i7-5775C CPU @ 3.70GHz DDR3 @ 1600MHz
        1488.4		AMD EPYC 7401P 24-Core Processor @ 2.80GHz DDR4 @ 2666MHz
        1472.9		Intel(R) Core(TM) i5-6200U CPU @ 2.80GHz LPDDR3 @ 1866MHz
        1414.8		Intel(R) Core(TM) i7-4750HQ CPU @ 3.20GHz DDR3 @ 1600MHz
        1411.3		Intel(R) Core(TM) i7-6500U CPU @ 3.10GHz DDR3 @ 1600MHz
         892.2		AMD FX(tm)-8350 Eight-Core Processor @ 4.00GHz DDR3 @ 1600MHz
         438.2		Intel(R) Core(TM)2 Duo CPU T8100 @ 2.10GHz DDR2 @ 666MHz
         119.9		Intel(R) Dual Core(TM) T2250 CPU @ 1.73GHz DDR2 @ 533MHz
           7.1		Intel(R) Celeron(R) CPU @ 2.60GHz DDR @ 333MHz

SIMD Arithmetic Instructions Multi-Thread Benchmark Intercomparison
-------------------------------------------------------------------
       28658.4		AMD EPYC 7532 32-Core Processor @ 3.30GHz DDR4 @ 3200MHz
       23032.1		AMD Ryzen Threadripper 2990WX 32-Core Processor @ 3.00GHz DDR4 @ 2133MHz
       22449.1		AMD Ryzen 7 7735HS with Radeon Graphics @ 4.83GHz DDR5 @ 4800MHz
       20160.3		AMD EPYC 7401P 24-Core Processor @ 2.80GHz DDR4 @ 2666MHz
       18852.4		AMD Ryzen 5 3600X 6-Core Processor @ 4.10GHz DDR4 @ 3200MHz
       17741.2		AMD Ryzen 5 3600 6-Core Processor @ 3.60GHz DDR4 @ 3200MHz
       17648.5		AMD Ryzen 5 3600X 6-Core Processor @ 4.00GHz DDR4 @ 3200MHz
       14110.5		Intel(R) Core(TM) i7-8700K CPU @ 4.90GHz DDR4 @ 3600MHz
       13289.6		Intel(R) Core(TM) i7-8700K CPU @ 4.90GHz DDR4 @ 3400MHz
       13284.2		Intel(R) Core(TM) i7-8700K CPU @ 4.70GHz DDR4 @ 3600MHz
        9258.6		Intel(R) Core(TM) i7-4770K CPU @ 4.50GHz DDR3 @ 2800MHz
        9210.3		Intel(R) Core(TM) i7-4770K CPU @ 4.50GHz DDR3 @ 2933MHz
        9101.9		Intel(R) Core(TM) i7-4770K CPU @ 4.40GHz DDR3 @ 2800MHz
        9026.8		Intel(R) Core(TM) i7-4770K CPU @ 4.40GHz DDR3 @ 2933MHz
        8645.6		Intel(R) Core(TM) i7-4770K CPU @ 4.20GHz DDR3 @ 2800MHz
        8493.1		Intel(R) Core(TM) i7-4770K CPU @ 4.20GHz DDR3 @ 2400MHz
        8037.1		Intel(R) Core(TM) i7-4770K CPU @ 4.20GHz DDR3 @ 2666MHz
        7741.2		Intel(R) Core(TM) i7-4770K CPU @ 4.00GHz DDR3 @ 2400MHz
        7434.9		Intel(R) Core(TM) i7-5775C CPU @ 3.70GHz DDR3 @ 1600MHz
        5643.0		Intel(R) Core(TM) i7-4750HQ CPU @ 3.20GHz DDR3 @ 1600MHz
        3758.8		Intel(R) Core(TM) i5-6200U CPU @ 2.80GHz LPDDR3 @ 1866MHz
        3651.6		AMD FX(tm)-8350 Eight-Core Processor @ 4.00GHz DDR3 @ 1600MHz
        2946.5		Intel(R) Core(TM) i7-6500U CPU @ 3.10GHz DDR3 @ 1600MHz
         894.8		Intel(R) Core(TM)2 Duo CPU T8100 @ 2.10GHz DDR2 @ 666MHz
         226.3		Intel(R) Dual Core(TM) T2250 CPU @ 1.73GHz DDR2 @ 533MHz

