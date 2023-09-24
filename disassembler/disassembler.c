#include <stdio.h>

int Disassemble6502p(unisgned char* buffer, int pc)
{
    unsigned char* code = &buffer[pc];
    int opbytes = 1;

    switch (*code)
    {
        /* Gabe does opcode $00 to opcode $40 */

        /* Jacob does opcode $41 to opcode $85 */

        /* Jeriah does opcode $86 to opcode $bd */

        /* Raul does opcode $be to opcode $fe */
    }
}