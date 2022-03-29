GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
FILE=$1

I=0
echo "$FILE\n" | awk -F '/results/' '{ print $2 }'
while read line 
do
	if [ $I -eq 1 ]
	then
		INFO_INFO=$(echo $line | awk -F 'INFO:' '{ print $2 }')
		printf "%s >>" "$INFO_INFO"
		printf "${RED}%s${NC}\n" "$FAIL_INFO"
		I=0;
	fi
	if [[ "$line" == *"PASS"* ]]
	then
		printf "${GREEN}[OK]${NC}"
	elif [[ "$line" == *"FAIL"* ]]
	then
		printf "\n${RED}[KO]${NC}"
		FAIL_INFO=$(echo $line | awk -F 'FAIL:' '{ print $2 }')
		I=1;
	fi
	if [[ "$line" == *"Tests"*"Failures"* ]]
	then
		echo "\n\n~~~~~~~~Final Results:~~~~~~~~\n$line"
		break
	fi
done < "$FILE"
