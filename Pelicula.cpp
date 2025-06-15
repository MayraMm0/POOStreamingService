#include "Pelicula.h"

// Constructores
Pelicula::Pelicula(): anio(0), duracion(0) {}

Pelicula::Pelicula(int _anio, int _id, int _duracion, string _titulo, string _genero, float _calificaion) : Video(_id, _titulo, _genero, _calificaion), anio(_anio), duracion(_duracion) {}

// Setters
void Pelicula::set_anio(int _anio)
{
    anio = _anio;
}

void Pelicula::set_duracion(int _duracion)
{
    duracion = _duracion;
}

// Getters
int Pelicula::get_anio() const
{
    return anio;
}

int Pelicula::get_duracion() const
{
    return duracion;
}

// Metodo sobreescrito para mostrar información
void Pelicula::mostrar_info() const
{
    // Se accede a cada atributo usando getters propios de la clase y heredados de Video
    cout << "****************************************" << endl;
    cout << "Tipo: Pelicula" << endl;
    cout << "Titulo: " << get_titulo() << endl;
    cout << "Duracion: " << get_duracion() << " minutos" << endl;
    cout << "Genero: " << get_genero() << endl;
    cout << "Anio: " << get_anio() << endl;
    cout << "Calificacion: " << get_calificacion() << endl;
    cout << "****************************************\n" << endl;
}
