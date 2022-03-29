for f in ../build/results/Test*.txt
	do
		./read_tester_output.sh $f
	done