Priority(pre-emptive):
Code:
#include <stdio.h>
struct Process {
int at, bt, pr, wt, tat, ct, rt;
};
int main() {
int n;
printf("Enter number of processes: ");
scanf("%d", &n);
struct Process p[n];
printf("Enter Arrival Time, Burst Time, Priority (lower value = higher
priority):\n");
for (int i = 0; i < n; i++) {
scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
p[i].rt = p[i].bt;
p[i].ct = 0;
}
int time = 0, completed = 0;
while (completed < n) {
int idx = -1, high = 1e9;
for (int i = 0; i < n; i++) {
if (p[i].at <= time && p[i].rt > 0) {
if (p[i].pr < high) {
high = p[i].pr;
idx = i;
}
}
}
if (idx != -1) {
p[idx].rt--;
time++;
if (p[idx].rt == 0) {
p[idx].ct = time;
p[idx].tat = p[idx].ct - p[idx].at;
p[idx].wt = p[idx].tat - p[idx].bt;
completed++;
}
} else {
time++;
}
}
float avgwt = 0, avgtat = 0;
printf("\nP\tAT\tBT\tPR\tCT\tTAT\tWT\n");
for (int i = 0; i < n; i++) {
avgwt += p[i].wt;
avgtat += p[i].tat;
printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
i + 1, p[i].at, p[i].bt, p[i].pr,
p[i].ct, p[i].tat, p[i].wt);
}
printf("\nAverage Waiting Time = %.2f", avgwt / n);
printf("\nAverage Turnaround Time = %.2f\n", avgtat / n);
return 0;
}


Round Robin :
#include <stdio.h>
int main() {
int n, tq;
printf("Enter number of processes: ");
scanf("%d",&n);
int bt[n], at[n], rt[n];
printf("Enter burst times:\n");
for(int i=0;i<n;i++) scanf("%d",&bt[i]);
printf("Enter arrival times:\n");
for(int i=0;i<n;i++) scanf("%d",&at[i]);
printf("Enter time quantum: ");
scanf("%d",&tq);
for(int i=0;i<n;i++) rt[i]=bt[i];
int time=0, remain=n, wt=0, tat=0;
while(remain!=0){
for(int i=0;i<n;i++){
if(rt[i]>0 && at[i]<=time){
if(rt[i]>tq){
time+=tq;
rt[i]-=tq;
} else {
time+=rt[i];
wt+=time - at[i] - bt[i];
tat+=time - at[i];
rt[i]=0;
remain--;
}
}
}
}
printf("Average Waiting Time = %.2f\n", (float)wt/n);
printf("Average Turnaround Time = %.2f\n", (float)tat/n);

return 0;
}

Question â 2
Priority â Non Preemptive
code -
#include <stdio.h>
struct Process {
int at, bt, pr, wt, tat, ct;
};
int main() {
int n;
printf("Enter number of processes: ");
scanf("%d", &n);
struct Process p[n];
printf("Enter Arrival Time, Burst Time, Priority (lower value = higher priority):\n");
for (int i = 0; i < n; i++) {
scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
p[i].ct = 0;
}
int time = 0, completed = 0;
while (completed < n) {
int idx = -1, high = 1e9;
for (int i = 0; i < n; i++) {
if (p[i].at <= time && p[i].ct == 0) {
if (p[i].pr < high) {
high = p[i].pr;
idx = i;
}
}
}
if (idx != -1) {
time += p[idx].bt;
p[idx].ct = time;
p[idx].tat = p[idx].ct - p[idx].at;
p[idx].wt = p[idx].tat - p[idx].bt;
completed++;
} else {
time++;
}
}
float avgwt = 0, avgtat = 0;
printf("\nP\tAT\tBT\tPR\tCT\tTAT\tWT\n");
for (int i = 0; i < n; i++) {
avgwt += p[i].wt;
avgtat += p[i].tat;
printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
i + 1, p[i].at, p[i].bt, p[i].pr,
p[i].ct, p[i].tat, p[i].wt);
}
printf("\nAverage Waiting Time = %.2f", avgwt / n);
printf("\nAverage Turnaround Time = %.2f\n", avgtat / n);
return 0;
}


BANKERâS ALGORITHM:
Code:
#include <stdio.h>
int main() {
int n, m;
printf("Enter number of processes: ");
scanf("%d", &n);
printf("Enter number of resources: ");
scanf("%d", &m);
int alloc[n][m], max[n][m], avail[m];
printf("Enter Allocation Matrix:\n");
for(int i=0;i<n;i++)
for(int j=0;j<m;j++)
scanf("%d",&alloc[i][j]);
printf("Enter Max Matrix:\n");
for(int i=0;i<n;i++)
for(int j=0;j<m;j++)
scanf("%d",&max[i][j]);
printf("Enter Available Resources:\n");
for(int j=0;j<m;j++)
scanf("%d",&avail[j]);
int need[n][m];
for(int i=0;i<n;i++)
for(int j=0;j<m;j++)
need[i][j] = max[i][j] - alloc[i][j];
int finish[n], safeSeq[n], ind=0;
for(int i=0;i<n;i++) finish[i]=0;
for(int k=0;k<n;k++){
for(int i=0;i<n;i++){
if(finish[i]==0){
int flag=0;
for(int j=0;j<m;j++){
if(need[i][j] > avail[j]){
flag=1;
break;
}
}
if(flag==0){
for(int j=0;j<m;j++)
avail[j]+=alloc[i][j];
safeSeq[ind++]=i;
finish[i]=1;
}
}
}
}
int flag=1;
for(int i=0;i<n;i++){
if(finish[i]==0){
flag=0;
printf("System is not in safe state\n");
break;
}
}
if(flag==1){
printf("Safe sequence: ");
for(int i=0;i<n-1;i++)
printf("P%d -> ",safeSeq[i]);
printf("P%d\n",safeSeq[n-1]);
}
return 0;
}

Producer-Consumer Algorithm:
Code:
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t empty, full;
pthread_mutex_t mutex;
void *producer(void *arg) {
int item;
for(int i=0;i<10;i++){
item = rand() % 100;
sem_wait(&empty);
pthread_mutex_lock(&mutex);
buffer[in] = item;
printf("Producer produced: %d\n", item);
in = (in+1)%BUFFER_SIZE;
pthread_mutex_unlock(&mutex);
sem_post(&full);
}
return NULL;
}
void *consumer(void *arg) {
int item;
for(int i=0;i<10;i++){
sem_wait(&full);
pthread_mutex_lock(&mutex);
item = buffer[out];
printf("Consumer consumed: %d\n", item);
out = (out+1)%BUFFER_SIZE;
pthread_mutex_unlock(&mutex);
sem_post(&empty);
}
return NULL;
}
int main() {
pthread_t prod, cons;
sem_init(&empty, 0, BUFFER_SIZE);
sem_init(&full, 0, 0);
pthread_mutex_init(&mutex, NULL);
pthread_create(&prod, NULL, producer, NULL);
pthread_create(&cons, NULL, consumer, NULL);
pthread_join(prod, NULL);
pthread_join(cons, NULL);
sem_destroy(&empty);
sem_destroy(&full);
pthread_mutex_destroy(&mutex);
return 0;
}


FCFS â With Arrival Time
#include <stdio.h>
void findTimes(int n, int at[], int bt[]) {
int ct[n], tat[n], wt[n];
float total_wt = 0, total_tat = 0;
int current_time = 0;
for (int i = 0; i < n; i++) {
if (current_time < at[i]) {
current_time = at[i];
}
ct[i] = current_time + bt[i];
tat[i] = ct[i] - at[i];
wt[i] = tat[i] - bt[i];
current_time = ct[i];
total_wt += wt[i];
total_tat += tat[i];
}
printf("P#\tAT\tBT\tCT\tTAT\tWT\n");
for (int i = 0; i < n; i++) {
printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
}
printf("Average Waiting Time: %f\n", total_wt / n);
printf("Average Turnaround Time: %f\n", total_tat / n);
}
int main() {
int n = 4;
int arrival_time[] = {0, 1, 2, 4};
int burst_time[] = {5, 3, 8, 6};
findTimes(n, arrival_time, burst_time);
return 0;
}

Shortest Job First (SJF) (Non-Preemptive)
#include <stdio.h>
#include <limits.h>
void findSJF(int n, int at[], int bt[]) {
int ct[n], tat[n], wt[n], completed[n];
float total_wt = 0, total_tat = 0;
int current_time = 0, completed_count = 0;
for(int i = 0; i < n; i++) completed[i] = 0;
while (completed_count < n) {
int shortest_job_index = -1;
int min_burst = INT_MAX;
for (int i = 0; i < n; i++) {
if (at[i] <= current_time && completed[i] == 0) {
if (bt[i] < min_burst) {
min_burst = bt[i];
shortest_job_index = i;
}
}
}
if (shortest_job_index == -1) {
current_time++;
} else {
int i = shortest_job_index;
current_time += bt[i];
ct[i] = current_time;
tat[i] = ct[i] - at[i];
wt[i] = tat[i] - bt[i];
total_wt += wt[i];
total_tat += tat[i];
completed[i] = 1;
completed_count++;
}
}
printf("P#\tAT\tBT\tCT\tTAT\tWT\n");
for (int i = 0; i < n; i++) {
printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
}
printf("Average Waiting Time: %f\n", total_wt / n);
printf("Average Turnaround Time: %f\n", total_tat / n);
}
int main() {
int n = 4;
int arrival_time[] = {0, 1, 2, 4};
int burst_time[] = {5, 3, 8, 6};
findSJF(n, arrival_time, burst_time);
return 0;
}


Shortest Remaining Time First (SRTF) (Preemptive)
#include <stdio.h>
#include <limits.h>
void findSRTF(int n, int at[], int bt[]) {
int rt[n], ct[n], tat[n], wt[n], completed = 0;
float total_wt = 0, total_tat = 0;
int current_time = 0;
for (int i = 0; i < n; i++) rt[i] = bt[i];
while (completed != n) {
int shortest = -1;
int min_rem_time = INT_MAX;
for (int i = 0; i < n; i++) {
if (at[i] <= current_time && rt[i] < min_rem_time && rt[i] > 0) {
min_rem_time = rt[i];
shortest = i;
}
}
if (shortest == -1) {
current_time++;
continue;
}
rt[shortest]--;
current_time++;
if (rt[shortest] == 0) {
completed++;
ct[shortest] = current_time;
tat[shortest] = ct[shortest] - at[shortest];
wt[shortest] = tat[shortest] - bt[shortest];
total_wt += wt[shortest];
total_tat += tat[shortest];
}
}
printf("P#\tAT\tBT\tCT\tTAT\tWT\n");
for (int i = 0; i < n; i++) {
printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
}
printf("Average Waiting Time: %f\n", total_wt / n);
printf("Average Turnaround Time: %f\n", total_tat / n);
}
int main() {
int n = 4;
int arrival_time[] = {0, 1, 2, 4};
int burst_time[] = {5, 3, 8, 6};
findSRTF(n, arrival_time, burst_time);
return 0;
}


COMPILER DESIGN - 

Lexical analyser

#include <stdio.h>
#include <string.h> // For strcmp() to check for keywords
#include <ctype.h>  // For isalpha(), isdigit(), isspace()

int main() {
    // This is the "source code" we will scan
    const char* input = "int result = 10 + var1;";

    int pos = 0; // Our current position in the input string

    printf("Input: %s\n", input);
    printf("--- Tokens ---\n");

    // The heart of the lexer: a loop that runs until the end of the string
    // The '\0' character marks the end of a C string
    while (input[pos] != '\0') {
        char current_char = input[pos];
        
        // 1. --- Skip Whitespace ---
        // isspace() checks for ' ', '\t', '\n'
        if (isspace(current_char)) {
            pos++; // Just move to the next character
            continue; // Go back to the start of the while loop
        }

        // 2. --- Recognize Keywords and Identifiers ---
        // isalpha() checks if a character is a letter (a-z, A-Z)
        if (isalpha(current_char) || current_char == '_') {
            char buffer[100]; // A temporary buffer to build the word
            int i = 0;

            // Keep reading characters as long as they are letters,
            // numbers, or underscores (valid for variable names)
            while (isalnum(input[pos]) || input[pos] == '_') {
                buffer[i++] = input[pos++];
            }
            buffer[i] = '\0'; // End the string

            // Now, check if the word is a keyword
            if (strcmp(buffer, "int") == 0) {
                printf("KEYWORD:   %s\n", buffer);
            } else if (strcmp(buffer, "if") == 0) {
                printf("KEYWORD:   %s\n", buffer);
            } else if (strcmp(buffer, "else") == 0) {
                printf("KEYWORD:   %s\n", buffer);
            } else {
                // If it's not a keyword, it's an identifier
                printf("IDENTIFIER: %s\n", buffer);
            }
            continue; // We've found our token, so restart the loop
        }

        // 3. --- Recognize Numbers ---
        // isdigit() checks if a character is a number (0-9)
        if (isdigit(current_char)) {
            char buffer[100];
            int i = 0;

            // Keep reading characters as long as they are numbers
            while (isdigit(input[pos])) {
                buffer[i++] = input[pos++];
            }
            buffer[i] = '\0';
            printf("NUMBER:    %s\n", buffer);
            continue;
        }

        // 4. --- Recognize Operators and Punctuation ---
        if (current_char == '=') {
            printf("OPERATOR:  =\n");
            pos++;
            continue;
        } else if (current_char == '+') {
            printf("OPERATOR:  +\n");
            pos++;
            continue;
        } else if (current_char == ';') {
            printf("PUNCTUATION: ;\n");
            pos++;
            continue;
        }

        // 5. --- Handle Unknown Characters ---
        printf("ERROR:     Unknown character '%c'\n", current_char);
        pos++;
    }

    printf("--- End of Tokens ---\n");
    return 0;
}



Left recursion

#include <stdio.h>
#include <string.h>
#define SIZE 10
int main() {
 char non_terminal;
 char beta, alpha;
 int num;
 char production[10][SIZE];
 int index = 3; /* starting of the string following "->" */
 printf("Enter Number of Production: ");
 scanf("%d", &num);
 printf("Enter the grammar as E->E-A : \n");
 for (int i = 0; i < num; i++) {
 scanf("%s", production[i]);
 }
 for (int i = 0; i < num; i++) {
 printf("\nGRAMMAR : : : %s", production[i]);
 non_terminal = production[i][0];
 if (non_terminal == production[i][index]) {
 alpha = production[i][index + 1];
 printf(" is left recursive.\n");
 while (production[i][index] != 0 && production[i][index] != '|') {
 index++;
 }
 if (production[i][index] != 0) {
 beta = production[i][index + 1];
 printf("Grammar without left recursion:\n");
 printf("%c -> %c%c'\n", non_terminal, beta, non_terminal);
 printf("%c' -> %c%c' | E\n", non_terminal, alpha, non_terminal);
 } else {
 printf(" can't be reduced\n");
 }
 } else {
 printf(" is not left recursive.\n");
 }
 index = 3;
 }
 return 0;
}

Left Factoring 

#include <stdio.h>
#include <string.h>
int main() {
char gram[20], part1[20], part2[20], modifiedGram[20], newGram[20];
int i, j = 0, k = 0, pos;
printf("Enter Production : A->");
gets(gram);
// Extract first part (before '|')
for (i = 0; gram[i] != '|'; i++, j++) {
part1[j] = gram[i];
}
part1[j] = '\0';
// Extract second part (after '|')
for (j = ++i, i = 0; gram[j] != '\0'; j++, i++) {
part2[i] = gram[j];
}
part2[i] = '\0';
// Find common prefix
for (i = 0; i < strlen(part1) || i < strlen(part2); i++) {
if (part1[i] == part2[i]) {
modifiedGram[k] = part1[i];
k++;
pos = i + 1;
}
}
// Remaining part of first production
for (i = pos, j = 0; part1[i] != '\0'; i++, j++) {
newGram[j] = part1[i];
}
newGram[j++] = '|';
// Remaining part of second production
for (i = pos; part2[i] != '\0'; i++, j++) {
newGram[j] = part2[i];
}
modifiedGram[k] = 'X';
modifiedGram[++k] = '\0';
newGram[j] = '\0';
// Output
printf("\nGrammar Without Left Factoring : : \n");
printf(" A->%s", modifiedGram);
printf("\n X->%s\n", newGram);
return 0;
}

RECURSIVE DESCENT PARSER

#include <stdio.h>
#include <ctype.h>
char input[100];
int i = 0;
void E();
void T();
void F();
void Eprime();
void Tprime();
void error() {
 printf("Error in parsing\n");
 exit(1);
}
void match(char expected) {
 if (input[i] == expected)
 i++;
 else
 error();
}
void E() {
 T();
 Eprime();
}
void Eprime() {
 if (input[i] == '+') {
 match('+');
 T();
 Eprime();
 }
}
void T() {
 F();
 Tprime();
}
void Tprime() {
 if (input[i] == '*') {
 match('*');
 F();
 Tprime();
 }
}
void F() {
 if (input[i] == '(') {
 match('(');
 E();
 match(')');
 } else if (isalpha(input[i])) {
 match(input[i]);
 } else {
 error();
 }
}
int main() {
 printf("Enter the string to parse: ");
 scanf("%s", input);
 E();
 if (input[i] == '\0')
 printf("String successfully parsed!\n");
 else
 printf("Error in parsing\n");
return 0;
}


LEX

Write a LEX code to recognize the Numbers and Operators.
Coding -
%option noyywrap
%{
#include <stdlib.h>
#include <stdio.h>
%}
number [0-9]+
operator [+\-|*]
%%
{number} { printf("Found: %d\n", atoi(yytext)); }
{operator} { printf("Found: %s\n", yytext); }
. { printf("Invalid = %s\n", yytext); }
%%
int main()
{
yylex();
return 1;
}


%{
#include <stdio.h>
%}
%%
[A-Z]+ {printf("capital word found:
%s\n",yytext);} [A-Za-z0-9]+ {/*ignore other
words*/}
.|\n {/*ignore other characters */}
%%
int main(){ printf("enter a string:");
yylex(); return 0;
}
int yywrap(){ return 1;
}

VOWELS
%{
#include <stdio.h>
int vowel_count=0;
%}
%%
[aeiouAEIOU] {vowel_count++;}
.|\n {/*ignore other characters*/}
%%
int main(){ printf("enter a string:"); yylex();
printf("total number of vowels: %d\n",vowel_count); return 0;
}
int yywrap(){ return 1;
}

PALINDROME
#include <stdio.h>
#include <string.h>
void check_palindrome(char *str);
%}
%%
[a-zA-Z]+ { check_palindrome(yytext); }
.|\n ; /* ignore everything else */
%%
void check_palindrome(char *str) {
int len = strlen(str);
int i, flag = 1;
for (i = 0; i < len / 2; i++) {
if (str[i] != str[len - i - 1]) {
flag = 0;
break;
}
}
if (flag)
printf("%s is a palindrome\n", str);
else
printf("%s is not a palindrome\n", str);
}
int yywrap() {
return 1;
}
int main() {
printf("Enter a string: ");
yylex();
return 0;
}


YACC

INFIX TO POSTFIX

Infix.l
/* infix.l: The lexer for the infix-to-postfix converter */
%{
/* This section includes C code and the YACC token header */
#include "y.tab.h"
#include <stdlib.h>
void yyerror(char *);
%}
/* Define regular expressions for tokens */
DIGIT [0-9]
ID [a-zA-Z]
%%
/* Rules for the lexer */
/* When a number (one or more digits) is found: */
/* 1. Convert it from a string (yytext) to an integer */
/* 2. Store this value in yylval (the token's value) */
/* 3. Return the 'NUMBER' token to the parser */
{DIGIT}+ {
yylval = atoi(yytext);
return NUMBER;
}
/* When a letter (ID) is found, return the ID token */
{ID} {
return ID;
}
/* Ignore whitespace (spaces and tabs) */
[ \t] ;
/* When a newline is found, return 0 (end of input) */
\n { return 0; }
/* For any other character, return it as its own token (e.g., '+', '-', '*') */
. { return yytext[0]; }
%%
/* This simple yywrap() function is required by lex */
int yywrap() {
return 1;
}
Infix.y
/* infix.y: The YACC parser for infix-to-postfix conversion */
%{
/* C code to be included in the final C file */
#include <stdio.h>
#include <stdlib.h>
/* Function prototypes */
int yylex(void);
void yyerror(char *);
%}
/* * Define the tokens. NUMBER and ID come from the lexer.
* The others are single-character tokens (operators).
*/
%token NUMBER ID
/* * Define operator precedence and associativity.
* This is crucial for handling infix notation correctly.
* 'PRINT' has the lowest precedence.
* '+' and '-' have the same, left-associative precedence.
* '*' and '/' have higher, left-associative precedence.
*/
%left 'P' /* Lowest precedence for our 'print' command */
%left '+' '-'
%left '*' '/' /* Highest precedence */
%%
/* The grammar rules for the parser */
/* The program can be a list of expressions */
program:
/* An empty program */
| program expr 'P' { printf("\n"); } /* 'P' acts as our "print" command */
;
/* An expression (expr) is defined here */
expr:
NUMBER { printf("%d ", $1); }
| ID { printf("%c ", $1); }
| expr '+' expr { printf("+ "); }
| expr '-' expr { printf("- "); }
| expr '*' expr { printf("* "); }
| expr '/' expr { printf("/ "); }
| '(' expr ')' /* Parentheses just group, they don't print */
;
%%
/* The main function to start the parser */
int main() {
printf("Enter an infix expression followed by 'P' to convert (e.g., 5+2*3 P): \n");
yyparse();
return 0;
}
/* Error handling function */
void yyerror(char *s) {
fprintf(stderr, "Error: %s\n", s);
}

ARMSTRONG NUMBER
%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int yylex();
int yyerror(char *msg);
%}
%union {
int num;
}
%token <num> NUMBER
%%
input:
NUMBER {
int n = $1;
int original = n;
int sum = 0;
int temp = n;
int digits = 0;
// Count digits
while (temp > 0) {
digits++;
temp /= 10;
}
temp = n;
// Compute sum of powers
while (temp > 0) {
int digit = temp % 10;
sum += pow(digit, digits);
temp /= 10;
}
// Check Armstrong
if (sum == original)
printf("%d is an Armstrong number\n", original);
else
printf("%d is not an Armstrong number\n", original);
}
;
%%
int yyerror(char *msg) {
printf("Error: %s\n", msg);
return 0;
}
int main() {
printf("Keshav Dadhich - 23BCE0789\n");
printf("Enter number: ");
yyparse();
return 0;
}
Arm.l
%{
#include "arm.tab.h"
#include <stdio.h>
int yyerror(char *msg);
%}
%%
[0-9]+ {
yylval.num=atoi(yytext);
return NUMBER;
}
[ \t\n]+ {/*skip whitespace*/}
. {yyerror("invalid character");}
%%
int yywrap(){return 1;}
