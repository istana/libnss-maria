FROM ubuntu:rolling
COPY ./Debug/src/libnss-maria.so.2.1.0 /etc
RUN ls -l
CMD ["ls -l"]
