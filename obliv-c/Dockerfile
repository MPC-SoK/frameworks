FROM ubuntu:16.04
WORKDIR /root

RUN apt-get update && apt-get install -y \
  ocaml \
  libgcrypt20-dev \
  ocaml-findlib \
  opam \
  m4 \
  git \
  vim \
  gcc \
  make

ADD install.sh .
RUN ["bash", "install.sh"]

ADD source/ /root/
ADD ./README.md .
