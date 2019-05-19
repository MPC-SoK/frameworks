FROM ubuntu:16.04
WORKDIR /root
RUN apt-get update && apt-get install -y \
  git \
  npm \
  vim \
  wget

RUN ["wget", "https://nodejs.org/dist/v10.15.3/node-v10.15.3-linux-x64.tar.xz"]
ADD *.sh ./
RUN ["bash", "install.sh"]
RUN ["git", "clone", "https://github.com/multiparty/jiff"]
RUN ["bash", "install_jiff.sh"]

RUN ["bash", "vim.sh"]
