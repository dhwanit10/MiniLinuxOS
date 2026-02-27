FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y build-essential

WORKDIR /app

COPY . .

RUN gcc src/*.c src/scheduling/*.c -Iinclude -o myOS

CMD ["./myOS"]