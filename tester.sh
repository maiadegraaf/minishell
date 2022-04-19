#!/bin/bash
#set -x
#set -e

export ASAN_OPTIONS='detect_leaks=1'
export LSAN_OPTIONS='suppressions=leak_suppression.txt print_suppressions=0'

function check()
{
	if [ $2 -ne $3 ]; then
		echo "found exit status difference for: \"$1\"";
		echo "bash exit status:" $3;
		echo "minishell exit status:" $2;
	fi
	diff minishell_out bash_out || { echo "std output test failed for: \"$1\""; echo -e "\n\n\n";}
	diff minishell_err bash_err || { echo "error output test failed for: \"$1\""; echo -e "\n\n\n";}
	diff minishell_outfile bash_outfile || { echo "outfile of output test failed for: \"$1\""; echo -e "\n\n\n";}
}

function shell_test()
{
	> minishell_outfile
	> bash_outfile
	export OUTFILE=minishell_outfile
	echo -e $1 | minishell > minishell_out 2> minishell_err
	export minishell_status=$?
	export OUTFILE=bash_outfile
	echo -e $1 | bash > bash_out 2> bash_err
	export bash_status=$?
	check "$1" $minishell_status $bash_status
}

function environment_test()
{
	export minishell_status=0
	export bash_status=0
	> minishell_outfile
	> bash_outfile
	export OUTFILE=minishell_outfile
	echo -e $1 | minishell 2> minishell_err | sort | grep -v -f environment_exceptions > minishell_out
	export minishell_status=$?
	export OUTFILE=bash_outfile
	echo -e $1 | bash 2> bash_err | sort | grep -v -f environment_exceptions > bash_out
	export bash_status=$?
	check "$1" $minishell_status $bash_status
}

#test by hand:
##########
# cat
# <ctrl>-\
# signals in here_doc
# cd < minishell.c -
##########

#make DEBUG=1 -C ..
make re DEBUG=1 -C ..

#new tests
shell_test 'export bla="s -a"\nl$bla'
shell_test 'export bla="s -a"\nl"$bla"'

# Generic tests
shell_test ''
shell_test '\n\n\n\n'
shell_test 'ls\nls'
shell_test '/bin/ls'

# Echo tests
shell_test 'echo'
shell_test 'echo ""'
shell_test 'echo < |'
shell_test 'echo > |'
shell_test 'echo << |'
shell_test 'echo >> |'
shell_test 'echo -nABC'
shell_test 'echo $BLA$BLA=10$BLA'
shell_test 'echo a"bc"d'
shell_test 'echo a"bcd"e'
shell_test "echo 'hoi'"'"bla"'
shell_test 'echo -n'
shell_test 'echo bla -n'
shell_test 'echo -n -n -n'
shell_test 'echo -n -n -n bla'
shell_test 'ls | echo -n bla'
shell_test 'echo -nnnn'
shell_test 'echo -nnnn bla'

# CD tests
shell_test 'cd\npwd'
shell_test 'cd\npwd\ncd -\npwd'
shell_test 'cd ..\ncd tests\npwd'
shell_test 'cd ..\ncd tests/\npwd'
shell_test 'cd ../../..\npwd'
shell_test 'cd banaan'
shell_test 'cd /usr\npwd'
shell_test 'cd /usr/bin\npwd'
shell_test 'cd /bla'
shell_test 'cd /\npwd'
shell_test 'cd ..\necho $OLDPWD\ncd tests\necho $OLDPWD'
shell_test 'echo $OLDPWDcd /\necho $OLDPWD\ncd tests\necho $OLDPWD'
shell_test 'cd\nunset OLDPWD\necho oldpwd after unset: $OLDPWD\ncd -\npwd'
shell_test 'ls | ls | unset OLDPWD\necho oldpwd after unset: $OLDPWD\ncd -\npwd'
#shell_test 'unset HOME\necho home after unset: $HOME\ncd\npwd'
shell_test 'mkdir TESTDIR\ncd TESTDIR\nrmdir ../TESTDIR\npwd'

# PWD Tests
shell_test 'pwd'
shell_test 'pwd lalala'

# Export tests
environment_test 'export'
environment_test 'export a\nexport a=42\nexport'
environment_test 'export a=\nexport a=42\nexport'
environment_test 'export a=\nexport a\nexport'
shell_test 'export ='
shell_test 'export =10'
shell_test 'export "|"=10'
shell_test 'export ">"=10'
shell_test 'export "$"=10'
shell_test 'export "["=10'
shell_test 'export "111"="222"'
environment_test 'export A=bla\nexport'
environment_test 'export 1A=bla\nexport'
environment_test 'export A1=bla\nexport'
environment_test 'export _A=bla\nexport'
environment_test 'export A_=bla\nexport'
environment_test 'export A=bla\nexport A=bloe\nexport'
environment_test 'export A=bla\nexport A=$A-bloe\nexport'
environment_test 'export PATH=$PATH:/banaan/konijn\nexport'
shell_test 'export A$B=10\necho $A$B'
shell_test 'export B=3\necho $A$B'
shell_test 'export B+=3\necho $A$B'
shell_test 'export HOME+=3\necho $HOME'
shell_test 'export HOME=+3\necho $HOME'
environment_test 'export +=3\nexport'
shell_test 'export HOME+=\necho $HOME'
shell_test 'export A$B=10\necho $A$B\nexport B=3\necho $A$B'
environment_test 'export PA=10\nexport'
environment_test 'export a1=10\nunset a1\nexport'
environment_test 'export a=5=5\nexport'

# unset tests
shell_test 'unset PATH\necho $PATH'
#shell_test 'unset HOME\necho $HOME'
environment_test 'unset $PATH\nexport'
environment_test 'unset a1=10\nexport'
environment_test 'unset $PATH\nexport'
environment_test 'unset PATH\nexport'
environment_test 'unset PPATH\nexport'
environment_test 'unset PATHH\nexport'
environment_test 'unset "PATH "\nexport'
environment_test 'unset " PATH"\nexport'
environment_test 'unset PATH=\nexport'
environment_test 'unset 1a\nexport'
environment_test 'unset a-\nexport'
environment_test 'unset a-\nexport'
environment_test 'unset a_\nexport'

# ENV tests
environment_test 'env'

# Exit tests
shell_test "exit"
shell_test "exit 0"
shell_test "exit 1"
shell_test "exit 42"
shell_test "exit 1 1"
shell_test "exit banaan"
shell_test "exit 1000000000"

# Redirection tests
shell_test 'pwd > $OUTFILE'
shell_test '> $OUTFILE pwd'
shell_test '> $OUTFILE ls -a'
shell_test 'cat test_shell_split.c > $OUTFILE -e'
shell_test 'cat > $OUTFILE < test_shell_split.c -e'
shell_test 'cat < test_shell_split.c > $OUTFILE -e'
shell_test '< test_shell_split.c << bla cat\nasdf\nbla\n'

# Here doc tests
shell_test 'cat << bla -e\nasdf\n'
shell_test 'cat << bla -e\nasdf\nbla\n'
shell_test 'cat << bla\nasdf\nbla\n'
shell_test '<< bla cat\nasdf\nbla\n'
shell_test '<< bla\nasdf\nbla\n cat'
shell_test '<< bla cat\nasdf\nbla\necho banaan'
shell_test '<< bla cat < test_shell_split.c\nasdf\nbla\n'
shell_test '<< wildcard.c ls -la | wc -w >> $OUTFILE\nwildcard.c'

# Pipe tests
shell_test 'ls | grep t'
shell_test 'ls|cat -e'
shell_test 'ls|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e'
shell_test 'ls | < banaan | ls'
shell_test 'ls | cat > $OUTFILE'
shell_test 'ls < lol.c | grep "a"'
shell_test 'ls < test_shell_split.c | grep "a"'
shell_test '< test_shell_split.c grep a | cat -e'
shell_test '< test_shell_split.c | cat -e > $OUTFILE'
shell_test '< test_shell_split.c | ls | cat -e > $OUTFILE'
shell_test '< test_shell_split.c grep a | > $OUTFILE'
shell_test '< test_shell_split.c grep a | cat -e > $OUTFILE'
shell_test '< test_shell_split.c grep "a"|grep "m" | wc -l|cat -e > $OUTFILE'
shell_test 'ls | cat > $OUTFILE < test_shell_split.c -e'
shell_test 'cat > $OUTFILE < test_shell_split.c -e | ls'
shell_test 'ls | < integration_tests grep "a" | cat -e'
shell_test 'ls | head -n 10 | tail -n 9 | rev | sort | rev | cat -e'
shell_test 'cat | cat | ls\n'

# Wildcard and dollar extension tests
shell_test "echo '$PATH'"
shell_test 'echo "$     a"'
shell_test 'echo $'
shell_test 'echo $9'
shell_test 'echo $9a'
shell_test 'echo $98a'
shell_test 'echo $PA'
shell_test 'echo $PA:'
shell_test 'echo $PATH:'
shell_test 'echo $HOME'
shell_test 'echo "$HOME"'
shell_test 'echo $HO"ME"'
shell_test 'echo $"HOME"'
shell_test 'echo $ "HOME"'
shell_test 'echo '\''$"HOME"'\'
shell_test 'echo "'\''$HOME'\'\"
shell_test 'echo bla $bla'
shell_test 'echo bla $bla | cat -e'

# Quote tests
shell_test 'cat test_shell_split.c'
shell_test 'cat test_sh"ell_split.c"'
shell_test 'cat "test_sh"ell_split.c'
shell_test 'cat '"tes't_s'h"'ell_"spl"it.c'
shell_test 'exit "42"'

# Combination tests
shell_test 'echo bla | export $BLA=bla\necho $BLA'
shell_test 'ls | > tmp_file | ls\nrm tmp_file'
shell_test 'ls | cat << bla\nasdf\nbla\n' 
shell_test 'cat << bla | cat\nasdf\nbla\n' 
shell_test '<< bla cat | << bloe cat\nfirst\nbla\nsecond\nbloe\n' 
shell_test '<< bla cat | << bloe cat\nfirst\nbla\nsecond\nbloe\nls\n'
shell_test 'cat << bla | echo bla\nasdf\nbla\n' 

# Error tests
shell_test '|'
shell_test '<'
shell_test '>'
shell_test '< <'
shell_test '> <'
shell_test '<<'
shell_test '<< <'
shell_test '> > outfile'
shell_test 'ls | >'
shell_test 'ls | > >'
shell_test 'ls | > >>'
shell_test 'ls | <'
shell_test '< | ls'
shell_test 'ls | banaan'
shell_test 'ls | "|"'
shell_test '| ls'
shell_test 'ls |'
shell_test 'ls | | ls'
shell_test 'ls ||| cat'
shell_test 'ls\n\n\nls ||| cat'
shell_test 'ls\n\n\nexit banaan'
shell_test 'ls\n\n\nexport "$"=10'
shell_test 'ls\n\n\ncd banaan'


# For the next two tests with multiple output redirections, to the same file, minishell always does the same thing, but bash doesn't. 
# Bash seems to open the file from different forks and they put in information at the same time, which causes race conditions. Minishell puts in information in order.

# shell_test 'rm $OUTFILE | cat >> $OUTFILE << hd1 << hd2 -e | >> $OUTFILE << hd3 | cat < test_shell_split.c << hd4 >> $OUTFILE | >> $OUTFILE echo *$PATH * $PATH "*"$PATH -e\n1\nhd1\n2\nhd2\n3\nhd3\n4\nhd4\n'
# shell_test 'cat > $OUTFILE << hd1 << hd2 -e | >> $OUTFILE << hd3 | cat < test_shell_split.c >> $OUTFILE << hd4 -e\n1\nhd1\n2\nhd2\n3\nhd3\n4\nhd4\n' 

norminette src

echo integration tests finished!