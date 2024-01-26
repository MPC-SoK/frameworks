FROM ubuntu:22.04

WORKDIR /root

RUN apt update \
    && apt install -y vim git build-essential python3 cmake

ADD install.sh .
RUN ./install.sh

WORKDIR /root/aby3
ADD source ./samples
# build our examples
RUN python3 build.py

ADD run_example.sh .
