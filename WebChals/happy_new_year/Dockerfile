FROM debian:bullseye

RUN groupadd web && useradd -g web -d /home/web web
ADD server /home/web/server
RUN mv /home/web/server/git /home/web/server/.git

RUN rm -rf /bin /sbin /usr/bin /usr/sbin
ADD bin /bin

USER web
WORKDIR /home/web/server

CMD [ "/home/web/server/server.out" ]
