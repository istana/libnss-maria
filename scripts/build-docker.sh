docker-compose \
$( (( DOCKERCFILE == 1 )) && printf %s '-f $DOCKERCFILE' ) exec \
$( (( CI == 1 )) && printf %s '-T' ) sys sh -c "\
CLIENT_FILE=${CLIENT_FILE} \
COMPILE_ONLY=${COMPILE_ONLY} \
CONFIG_FILE=${CONFIG_FILE:=libnss-maria-docker.conf} \
EXAMPLE_SET=${EXAMPLE_SET} \
RELEASE=${RELEASE} \
VERBOSE=${VERBOSE} \
TEST_USE_SSL=${TEST_USE_SSL} \
/home/libnss-maria/scripts/compile_and_test.sh"
