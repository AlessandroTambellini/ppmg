# ppmg

Draw ppm images.  
A ppm viewer is required to look at the generated image: [PPM
Viewer](https://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html).  

## Build
### Without SDL:
```sh
chmod +x build.sh
./build
```
### With SDL:
```sh
chmod +x build.sh
./build sdl
```

## Install SDL (Optional)
### On Ubuntu/Debian:
```sh
sudo apt-get install libsdl2-dev
```
### On Fedora/RHEL/CentOS:
```sh
sudo dnf install SDL2-devel
```

Credits: [New Graphics Library in C (Olive.c Ep.01)](https://www.youtube.com/watch?v=LmQKZmQh1ZQ&list=PLpM-Dvs8t0Va-Gb0Dp4d9t8yvNFHaKH6N&index=1)
