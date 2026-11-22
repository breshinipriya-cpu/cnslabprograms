# Experiment 9: PT-109 Playfair Cipher Decryption

## Aim
To write a C program to decrypt the historic PT-109 Playfair cipher message sent when Lt. John F. Kennedy's patrol boat was sunk during World War II.

## Algorithm
1. Start the program.
2. Setup the 5x5 Playfair matrix using the historical key phrase `ROYAL NEW ZEALAND NAVY`.
3. Store the received ciphertext:
   `KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ`
4. Filter out whitespace to obtain the consecutive digraphs.
5. For each digraph $(C_1, C_2)$:
   - If in the same row, replace with characters to their left (wrap around).
   - If in the same column, replace with characters above them (wrap around).
   - If forming a rectangle, replace with characters in same row but opposite column.
6. Assemble and display the decrypted message.
7. Stop.

## Sample Output
```text
Key used: "ROYAL NEW ZEALAND NAVY"

5x5 Playfair Matrix:
R O Y A L 
N E W Z B 
C D F G H 
I K M P Q 
S T U V X 

Decrypted Digraphs:
PT ON EZ ER ON IN EL OS TI NA CT IO NI NB LA CK ET TS TR AI TT WO MI LE SS WM ER ES UC OV EX CR EW OF TW EL VE EN RO UT ET OP AG OP AG O. . .

Formatted English Text:
"PT ONE ZERO NINE LOST IN ACTION IN BLACKETT STRAIT TWO MILES SW MERESU COVE X CREW OF TWELVE EN ROUTE TO PAGO PAGO ..."
```
