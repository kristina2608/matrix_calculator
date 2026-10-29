# По умолчанию берем официальный образ, но на ПК сможем переопределить через --build-arg
ARG BASE_IMAGE=ubuntu:22.04
FROM ${BASE_IMAGE} AS builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y cmake g++ git && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --parallel $(nproc)

FROM ${BASE_IMAGE}

WORKDIR /app

COPY --from=builder /app/build/matrix_calculator .

CMD ["./matrix_calculator"]

