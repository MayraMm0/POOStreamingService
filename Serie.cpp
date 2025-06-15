#include "Serie.h"
#include <iostream>
using namespace std;

// Constructores
Serie::Serie(): temporadas(0), numEpisodios(0) {}

Serie::Serie(int _temporadas, int _id, string _titulo, string _genero, float _calificacion, int _numEpisodios,vector<Episodio> _episodios)
    :Video(_id, _titulo, _genero, _calificacion), temporadas(_temporadas), numEpisodios(_numEpisodios),episodios(_episodios) {}

// Setters
void Serie::set_temporadas(int _temporadas)
{
    temporadas = _temporadas;
}

void Serie::set_numEpisodios(int _numEpisodios)
{
    numEpisodios = _numEpisodios;
}

void Serie::set_episodios(vector<Episodio> _episodios)
{
    episodios = _episodios;
}

// Getters
int Serie::get_temporadas() const
{
    return temporadas;
}

int Serie::get_numEpisodios() const
{
    return numEpisodios;
}

vector<Episodio> Serie::get_episodios()
{
    return episodios;
}

// Metodo específico de serie
void Serie::agregar_episodio(const Episodio& episodio) // se toma una referencia a un episodio instanciado
{
    // Se agrega al vector de episodios de la serie
    episodios.push_back(episodio);
}

// Metodo específico de serie, usado en opción 3. del menú principal
void Serie::mostrar_episodiosCalificacion()
{
    if (get_episodios().size() == 0)
    {
        // Checa si la serie no tiene episodios
        cout << "Esta serie aun no tiene episodios" << endl;
    }

    // En caso de que sí tenga episodios
    cout << "----------------- " << get_titulo() << " -----------------" << endl;
    for (int i = 1; i <= get_temporadas(); i++) // Ciclo realizado por de temporada de la serie
    {
        cout << "Temporada " << i << endl;
        for (Episodio& ep : episodios)
        {
            // Se recorre el vector de referencias a episodios
            if (ep.get_temporada() == i)
            {
                // Checa si el episodio pertenece a la temporada del ciclo
                cout << "  " << ep.get_titulo() // imprime título
                    << " | Calificacion: " << ep.get_calificacion() << endl; // imprime calificación
            }
        }
        cout << "\n";
    }
}

// Metodo sobreescrito
void Serie::mostrar_info() const
{
    // Se accede a cada atributo usando getters propios de la clase y heredados de Video
    cout << "****************************************" << endl;
    cout << "Tipo: Serie" << endl;
    cout << "Titulo: " << get_titulo() << endl;
    cout << "Temporadas: " << get_temporadas() << endl;
    cout << "Genero: " << get_genero() << endl;
    cout << "Calificacion promedio: " << get_calificacion() << endl;
    cout << "Numero de episodios: " << get_numEpisodios() << endl;
    cout << "------------- Episodios ----------------" << endl;
    for (const auto& ep : episodios)
    {
        // Recorre el vector de referencias a episodios y los imprime
        cout << "----------------" << endl;
        ep.mostrar_info();
    }
    cout << "****************************************\n" << endl;
}
