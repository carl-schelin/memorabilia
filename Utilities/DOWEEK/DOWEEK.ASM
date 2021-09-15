.model          small
.code

        mov     ah,2ah                  ; Get current date function
        int     21h                     ; Interrupt 21
        mov     ah,4ch                  ; Quit with exit code in ah
        int     21h                     ; Interrupt 21
        int     20h                     ; Exit DOWeek

        end
