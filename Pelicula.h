#ifndef PELICULA_H
#define PELICULA_H
#include <string>
#include "Video.h"
using namespace std;

class Pelicula : public Video { // Hereda de clase virtual Video.
private:
    // Atributos específicos de películas.
    int anio, duracion;
public:
    // Constructores.
    Pelicula();
    Pelicula(int _anio, int _id, int _duracion, string _nombre, string _genero, float _calificacion);

    // Setters.
    void set_duracion(int _duracion);
    void set_anio(int _anio);

    // Getters.
    int get_duracion() const;
    int get_anio() const;

    // Metodos sobreescritos.
    void mostrar_info() const override;
    bool Peli() override{ return true;}

};

#endif // PELICULA_H
