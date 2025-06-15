#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Video.h"
#include "Pelicula.h"
#include "Serie.h"
#include "Funciones.h"
#include "Episodio.h"
#include "exception"
#include "limits"
using namespace std;


int main()
{
    int opcion = -1;

    //  Declaración de algunas variables.
    string nombreArchivo, video_calificar, _titulo, _input, opcionStr;
    float calificacion;

    //  Se inicializa un vector del tipo Episodios.
    vector<Episodio> ep_serie1;

    //  Se intstancian episodios para una serie default.
    ep_serie1.emplace_back("Metamorfosis", 1, 8.2);
    //Se usa emplace_back porque el objeto se crea directamente en el vector
    ep_serie1.emplace_back("Fiesta en la piscina", 1, 9.0);
    ep_serie1.emplace_back("Pesca del dia", 1, 9.5);

    // Crea dinámicamente una serie y la guarda en el vector global.
    Serie* Serie1 = new Serie(1, 7, "H2O sirenas del mar", "drama", 9.5, 3, ep_serie1);
    todosLosVideos.push_back(Serie1);

    try
    {
        while (opcion != 0)
        {
            //  Se despliega el menú principal del programa.
            cout << "\n--- MENU DE OPCIONES ---\n";
            cout << "1. Cargar archivo de datos\n";
            cout << "2. Mostrar videos\n";
            cout << "3. Mostrar episodios de una serie con calificacion\n";
            cout << "4. Mostrar peliculas con cierta calificacion\n";
            cout << "5. Calificar un video\n";
            cout << "0. Salir\n";
            cout << "Ingrese una opcion: \n";
            cin.clear(); // Limpia flags de error.
            if (cin.peek() == '\n') cin.ignore(); // Elimina el salto de línea en caso de que exista.
            getline(cin, opcionStr);

            try
            {
                // Convierte entraga de string a int con manejo de errores.
                opcion = stoi(opcionStr); // Puede lanzar exception si no es un número.
            }
            catch (invalid_argument&)
            {
                cerr << "Error: Entrada invalida. Debe ingresar un numero.\n";
                continue;
            } catch (out_of_range&)
            {
                cerr << "Error: Numero fuera de rango permitido.\n";
                continue;
            }

            switch (opcion)
            {
            case 1:
                //  Opción de lectura de datos y construcción de objetos.   //
                nombreArchivo = "../Datos.txt";
                cout << "Cargando archivo desde '" << nombreArchivo << "'...\n";
                leerVideosDesdeArchivos(nombreArchivo);
                cout << "Se cargaron " << todosLosVideos.size() << " videos.\n";
                cout << "\n" << endl;
                break;
            case 2:
                //  Opción impresión de catálogo de videos. Muestra el contenido.   //
                cout << "Buscando contenido...\n";
                cout << endl;
                mostrarTodosLosVideos();
                break;

            case 3:
                // Opción para mostrar los episodios de una serie, con su calificación. //
                try
                {
                    cout << "Que serie quieres ver?" << endl;
                    //cin.ignore(); // Limpia el buffer para evitar errores con getline.
                    getline(cin, _titulo);
                    if (_titulo.empty())
                    {
                        //runtime_error se usa cuando: entrada inválida, no se encuentra un dato, fallas lógicas.
                        throw runtime_error("El titulo no puede estar vacio.");
                    }

                    if (todosLosVideos.empty())
                    {
                        throw runtime_error("No hay contenido en el catalogo.");
                    }

                    bool encontrado = false;

                    for (Video* v : todosLosVideos)
                    {
                        if (v->get_titulo() == _titulo)
                        {
                            encontrado = true;
                            Serie* s = dynamic_cast<Serie*>(v); // Down.
                            if (s != nullptr)
                            {
                                s->mostrar_episodiosCalificacion();
                            }
                            else
                            {
                                throw runtime_error("Ese titulo no corresponde a una serie con episodios.");
                            }
                        }
                    }

                    if (!encontrado)
                    {
                        throw runtime_error("No se encontro ninguna serie con ese titulo.");
                    }
                }
                catch (const exception& e)
                {
                    cerr << "Error: " << e.what() << endl;
                }
                break;

            case 4:
                //  Opción para acceder a una película dada una calificación.   //
                cout << "Ingrese la calificacion de la pelicula a buscar: " << endl;
                getline(cin, _input);

                try
                {
                    calificacion = stof(_input);
                    if (calificacion < 0 || calificacion > 10) // Validacion para que la calificacion este entre 1 y 10.
                    {
                        cerr << "Error: La calificacion debe de estar entre 1 y 10." << endl;
                        break;
                    }
                    mostrarCalificacionPeliculas(calificacion);
                }
                catch (invalid_argument& e)
                {
                    cerr << "Error: Entrada invalida. Debe de ingresar un numero.";
                }
                catch (out_of_range& e)
                {
                    cerr << "Error: La calificacion fuera de rango." << endl;
                }
                break;

            case 5:
                // Opción para calificar algún video existente en el catálogo.
                try
                {
                    cout << "Que video quieres calificar?" << endl;
                    getline(cin, video_calificar);

                    if (video_calificar.empty())
                    {
                        throw runtime_error("El nombre del video no puede estar vacio.");
                    }

                    // Validar que no sea solo un número
                    bool soloNumeros = true;
                    for (char c : video_calificar)
                    {
                        if (!isdigit(c) && !isspace(c))
                        {
                            soloNumeros = false;
                            break;
                        }
                    }

                    if (soloNumeros)
                    {
                        throw runtime_error("El nombre del video no puede ser solo un numero.");
                    }

                    calificarVideo(video_calificar);
                }
                catch (const exception& e)
                {
                    cerr << "Error: " << e.what() << endl;
                }
                break;

            case 0:
                // Opción para terminar el programa.     //
                cout << "Saliendo del programa.\n";
                liberarMemoria();
                exit(0);

            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
            }
        }
    }

    catch (const exception& e)
    {
        cerr << "Se produjo un error inesperado: " << e.what() << endl;
    }
    return 0;
}
