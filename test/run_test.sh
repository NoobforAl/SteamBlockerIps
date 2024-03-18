docker build --pull --rm -f "test/Dockerfile" -t testsbips:latest "test" 

docker network create test_sbips_network

docker run --rm --cap-add=NET_ADMIN --network test_sbips_network  -v ./:/app --name test_sbips testsbips:latest

docker network rm test_sbips_network