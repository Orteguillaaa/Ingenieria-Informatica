.MODEL SMALL
.STACK 100h

.DATA
CADENA    DB 5,0,0,0,0,0,0        ; buffer para INT 21h AH=0Ah
PESO      DB 8,4,2,1
DEC_NAT   DB ?
DEC_COMP  DB ?
SIGNO     DB ?
MSG1      DB 13,10,'Introduce un numero binario de 4 bits: $'
MSG2      DB 13,10,'Binario natural (decimal): $'
MSG3      DB 13,10,'Complemento a 1 (decimal): $'
ALATTR    DB 0Fh                  ; atributo: blanco sobre negro
TempChar  DB ?

.CODE
MAIN PROC
    ; Inicializar segmentos
    MOV AX, @DATA
    MOV DS, AX

    ; Inicializar ES al segmento de vídeo B800h
    MOV AX, 0B800h
    MOV ES, AX

    ; ----------------------------
    ; Mostrar MSG1 en memoria de vídeo (fila 0, col 0)
    ; ----------------------------
    LEA SI, MSG1
    MOV DI, 0                ; fila 0, col 0 -> offset bytes = 0
    MOV BL, [ALATTR]
    CALL PrintDollarStringToVideo

    ; ---------------------------------------------------------
    ; MOVER EL CURSOR DE BIOS A LA LÍNEA SIGUIENTE (fila 1, col 0)
    ; De esta forma la entrada por teclado aparecerá en la línea
    ; siguiente y no sobrescribirá el prompt impreso en vídeo.
    ; INT 10h AH=02h -> set cursor position
    ; BH = page (0), DH = row, DL = col
    ; ---------------------------------------------------------
    MOV AH, 02h
    MOV BH, 0
    MOV DH, 1                ; fila 1
    MOV DL, 0                ; columna 0
    INT 10h

    ; Leer la cadena por teclado con INT 21h AH=0Ah (igual que antes)
    LEA DX, CADENA
    MOV AH, 0Ah
    INT 21h

    ; Convertir ASCII '0'/'1' a 0/1 (igual que tu código original)
    SUB CADENA[2], 48
    SUB CADENA[3], 48
    SUB CADENA[4], 48
    SUB CADENA[5], 48

    ; Determinar SIGNO (MSB = CADENA[2])
    MOV AL, CADENA[2]
    CMP AL, 1
    JE ES_NEGATIVO
    MOV SIGNO, 0
    JMP SEGUIR
ES_NEGATIVO:
    MOV SIGNO, 1
SEGUIR:
    ; ----------------------------
    ; Cálculo DEC_NAT (igual al original)
    ; ----------------------------
    MOV AL, CADENA[2]
    MUL PESO[0]
    MOV DEC_NAT, AL

    MOV AL, CADENA[3]
    MUL PESO[1]
    ADD DEC_NAT, AL

    MOV AL, CADENA[4]
    MUL PESO[2]
    ADD DEC_NAT, AL

    MOV AL, CADENA[5]
    MUL PESO[3]
    ADD DEC_NAT, AL

    ; ----------------------------
    ; Mostrar MSG2 en vídeo (fila 2, col 0)
    ; ----------------------------
    LEA SI, MSG2
    MOV DI, 320              ; fila 2 -> (2*80)*2 = 320 bytes
    MOV BL, [ALATTR]
    CALL PrintDollarStringToVideo

    ; Imprimir DEC_NAT (0..15) en la celda siguiente
    MOV AH, 0
    MOV BL, 10
    MOV AL, DEC_NAT
    DIV BL                   ; AL = decena, AH = unidad

    CMP AL, 0
    JE NAT_UNO_ONLY

    PUSH AX
    ADD AL, 48
    MOV TempChar, AL
    MOV AL, TempChar
    MOV BL, [ALATTR]
    CALL PrintCharToVideo
    POP AX

NAT_UNO_ONLY:
    ADD AH, 48
    MOV AL, AH
    MOV BL, [ALATTR]
    CALL PrintCharToVideo

    ; ----------------------------
    ; Preparar Complemento a 1: si SIGNO=1 invertir bits de CADENA[2..5]
    ; ----------------------------
    CMP SIGNO, 1
    JNE NO_COMP_2
    MOV BL, CADENA[2]
    NOT BL
    AND BL, 1
    MOV CADENA[2], BL
NO_COMP_2:
    CMP SIGNO, 1
    JNE NO_COMP_3
    MOV BL, CADENA[3]
    NOT BL
    AND BL, 1
    MOV CADENA[3], BL
NO_COMP_3:
    CMP SIGNO, 1
    JNE NO_COMP_4
    MOV BL, CADENA[4]
    NOT BL
    AND BL, 1
    MOV CADENA[4], BL
NO_COMP_4:
    CMP SIGNO, 1
    JNE NO_COMP_5
    MOV BL, CADENA[5]
    NOT BL
    AND BL, 1
    MOV CADENA[5], BL
NO_COMP_5:

    ; ----------------------------
    ; Cálculo DEC_COMP (igual al original)
    ; ----------------------------
    MOV AL, CADENA[2]
    MUL PESO[0]
    MOV DEC_COMP, AL

    MOV AL, CADENA[3]
    MUL PESO[1]
    ADD DEC_COMP, AL

    MOV AL, CADENA[4]
    MUL PESO[2]
    ADD DEC_COMP, AL

    MOV AL, CADENA[5]
    MUL PESO[3]
    ADD DEC_COMP, AL

    ; ----------------------------
    ; Mostrar MSG3 en vídeo (fila 4, col 0)
    ; ----------------------------
    LEA SI, MSG3
    MOV DI, 640              ; fila 4 -> (4*80)*2 = 640 bytes
    MOV BL, [ALATTR]
    CALL PrintDollarStringToVideo

    ; Si SIGNO=1 imprimir '-'
    CMP SIGNO, 1
    JNE NO_SIGNO
    MOV AL, '-'
    MOV BL, [ALATTR]
    CALL PrintCharToVideo
NO_SIGNO:

    ; Imprimir DEC_COMP en vídeo
    MOV AH, 0
    MOV BL, 10
    MOV AL, DEC_COMP
    DIV BL

    CMP AL, 0
    JE COMP_UNO_ONLY

    PUSH AX
    ADD AL, 48
    MOV TempChar, AL
    MOV AL, TempChar
    MOV BL, [ALATTR]
    CALL PrintCharToVideo
    POP AX

COMP_UNO_ONLY:
    ADD AH, 48
    MOV AL, AH
    MOV BL, [ALATTR]
    CALL PrintCharToVideo

    ; Pausa: esperar tecla (igual que original; AH=00h INT 16h)
    MOV AH, 00h
    INT 16h

    ; Terminar programa
    MOV AH, 4Ch
    INT 21h

MAIN ENDP

; --------------------------------------------
; Rutina: PrintDollarStringToVideo
;   DS:SI -> cadena terminada en '$'
;   ES:DI -> posición inicial en memoria de vídeo (bytes)
;   BL     -> atributo
;   Deja DI apuntando a la siguiente celda libre
; --------------------------------------------
PrintDollarStringToVideo PROC
    PUSH AX
    PUSH BX
    PUSH CX
.loop_write:
    LODSB
    CMP AL, '$'
    JE .done_write
    MOV AH, BL
    MOV ES:[DI], AX
    ADD DI, 2
    JMP .loop_write
.done_write:
    POP CX
    POP BX
    POP AX
    RET
PrintDollarStringToVideo ENDP

; --------------------------------------------
; Rutina: PrintCharToVideo
;   AL = ASCII a imprimir
;   BL = atributo
;   ES:DI = posición donde escribir
;   Incrementa DI en 2
; --------------------------------------------
PrintCharToVideo PROC
    PUSH AX
    MOV AH, BL
    MOV ES:[DI], AX
    ADD DI, 2
    POP AX
    RET
PrintCharToVideo ENDP

END MAIN




