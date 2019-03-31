#include <stdio.h>
#include <math.h>

int main(void) {
  double a, b, c;

  scanf("%lf %lf %lf", &a, &b, &c);

  double delta = pow(b, 2) - 4 * a * c;

  if (delta < 0 || a == 0) {
    puts("Impossivel calcular");
    return 0;
  }

  double result1 = (-b + sqrt(delta)) / (2 * a);
  double result2 = (-b - sqrt(delta)) / (2 * a);  

  printf("R1 = %.5lf\nR2 = %.5lf\n", result1, result2);

  return 0;
}
