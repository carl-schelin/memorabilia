.model          small
.code

   MOV     AX,B800h    ; Move screen buffer into AX
   MOV     ES,AX       ; Move it into ES segment
StartIt:               ;
   MOV     CX,07D0h    ; Move 7, 208 into CX
   XOR     BX,BX       ; Zero BX (counter)
   MOV     SI,0000     ; Move 0000 into SI
StartLoop:             ;
;   ES:                 ; ???
   MOV     AH,[SI]     ;
   CMP     AH,20       ;
   JZ      SkipIt      ;
   JL      IncAH       ;
   DEC     AH          ; subtract one from AH
;   ES:                 ;
   MOV     [SI],AH     ;
   INC     BX          ; add one to BX
   JMP     SkipIt      ;
   NOP                 ;
IncAH:                 ;
   INC     AH          ; add one to AH
;   ES:                 ;
   MOV     [SI],AH     ;
   INC     BX          ;
SkipIt:                ;
   INC     SI          ;
   INC     SI          ;
   LOOP    StartLoop   ;
   CMP     BX,+00      ;
   JNZ     StartIt     ;
   MOV     AH,4Ch      ; Exit with error code
   INT     21          ; Exit

   end
