for i in {100..10000..100}
do
	./heap $i >> results.txt
	sleep 1.1
done
