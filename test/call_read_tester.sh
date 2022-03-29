for f in ../build/results/test_*.txt
	do
		./read_tester_output.sh $f
	done