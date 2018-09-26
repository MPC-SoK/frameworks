FROM ubuntu:16.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  bison \
  flex \
  g++ \
  git \
  libgmp-dev \
  libssl-dev \
  make \
  python \
  vim
ADD source/ /root/source
ADD README.md .
ADD install.sh .
RUN ["bash", "install.sh"]
CMD ["/bin/bash"]

