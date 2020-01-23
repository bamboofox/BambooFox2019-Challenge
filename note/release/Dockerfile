FROM ubuntu:18.04
MAINTAINER pandaft
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install xinetd -y
RUN apt-get install python3 -y
RUN useradd -m note 
COPY ./xinetd /etc/xinetd.d/note
COPY ./flag /home/note/flag
COPY ./note /home/note/note
COPY ./run.sh /home/note/run.sh
RUN chown -R root:root /home/note
RUN chmod -R 755 /home/note/
CMD ["/usr/sbin/xinetd","-dontfork"]
