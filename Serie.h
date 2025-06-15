#ifndef SERIE_H
#define SERIE_H

#include "Video.h"
#include "Episodio.h"
#include <vector>
#include <string>
using namespace std;

class Serie : public Video { // Hereda de clase virtual Video.
private:
    // Atributos específicos de una serie.
    int temporadas;
    int numEpisodios;
    vector<Episodio> episodios;

public:
    // Constructores.
    Serie();
    Serie(int _temporadas, int _id, string _titulo, string _genero, float _calificacion, int num_episodios, vector<Episodio> _episodios);

    // Setters..
    void set_temporadas(int _temporadas);
    void set_numEpisodios(int _numEpisodios);
    void set_episodios(vector<Episodio> _episodios);

    // Getters.
    int get_temporadas() const;
    int get_numEpisodios() const;
    vector<Episodio> get_episodios();

    // Metodo propio de serie para añadir episodios individuales (no varios a la vez).
    void agregar_episodio(const Episodio& episodio);

    // Metodo propio de serie para mostrar sus episodios, con calificación, organizados por temporada.
    void mostrar_episodiosCalificacion();

    //  Metodo sobreescrito de Video.
    void mostrar_info() const override;
};

#endif // SERIE_H
