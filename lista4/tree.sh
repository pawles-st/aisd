#!/bin/bash

m=20

for n in {10000..100000..10000}
do
	rm ./results/bst_${n}.txt 2>/dev/null
	for _ in $(eval echo "{1..${m}}")
	do
		./bst/bst_ex $n >> ./results/bst_${n}.txt
	done
	rm ./results/rbbst_${n}.txt 2>/dev/null
	for _ in $(eval echo "{1..${m}}")
	do
		./rbbst/rbbst_ex $n >> ./results/rbbst_${n}.txt
	done
	rm ./results/splay_${n}.txt 2>/dev/null
	for _ in $(eval echo "{1..${m}}")
	do
		./splay/splay_ex $n >> ./results/splay_${n}.txt
	done
done
