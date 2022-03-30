BLUE='\033[0;34m'
BOLDBLUE="\e[1;34m"
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
FILE=$1

I=0
FILE_NAME=$(echo "$FILE\n" | awk -F '/results/' '{ print $2 }' | awk -F 'Test' '{ print $2 }' | awk -F '.txt' '{ print $1 }' | tr 'a-z' 'A-Z')
center() {
  termwidth="$(tput cols)"
  padding="$(printf '%0.1s' ={1..500})"
  printf "\n%*.*s${BOLDBLUE}%s${NC}%*.*s\n" 0 "$(((termwidth-2-${#1})/2))" "$padding" "$1" 0 "$(((termwidth-1-${#1})/2))" "$padding"
}
center " $FILE_NAME "
echo ''
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
		FAILURES=$(echo $line | awk -F 'Tests ' '{ print $2 }' | awk -F ' Failures' '{ print $1 }')
		TESTS=$(echo $line | awk -F 'Tests' '{ print $1 }')
		PASSED=$(expr $TESTS - $FAILURES)
		printf "\n\n$PASSED/$TESTS\n\n"
		if [ $FAILURES -gt 0 ]
		then
			printf "${RED}yeah no......${NC}"
		else
			printf "🎉🥳${GREEN}you never cease to amaze me${NC}👏🎉"
		fi
		break
	fi
done < "$FILE"

echo ''
center ""
echo '\n'
