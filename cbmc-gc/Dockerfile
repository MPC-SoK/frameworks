FROM ubuntu:16.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  bison \
  flex \
  g++ \
  git \
  libwww-perl \
  make \
  patch \
  python \
  wget \
  vim

ADD install.sh .
RUN ["bash", "install.sh"]

WORKDIR /root/CBMC-GC-2

ADD source/ ./examples/

ADD README.md .

ADD runall.sh .

CMD ["/bin/bash"]


