CC := gcc
COMPRSORE := upx

PATH_OBJECT_FILES_TO_COMPILE := ./build/main.o ./build/log.o ./build/core.o ./build/version.o
LIB_FLAGS := -lcurl -lcjson
OUT_EXE := ./app

all: run

run: build
	./app

build: buildfolder main.o log.o core.o version.o
	$(CC) -o $(OUT_EXE) $(PATH_OBJECT_FILES_TO_COMPILE) $(LIB_FLAGS)
	$(COMPRSORE) $(OUT_EXE)

buildfolder:
	@mkdir -p ./build 

main.o: ./src/main.c
	$(CC) -o ./build/main.o -c ./src/main.c

log.o: ./src/log.c
	$(CC) -o ./build/log.o -c ./src/log.c

core.o: ./src/core.c
	$(CC) -o ./build/core.o -c ./src/core.c

version.o: ./src/version.c
	$(CC) -o ./build/version.o -c ./src/version.c

clean: 
	rm -rf ./build/* ./app ./blockips.txt ./data.json

test: 
	@echo "Start tests"
	sh ./test/run_test.sh

