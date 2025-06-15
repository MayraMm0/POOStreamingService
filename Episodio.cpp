#include "Episodio.h"

// Constructores
Episodio::Episodio() {}

Episodio::Episodio(string _titulo, int _temporada, float _calificacion)
{
    titulo = _titulo;
    temporada = _temporada;
    calificacion = _calificacion;
}

// Setters
void Episodio::set_titulo(string _titulo)
{
    titulo = _titulo;
}

void Episodio::set_temporada(int _temporada)
{
    temporada = _temporada;
}

void Episodio::set_calificacion(float _calificacion)
{
    calificacion = _calificacion;
}

// Getters
string Episodio::get_titulo() const
{
    return titulo;
}

int Episodio::get_temporada() const
{
    return temporada;
}

float Episodio::get_calificacion() const
{
    return calificacion;
}

// Metodo para mostrar su informacion
void Episodio::mostrar_info() const
{
    // Usa los getters para acceder a cada atributo
    cout << "Episodio: " << get_titulo() << endl;
    cout << "Temporada: " << get_temporada() << endl;
    cout << "Calificacion: " << get_calificacion() << endl;
}
