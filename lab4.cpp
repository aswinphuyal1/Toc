#include <stdio.h>
6. int EE=0, OE=1, OO=2, EO=3; // DFA states
7. int state = 0; // initial DFA state
8. char input;
9. int main(void) {
10. printf("Enter a string of 0s and 1s: ");
11. while (1) {
12. scanf("%c", &input);
13. if (input == '\n') // if end-of-line exit loop
14. break;
15. if ( (input != '0') && (input != '1') ) { // invalid input printf("Invalid input: program
terminating\n");
16. break;
17. }
18. if (state==0) {
19. // input is either '0' or '1' state = (input == '0') ? OE : EO;
20. }
21. else if(state==1) {
22. state = (input == '0') ? EE : OO;
23. }
24. else if (state==2) {
25. state = (input == '0') ? EO : OE;
26. } else {
27. state = (input == '0') ? OO : EE;
28. }
29. };
30. if (input == '\n') {
31. if (state == OO)
32. printf("Input accepted\n");
33. else
34. printf("Input rejected\n");
35. }
36. return 0;
37. }