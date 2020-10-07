
echo -en "\nSIMD Arithmetic Instructions Single-Thread Benchmark\n"
echo -en "------------------------------------------------------------------\n"
cd bmresults ; grep SIMD-AI-ST-BM * | awk -F:SIMD-AI-ST-BM '{print $NF "\t\t" $1}' | sort -gr; cd ..

echo -en "\nSIMD Arithmetic Instructions Multi-Thread Benchmark\n"
echo -en "------------------------------------------------------------------\n"
cd bmresults ; grep SIMD-AI-MT-BM * | awk -F:SIMD-AI-MT-BM '{print $NF "\t\t" $1}' | sort -gr; cd ..; echo
