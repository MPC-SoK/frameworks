FROM ubuntu:22.04

WORKDIR /root

# Install required packages
RUN apt-get update && apt-get install -y \
  bzip2 \
  curl \
  doxygen \
  g++ \
  gcc \
  git \
  libcrypto++-dev \
  libgmp3-dev \
  libssl-dev \
  m4 \
  make \
  patch \
  python3 \
  python2 \
  python-is-python3 \
  vim \
  wget \
  yasm \
  zip \
  autotools-dev \
  autoconf \
  libtool \
  texinfo

ADD install_dependencies.sh .
RUN ["bash", "install_dependencies.sh"]

ADD source/ /root/source
ADD install.sh .
RUN ["bash", "install.sh"]

ADD README.md .

ENV PATH ~/.cargo/bin/:${PATH}

CMD ["/bin/bash"]
