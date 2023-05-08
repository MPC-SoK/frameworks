FROM node:19.7.0-alpine3.16
WORKDIR /root
RUN apk add  \
  git \
  vim \
  bash

RUN git clone https://github.com/multiparty/jiff
WORKDIR /root/jiff
RUN git checkout 8ea565d
RUN npm install

ADD *.sh ./
ADD source/ /root/source
#RUN bash vim.sh

RUN cp -r ../source/* demos/
ENTRYPOINT /bin/bash
