#!/bin/bash

declare -a statistics=("1" "40" "95")
declare -a types=("desc" "asc" "random")
declare -a div_size=("3" "5" "7" "9")

m=100

for n in {100..10000..100}
do
	for k in ${statistics[@]}
	do
		for t in ${types[@]}
		do
			for d in ${div_size[@]}
			do
				rm ./results/select_${d}_${t}_${k}_${n}.txt 2>/dev/null
				for _ in $(eval echo "{1..${m}}")
				do
					cargo -q run --manifest-path ./${t}/Cargo.toml $n $k $d | cargo -q run --manifest-path ./select/Cargo.toml >> ./results/select_${d}_${t}_${k}_${n}.txt
				done
			done
		done
	done
done
