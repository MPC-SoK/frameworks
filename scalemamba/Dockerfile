FROM centos:7 
WORKDIR /root
RUN yum update 
# for yasm:
RUN yum --enablerepo=extras install -y epel-release 
RUN yum install -y \
  bzip2 \
  doxygen \
  gcc-c++ \
  git \
  libgmp3-dev \
  m4 \
  make \
  patch \
  python \
  texlive-full \ 
  vim \
  wget \
  yasm

ADD source/ /root/source
ADD install.sh .
RUN ["bash", "install.sh"]

ADD README.md .

CMD ["/bin/bash"]
