FROM python:3.9.16-bullseye

ARG fromsource=no

WORKDIR /root
RUN apt-get update && apt-get install -y \
  curl \
  openssl \
  xz-utils \
  automake \
  build-essential \
  clang \
  cmake \
  git \
  libboost-dev \
  libboost-thread-dev \
  libgmp-dev \
  libntl-dev \
  libsodium-dev \
  libssl-dev \
  libtool \
  python3

ADD install.sh .
RUN ./install.sh $fromsource

ADD README.md test_readme.sh ./
ADD source/* ./MP-SPDZ/Programs/Source/

CMD ["/bin/bash"]
