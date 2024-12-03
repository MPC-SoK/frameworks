FROM secretflow/secretflow-lite-anolis8:1.10.0b1

RUN yum install -y time

WORKDIR /root

ADD source ./

RUN ./mult3.py 1 2 3
RUN ./innerprod.py 10
RUN ./xtabs.py 10
RUN ./xtabs_jax.py 10
RUN ./cmp.py 10
