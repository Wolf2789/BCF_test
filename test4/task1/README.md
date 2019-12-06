## 1. Building docker image
```
docker build --no-cache -t ubuntu/yaml:latest .
```
---
## 2. Runing docker container
```
docker run --rm -it ubuntu/yaml
```
---
# Inside docker container:
---
## 3. Compiling source code into executable
```
make
```
---
## 4. Running compiled executable
```
make run
```
or
```
./persons
```
---
You can also compile and run at once, using this command:
```
make all
```