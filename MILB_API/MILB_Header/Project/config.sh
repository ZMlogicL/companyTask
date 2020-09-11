#! /bin/sh

proj_top_dir=`dirname "$0"`
cd "${proj_top_dir}"

if [ -f ./setenv.bat ] ; then
	rm -f ./setenv.bak
	mv ./setenv.bat ./setenv.bak > /dev/null 2>&1
fi
SETENV=./setenv.sh
echo '#! /bin/sh' > "${SETENV}"
echo "MAKE_OPT=; export MAKE_OPT" >> "${SETENV}"

echo ''
basename "$0"
echo complete !
echo ''
exit 0
