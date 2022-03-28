GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
FILE='../build/results/Testparser.txt'

I=0
cat $FILE | while read line 
do
	if [ $I -le 0 ]
	then
		awk -F 'INFO:' '{ print $2 }'
	 	I=1
	else 
		if [`grep -s PASS ../build/results/*.txt`]
		then
			printf "${GREEN}[OK]${NC}"
		else
			printf "${RED}[KO]${NC}"
		fi
	 	I=0
	fi
done
