#!/bin/bash

MINISHELL_PATH=$1

mkdir minishell
rsync -av --exclude='miniminishell_tester' $MINISHELL_PATH/** minishell
cd minishell
sed '/^\s*printf(/a fflush(stdout);' -i *.c
make all