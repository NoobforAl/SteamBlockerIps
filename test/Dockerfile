FROM ubuntu:22.04

LABEL AUTHOR="NoobforAl"
LABEL VERSION="0.1.0"

WORKDIR /app

RUN apt update 

RUN apt install -y \
    gcc make curl \
    libcurl4 libcurl4-gnutls-dev  libcjson-dev \
    python3 python3-pip \
    ufw upx sudo

RUN pip install requests

CMD [ "python3", "test/sbips_test.py" ]