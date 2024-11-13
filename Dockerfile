FROM ubuntu:20.04

RUN apt update -y

ENV DEBIAN_FRONTEND=noninteractive

RUN apt install -y build-essential git nano wget cmake dos2unix octave libxml2 libxml2-dev bc gdb

RUN mkdir /root/tests

WORKDIR /root

RUN git clone https://vcis-gitlab.f4e.europa.eu/aneto/MARTe2.git MARTe2

RUN git clone https://vcis-gitlab.f4e.europa.eu/aneto/MARTe2-components.git

# We implement this patch mainly for test purposes - it ensures that when we tear down the application, we let the filewriter
# datasource flush and close the file properly by waiting for it infinitely. This allows us to test at max speeds without losing
# data due to the filewriter writing slowly - this is purely for testing and not intended to be added to production
# in production we'll be writing to binary, it's possible filewriter is only slow in csv because its ASCII writing and we have
# seen this sort of data, also in production we run at 2ms, not trying to infinite go as we're trying to reduce test time.

COPY ensurefileflush.patch /root/MARTe2/ensurefileflush.patch

RUN cd /root/MARTe2 && git apply ensurefileflush.patch

RUN cd MARTe2 && make -f Makefile.x86-linux core

ENV MARTe2_DIR=/root/MARTe2

RUN cd MARTe2-components && make -f Makefile.x86-linux core

ENV MARTe2_Components_DIR=/root/MARTe2-components

RUN mkdir /root/RunnerGAMs

RUN mkdir /root/RunnerGAMs/EndGAM && mkdir /root/RunnerGAMs/RFileDataSource

RUN cd /root

ADD ./EndGAM/* /root/RunnerGAMs/EndGAM/

ADD ./RFileDataSource/* /root/RunnerGAMs/RFileDataSource/

ADD ./Makefile.* /root/RunnerGAMs/

RUN dos2unix -R /root/*

RUN cd RunnerGAMs && make -f Makefile.x86-linux

ENV Runner_DIR=/root/RunnerGAMs

ADD marte.sh /root/

RUN chmod +x /root/marte.sh

RUN dos2unix -R /root/marte.sh