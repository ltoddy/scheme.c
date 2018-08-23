FROM ubuntu:18.04

WORKDIR /usr/src/scheme.c

COPY . /usr/src/scheme.c

ENV PATH=/usr/src/scheme.c/bin:${PATH}
