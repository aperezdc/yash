echo \
ok
cat <<END
here-document
ok
END
PS1='${PWD##${PWD}}? '
PS1=
