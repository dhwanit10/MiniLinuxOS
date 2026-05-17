FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    build-essential \
    libreadline-dev

WORKDIR /app

COPY . .

RUN gcc src/myOS.c src/thread-process/thread.c src/scheduling/fcfs.c src/scheduling/srtf.c src/scheduling/roundrobin.c src/scheduling/priority.c -Iinclude -o myOS -lreadline -lm -pthread

CMD ["./myOS"]