FROM ubuntu:22.04

WORKDIR /root

RUN apt update \
    && apt install -y vim git build-essential python3 cmake

ADD install.sh .
RUN ./install.sh

WORKDIR /root/aby3
ADD source .
