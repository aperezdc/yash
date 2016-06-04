# errexit-y.tst: yash-specific test of the errexit option

# I think the shell should exit for all cases below, but POSIX and existing
# implementations vary...

# An expansion error in a non-interactive shell causes immediate exit of the
# shell (regardless of errexit), so expansion errors should be tested in an
# interactive shell.

setup 'set -e'

test_o -e 0 'expansion error in case word' -i +m
case ${a?} in (*) esac
echo reached
__IN__
reached
__OUT__

test_o -e 0 'expansion error in case pattern' -i +m
case a in (${a?}) esac
echo reached
__IN__
reached
__OUT__

test_o -e 0 'expansion error in for word' -i +m
for i in ${a?}; do echo not reached; done
echo reached
__IN__
reached
__OUT__

test_O -e n 'redirection error on subshell'
( :; ) <_no_such_file_
echo not reached
__IN__

test_o -e 0 'redirection error on grouping'
{ :; } <_no_such_file_
echo reached
__IN__
reached
__OUT__

test_o -e 0 'redirection error on for loop'
for i in i; do :; done <_no_such_file_
echo reached
__IN__
reached
__OUT__

test_o -e 0 'redirection error on case'
case i in esac <_no_such_file_
echo reached
__IN__
reached
__OUT__

test_o -e 0 'redirection error on if'
if :; then :; fi <_no_such_file_
echo reached
__IN__
reached
__OUT__

test_o -e 0 'redirection error on while loop'
while echo not reached; false; do :; done <_no_such_file_
echo reached
__IN__
reached
__OUT__

test_o -e 0 'redirection error on until loop'
until echo not reached; do :; done <_no_such_file_
echo reached
__IN__
reached
__OUT__

# vim: set ft=sh ts=8 sts=4 sw=4 noet: