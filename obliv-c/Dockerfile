# We cannot use anything more recent than ubuntu 20.04,
# because otherwise we get the error "Cabs2cil had some errors".
# Details are described in this issue: https://github.com/samee/obliv-c/issues/109
FROM ubuntu:20.04

WORKDIR /root

RUN apt-get update && apt-get install -y \
  ocaml \
  libgcrypt20-dev \
  ocaml-findlib \
  ocamlbuild \
  ocaml-batteries-included \
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
