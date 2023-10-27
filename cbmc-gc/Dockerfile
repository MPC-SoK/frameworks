FROM ubuntu:20.04
# Can't upgrade to ubuntu:22:04 since this causes bison 3.8.2 to be installed, which is incompatible
WORKDIR /root
RUN apt-get update && apt-get install -y \
  bison \
  flex \
  g++ \
  git \
  libwww-perl \
  make \
  patch \
  python3 \
  wget \
  vim

ADD install.sh .
RUN ["bash", "install.sh"]

WORKDIR /root/CBMC-GC-2

ADD source/ ./examples/

ADD README.md .

ADD runall.sh .

CMD ["/bin/bash"]


