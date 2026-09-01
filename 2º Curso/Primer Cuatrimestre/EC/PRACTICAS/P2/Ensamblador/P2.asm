.model small

.code

org 100h

Programa_Int:

jmp Reside

;Declaración de variables

contador_int db 0

reloj db '00:00'

segun db 0

min db 0

Rutina_Servicio proc

cli

;Salvar el contenido de los registros utilizados.

push ax

push bx

push cx

push dx

;Comprobar si se ha llegado al segundo

inc contador_int

cmp contador_int, 18

jb salir

;Si se ha llegado al segundo.

mov contador_int, 0



;Inicialización de la memoria de video

mov ax, 0B800h

mov es, ax

;Fondo negro con letras blancas

mov ah, 00001111b

 ;Mostar el reloj

mov si, 0

mov di, 308

for:

mov al, reloj[si]

mov es:[di], ax

add di, 2

inc si

cmp si, 4

jbe for

;Ver si se ha llegado a 60 segundos

inc segun

cmp segun, 60

jnz minutos

mov segun, 0

inc min

;Ver si se ha llegado a 60 minutos

minutos:

cmp min, 60

jnz actualizar_reloj

mov min, 0

actualizar_reloj:



mov al, min

mov ah, 0

mov bl, 10

div bl

;or ax, 3030h

add al, '0'

add ah, '0'

mov reloj[0], al

mov reloj[1], ah

mov al, segun

mov ah, 0

mov bl, 10

div bl

;or ax, 3030h

add al, '0'

add ah, '0'

mov reloj[3], al

mov reloj[4], ah

salir:

;Recupera el valor de los registros implicados en la rutina

pop dx

pop cx

pop bx

pop ax

sti

iret

endp



Reside: ;Etiqueta para determinar la dirección siguiente a

;la última de la rutina que debe quedar residente.

mov dx, offset Rutina_Servicio

mov ax, 0

mov es, ax

mov si, 1Ch*4

cli

mov es:[si], dx

mov es:[si+2], cs

sti

mov dx, offset Reside

int 27h

end Programa_Int

(Sin asunto)
?
Juan Carlos Ortega Lepe
?
Saul Jose Carbajosa Sandez?

