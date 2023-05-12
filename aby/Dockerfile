FROM ubuntu:22.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  git \
  lzip \
  m4 \
  make \
  cmake \
  g++ \
  libgmp-dev \
  libglib2.0-dev \
  libssl-dev \
  libboost-all-dev \
  software-properties-common \
  vim \
  wget

ADD source/ /root/source
ADD README.md .

ADD install.sh .
RUN ["bash", "install.sh"]
CMD ["/bin/bash"]

