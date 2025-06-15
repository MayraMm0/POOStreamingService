#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include "Pelicula.h"
#include "Serie.h"
#include "Episodio.h"
using namespace std;

vector<Video*> todosLosVideos; // Se instancía el vector global (solo aquí)
// Esto permite polimorfismo, ya que se almacenan Pelicula* y Serie* en un solo vector de Video*.

//  OP #1 | METODO DE LECTURA Y CONSTRUCCION DE OBJETOS //
vector<Video*> leerVideosDesdeArchivos(const string& nombreArchivo)
{
    // // Abre el archivo en modo lectura.
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        // Si falla la apertura, muestra error y retorna lo que haya en todosLosVideos.
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return todosLosVideos;
    }

    string tipoVideo, etiqueta, valor; // Variables auxiliares para lectura.

    while (archivo >> tipoVideo)
    {
        // Mientras haya tipo de video que leer.
        if (tipoVideo == "Pelicula")
        {
            // Variables para construir objeto Pelicula.
            string nombre, genero;
            int id, duracion, anio;
            float calificacion;

            // Lee los datos según el formato del archivo, y los convierte al tipo de dato aceptado por el constructor.
            archivo >> etiqueta >> etiqueta >> valor;
            id = stoi(valor);
            archivo >> etiqueta >> etiqueta;
            getline(archivo, nombre);
            nombre = nombre.substr(1); // Quita primer espacio.
            archivo >> etiqueta >> etiqueta >> valor;
            duracion = stoi(valor);
            archivo >> etiqueta >> etiqueta;
            getline(archivo, genero);
            genero = genero.substr(1);
            archivo >> etiqueta >> etiqueta >> valor;
            calificacion = stof(valor);
            archivo >> etiqueta >> etiqueta >> valor;
            anio = stoi(valor);

            // Crea nueva película y la agrega al vector global.
            // Usando pointer esta se guarda hasta que se destruya con delete.
            Pelicula* p = new Pelicula(anio, id, duracion, nombre, genero, calificacion);
            todosLosVideos.push_back(p);
        }

        else if (tipoVideo == "Serie")
        {
            // Variables para construir objeto Serie.
            vector<Episodio> episodios;
            int id, temporadas, numEpisodios;
            string nombre, genero;
            float calificacion;

            // Lee datos generales de la serie.
            archivo >> etiqueta >> etiqueta >> valor;
            id = stoi(valor);
            archivo >> etiqueta >> etiqueta;
            getline(archivo, nombre);
            nombre = nombre.substr(1); // Quita primer espacio.
            archivo >> etiqueta >> etiqueta;
            getline(archivo, genero);
            genero = genero.substr(1);
            archivo >> etiqueta >> etiqueta >> valor;
            calificacion = stof(valor);
            archivo >> etiqueta >> etiqueta >> valor;
            temporadas = stoi(valor);
            archivo >> etiqueta >> etiqueta >> valor;
            numEpisodios = stoi(valor);

            for (int i = 0; i < numEpisodios; ++i)
            {
                // Datos de cada episodio
                string tituloEpi;
                int temporadaEpi;
                float calificacionEpi;

                archivo >> etiqueta >> etiqueta;
                getline(archivo, tituloEpi);
                tituloEpi = tituloEpi.substr(1);
                archivo >> etiqueta >> etiqueta >> valor;
                temporadaEpi = stoi(valor);
                archivo >> etiqueta >> etiqueta >> valor;
                calificacionEpi = stof(valor);

                // Agrega episodio al vector
                Episodio ep(tituloEpi, temporadaEpi, calificacionEpi);
                episodios.push_back(ep);
            }

            // Crea serie con todos sus episodios y la agrega al vector global.
            Serie* s = new Serie(temporadas, id, nombre, genero, calificacion, numEpisodios, episodios);
            todosLosVideos.push_back(s);
        }
    }
    archivo.close(); // Cierra.
    return todosLosVideos;
}


//  OP #2 | METODO PARA ACCEDER A LA INFROMACION DE CADA OBJETO DEL VECTOR VIDEOS  //
void mostrarTodosLosVideos()
{
    if (todosLosVideos.empty()) // Si no hay video.
    {
        cout << "No hay contenido..." << endl;
        return;
    }
    for (Video* v : todosLosVideos) // Recorre vector global donde está el catálogo.
    {
        cout << *v << endl; // Usamos polimorfismo usando sobrecarga de operador..
        // Se imprime de diferente modo según su tipo.
    }
}


// OP #4 | METODO PARA MOSTRAR PALICULAS POR CALIFICACION   //
void mostrarCalificacionPeliculas(float calificacion)
{
    bool hayCoincidencias = false; // Variable para saber si se encontraron películas en el rango de calificación.

    for (int i = 0; unsigned(i) < todosLosVideos.size(); i++)
    {
        // Recorre vector global.
        if (todosLosVideos[i]->Peli()) // Verifica si el objeto actual es de tipo película.
        {
            float calif = todosLosVideos[i]->get_calificacion(); // Obtiene su calificación.
            // Compara si la calificación está dentro de cierto rango, de acuerdo a lo que quiere el usuario.
            if (calif >= (calificacion - 0.5) && calif <= (calificacion + 1.0))
            {
                todosLosVideos[i]->mostrar_info();
                hayCoincidencias = true; // Marca que sí hubo coincidencias.
            }
        }
    }

    if (!hayCoincidencias)
    {
        // Si no se encontraron coincidencias.
        cout << "No se encontraron peliculas cercanas y/o con calificacion " << calificacion << "." << endl;
    }
}


//  OP #5 | METODO PARA CALIFICAR UN VIDEO POR NOMBRE   //
void calificarVideo(string video_calificar)
{
    bool encontrado = false; // Variable para saber si el video fue encontrado.

    for (Video* v : todosLosVideos)
    {
        if (v->get_titulo() == video_calificar)
        {
            // Busca el video por título.
            float calificacion;
            cout << "Ingresa la calificacion del 1-10:" << endl;
            cin >> calificacion; // Pide la calificación a aplicar.


            if (cin.fail())
            {
                // Verifica que el usuario haya ingresado un número.
                cin.clear(); // Limpia error de entrada.

                // Descarta toda la línea de entrada hasta encontrar un salto de línea (\n).
                // Evita que basura (entrada inválida) se quede en el buffer de entrada.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Error: Entrada invalida. Debe ser un numero." << endl;
                return;
            }

            if (calificacion < 1 || calificacion > 10)
            {
                // Valida que el usuario haya ingresado un número en el rango válido.
                cout << "Error: La calificacion debe estar entre 1 y 10." << endl;
                break;
            }

            v->set_calificacion(calificacion); // Asigna la nueva calificación.
            cout << "Se ha actualizado la calificacion." << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado)
    {
        // Si el video no fue encontrado en el catálogo.
        try
        {
            // Pregunta si quiere agregarlo
            cout << "No tenemos ese titulo en nuestro catalogo. Quieres agregarlo? (Si | No)" << endl;
            string decide_agregar;
            cin >> decide_agregar;

            if (decide_agregar != "Si" && decide_agregar != "si" &&
                decide_agregar != "No" && decide_agregar != "no")
            {
                // Valida la respuesta del usuario
                throw invalid_argument("Respuesta invalida. Escribe 'Si' o 'No'.");
            }

            if (decide_agregar == "No" || decide_agregar == "no")
            {
                // Termina la función si no quiere agregarlo.
                cout << "Regresando al menu..." << endl;
                return;
            }

            cout << "Es una Pelicula o una Serie? (p | s): " << endl; // Pregunta por el tipo de video.
            char tipo;
            cin >> tipo;
            if (tipo != 'p' && tipo != 's')
            {
                // Valida la respuesta del usuario.
                throw invalid_argument("Tipo invalido. Escribe 'p' para película o 's' para serie.");
            }

            // Inicializa atributos comúnes de la clase base.
            int id;
            string titulo, genero;
            float calificacion;

            cout << "Titulo: ";
            cin.ignore();
            getline(cin, titulo); // Usa getline para capturar un título con más de una palabra.
            if (cin.fail())
            {
                // Valida la respuesta del usuario.
                cin.clear();
                throw invalid_argument("Titulo invalido. Debe ser texto.");
            }

            cout << "ID: ";
            cin >> id; // Pide el ID.
            if (cin.fail())
            {
                // Valida la respuesta del usuario.
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("ID invalido. Debe ser un numero entero.");
            }

            for (Video* v : todosLosVideos)
            {
                // Valida que el ID no se repita.
                if (v->get_id() == id)
                {
                    cerr << "Error: Ya existe un video con ese ID." << endl;
                    return;
                }
            }


            cout << "Genero: "; // Pide el género.
            cin.ignore();
            getline(cin, genero);

            cout << "Calificacion inicial: "; // Pide la calificación.
            cin >> calificacion;

            if (cin.fail())
            {
                // Valida la respuesta del usuario.
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Calificacion invalida. Debe ser un numero.");
            }

            if (calificacion < 1 || calificacion > 10)
            {
                // Valida que el usuario haya ingresado un número en el rango válido.
                cerr << "Error: La calificacion debe estar entre 1 y 10." << endl;
                return;
            }

            // Verifica cuál es el tipo de video que se quiere agregar.
            if (tipo == 'p')
            {
                // Si es película.
                int duracion;
                cout << "Duracion: "; // Pide la duración.
                cin >> duracion;
                if (cin.fail())
                {
                    // Valida la respuesta del usuario.
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw invalid_argument("Duracion invalida. Debe ser un numero entero.");
                }
                cin.ignore();

                int anio;
                cout << "Anio: "; // Pide el año.
                cin >> anio;

                if (cin.fail())
                {
                    // Valida la respuesta del usuario.
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw invalid_argument("Anio invalido. Debe ser un numero entero.");
                }

                if (anio < 1900 || anio > 2026)
                {
                    cerr << "Error: Año inválido. Debe estar entre 1900 y 2026." << endl;
                    return;
                }

                // Agrega el apuntador al nuevo objeto en memoria dinámica al vector global.
                todosLosVideos.push_back(new Pelicula(anio, id, duracion, titulo, genero, calificacion));
            }
            else if (tipo == 's')
            {
                // Si es una serie.
                vector<Episodio> episodios;
                int temporadas, num_episodios;

                cout << "Numero de temporadas: "; // Pide las temporadas.
                cin >> temporadas;
                if (cin.fail())
                {
                    // Valida la respuesta del usuario.
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw invalid_argument("Numero de temporadas invalido. Debe ser un numero entero.");
                }

                cout << "Desea agregar episodios ahora? (Si | No): "; // Pregunta si se desean agregar episodios.
                string respuesta_epi;
                cin >> respuesta_epi;
                if (cin.fail())
                {
                    // Valida la respuesta del usuario.
                    cin.clear();
                    throw invalid_argument("Respuesta invalida. Debe ser texto.");
                }

                vector<Episodio> nuevos_episodios;
                num_episodios = 0;

                if (respuesta_epi == "Si" || respuesta_epi == "si")
                {
                    // Si se desean agregar episodios.
                    cout << "Cuantos episodios deseas agregar? "; // Pide el numero de episodios.
                    cin >> num_episodios;
                    if (cin.fail())
                    {
                        // Valida la respuesta del usuario.
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        throw invalid_argument("Numero de episodios invalido. Debe ser un numero entero.");
                    }
                    cin.ignore();

                    for (int i = 0; i < num_episodios; ++i)
                    {
                        string titulo_ep;
                        int temporada_ep;
                        float calificacion_ep;

                        cout << "Titulo: "; // Pide titulo del episodios.
                        getline(cin, titulo_ep);

                        cout << "Temporada: "; // Pide la temporada en la que está el episodio.
                        cin >> temporada_ep;

                        cout << "Calificacion: ";
                        cin >> calificacion_ep;
                        if (cin.fail())
                        {
                            // Valida la respuesta del usuario.
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            throw invalid_argument("Calificacion invalida. Debe ser un numero.");
                        }

                        if (calificacion_ep < 1 || calificacion_ep > 10)
                        {
                            // Valida que el usuario haya ingresado un número en el rango válido.
                            cerr << "Error: La calificacion debe estar entre 1 y 10." << endl;
                            return;
                        }


                        cin.ignore();

                        // Usa memoria automática y crea un objeto dentro del vector
                        nuevos_episodios.emplace_back(titulo_ep, temporada_ep, calificacion_ep);
                    }
                }

                // Agrega el apuntador al nuevo objeto en memoria dinámica al vector global
                todosLosVideos.push_back(new Serie(temporadas, id, titulo, genero, calificacion, num_episodios,
                                                   nuevos_episodios));
            }

            cout << "Se ha agregado el video al catalogo." << endl;

            // Captura de excepciones si usuario proporciona datos inválidos
        }
        catch (invalid_argument& e)
        {
            // Si se escribió mal algo o se ingresó un tipo de dato no válido
            cerr << "Error: " << e.what() << endl;
        } catch (...)
        {
            cerr << "Error desconocido." << endl;
        }
    }
}

//  OP #0 | METODO PARA LIBERAR MEMORIA.   //

void liberarMemoria()
{
    for (Video* v : todosLosVideos)
    {
        delete v;
    }
    todosLosVideos.clear(); // limpia el vector
}
