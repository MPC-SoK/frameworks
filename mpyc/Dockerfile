FROM python:3.9.16-bullseye
WORKDIR /root
RUN apt-get update && apt-get install -y \
  libmpc-dev \
  vim 

ADD requirements.txt .
RUN ["pip", "install", "-r", "requirements.txt"]

ADD source/ /root/source

CMD ["/bin/bash"]
