.MODEL SMALL
.STACK 100h

.DATA
CADENA DB 5,0,0,0,0,0,0
PESO   DB 8,4,2,1
DEC_NAT DB ?
DEC_COMP DB ?
MSG1 DB 13,10,'Introduce un numero binario de 4 bits: $'
MSGNAT DB 13,10,'Valor en binario natural: $'
MSGCOMP DB 13,10,'Valor en complemento a 1: $'

.CODE
    MOV AX, @DATA
    MOV DS, AX

    MOV AH, 09h
    LEA DX, MSG1
    INT 21h

    MOV AH, 0Ah
    LEA DX, CADENA
    INT 21h

    ; convertir ASCII a 0/1
    SUB CADENA[2], 48
    SUB CADENA[3], 48
    SUB CADENA[4], 48
    SUB CADENA[5], 48

; ===========================================
; CALCULAR NATURAL SIEMPRE
; ===========================================
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


; ===========================================
; CALCULAR COMPLEMENTO A 1:
; SOLO se invierte si el primer bit = 1
; ===========================================

    MOV AL, CADENA[2]
    CMP AL, 1
    JNE NO_INVERTIR

; --- INVERTIR bits si empieza en 1 ----
    MOV BL, CADENA[2]
    NOT BL
    AND BL, 1
    MOV CADENA[2], BL

    MOV BL, CADENA[3]
    NOT BL
    AND BL, 1
    MOV CADENA[3], BL

    MOV BL, CADENA[4]
    NOT BL
    AND BL, 1
    MOV CADENA[4], BL

    MOV BL, CADENA[5]
    NOT BL
    AND BL, 1
    MOV CADENA[5], BL

    JMP CALC_COMP

NO_INVERTIR:
; Si empieza en 0 ? copiar bits naturales tal cual
    MOV AL, CADENA[2]
    MOV BL, AL
    MOV CADENA[2], BL

    MOV AL, CADENA[3]
    MOV CADENA[3], AL

    MOV AL, CADENA[4]
    MOV CADENA[4], AL

    MOV AL, CADENA[5]
    MOV CADENA[5], AL


; ===========================================
; CALCULAR DEC_COMP
; ===========================================
CALC_COMP:
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


; ===========================================
; MOSTRAR VALOR NATURAL
; ===========================================
    MOV AH, 09h
    LEA DX, MSGNAT
    INT 21h

    MOV AL, DEC_NAT
    CALL PRINT_DEC


; ===========================================
; MOSTRAR COMPLEMENTO A 1
; ===========================================
    MOV AH, 09h
    LEA DX, MSGCOMP
    INT 21h

    MOV AL, DEC_COMP
    CALL PRINT_DEC


; ===========================================
; FIN
; ===========================================
    MOV AH, 00h
    INT 16h
    MOV AH, 4Ch
    INT 21h

; ===========================================
; RUTINA PARA IMPRIMIR DECIMAL (0–15)
; ===========================================
PRINT_DEC PROC
    MOV AH,0
    MOV BL,10
    DIV BL

    CMP AL,0
    JE DIG_UNO

    ADD AL,48
    MOV DL,AL
    MOV AH,02h
    INT 21h

DIG_UNO:
    ADD AH,48
    MOV DL,AH
    MOV AH,02h
    INT 21h
    RET
PRINT_DEC ENDP

END
