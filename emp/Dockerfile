FROM ubuntu:18.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  build-essential \
  cmake \
  git \
  libssl-dev \
  sudo \
  wget \
  python \
  vim
ADD sh_test/ /root/sh_test
ADD ag_test/ /root/ag_test
ADD README.md .
ADD install.sh .
RUN ["bash", "install.sh"]
CMD ["/bin/bash"]

