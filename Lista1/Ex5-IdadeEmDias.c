#include <stdio.h>
 
int main() {
    int dias;
    
    scanf("%d", &dias);
    
    printf("%d ano(s)\n", dias / 365);
    dias = dias % 365;
    
    printf("%d mes(es)\n", dias / 30);
    dias = dias % 30;
    
    printf("%d dia(s)\n", dias);
    

    return 0;
}
