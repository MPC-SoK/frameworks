FROM ubuntu:22.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  g++ \
  git \
  flex \
  make \
  python3 \
  vim \
  flex \
  bison \
  libbison-dev \
  wget

ADD README.md .
COPY source/frigate.vim /root/source/frigate.vim
ADD install.sh .
RUN ["bash", "install.sh"]

ADD source/ /root/frigaterelease/src/tests
CMD ["/bin/bash"]

