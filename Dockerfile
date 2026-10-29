FROM cr.yandex/mirror/library/ubuntu:22.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive

# ДОБАВЛЕН GIT для скачивания Google Test внутри контейнера
RUN apt-get update && apt-get install -y cmake g++ git && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --parallel $(nproc)

# Этап 2: Финальный минимальный образ
FROM cr.yandex/mirror/library/ubuntu:22.04

WORKDIR /app

COPY --from=builder /app/build/matrix_calculator .

CMD ["./matrix_calculator"]
