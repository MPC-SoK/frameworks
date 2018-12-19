FROM ubuntu:16.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  autoconf \
  gcc \
  g++ \
  git \
  libboost-dev \
  libboost-thread-dev \
  libgmp3-dev \
  libntl-dev \
  libsodium-dev \
  libssl-dev \
  libtool \
  m4 \
  make \
  man \
  python \
  sudo \
  texinfo \
  valgrind \
  vim \
  yasm

ADD install.sh .
RUN ["bash", "install.sh"]

add README.md test_readme.sh ./
add source/* ./MP-SPDZ/Programs/Source/
