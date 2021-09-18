docker-compose exec $( (( CI == 1 )) && printf %s '-T' ) sys sh -c "CONFIG_FILE=\"libnss-maria-docker.conf\" VERBOSE=${VERBOSE} /home/libnss-maria/scripts/compile_and_test.sh"
