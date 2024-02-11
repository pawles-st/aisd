for i in {100..5000..100}
do
	./main $i >> results.txt
	sleep 1.1
done
