#!/bin/bash

VAR="salut"

#exec 1>res
exec 2>vg
exec 3> >(valgrind ./test)
echo "salut" >&3
echo "segfault" >&3
echo "exit" >&3
exec 3>&-
1>res
#exec 1>/dev/tty
exec 2>/dev/tty
#./test > res | write()
#echo $VAR > to_test
#diff to_test res