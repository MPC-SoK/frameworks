FROM ubuntu:18.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  bzip2 \
  clang \
  g++ \
  git \
  make \
  vim \
  wget

ADD source/ /root/source
#ADD README.md .

ADD install_dependencies.sh .
RUN ["bash", "install_dependencies.sh"]
ADD install.sh .
RUN ["bash", "install.sh"]
CMD ["/bin/bash"]

