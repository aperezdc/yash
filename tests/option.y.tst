# option.y.tst: yash-specific test of shell options
# vim: set ft=sh ts=8 sts=4 sw=4 noet:

tmp="${TESTTMP}/option.y.tmp"
mkdir -p "$tmp"

echo ===== -h =====
set -h
echo "$-" | grep -Fq h || echo 'no h in $-' >&2
hash -r
hoptiontest () {
    cat /dev/null
}
echo $(hash | grep /cat\$ | wc -l)
set +h

echo ===== nocaseglob =====
set --no=caseglob
echo O[OPQ]T*ON.y.tst OPTION.y.tst
set +o no_caseglob
echo O[OPQ]T*ON.y.tst OPTION.y.tst

cd "$tmp"

echo ===== dotglob =====
touch .dotfile
set --dotglob
echo *
set +o dotglob
echo *

echo ===== markdirs =====
mkdir dir
set --markdirs
echo di*
set +o mark\ dirs
echo di*

echo ===== extendedglob =====
mkdir dir/dir2
touch dir/dir2/file
mkdir anotherdir
touch anotherdir/file
ln -s ../../anotherdir dir/dir2/link
ln -s ../dir anotherdir/loop
set --extended-glob
echo **/file
echo ***/file
set +o extended-glob
echo **/file
echo ***/file

mv dir/dir2 dir/.dir2
set -o extended_glob
echo dir/**/file
echo dir/***/file
echo dir/.**/file
echo dir/.***/file
set ++extended_glob
echo dir/**/file
echo dir/***/file
echo dir/.**/file
echo dir/.***/file

echo ===== nullglob =====
set --nullglob
echo n*ll f[o/b]r f?o/b*r 1
set +o nullglob
echo n*ll f[o/b]r f?o/b*r 2

# test of braceexpand is in "expand.tst"

cd - >/dev/null

echo ===== posix =====
$INVOKE $TESTEE         -c 'echo "$PS1"'
$INVOKE $TESTEE --posix -c 'echo "$PS1"'

rm -fr "$tmp"
