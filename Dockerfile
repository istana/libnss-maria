FROM ubuntu:rolling
COPY ./Debug/src/libnss-maria.so.2.1.0 /etc

COPY ./examples/sos-sso/libnss-maria.conf /etc
RUN chown root:root /etc/libnss-maria.conf
RUN chmod 644 /etc/libnss-maria.conf

COPY ./examples/sos-sso/libnss-maria-root.conf /etc
RUN chown root:root /etc/libnss-maria-root.conf
RUN chmod 600 /etc/libnss-maria-root.conf

COPY ./examples/sos-sso/nsswitch.conf /etc
