
echo -en "\nSIMD Arithmetic Instructions Single-Thread Benchmark Intercomparison\n" > results.list
echo -en "-------------------------------------------------------------------\n" >> results.list
cd bmresults; grep SIMD-AI-ST-BM * | awk -F:SIMD-AI-ST-BM '{print $NF "\t\t" $1}' | sort -gr >> ../results.list; cd ..

echo -en "\nSIMD Arithmetic Instructions Multi-Thread Benchmark Intercomparison\n" >> results.list
echo -en "-------------------------------------------------------------------\n" >> results.list
cd bmresults; grep SIMD-AI-MT-BM * | awk -F:SIMD-AI-MT-BM '{print $NF "\t\t" $1}' | sort -gr >> ../results.list; cd ..; echo >> results.list

cat results.list
