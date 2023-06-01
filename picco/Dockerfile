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
  vim
ADD source/ /root/source
ADD README.md .
ADD install.sh .
RUN ["bash", "install.sh"]
CMD ["/bin/bash"]

