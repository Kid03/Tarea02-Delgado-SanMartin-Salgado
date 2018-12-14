# Tarea02-Delgado-SanMartin-Salgado

<p>Implementación de un servidor web iterativo para el curso de Redes de Computadores.</p>

<h2>Integrantes:</h2>
  <p>Héctor Delgado --> hector.delgado@alumnos.uv.cl </p>
  <p>Ariel Salgado --> ariel.salgado@alumnos.uv.cl </p>
  <p>Benjamín San Marín --> benjamin.sanmartin@alumnos.uv.cl </p>
<h2>Descripción de funcionamiento:</h2>
  <p></p>
  <h3>Método de compilación:</h3>
    <p>estando el terminal abierto, se ubica en la carpeta tarea2, 1° se hace un make clean, y luego un make</p>
    <p>creando así el ejecutable echoServer, luego se ejecuta con el compando "./echoServer <Server Port> ",donde </p>
    <p><Server Port> es el numero del servidor, si no se pone nada, por defecto es 8080</p>
  <h3>Ejemplos de uso:</h3>
    <p>[usuario1@localhost ~]$ cd tarea2</p>
    <p>[usuario1@localhost tarea2]$ make clean</p>
    <p>[usuario1@localhost tarea2]$ make</p>
    <p>[usuario1@localhost tarea2]$ ./echoServer</p>
    <p>Luego se abre el navegador y se ingresa lo siguiente</p>
    <p>127.0.0.1:8080</p>
    <p>para empezar a pedir los GET, solo se modifica lo sig.</p>
    <p>127.0.0.1:8080/MODIFICA.html</p>
    <p>Ejemplo: </p>
    <p>     127.0.0.1:8080/holamundo.html</p>
