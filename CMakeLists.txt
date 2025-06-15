cmake_minimum_required(VERSION 3.30)
project(ServicioStreamingSP)

set(CMAKE_CXX_STANDARD 20)

add_executable(ServicioStreamingSP main.cpp
        Video.cpp
        Video.h
        Serie.cpp
        Serie.h
        Pelicula.cpp
        Pelicula.h
        Episodio.cpp
        Episodio.h
        Funciones.cpp
)
