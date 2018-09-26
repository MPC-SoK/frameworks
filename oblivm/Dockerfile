FROM ubuntu:16.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  default-jdk \
  git \
  python \
  vim

ADD README.md .

ADD install.sh .
RUN ["bash", "install.sh"]

ADD source/mult3 /root/ObliVMLang/examples/mult3
ADD source/innerProd /root/ObliVMLang/examples/innerProd
ADD source/xtabs /root/ObliVMLang/examples/xtabs
ADD source/genInput.py /root/ObliVMLang/
