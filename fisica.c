#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define A 0.1
#define G 10
#define M 1
#define PI 3.14159
#define Ta 0.1
#define Tb 0.01
#define T 2
double val = PI / 180;

typedef struct ponto{
	double x, y;
} Ponto;


double norma(Ponto p){
	return sqrt(pow(p.x, 2) + pow(p.y, 2));
}

Ponto aceleracao(Ponto v){
	Ponto *a = malloc(sizeof(Ponto));
	a->x = ((A * (-1))/M) * v.x;
	a->y = G * (-1) - (A / M) * v.y;
	return *a;
}

Ponto velocidade(Ponto a0, Ponto v0, double t){
	Ponto *v = malloc(sizeof(Ponto));
	v->x = v0.x + a0.x * t;
	v->y = v0.y + a0.y * t;
	return *v;
}

Ponto posicao(Ponto r0, Ponto v0, Ponto v, double t){
	Ponto *r = malloc(sizeof(Ponto));
	r->x = r0.x + ((v0.x + v.x) / 2) * t;
	r->y = r0.y + ((v0.y + v.y) / 2) * t;
	return *r;
}

Ponto posicao_N(Ponto r0, Ponto v0, double t){
	Ponto vv0;
	vv0.x = cos(val * 45) * 10;
	vv0.y = sin(val * 45) * 10;
	Ponto *r = malloc(sizeof(Ponto));
	r->x = r0.x + 10 * cos(val * 45) * t;
	r->y = r0.y + t * v0.y;
	return *r;
}

Ponto velocidade_N(Ponto r0, Ponto v0, double t){
	Ponto *v = malloc(sizeof(Ponto));
	v->y = v0.y - t * G;
	return *v;
}

FILE *write(FILE *file, double x, double y){
	fprintf(file, "%f %f\n", x, y);
}

int main(){
	double val = PI / 180;
	Ponto v0, v, a0, a, r0, r;
	int sim = 0;

	printf("V0=(%fi + %fj)m/s\n", v0.x, v0.y);
	FILE *arq = fopen("0,1s com arraste.txt", "w");
	v0.x = cos(val * 45) * 10;
	v0.y = sin(val * 45) * 10;
	r0.x = r0.y = 0; // Posição inicial é zero
	write(arq, 0, 0);
	printf("\n\n0,1s com arraste");
	printf("DeltaT = %f\n", Ta);
	for(float i = Ta; i <= T; i += Ta){ //0.1 segundos
		a = aceleracao(v0);
		v = velocidade(a, v0, Ta);
		r = posicao(r0, v0, v, Ta);
		if(r.y < 0) break;
		printf("Instante = %f     ", i);
		printf("r=(%fi + %fj)m     ", r.x, r.y);
		printf("v=(%fi + %fj)m/s     ", v.x, v.y);
		printf("a=(%fi + %fj)m/s*s\n", a.x, a.y);
		fprintf(arq, "%f;%f\n", r.x, r.y);
		v0 = v;
		a0 = a;
		r0 = r;
	}
	fclose(arq);

	sim = 0;
	arq = fopen("0,01s com arraste.txt", "w");
	v0.x = cos(val * 45) * 10;
	v0.y = sin(val * 45) * 10;
	r0.x = r0.y = 0; // Posição inicial é zero
	write(arq, 0, 0);
	printf("\n\n0,01s com arraste");
	printf("DeltaT = %f\n", Tb);
	for(float i = Tb; i <= T; i += Tb){ //0.01 segundos
		a = aceleracao(v0);
		v = velocidade(a, v0, Tb);
		r = posicao(r0, v0, v, Tb);
		if(r.y < 0) break;
		printf("Instante = %f     ", i);
		printf("r=(%fi + %fj)m     ", r.x, r.y);
		printf("v=(%fi + %fj)m/s     ", v.x, v.y);
		printf("a=(%fi + %fj)m/s*s\n", a.x, a.y);
		fprintf(arq, "%f;%f\n", r.x, r.y);
		v0 = v;
		a0 = a;
		r0 = r;
	}
	fclose(arq);

	sim = 0;
	arq = fopen("0,1s sem arraste.txt", "w");
	v0.x = cos(val * 45) * 10;
	v0.y = sin(val * 45) * 10;
	a.x = a.y = 0;
	r0.x = r0.y = 0; // Posição inicial é zero
	write(arq, 0, 0);
	printf("\n\n0,1s sem arraste");
	printf("\nDeltaT = %f\n", Ta);
	for(float i = Ta; i <= T; i += Ta){ //0.1 segundos
		v = velocidade_N(r0, v0, Ta);
		r = posicao_N(r0, v0, Ta);
		if(r.x > 10) break;
		if(sim == 2) break;
		printf("Instante = %f     ", i);
		printf("r=(%fi + %fj)m     ", r.x, r.y);
		printf("v=(%fi + %fj)m/s     ", v.x, v.y);
		printf("a=(%fi + %fj)m/s*s\n", a.x, a.y);
		fprintf(arq, "%f;%f\n", r.x, r.y);
		v0 = v;
		v0.x = cos(val * 45) * 10;
		r0 = r;
	}
	fclose(arq);

	sim = 0;
	arq = fopen("0,01s sem arraste.txt", "w");
	v0.x = cos(val * 45) * 10;
	v0.y = sin(val * 45) * 10;
	a.x = a.y = 0;
	r0.x = r0.y = 0; // Posição inicial é zero
	write(arq, 0, 0);
	printf("\n\n0,01s sem arraste");
	printf("\nDeltaT = %f\n", Tb);
	for(float i = Ta; i <= T; i += Tb){ //0.1 segundos
		v = velocidade_N(r0, v0, Tb);
		r = posicao_N(r0, v0, Tb);
		if(r.x > 10) break;
		if(sim == 2) break;
		printf("Instante = %f     ", i);
		printf("r=(%fi + %fj)m     ", r.x, r.y);
		printf("v=(%fi + %fj)m/s     ", v.x, v.y);
		printf("a=(%fi + %fj)m/s*s\n", a.x, a.y);
		fprintf(arq, "%f;%f\n", r.x, r.y);
		v0 = v;
		v0.x = cos(val * 45) * 10;
		r0 = r;
	}
	fclose(arq);

	return 0;
}
