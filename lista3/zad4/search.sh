#!/bin/bash

m=100

for n in {1000..100000..1000}
do
#	rm ./results/search_begin_${n}.txt 2>/dev/null
#	for _ in $(eval echo "{1..${m}}")
#	do
#		cargo -q run --manifest-path ./asc/Cargo.toml $n 1 | cargo -q run --manifest-path ./search_dev/Cargo.toml >> ./results/search_begin_${n}.txt
#	done
	rm ./results/search_middle_${n}.txt 2>/dev/null
	for _ in $(eval echo "{1..${m}}")
	do
		cargo -q run --manifest-path ./asc/Cargo.toml $n $((($n + 1) / 2)) | cargo -q run --manifest-path ./search_dev/Cargo.toml >> ./results/search_middle_${n}.txt
	done
#	rm ./results/search_end_${n}.txt 2>/dev/null
#	for _ in $(eval echo "{1..${m}}")
#	do
#		cargo -q run --manifest-path ./asc/Cargo.toml $n $n | cargo -q run --manifest-path ./search_dev/Cargo.toml >> ./results/search_end_${n}.txt
#	done
#	rm ./results/search_nonexistent_${n}.txt 2>/dev/null
#	for _ in $(eval echo "{1..${m}}")
#	do
#		cargo -q run --manifest-path ./asc/Cargo.toml $n $(($n + 1)) | cargo -q run --manifest-path ./search_dev/Cargo.toml >> ./results/search_nonexistent_${n}.txt
#	done
#	rm ./results/search_random_${n}.txt 2>/dev/null
#	for _ in $(eval echo "{1..${m}}")
#	do
#		cargo -q run --manifest-path ./asc/Cargo.toml $n $((1 + $RANDOM % $n)) | cargo -q run --manifest-path ./search_dev/Cargo.toml >> ./results/search_random_${n}.txt
#	done
done
