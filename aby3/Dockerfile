FROM ubuntu:18.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  bzip2 \
  clang \
  g++ \
  git \
  cmake \
  make \
  vim \
  wget
#ADD source/ /root/source
#ADD README.md .

ADD install.sh .
RUN ["bash", "install.sh"]
# this breaks
ADD breaks.sh .
RUN ["bash", "breaks.sh"]
CMD ["/bin/bash"]

