# BlackJack GSC

## Visión General de la Arquitectura
Este proyecto es un Blackjack simple desarrollado en C++ que utiliza la biblioteca Allegro para la implementación de la interfaz gráfica de usuario (GUI). El proyecto busca ser creativo a la vez que organizado, con un énfasis en lograr una compilación y ejecución simple de la aplicación.

### Proceso de Construcción
1. **Compilación**: Todos los archivos `.cpp` ubicados en el directorio `src/` se compilan en archivos objeto (`.o`) y se colocan en el directorio `build/`.
2. **Vinculación**: Los archivos objeto en `build/` se vinculan para generar el ejecutable final, `app.exe`, que se coloca en el directorio `bin/`.

## Script de Construcción (`build.bat`)
El script `build.bat` automatiza los siguientes pasos:
1. **Creación del directorio `build/`**: Si no existe, el script crea el directorio `build/` para almacenar los archivos objeto compilados.
2. **Compilación**: El script compila todos los archivos fuente C++ (`.cpp`) desde el directorio `src/` en archivos objeto.
3. **Vinculación**: Una vez que todos los archivos objeto han sido compilados, se vinculan para generar el ejecutable (`app.exe`) en el directorio `bin/`.
4. **Ejecución**: Si la compilación es exitosa, el script lanza la aplicación ejecutando `app.exe`.

## Bibliotecas Utilizadas
- **Allegro 5**: Una biblioteca usada para el desarrollo de juegos y la creación de interfaces gráficas.

## Requisitos
Para compilar y ejecutar este proyecto, asegúrate de tener un compilador reciente, de otra manera, puede que la aplicación no sea compatible.

## Cómo Construir y Ejecutar
1. Clona o descarga el proyecto.
2. Abre una terminal o símbolo del sistema en el directorio del proyecto.
3. Ejecuta el script `./run.bat`:
   ```bash
   $ ./run.bat