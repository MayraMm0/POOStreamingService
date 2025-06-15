#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "Video.h"
#include "Pelicula.h"
#include "Serie.h"
#include "Episodio.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// El vector que guarda el catálogo se declara aquí.
// extern: declara una variable global para poder acceder a ella en otros archivos.
extern vector<Video*> todosLosVideos;

// Usada en opción 1. Para recibir un archivo con videos a instanciar.
vector<Video*> leerVideosDesdeArchivos(const string& nombreArchivo);

// Usada en opción 2. Para mostrar el catálogo.
void mostrarTodosLosVideos();

// Usada en opción 4. Para encontrar películas con cierta calificación.
void mostrarCalificacionPeliculas(float calificacion);

// Usada en opción 5. Para calificar un video específico.
void calificarVideo(string video_calificar);

// Usada en opción 0. Para liberar memoria.
void liberarMemoria();

#endif //FUNCIONES_H
