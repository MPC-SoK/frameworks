FROM ubuntu:14.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  g++ \
  git \
  flex \
  make \
  python \
  vim \
  wget
ADD source/ /root/source
ADD README.md .
ADD install.sh .

RUN ["bash", "install.sh"]
CMD ["/bin/bash"]

