.MODEL SMALL
.STACK 100h

.DATA
CADENA    DB 5,0,0,0,0,0,0
PESO      DB 8,4,2,1
DEC_NAT   DB ?
DEC_COMP  DB ?
SIGNO     DB ?
MSG1      DB 13,10,'Introduce un numero binario de 4 bits: $'
MSG2      DB 13,10,'Binario natural (decimal): $'
MSG3      DB 13,10,'Complemento a 1 (decimal): $'
ALATTR    DB 0Fh
TempChar  DB ?

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

    MOV AX, 0B800h
    MOV ES, AX

    LEA SI, MSG1
    MOV DI, 0
    MOV BL, [ALATTR]
    CALL Imprimir

    MOV AH, 02h
    MOV BH, 0
    MOV DH, 1
    MOV DL, 0
    INT 10h

    LEA DX, CADENA
    MOV AH, 0Ah
    INT 21h

    SUB CADENA[2], 48
    SUB CADENA[3], 48
    SUB CADENA[4], 48
    SUB CADENA[5], 48

    MOV AL, CADENA[2]
    CMP AL, 1
    JE ES_NEGATIVO
    MOV SIGNO, 0
    JMP SEGUIR
ES_NEGATIVO:
    MOV SIGNO, 1
SEGUIR:
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

    LEA SI, MSG2
    MOV DI, 320
    MOV BL, [ALATTR]
    CALL Imprimir

    MOV AH, 0
    MOV BL, 10
    MOV AL, DEC_NAT
    DIV BL

    CMP AL, 0
    JE soloNat

    PUSH AX
    ADD AL, 48
    MOV TempChar, AL
    MOV AL, TempChar
    MOV BL, [ALATTR]
    CALL Caracter
    POP AX

soloNat:
    ADD AH, 48
    MOV AL, AH
    MOV BL, [ALATTR]
    CALL Caracter

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

    LEA SI, MSG3
    MOV DI, 640
    MOV BL, [ALATTR]
    CALL Imprimir

    CMP SIGNO, 1
    JNE NO_SIGNO
    MOV AL, '-'
    MOV BL, [ALATTR]
    CALL Caracter
NO_SIGNO:

    MOV AH, 0
    MOV BL, 10
    MOV AL, DEC_COMP
    DIV BL

    CMP AL, 0
    JE soloComp

    PUSH AX
    ADD AL, 48
    MOV TempChar, AL
    MOV AL, TempChar
    MOV BL, [ALATTR]
    CALL Caracter
    POP AX

soloComp:
    ADD AH, 48
    MOV AL, AH
    MOV BL, [ALATTR]
    CALL Caracter

    MOV AH, 00h
    INT 16h

    MOV AH, 4Ch
    INT 21h

MAIN ENDP

Imprimir PROC
    PUSH AX
    PUSH BX
    PUSH CX
bucle:
    LODSB
    CMP AL, '$'
    JE fin
    MOV AH, BL
    MOV ES:[DI], AX
    ADD DI, 2
    JMP bucle
fin:
    POP CX
    POP BX
    POP AX
    RET
Imprimir ENDP

Caracter PROC
    PUSH AX
    MOV AH, BL
    MOV ES:[DI], AX
    ADD DI, 2
    POP AX
    RET
Caracter ENDP

END MAIN
