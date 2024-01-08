# Sistema-de-Prestamos-a-clientes-amortizadores
Se trata de implementar un sistema de préstamos a clientes quienes amortizan sus prestamos y pagan sus intereses en cierta cantidad de cuotas que en su totalidad cubren el préstamo solicitado.
El sistema realiza los siguientes procesos:
l. Mantenimiento de información en archivos con organización secuencial
2. Mantenimiento de información en archivos con organización secuencial indexada
3. Listados por pantalla que muestran la información de un archivo binario
4. Listados por pantalla que muestran la información de archivos binarios combinados
y/o relacionados que conforman una base de datos.
5. Operaciones de cálculo que involucra el acceso a datos de diferentes archivos
binarios que conforman una base de datos.
6. Control de campos de identificación o claves de archivos binarios
La aplicación de la programación orientada a objetos en éste proyecto ilustra lo
siguiente:
1. El encapsulamiento de clases
2. La preparación de clases para su extensión (herencia y polimorfismo)
3. El instanciamiento de objetos dentro de una clase, con el fin de acdeder a sus
servicios y/o datos.
4. La elaboración de mensajes de comunicación entre clases
5. La utilización de clases abstractas/plantillas aplicándolas a necesidades específicas.
6. Elaboración de clases de aplicación desde la cual se ponen en marcha objetos de
otras clases.
7. Integración e implementación de clases como proyecto final.
#DESCRIPCION DEL SISTEMA
Una empresa financiera ha implementado una modalidad de préstamos a sus clientes
bajo las siguientes condiciones:
l. El cliente debe tener una antiguedad no menor de 1 año
2. El último saldo del cliente debe registrar un monto rrúnimo de S/. l 00.00 al momento
de la solicitud del préstamo.
3. Un cliente se hace acreedor a un préstamo siempre que no tenga otro préstamo
pendiente de pago.
4. El monto del préstamo es automáticamente I O veces el monto que registra su
último saldo.
5. La tasa de interés mensual es del 1. 5% y el plazo mínimo de devolución del monto
del préstamo con sus respectivos intereses es de 12 meses y el plazo máximo es
de 36 meses.
6. En los cobros mensuales que se realizan, el sistema debe diferenciarlos entre
cobro por intereses y por amortización. El monto por amortización es la diferencia
entre el monto que se cobra y el monto correspondiente por intereses.
7. Se dá por cancelado un préstamo cuando el número de cuotas es igual al número
de pagos.
8. Se asume que los pagos se realizan en fechas que corresponden, dentro de los
límites fijados por ley.
OBJETIVO DEL SISTEMA
Otorgar préstamos a los clients hábiles, realizando un seguimiento, a nivel de
consultas, de todos los préstamos otorgados, así como de sus respectivos pagos
realizados, desde su otorgamiento hasta su cancelación.
#OPCIONES DEL MENU PRINCIPAL
1.-CLIENTES
Al elegir ésta opción usted presentará una pantalla para el mantenimiento de la
información de los clientes, como la que se muestra a continuación:
##Ingresa
Se registran los clientes de la financiera evitando la duplicidad de libretas electorales,
ya que se supone que una misma libreta electoral no puede pertenecer a dos
personas distintas.
El campo Nro.Préstamos es un contador del número de préstamos que recibe un
cliente, por lo que éste debe ser inicializado en O. Este campo no se ingresa,
solamente es informativo cuando se hace alguna consulta.
El campo Préstamo Actual debe inicializarse como falso ( O )debido a que éste
campo indica si el cliente tiene o nó algun prestamo vigente. Este campo tampoco
se ingresa, solamente es informativo cuando se hace alguna consulta.
El campo Estado debe inicializarce como activo, es decir con l.
##Modifica
Se permite modificar todos los datos ingresados de los clientes, excepto la libreta
electoral. En caso se desee modificar la libreta electoral, lo que se debe hacer es
anular al cliente y luego ingresarlo como nuevo.
##Anula
Se permite la anulación de un cliente, siempre que esté activo y que no tenga préstamos pendientes de pago, solicitando su número de libreta electoral, se muestra
todos sus datos y se pide conformidad para proceder a anularlo. La anulación es
lógica y consiste en asignar el valor O al campo estado del registro.
##Consulta
A través del número de libreta electoral se muestra la información de un cliente.
##Listado
Se muestra la información de los clientes registrados, en forma secuencial, en el
mismo orden en que fueron ingresados. La información a presentar debe ser: Libreta
Electoral, Apellidos y Nombres, Dirección, Fecha de Ingreso y Ultimo Saldo.
En la parte inferior presentar las teclas de control para el desplazamiento del listado,
tales como [PgDn] Siguiente, [PgUp] Anterior, [Home] Inicio, [End] Final, [Ese]
Salir.
2. PRESTAMOS
3. PAGOS
4. CONSULTAS
