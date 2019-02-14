// Decimal, octal, hexadecimal, ASCII table printer
// usage: a.out
//        a.out stop
//        a.out start stop
//
// Prints number representation for the range specified on the command
// line. Default range is 0 to 31.
//
// Examples:
// > gcc table.c
// > a.out 5
// Table from 0 to 5
// First three columns are decimal, octal, and hexadecimal versions of the number
// Last column is the ASCII character associated with the number
// - Normal characters are printed with single quotes around them like 't'.
// - Non-printing control characters do not have single quotes like BEL.
// - Blanks indicate no ASCII character associated with number (above 127)
// 
//    N  Octal    Hex ASCII 
//    0 000000 0x0000 '\0' 
//    1 000001 0x0001 SOH 
//    2 000002 0x0002 STX 
//    3 000003 0x0003 ETX 
//    4 000004 0x0004 EOT 
// > a.out 60 70
// Table from 60 to 70
// First three columns are decimal, octal, and hexadecimal versions of the number
// Last column is the ASCII character associated with the number
// - Normal characters are printed with single quotes around them like 't'.
// - Non-printing control characters do not have single quotes like BEL.
// - Blanks indicate no ASCII character associated with number (above 127)
// 
//    N  Octal    Hex ASCII 
//   60 000074 0x003C '<' 
//   61 000075 0x003D '=' 
//   62 000076 0x003E '>' 
//   63 000077 0x003F '?' 
//   64 000100 0x0040 '@' 
//   65 000101 0x0041 'A' 
//   66 000102 0x0042 'B' 
//   67 000103 0x0043 'C' 
//   68 000104 0x0044 'D' 
//   69 000105 0x0045 'E' 

#include <stdio.h>
#include <stdlib.h>

int table_len;                         // declare two variables that are defined
char *table[];                         // later after main; only works for globals

int main(int argc, char *argv[]){      // main entry point takes # and string command args
  int start = 0;                       // default start index of table
  int stop = 32;                       // default stop index of table

  if(argc == 2){                       // single command line changes stop point
    stop = atoi(argv[1]);              // atoi() converts a string to an integer
  }
  else if(argc == 3){                  // two argumnets changes start and stop point
    start = atoi(argv[1]);             // first argumnet is start index
    stop  = atoi(argv[2]);             // second arguments is stop index
  }

  printf("Table from %d to %d\n",      // substitute two integers into this string where %d is present
         start, stop);                 // sub in values of start and stop variables

  // Print some information about what is being shown
  printf("First three columns are decimal, octal, and hexadecimal versions of the number\n");
  printf("Last column is the ASCII character associated with the number\n");
  printf("- Normal characters are printed with single quotes around them like 't'.\n");
  printf("- Non-printing control characters do not have single quotes like BEL.\n");
  printf("- Blanks indicate no ASCII character associated with number (above 127)\n");
  printf("\n");

  printf("%4s %6s %6s ",               // print a header, strings aligned in width 4, 8, 8, right justified
         "N","Octal","Hex");           // substitute "N", "Octal", "Hex" into format positions
  printf("%s ","ASCII");               // same as above, single substitution left justified
  printf("\n");                        // print a newline

  for(int i=start; i<stop; i++){       // loop from start to less than stop
    printf("%4d %06o 0x%04X ",i,i,i);    // print decimal, octal, hex reps of i
    if(i < table_len){
      if(table[i]!=NULL){              // check if a table entry is NULL (nothing)
        printf("%s ",table[i]);        // print special string for character
      }
      else {                           // table[i] is null so i can be interpretted as a character
        printf("'%c' ",i);             // print as a character
      }
    }
    printf("\n");
  }
  return 0;                            // main returns 0 on successful completion
}

// number entries in table, 128 ASCII characters
int table_len = 128;

// table of strings for "special" ASCII chars that don't print normally 
char *table[] = {                      
  "'\\0'",  // 0     NUL '\0' (null character)
  "SOH",    // 1     SOH (start of heading)   
  "STX",    // 2     STX (start of text)      
  "ETX",    // 3     ETX (end of text)        
  "EOT",    // 4     EOT (end of transmission)
  "ENQ",    // 5     ENQ (enquiry)            
  "ACK",    // 6     ACK (acknowledge)        
  "BEL",    // 7     BEL '\a' (bell)          
  "'\\b'",  // 8     BS  '\b' (backspace)     
  "'\\t'",  // 9     HT  '\t' (horizontal tab)
  "'\\n'",  // 10    LF  '\n' (new line)      
  "'\\v'",  // 11    VT  '\v' (vertical tab)  
  "'\\f'",  // 12    FF  '\f' (form feed)     
  "'\\r'",  // 13    CR  '\r' (carriage ret)  
  "SO ",    // 14    SO  (shift out)          
  "SI ",    // 15    SI  (shift in)           
  "DLE",    // 16    DLE (data link escape)   
  "DC1",    // 17    DC1 (device control 1)   
  "DC2",    // 18    DC2 (device control 2)   
  "DC3",    // 19    DC3 (device control 3)   
  "DC4",    // 20    DC4 (device control 4)   
  "NAK",    // 21    NAK (negative ack.)      
  "SYN",    // 22    SYN (synchronous idle)   
  "ETB",    // 23    ETB (end of trans. blk)  
  "CAN",    // 24    CAN (cancel)             
  "EM ",    // 25    EM  (end of medium)      
  "SUB",    // 26    SUB (substitute)         
  "ESC",    // 27    ESC (escape)             
  "FS ",    // 28    FS  (file separator)     
  "GS ",    // 29    GS  (group separator)    
  "RS ",    // 30    RS  (record separator)   
  "US ",    // 31    US  (unit separator)     
  NULL,     // 32    SPACE                    
  NULL,     // 33    !                        
  NULL,     // 34    "                        
  NULL,     // 35    #                        
  NULL,     // 36    $                        
  NULL,     // 37    %                        
  NULL,     // 38    &                        
  NULL,     // 39    '                        
  NULL,     // 40    (                        
  NULL,     // 41    )                        
  NULL,     // 42    *                        
  NULL,     // 43    +                        
  NULL,     // 44    ,                        
  NULL,     // 45    -                        
  NULL,     // 46    .                        
  NULL,     // 47    /                        
  NULL,     // 48    0                        
  NULL,     // 49    1                        
  NULL,     // 50    2                        
  NULL,     // 51    3                        
  NULL,     // 52    4                        
  NULL,     // 53    5                        
  NULL,     // 54    6                        
  NULL,     // 55    7                        
  NULL,     // 56    8                        
  NULL,     // 57    9                        
  NULL,     // 58    :                        
  NULL,     // 59    ;                        
  NULL,     // 60    <                        
  NULL,     // 61    =                        
  NULL,     // 62    >                        
  NULL,     // 63    ?                        
  NULL,     // 64    @         
  NULL,     // 65    A         
  NULL,     // 66    B         
  NULL,     // 67    C         
  NULL,     // 68    D         
  NULL,     // 69    E         
  NULL,     // 70    F         
  NULL,     // 71    G         
  NULL,     // 72    H         
  NULL,     // 73    I         
  NULL,     // 74    J         
  NULL,     // 75    K         
  NULL,     // 76    L         
  NULL,     // 77    M         
  NULL,     // 78    N         
  NULL,     // 79    O         
  NULL,     // 80    P         
  NULL,     // 81    Q         
  NULL,     // 82    R         
  NULL,     // 83    S         
  NULL,     // 84    T         
  NULL,     // 85    U         
  NULL,     // 86    V         
  NULL,     // 87    W         
  NULL,     // 88    X         
  NULL,     // 89    Y         
  NULL,     // 90    Z         
  NULL,     // 91    [         
  NULL,     // 92    \  '\\'   
  NULL,     // 93    ]         
  NULL,     // 94    ^         
  NULL,     // 95    _         
  NULL,     // 96    `         
  NULL,     // 97    a         
  NULL,     // 98    b         
  NULL,     // 99    c         
  NULL,     // 100   d         
  NULL,     // 101   e         
  NULL,     // 102   f         
  NULL,     // 103   g         
  NULL,     // 104   h         
  NULL,     // 105   i         
  NULL,     // 106   j         
  NULL,     // 107   k         
  NULL,     // 108   l         
  NULL,     // 109   m         
  NULL,     // 110   n         
  NULL,     // 111   o         
  NULL,     // 112   p         
  NULL,     // 113   q         
  NULL,     // 114   r         
  NULL,     // 115   s         
  NULL,     // 116   t         
  NULL,     // 117   u         
  NULL,     // 118   v         
  NULL,     // 119   w         
  NULL,     // 120   x         
  NULL,     // 121   y         
  NULL,     // 122   z         
  NULL,     // 123   {         
  NULL,     // 124   |         
  NULL,     // 125   }         
  NULL,     // 126   ~         
  "DEL",    // 127   DEL                            
};
