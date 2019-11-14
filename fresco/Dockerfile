FROM ubuntu:18.04
RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install -y openjdk-8-jdk maven
WORKDIR /home/fresco-samples
ADD . /home/fresco-samples
RUN mvn package
