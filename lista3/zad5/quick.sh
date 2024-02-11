#!/bin/bash

declare -a statistics=("1" "40" "95")
declare -a types=("desc" "asc" "random")
declare -a div_size=("3" "5" "7" "9")

m=100

for n in {1000..20000..1000}
do
	for t in ${types[@]}
	do
#		rm ./results/select_quick_sort_${t}_${n}.txt 2>/dev/null
#		for _ in $(eval echo "{1..${m}}")
#		do
#			cargo -q run --manifest-path ./${t}/Cargo.toml $n $k $d | cargo -q run --manifest-path ./quick_sort/Cargo.toml >> ./results/select_quick_sort_${t}_${n}.txt
#		done
		rm ./results/select_dual_quick_sort_${t}_${n}.txt 2>/dev/null
		for _ in $(eval echo "{1..${m}}")
		do
			cargo -q run --manifest-path ./${t}/Cargo.toml $n $k $d | cargo -q run --manifest-path ./dual_quick_sort/Cargo.toml >> ./results/select_dual_quick_sort_${t}_${n}.txt
		done
#		rm ./results/quick_sort_${t}_${n}.txt 2>/dev/null
#		for _ in $(eval echo "{1..${m}}")
#		do
#			cargo -q run --manifest-path ./${t}/Cargo.toml $n $k $d | ./old_quick_sort_lomuto >> ./results/quick_sort_${t}_${n}.txt
#		done
#		rm ./results/dual_quick_sort_${t}_${n}.txt 2>/dev/null
#		for _ in $(eval echo "{1..${m}}")
#		do
#			cargo -q run --manifest-path ./${t}/Cargo.toml $n $k $d | ./old_dual_quick_sort >> ./results/dual_quick_sort_${t}_${n}.txt
#		done
	done
done
