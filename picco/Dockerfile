FROM ubuntu:22.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  flex \
  bison \
  g++ \
  git \
  libgmp-dev \
  libssl-dev \
  make \
  python3 \
  libcrypto++-dev \
  vim

ADD install_picco.sh .
RUN sh install_picco.sh

ADD source/ /root/source/
ADD install_examples.sh .
RUN sh install_examples.sh
WORKDIR /root/source

CMD ["/bin/bash"]

