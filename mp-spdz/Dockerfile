FROM python:3.9.16-bullseye
WORKDIR /root
RUN apt-get update && apt-get install -y \
  curl \
  openssl \
  xz-utils

ADD install.sh .
RUN ["bash", "install.sh"]

ADD README.md test_readme.sh ./
ADD source/* ./MP-SPDZ/Programs/Source/

CMD ["/bin/bash"]
