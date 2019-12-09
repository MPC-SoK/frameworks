FROM ubuntu:16.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  cmake \
  g++ \
  git \
  lzip \
  m4 \
  make \
  libglib2.0-dev \
  libgmp-dev \
  libssl-dev \
  ocaml \
  opam \
  software-properties-common \
  unzip \
  vim \
  wget

ADD install_dependencies.sh .
RUN ["bash", "install_dependencies.sh"]

ADD install_aby.sh .
RUN ["bash", "install_aby.sh"]

ADD install_ezpc.sh .
RUN ["bash", "install_ezpc.sh"]

CMD ["/bin/bash"]

