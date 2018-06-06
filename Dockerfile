FROM ubuntu:18.04

WORKDIR /usr/src/scheme.c

COPY . /usr/src/scheme.c

RUN cp ./bin/scheme /usr/local/bin && \
    cd / && \
    rm -rf /usr/src/scheme.c
