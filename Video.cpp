#include "Video.h"

// Constructores
Video::Video(): id(0), calificacion(0.0) {}

Video::Video(int _id, string _titulo, string _genero, float _calificacion)
{
    id = _id;
    titulo = _titulo;
    genero = _genero;
    this->calificacion = _calificacion;
}

// Destructor
Video::~Video(){}

// Getters
int Video::get_id() const
{
    return id;
}

string Video::get_titulo() const
{
    return titulo;
}

string Video::get_genero() const
{
    return genero;
}

float Video::get_calificacion() const
{
    return calificacion;
}

// Setters
void Video::set_id(int _id)
{
    id = _id;
}

void Video::set_titulo(string _titulo)
{
    titulo = _titulo;
}

void Video::set_genero(string _genero)
{
    genero = _genero;
}

void Video::set_calificacion(float _calificacion)
{
    calificacion = _calificacion;
}

// Sobrecarga de operador.
// ostream: importante para cademas de output.
ostream& operator<<(ostream& os, const Video& v)
{
    // Redirige la impresión al metodo virtual polimórfico.
    v.mostrar_info(); // Imprime directamente (usa cout por dentro del metodo).
    return os;
}
