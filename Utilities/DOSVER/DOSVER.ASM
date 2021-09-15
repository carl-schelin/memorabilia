.model          small
.code

        mov     ah,30h                  ; Get major dos version
        int     21h                     ; Interrupt 21
        mov     ah,4ch                  ; Quit with exit code in ah
        int     21h                     ; Interrupt 21
        int     20h                     ; Exit DosVer

        end
