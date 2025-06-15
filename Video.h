#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <iostream>
using namespace std;

class Video { // Clase base ABSTRACTA PURA
private:
    // Atributos de clase base "Video", de la que heredan pelicula y serie
    int id;
    string titulo, genero;
    float calificacion;

public:
    // Constructores
    Video();
    Video(int _id, string _titulo, string _genero, float _calificacion);

    // Destructor virtual
    virtual ~Video();

    // Getters
    int get_id() const;
    string get_titulo() const;
    string get_genero() const;

    // Setters
    void set_id(int _id);
    void set_titulo(string _titulo);
    void set_genero(string _genero);

    // Metodos virtuales que las derivadas pueden sobreescribir
    virtual float get_calificacion() const;
    virtual void set_calificacion(float _calificacion);
    virtual bool Peli(){return false;}

    // Method virtual puro, no se implementa en clase base
    // Obliga a las derivadas a implementarlo
    virtual void mostrar_info() const = 0;

    // Sobrecarga de operador "<<"
    friend ostream& operator<<(ostream& os, const Video& v);

};

#endif // VIDEO_H
