.MODEL SMALL
.CODE
ORG 100h

Programa_Int:
    JMP Reside

contador        DB  0
reloj           DB  '00:00'
seg             DB  0
min             DB  0

Rutina_Servicio PROC
    CLI
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX

    INC contador
    CMP contador, 18
    JB  finalizar

    MOV contador, 0

    MOV AX, 0B800h
    MOV ES, AX

    MOV AH, 00001111b

    MOV SI, 0
    MOV DI, 308

bucle:
    MOV AL, reloj[SI]
    MOV ES:[DI], AX
    ADD DI, 2
    INC SI
    CMP SI, 4
    JBE bucle

    INC seg
    CMP seg, 60
    JNZ minutos
    MOV seg, 0
    INC min

minutos:
    CMP min, 60
    JNZ actualizar
    MOV min, 0

actualizar:
    MOV AL, min
    MOV AH, 0
    MOV BL, 10
    DIV BL
    ADD AL, '0'
    ADD AH, '0'
    MOV reloj[0], AL
    MOV reloj[1], AH

    MOV AL, seg
    MOV AH, 0
    MOV BL, 10
    DIV BL
    ADD AL, '0'
    ADD AH, '0'
    MOV reloj[3], AL
    MOV reloj[4], AH

finalizar:
    POP DX
    POP CX
    POP BX
    POP AX
    STI
    IRET
ENDP

Reside:
    MOV DX, OFFSET Rutina_Servicio
    MOV AX, 0
    MOV ES, AX
    MOV SI, 1Ch*4
    CLI
    MOV ES:[SI], DX
    MOV ES:[SI+2], CS
    STI
    MOV DX, OFFSET Reside
    INT 27h

END Programa_Int
