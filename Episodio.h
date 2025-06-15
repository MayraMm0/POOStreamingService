#ifndef EPISODIO_H
#define EPISODIO_H

#include <iostream>
#include <string>
using namespace std;

class Episodio {
private:
    // Atributos de cada episodio.
    string titulo;
    int temporada;
    float calificacion;
public:
    // Constructor
    Episodio();
    Episodio(string _titulo, int _temporada, float _calificacion);

    // Setters.
    void set_titulo(string _titulo);
    void set_temporada(int _temporada);
    void set_calificacion(float _calificacion);

    // Getters.
    string get_titulo() const;
    int get_temporada() const;
    float get_calificacion() const;

    // Metodo para acceder a toda la informacion de un episodio.
    void mostrar_info() const;
};

#endif // EPISODIO_H
