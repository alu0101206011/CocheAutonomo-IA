# IA-P1

## Empezar a utilizar el programa

### Requerimientos

- Necesitas estar en un entorno linux
- Necesitas tener instalado make
- Necesitas tener instalado g++

### ¿Cómo ejecutar programa IA-P1?

Para ejecutar el programa desde cero primero necesitamos descargar el repositorio..
El programa contiene un makefile para mayor comodidad. Con el comando `make run` se borraran todos los ".o" de la carpeta obj
y el ejecutable de la carpeta bin, se generarán unos ".o" nuevos, se creará un nuevo ejecutable y se ejecutará, por lo que no 
tendrían que hacer nada más.
Si prefieren solo compilar, se puede hacer con un simple `make`. 

     ```bash
     cd ~
     git clone https://github.com/JorNiebla/IA-P1.git
     cd IA-P1
     make run
     ```

#### Precaución

El programa está pensado para que se ejecute desde la carpeta del proyecto, bien con `bin/Board_Test` o con `make run`

Para empezar necesitamos tener las carpetas siguientes:
* bin
* boards
* include
* obj
* src
