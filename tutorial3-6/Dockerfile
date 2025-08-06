FROM ubuntu:noble AS base
WORKDIR /app
COPY --chmod=555 challx run
COPY flag.txt /app/flag.txt

FROM pwn.red/jail
COPY --from=base / /srv
ENV JAIL_TIME=120 JAIL_CPU=100 JAIL_MEM=10M
