FROM ubuntu:22.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  software-properties-common \
  build-essential \
  cmake \
  git \
  libssl-dev \
  sudo \
  wget \
  python3 \
  vim

ADD install.sh .
RUN bash install.sh

ADD sh_test/ /root/sh_test
ADD ag_test/ /root/ag_test

RUN cd sh_test && cmake . && make && cd ..
RUN cd ag_test && cmake . && make && cd ..


CMD ["/bin/bash"]

