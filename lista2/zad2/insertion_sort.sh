#!/bin/bash

k1=1
k2=10
k3=100

declare -a types=("desc" "asc" "random")

for n in {10..200..10}
do
	for t in ${types[@]}
	do
		rm insertion_sort_${t}_${k1}_${n}.txt 2>/dev/null
		rm insertion_sort_${t}_${k2}_${n}.txt 2>/dev/null
		rm insertion_sort_${t}_${k3}_${n}.txt 2>/dev/null
		for _ in $(eval echo "{1..${k1}}")
		do
			cargo -q run --manifest-path ../${t}/Cargo.toml $n | ./insertion_sort >> results/insertion_sort_${t}_${k1}_${n}.txt
		done
		for _ in $(eval echo "{1..${k2}}")
		do
			cargo -q run --manifest-path ../${t}/Cargo.toml $n | ./insertion_sort >> results/insertion_sort_${t}_${k2}_${n}.txt
		done
		for _ in $(eval echo "{1..${k3}}")
		do
			cargo -q run --manifest-path ../${t}/Cargo.toml $n | ./insertion_sort >> results/insertion_sort_${t}_${k3}_${n}.txt
		done
	done
done
