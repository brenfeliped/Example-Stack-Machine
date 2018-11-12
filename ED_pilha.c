#include <stdio.h>
#include <stdlib.h>
#include <string.h>
float vet_num[30];
char posfixa[50];

void avaliacao();

typedef struct elemento{
	char dado;
	float dado_float;
	struct  elemento * proximo;

}t_elemento;

typedef struct pilha{
	t_elemento * topo;

}t_pilha;
/*INICIO PILHA*/
t_pilha * criarPilha(){
	t_pilha * p =(t_pilha * )malloc(sizeof(t_pilha));
	p->topo=NULL;
	return p;
}
int Vazia(t_pilha * p){
	if(p->topo==NULL){
		return 0; /* se tiver vazia retorna 0*/
	}
	else{
		return 1;/* se nao estiver vazia retorrna 1 */
	}
}
void empilharFloat(float dado, t_pilha * p){
	t_elemento * novoElemento= (t_elemento *) malloc(sizeof(t_elemento));
	novoElemento->dado_float=dado;
	if(p->topo==NULL){
		p->topo=novoElemento;
		p->topo->proximo=NULL;
	}
	else{
		novoElemento->proximo=p->topo;
		p->topo=novoElemento;		
	}

}
void empilhar(char dado, t_pilha * p){
	t_elemento * novoElemento= (t_elemento *) malloc(sizeof(t_elemento));
	novoElemento->dado=dado;
	if(p->topo==NULL){
		p->topo=novoElemento;
		p->topo->proximo=NULL;
	}
	else{
		novoElemento->proximo=p->topo;
		p->topo=novoElemento;		
	}

}
float desempilharFloat(t_pilha * p){
	float retorno;
	t_elemento * removido;
	if(p->topo== NULL){
		return -1;
	}
	else{
		retorno=p->topo->dado_float;
		removido=p->topo;
		p->topo=p->topo->proximo;
	}
	free(removido);
	return retorno;
}
char desempilhar(t_pilha * p){
	char retorno;
	t_elemento * removido;
	if(p->topo== NULL){
		return -1;
	}
	else{
		retorno=p->topo->dado;
		removido=p->topo;
		p->topo=p->topo->proximo;
	}
	free(removido);
	return retorno;
}
/*FIM PILHA*/
int validar(t_pilha * p, char expre[]){
	int caracter,i=0,r;
	while(expre[i] != '\0'){
		caracter=expre[i];
		if(caracter>=40 && caracter<=57 && caracter!=46 && caracter!= 44){
			if(caracter==40){ /*ver se é ( para empilhar*/
				empilhar('(',p); 
			}else if(caracter == 41){
				r=desempilhar(p);
				if(r==-1){
					return 0; /*expressao invalida*/
				}
			}
		}else{
			return 0; /*0 para expressao invalida*/
		}
		i++;
	}
	caracter=expre[0];
	if(caracter>=42 && caracter<=45)return 0; /*Se a expressão não começa com sinal*/
	caracter=expre[i-1];/*verificar se o ultimo char da expre e um sinal*/
	if(caracter>=42 && caracter<=45){
		return 0;
	}
	r=Vazia(p);
	if(r==1){
		return 0; /* expressao invalida */
	}else{
		return 1; /*expressao valida*/
	}

}
int prioridade(char sinal){
	if(sinal=='+' || sinal=='-'){
		return 1;
	}
	else if(sinal=='/' || sinal=='*'){
		return 2;
	}
	return 0;
}
void guardarNumeros(char expre[]){
	int i=0,caracter,j=0,h=0;
	char aux[20];
	while(expre[i] != '\0'){
		caracter=expre[i];
		while(caracter>=48 && caracter<=57){
			aux[j]=expre[i];
			j++;
			i++;
			caracter=expre[i];
		}
		if(j!=0){
			aux[j]='\0';
			vet_num[h]=atof(aux);
			h++;
			j=0;
		}
		i++;
	}
}
void posFixa(char expre[]){
	t_pilha * pilha=criarPilha();
	int i=0, caracter, j=0, prio_p, prio, p_vazia;
	char aux_pos;
	while(expre[i] !='\0'){
		caracter=expre[i];
		if(caracter>=48 && caracter<=57){
			posfixa[j]=expre[i];
			j++;
		}
		else{
			if(caracter==41){ /*caso for )*/
				aux_pos=desempilhar(pilha);
				while(aux_pos!='('){
						posfixa[j]=aux_pos;
						j++;
					aux_pos=desempilhar(pilha);
				}
			}
			else{
				if(caracter==40){ /*caso for (*/
					empilhar(expre[i], pilha);
				}
				else{ /*caso for sinal*/
					do{
							p_vazia=Vazia(pilha);
							if(p_vazia==1){
								prio_p=prioridade(pilha->topo->dado);
								prio=prioridade(expre[i]);
								if(prio_p>=prio){
									aux_pos=desempilhar(pilha);
									posfixa[j]=aux_pos;
									j++;
								}
							}
							p_vazia=Vazia(pilha);
							if(p_vazia==1){
								prio_p=prioridade(pilha->topo->dado);
								prio=prioridade(expre[i]);
							}

                    }while(p_vazia==1 && prio_p>=prio);
					empilhar(expre[i],pilha);
				}
			}
		}
		i++;
	}
	p_vazia=Vazia(pilha);
	while(p_vazia == 1){ /* desmpilhar os sinais enquanto a pilha nao estive vazia */
		aux_pos=desempilhar(pilha);
		posfixa[j]=aux_pos;
		j++;
		p_vazia=Vazia(pilha);
	}
	posfixa[j]='\0';
	printf("Expressao posfixa: %s\n",posfixa);
	avaliacao();
}
int contDigitos(float valor){
	int count=0,valor_int;
	valor_int=valor;
	if(valor_int==0){
		count=1;
	}
	else{
		while(valor_int!= 0){
			count++;
			valor_int=valor_int/10;
		}
	}
	return count;
}
float calcular(float termo1, float termo2, char sinal){
	float resultado;
	switch(sinal){
		case '+' :
			resultado=termo1+termo2;
		break;
		case '-':
			resultado=termo1-termo2;
		break;
		case '*':
			resultado=termo1*termo2;
		break;
		case '/':
			resultado=termo1/termo2;
		break;
	}
	return resultado;
}
void avaliacao(){
	t_pilha * pilha=criarPilha();
	float termo1,termo2,aux_vet,resul;
	int i=0,j=0,caracter,count;
	while(posfixa[i] != '\0'){
		caracter=posfixa[i];
		if(caracter>=48 && caracter<=57){
			aux_vet=vet_num[j];
			empilharFloat(aux_vet,pilha);
			count=contDigitos(aux_vet);
			i=count+i;
			j++;
		}
		else{
			termo2=desempilharFloat(pilha);
			termo1=desempilharFloat(pilha);
			resul=calcular(termo1,termo2,posfixa[i]);
			empilharFloat(resul,pilha);
			i++;
		}
	}
	resul=desempilharFloat(pilha);
	printf("Resultado =  %.2f \n", resul);
}
int main(){
	char expre[50];
	int v;
	t_pilha * pilha=criarPilha();
	do{
		printf("======================================\n");
		printf("=======     CALCULADORA       ========\n");
		printf("======================================\n");
		printf("\n");
		printf("Digite a expressão: ");
		scanf("%s", expre);
		v=validar(pilha,expre);
		if(v==1){
			printf("Expressao válida\n");
			guardarNumeros(expre);
			posFixa(expre);
		}else{
			printf("Expressa inválida\n");
			printf("Digite novamente!!!\n");
		}
	}while(v!=1);
	return 0;
}