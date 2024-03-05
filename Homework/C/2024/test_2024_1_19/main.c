/*#include <stdio.h>

int main(void) {
	int n, i;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		printf("%d ", i); 
	} 
	printf("\n");
	return 0;
} */
/*#include <stdio.h>
int main() {
  char ch;
  int a_ct, e_ct, i_ct, o_ct, u_ct;

  a_ct = e_ct = i_ct = o_ct = u_ct = 0;
  printf("Enter some text; enter # to quit.\n");
  while ((ch = getchar()) != '#') {
    switch (ch) {
      case 'a':
      case 'A':
        a_ct++;
        break;
      case 'e':
      case 'E':
      	e_ct++;
      	break;
      case 'i':
      case 'I':
      	i_ct++;
      	break;
      case 'o':
      case 'O':
      	o_ct++;
      	break;
      case 'u':
      case 'U':
      	u_ct++;
      	break;
      default:
      	break;
    }
  }
  printf("number of vowels:\tA\tE\tI\tO\tU\n");
  printf("                 \t%d\t%d\t%d\t%d\t%d\n",
         a_ct, e_ct, i_ct, o_ct, u_ct);
  return 0;
}*/

