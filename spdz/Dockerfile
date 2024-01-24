FROM ubuntu:22.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  bzip2 \
  gcc \
  g++ \
  git \
  libgmp3-dev \
  m4 \
  make \
  man \
  python2 \
  tar \
  valgrind \
  vim \
  wget \
  yasm \
  autotools-dev \
  autoconf \
  libtool \
  texinfo

ADD install_dependencies.sh .
RUN bash install_dependencies.sh

ADD install.sh .
RUN bash install.sh

ADD README.md .
ADD run_example.sh ./SPDZ-2
ADD source/*.mpc ./SPDZ-2/Programs/Source/
ADD source/InputData ./SPDZ-2/Programs/InputData
