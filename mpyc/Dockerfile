FROM ubuntu:18.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  libmpc-dev \
  python3 \
  python3-pip \
  vim 

ADD source/ /root/source
ADD install.sh .
RUN ["bash", "install.sh"]

CMD ["/bin/bash"]
