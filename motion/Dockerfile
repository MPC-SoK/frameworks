FROM ubuntu:20.04

ENV DEBIAN_FRONTEND noninteractive

WORKDIR /root
RUN apt-get update && apt-get install -y --no-install-recommends \
  libssl-dev \
  git \
  make \
  wget \
  build-essential \
  software-properties-common \
  libgoogle-perftools-dev

ADD install_dependencies.sh .
RUN ["bash", "install_dependencies.sh"]

ADD install.sh .
RUN ["bash", "install.sh"]
CMD ["/bin/bash"]
