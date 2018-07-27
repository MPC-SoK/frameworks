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

ADD source/* /root/ObliVMLang/examples/
RUN ["mv", "/root/ObliVMLang/examples/genInput.py", "/root/ObliVMLang/"]
#ADD mult3 /root/ObliVMLang/examples/mult3
#ADD innerProd /root/ObliVMLang/examples/innerProd 
#ADD xtabs /root/ObliVMLang/examples/xtabs

#ADD source/genInput.py /root/ObliVMLang/
