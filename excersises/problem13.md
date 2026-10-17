# Excersies 13

<p> Se quiere construir un sistema de comunicación serie síncrona entre dos dispositivos, usando dos líneas:
R y D. Los datos se reciben bit a bit por la línea D, con un nuevo bit por cada flanco de bajada del reloj R, y
comenzando por el más significativo. Si no se reciben datos, la línea de reloj permanece a 1. Por ejemplo, el dato
11000100 (en binario):</p>

![imagen](../img/pb13.png)

<p>Esta información es mandada por el dispositivo origen, mientras que el dispositivo destino se encarga de
controlar los valores del reloj e ir leyendo de la línea de datos cuando sea oportuno. El receptor, dispone de un
controlador de E/S que recoge el valor de estas dos señales de manera constante y lo guarda en un registro de
datos (al guardar un nuevo valor, sustituye el valor anterior del registro anteriormente mencionado), al que se
puede acceder mediante una lectura a la dirección 0x1000. En este registro de 8 bits, el bit 0 se encuentra
conectado a la señal de reloj (R) y el bit 1 a la señal de datos (D).
Además, tiene un registro de control (accesible en la dirección 0x1001) mediante el que se controla la
activación del dispositivo: El bit 0 habilita el dispositivo si está a uno, y el bit 1, habilita la generación de
interrupciones). Si el dispositivo genera interrupciones, producirá una interrupción al procesador cuyo vector
de interrupción es el 27)</p>

### Apartado A

<p>Diseñe un programa que inicialice el periférico para la adquisición de datos por E/S por polling. El
programa ha de recoger 1024 bytes y después, desactivar el dispositivo. Recuerde que, por cada byte,
tendrá que hacer 8 lecturas de la señal D (una por bit), esperando los flancos de bajada de la señal R. 

Además, tendrá que concatenar estos bits mediante desplazamientos para obtener un byte. Cada vez
que forme un byte, deberá almacenarlo en un vector de 1024 posiciones (unsigned char v[1024];).
</p>

```c


