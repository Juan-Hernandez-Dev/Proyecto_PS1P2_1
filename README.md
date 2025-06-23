# Blackjack Console Game

Un juego de Blackjack en la consola implementado en C++ con soporte para colores y una interfaz de usuario intuitiva.

## 🎮 Características

- Juego de Blackjack completo con reglas estándar
- Interfaz de consola con colores
- Soporte para múltiples partidas
- Baraja de cartas con mezclado
- Sistema de puntuación automático
- Compatible con Windows

## 🛠️ Requisitos

- Compilador de C++ (como g++ o MinGW en Windows)
- Terminal que soporte códigos de colores ANSI (como Windows Terminal, CMD con activación de códigos ANSI, o cualquier terminal moderna)

## 🚀 Cómo ejecutar

1. Clona el repositorio o descarga los archivos
2. Abre una terminal en el directorio del proyecto
3. Ejecuta el script de compilación:
   ```
   .\run.bat
   ```
4. El ejecutable se generará en la carpeta `build/`
5. Si deseas ejecutar la ultima instancia del juego hazlo con:
   ```
   .\build\blackjack.exe
   ```

## 🎲 Cómo jugar

1. El juego comienza repartiendo dos cartas al jugador y dos al crupier (con una carta oculta)
2. En tu turno, puedes:
   - **h**: Pedir otra carta (Hit)
   - **s**: Plantarte (Stand)
   - **e**: Salir del juego
3. El objetivo es sumar 21 puntos o acercarse lo más posible sin pasarse
4. Las cartas numéricas valen su valor, las figuras (J, Q, K) valen 10 y el As (A) puede valer 1 u 11
5. Después de tu turno, el crupier jugará automáticamente

## 📂 Estructura del proyecto

```
Proyecto_PS1P2_1/
├── build/               # Carpeta para los archivos compilados
├── include/             # Archivos de encabezado
│   ├── utils.h          # Utilidades y constantes
│   └── utils.cpp        # Implementación de utilidades
├── main.cpp             # Código principal del juego
└── run.bat              # Script de compilación para Windows
```

## 🎨 Personalización

### Colores disponibles

El juego utiliza códigos de color ANSI para una mejor experiencia visual:

- **Naranja**: Títulos y encabezados
- **Azul**: Mensajes informativos y acciones
- **Verde**: Éxito (victorias)
- **Rojo**: Errores (derrotas)
- **Amarillo**: Advertencias

### Funciones de utilidad

El archivo `utils.h` contiene varias funciones útiles:

- `clearScreen()`: Limpia la pantalla de la consola
- `printTitle(texto)`: Muestra un título formateado
- `printSubTitle(texto)`: Muestra un subtítulo en naranja
- `printSuccess(texto)`: Muestra un mensaje de éxito en verde
- `printError(texto)`: Muestra un mensaje de error en rojo
- `printWarning(texto)`: Muestra una advertencia en amarillo
- `askForInput(prompt)`: Solicita entrada al usuario con un mensaje

---

Disfruta del juego de Blackjack! 🃏