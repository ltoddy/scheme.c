FROM ubuntu:18.04

WORKDIR /usr/src/scheme.c

COPY . /usr/src/scheme.c

RUN apt-get update && \
    apt-get install cmake && \
    cmake . && make

ENV PATH=/usr/src/scheme.c/bin:${PATH}
