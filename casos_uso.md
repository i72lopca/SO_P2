# Uso Credenciales

**ID:** *1*

**Breve descripción:**
El sistema debe identificar entre ayudante o coordinador a través de las credeenciales del usuario.

**Actores principales:** Usuario: Profesor Coordinador o Ayudante.

**Actores Secundarios:** Alumnos.

**Precondiciones:**
 
1.- Las credenciales y deben coincidir con las que tendremos en un fichero binario. 

2.- Tendremos 5 oportunidades para introducir las credenciales de forma correcta, si fallamos saldrá del sistema.

**Flujo principal:**

1. El caso de uso comienza cuando el usuario ejecuta el porgrama.
2. Tendremos la opcion de salir del programa o introducir credenciales.

2.1. El usuario introduce sus credenciales.

2.1.1. Dependiendo de dichas credenciales, asignaremos un Rol: Ayudante o Coordinador.

**Postcondiciones:**

* Se mostrará un menú diferente dependiendo de las credenciales introducidas. 

**Flujos alternativos:**

2.1.a. Si las credenciales no coinciden con las del archivo binario se muestra un mensaje de error.

# Cargar Backup

**ID:** *02*

**Breve descripción:**
En cualquier momento se podrá cargar un fichero el cual contiene los ditintos datos de los alumnos.

**Actores principales:** Usuario: Profesor Coordinador.

**Actores Secundarios:** Alumnos.

**Precondiciones:**

1. Para poder cargar un backup el usuario tiene que tener un backup con el formato correcto, en un fichero binario.
2. El fichero debe existir en la ruta especificada.
3. El actor principal debe ser el coordinador.

**Flujo principal:**

1. El caso de uso comienza cuando el usuario selecciona la opción de "Cargar backup".
2. El programa pide opcionalmente la ruta del backup, sino introduce nada será por defecto la misma carpeta del software. 
3. Se cargan los datos del fichero en memoria.

**Postcondiciones:**

* Se muestra un mensaje informando que el proceso se ha realizado con éxito.


**Flujos alternativos:**

2.a En caso de no encontrar el fichero especificado saltará un error, y después se pedirá de nuevo el nombre de la ruta del backup.

3.a Si el fichero está corrupto se lanza un mensaje de error.

# Introducir datos

**ID:** *03*

**Breve descripción:** En cualquier momento el usuario puede introducir nuevos alumnos.

**Actores principales:** Usuario: Profesor Coordinador o Ayudante.

**Actores Secundarios:** Alumnos.

**Precondiciones:**

1. Cuando se introduce un alumno se deben introducir obligatoriamente el DNI, Nombre, apellidos, Teléfono, E-mail corporativo, dirección, curso mas alto de matriculación, y, de forma opcional, el grupo y el líder, pudiendo dejar estos 2 últimos campos en blanco.
2. Los datos se introducen únicamente de forma manual por teclado.

**Flujo principal:**

1. El caso de uso comienza cuando el usuario escoge del menú principal la opción de "introducir datos".

2. Se pregunta cuántos alumnos de desea introducir.

3. El programa pide el DNI, nombre,...,del alumno campo por campo.

4. Si se ha llegado al número de alumnos que se desea introducir se sale al menú, sino se introduce otro alumno.

**Postcondiciones:**

* Al finalizar se muestra un mensaje con el número de alumnos en el sistema.

* Los alumnos quedan guardados en memoria principal hasta que se hace el backup.

**Flujos alternativos:**

2.a Si se desea introducir mas de 150 alumnos en total o ningún alumno se muestra un error, y se pide de nuevo el número de alumnos que se desea introducir.

3.a  Si se deja en blanco algún campo obligatorio se muestra un error y se pide de nuevo el dato.

3.b  Si un alumno ya tiene asignado un grupo, nos mostrará si deseamos sustituirlo.

# Borrar_Alumno

**ID:** *04*

**Breve descripción:** El usuario podrá borrar únicamente un solo alumno a la vez.

**Actores principales:** Usuario: Profesor Coordinador o Ayudante.

**Actores Secundarios:** Alumnos.

**Precondiciones:**

 1. El alumno a borrar ya tiene que estar añadido al sistema.

**Flujo principal:**

 1. El caso de uso empieza cuando se accede en el menú a la opción: *Borrar_Alumno*.
 2. Después nos pedirá la opción de borrar por DNI o apellido al alumno.
 3. Debemos de introducir dicho DNI o Apellido por terminal.

**Postcondiciones:**

 * Si existen dos alumnos con el mismo apellido, solo se podrá borrar por DNI.
 * Una vez borremos un alumno, se mostrará por terminal: *Alumno borrado correctamente*.

**Flujos alternativos:**

 3.a. Si no existe el alumno o se ha introducido el DNI / Apellido de manera incorrecta el sistema dará error de borrado.

# Mostrar_Alumno

**ID:** *05*

**Breve descripción:** El usuario podrá mostrar uno o varios alumnos.

**Actores principales:** Usuario: Profesor Coordinador o Ayudante.

**Actores Secundarios:** Alumnos.

**Precondiciones:**

 1. El alumno/os a mostrar ya tiene/n que estar añadidos al sistema.


**Flujo principal:**

 1. El caso de uso empieza cuando se accede en el menú a la opción: *Mostrar_Alumno*.
 2. Nos dará la opción de mostrar todos los alumnos o solo algunos.
 3. Se muestran los datos del/los alumno/s.

**Postcondiciones:**

 * Se mostrarán los datos de alumnos por el terminal (por defecto).
 * Se podrá seleccionar adicionalmente mostrar mediante fichero (markdown).
 * Si los mostramos por curso más alto, nos dará la opción de: Ascendete o descendente.
 * El líder de grupo saldrá diferenciado respecto a los demás.

**Flujos alternativos:**

2.a Si no existe el alumno o se ha introducido el DNI / Apellido de manera incorrecta el sistema mostrará un mensaje de error.

2.b Si se selecciona mostrar todos los alumnos existirán cuatro opciones:
- Ordenar por dni (Ascendente o descendente).
- Ordenar por apellidos.
- Ordenar por curso más alto (Ascendente o descendente).
- Ordenar por nombre.

2.c Si se selecciona no mostrar todos los alumnos existirán tres opciones:
- Mostrar por dni.
- Mostrar por apellidos.
- Mostrar por grupo.

3.a Si el grupo, apellido o dni no existen se muestra mensaje de error y se retorna al menú principal.

# Modificar_Alumno

**ID:** *06*

**Breve descripción:**
El sistema permite la modificación de los datos del alumno.

**Actores principales:** Usuario: Profesor Coordinador o Ayudante.

**Actores Secundarios:** Alumnos.

**Precondiciones:**

1. Debe existir al menos un alumno cargado en el sistema para poder modificarlo.

2. Es necesario hacer una búqueda previa del alumno a modificar.

3. El Grupo a modificar deve de existir previamente.

**Flujo principal:**

1. El caso de uso comienza cuando el usuario introduce la opción indicada en el menú que le permite modificar los datos del alumno.
2. Para modificar el alumno lo buscamos por su DNI / Apellidos o grupo al modificar varios alumnos y sus datos.
3. El sistema debe permitir con una opción de (Si / No) en cada campo modificar o no los datos del alumno.

**Postcondiciones:**

* El sistema muestra los datos del alumno por pantalla una vez modificado.
* Los datos modificados del alumno quedan guardados en memoria principal.


**Flujos alternativos:**

1.a. En caso de no existir un alumno cargado, el sistema debe mandar un mensaje de error.
2.a. Si el DNI no concuerda con ningún usuario salta un mensaje de error y vuelve al Menú Principal.
2.b. Si el Apellido no concuerda con ningun usuario salta un mensaje de error y vuelve al Menú Principal.
3.c. Si el Grupo no existe salta un mensaje de error y vuelve al Menú Principal.

# Hacer_BackUp

**ID:** *07*

**Breve descripción:**
El sistema realiza un Back_Up

**Actores principales:** Usuario: Profesor Coordinador.

**Actores Secundarios:** Alumnos.

**Precondiciones:**

1. Debe existir un fichero de tipo binario que pueda ser utilizado por el programa.

2. En el menú existe un a opción que permite al usuario seleccionar Hacer_BackUp.

3. La opción introducida debe estar en el rango del menú.

**Flujo principal:**

1. El caso de uso comienza cuando el usuario selecciona la opción de *Hacer_BackUp* desde el menú principal.

2. Aparece por pantalla un mensaje para introducir la ruta que el usuario quiera darle al fichero.

3. El sistema busca el fichero binario en la ruta especificada y guarda todos los datos del sistema.

4. El sistema manda un mensaje una vez se han copiado todos los datos en el fichero, mostrando éxito o error.

**Postcondiciones:**

* El sistema muestra mensaje de error o éxito al terminar el BackUp.

**Flujos alternativos:**

1.a Si el usuario introduce un número que no esté dentro del rango del menú debe aparecer un mensaje de error y se debe volver a introducir una opción.


3.a En caso de existir el fichero se sobreeescribe con el nuevo nombre, y si no existe en la ruta especificada, se crea un fichero binario con el nombre introducido.

# Búsqueda_Datos

**ID:** *08*

**Breve descripción:**
El sistema busca los datos de un alumno o un grupo.

**Actores principales:** Usuario: Profesor Coordinador o Ayudante.

**Actores Secundarios:** Alumnos.

**Precondiciones:**

1. Debe haber cargado un alumno como mínimo para usar esta función.

2. Para acceder a esta opción es necesario acceder previamente a mostrar/modificar/borrar un alumno.

3. Si se va a buscar un grupo debe de existir.

**Flujo principal:**

1. El caso de uso comienza cuando el usuario muestra/modifica/borra los datos de un alumno.

2. Dependiendo de los parámetros introducidos por el usuario se buscara internamente en nuestro sistema.

3. Se devuelve un vector de indices con las posiciones correspondientes a los elementos especificados con antelación.

**Postcondiciones:**

* Se devuelve el vector con los índices almacenados.

**Flujos alternativos:**

1.a Si no hay ningún dato se devuelve NULL.

2.a En caso de no existir el dni/apellido o grupo introducido para buscar, se devuelve NULL.

# Administración de líderes

**ID:** *09*

**Breve descripción:** El sistema se encarga de organizar y administrar los líderes de cada grupo.

**Actores principales:** Usuario: Profesor Coordinador o Ayudante.

**Actores Secundarios:** Alumnos.

**Precondiciones:**

1.- Es necesario introducir un alumno previamente.

**Flujo principal:**

1.- El caso de uso comienza cuando el usuario introduce o modifica un alumno el cual ha sido marcado como líder.

2.- El sistema comprueba dentro del grupo del alumno modificado/introducido si alguno de los integrantes es ya un líder o no.

3.- Si no existe un líder en el grupo del alumno modificado/introducido, se asignará dicho cargo a dicho alumno.

**Postcondiciones:**

* Si se introduce el alumno como líder, quedará modificado en los datos del sistema hasta que se realice el BackUp.

**Flujos alternativos:**

3.a En el caso de existir un líder, se mostrará un mensaje por pantalla indicando que no es posible asignar dicho cargo y se mostrará el actual líder del grupo, y en caso de que el usuario quiera asignar un nuevo líder, deberá modificarlo manualmente.

# Cargar_Almacenamiento

**ID:** *10*

**Breve descripción:** Los datos del sistema almacenados se podrán cargar en el sistema.

**Actores principales:** Usuario: Profesor Coordinador o Ayudante.

**Actores Secundarios:** Alumnos.

**Precondiciones:**

1.- En el almacenamiento debe existir un fichero binario de alumno/s

**Flujo principal:**

1. El caso de uso comienza cuando el usuario introduce correctamente sus credenciales.

2. Se cargarán los datos desde un fichero binario en el sistema.

**Postcondiciones:**

* Los datos de los alumnos quedan en el sistema para poder ser manipulados.

**Flujos alternativos:**

1.a En caso de que no exista un fichero se mostrara un error y el sistema continuará sin alumnos en la base de datos.

# Guardar_Almacenamiento

**ID:** *11*

**Breve descripción:** Los datos del sistema se almacenarán de forma automática en un fichero binario.

**Actores principales:** Coordinador o Ayudante.

**Actores Secundarios:** Alumnos.

**Precondiciones:**

1.- El fichero debe tener formato binario.

**Flujo principal:**

1. El caso de uso comienza cuando el usuario elige la opción de salir.

2. Se guardarán los datos en un fichero binario.

**Postcondiciones:**

* Los datos quedan almacenados en un fichero binario.

**Flujos alternativos:**

1.a Si el guardado falla se mostrará un error.