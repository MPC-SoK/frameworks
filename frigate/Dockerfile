# Unfortunately, no version of Ubuntu > 18.04 is supported. This is because we use
# Semi-Honest-BMR for executing the generated circuit, which does not compile on Ubuntu > 18.04.
# See: https://github.com/cryptobiu/Semi-Honest-BMR/issues/2

FROM ubuntu:18.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  g++ \
  git \
  flex \
  make \
  python3 \
  vim \
  wget

ADD README.md .
COPY source/frigate.vim /root/source/frigate.vim
ADD install.sh .
RUN ["bash", "install.sh"]

ADD source/ /root/frigaterelease/src/tests
CMD ["/bin/bash"]

