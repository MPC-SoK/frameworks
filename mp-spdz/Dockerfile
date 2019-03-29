FROM ubuntu:16.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  curl \
  python \
  openssl

ADD install.sh .
RUN ["bash", "install.sh"]

add README.md test_readme.sh ./
add source/* ./MP-SPDZ/Programs/Source/
