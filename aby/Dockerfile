FROM ubuntu:16.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  g++ \
  git \
  make \
  libgmp-dev \
  libglib2.0-dev \
  libssl-dev \
  vim \
  wget
ADD source/ /root/source
ADD README.md .
ADD install.sh .
RUN ["bash", "install.sh"]
CMD ["/bin/bash"]

