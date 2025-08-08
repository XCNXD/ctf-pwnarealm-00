FROM ubuntu:noble as base

WORKDIR /app
COPY --chmod=777 challx run
COPY --chmod=774 flag.txt flag.txt
# COPY --chmod=772 fd fd
FROM pwn.red/jail
COPY --from=base / /srv

ENV JAIL_TIME=120 JAIL_CPU=100 JAIL_MEM=10M JAIL_SYSCALLS=open,openat

