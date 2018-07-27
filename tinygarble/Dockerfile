FROM ubuntu:16.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  g++ \
  git \
  libboost-all-dev \
  libssl-dev \
  software-properties-common \
  vim \
  yosys
RUN ["apt-add-repository", "ppa:george-edison55/cmake-3.x"]
RUN ["apt-get", "update"]
#RUN ["apt-get", "upgrade"]
RUN apt-get install -y cmake
#ADD source/ /root/source
#ADD README.md .
ADD install.sh .
RUN ["bash", "install.sh"]
CMD ["/bin/bash"]

