FROM ubuntu:16.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  bzip2 \
  gcc \
  g++ \
  git \
  libboost-thread-dev \
  libgmp3-dev \
  m4 \
  make \
  man \
  python \
  tar \
  valgrind \
  vim \
  wget \
  yasm

ADD install.sh .
RUN ["bash", "install.sh"]

add README.md test_readme.sh ./
add source/* ./MP-SPDZ/Programs/Source/
