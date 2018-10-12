#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define pedcabeca 'O'
#define pedcorp '*'
#define peddoce '#'

int shara=10; //VARIAVEL GLOBAL

struct local{    //struct local
       int posicx;
       int posicy;
};

void preenchercabeca(struct local *pont){      //Preenher base corpo
    for(int i=0;i<3;++i){
    	(pont+i)->posicx=0;
        (pont+i)->posicy=i;
    }
}

void preencherdoce(struct local *pont){         //Preencher base doce
    pont->posicx=5;
    pont->posicy=0;
}



void mostramatrizcampo(char matriz[10][10],struct local *pont,struct local *doce,int tam,int p){
	printf("Pontuacao: %d\n",p);
	for(int i=0;i<10;i++){			//Preenchendo a matriz
        for(int j=0;j<10;j++){                 
            matriz[i][j]=' ';      
        }
    }
    for(int n=0;n<tam;n++){                                              //Irá rodar para colocar as define em suas posições
        for(int x=0;x<shara;x++){
            for(int y=0;y<shara;y++){                     
                if(((pont+n)->posicx == x) && ((pont+n)->posicy == y)){
                    if(n==0){
                        matriz[x][y] = pedcabeca;          
                    }
                    else{
                        matriz[x][y] = pedcorp;         
                    }                                 
                }                                             
            }
        }
    }
    for(int x=0;x<shara;x++){
        for(int y=0;y<shara;y++){                     
        	if((doce->posicx == x) && (doce->posicy == y)){
                matriz[x][y] = peddoce;                                
            }                                             
        }
     }   
    for(int x=0;x<10;x++){					//Colocando os Paramêtros
        printf("|");
        for(int y=0;y<10;y++){                     
            printf("%c",matriz[x][y]);                                           
        }
        printf("|\n");
    }    
}

void salvaposicao(struct local *pont,struct local *save){	// Salva a posição antes de se mover
    save->posicx = pont->posicx;					
    save->posicy = pont->posicy;    
}

void attposicao(struct local *pont,struct local *save,int tam){ //Atualiza a Posição
    for(int i=1;i<tam;i++){
        (pont+i)->posicx = (save+(i-1))->posicx;          
        (pont+i)->posicy = (save+(i-1))->posicy;
	}         
}

int mudadoce(struct local *doce,struct local *pont,int tam){ //Randomiza o doce
    srand(time(NULL));
    int z=0;
    int y=1;
    while(y){
    	int x=0;  
    	doce->posicx = rand()%shara;                                       
    	doce->posicy = rand()%shara;                                      
    	for(int i=0;i<tam;i++){ 
        	if(((doce->posicx) == ((pont+i)->posicx) && (doce->posicy) == ((pont+i)->posicy))){         
           		x++;
				z++;
				if(z==100000000000){
					system("cls");
					printf("Melhor de todos os tempos!!!\nE nem chamou a mae.\nMito.\nVai jogar mais nao.\nAgora tu vai chamar, né?.\nChama la to esperando.\n");
					return 0;
				}          
        	}
    	}
    	if(x==0){
       		y=0;
    	}
    }
}

int gameover(struct local *pont,int tam){
    int x=0;
    for(int i=1;i<tam;i++){ 
        if(((pont->posicx) == ((pont+i)->posicx) && (pont->posicy) == ((pont+i)->posicy))){ 	//se ela se bate               
            x++;        
        }
	}
    if(((pont->posicx)<0 || (pont->posicy)<0 || (pont->posicx)>9 || (pont->posicy)>9)){		//se ela bater na parede
    	x++;
	}
      	
    if(x>0){	//colidiu	  
        return(0);
    }
    else{
        return(1);
    }	       
}

int Verifica(struct local *a){		// Verifica se há alocação 
    if(a==NULL){
        puts("Erro de alocação posicao do corpo");
        return 0;      
    }
    else{
    	return 1;
	}  
}

void menu(){
	puts("1.NEW GAME");
	puts("2.LOAD GAME");
	puts("3.RANKING");
	puts("4.EXIT");
}

int main(){
	// Variavel
	char control,matrizcampo[10][10],nome[100];
    int es,n,time=1,cont=0,tam=3,pont=0,ran=1,op;
	// Structs do Jogo  
    struct local *minhoca;
    struct local *save;
    struct local *doce;
    // Alocando e verificando
    minhoca=(struct local*) malloc(sizeof(struct local)*tam);         
	if(Verifica(minhoca)==0){return 0;};                                    
	save=(struct local*) malloc(sizeof(struct local)*tam);             
	if(Verifica(save)==0){return 0;};
	doce=(struct local*) malloc(sizeof(struct local)*1);               
	if(Verifica(doce)==0){return 0;};
    while(1){
		if(cont==0){
    		menu();
    		scanf("%d",&es);
    		while(es>4){		//enquanto o usuario teclar errado
       			system("cls");
       			menu();
       			puts("Comando invalido!");
       			scanf("%d",&es);
			}
			switch(es){
    			case 1:
    				system("cls");
					// Removendo se tiver algo
					remove("cobra.txt");
					if((Verifica(minhoca)==1)||(Verifica(save)==1)||(Verifica(doce)==1)){  
	    				free(minhoca);    
						free(save);     
						free(doce);
					}
					tam=3;
				    minhoca=(struct local*) malloc(sizeof(struct local)*tam);    //Alocando denovo     
				    if(Verifica(minhoca)==0){return 0;};                                    
				    save=(struct local*) malloc(sizeof(struct local)*tam);             
				    if(Verifica(save)==0){return 0;};
				    doce=(struct local*) malloc(sizeof(struct local)*1);               
				    if(Verifica(doce)==0){return 0;};
				    // Preenchendo as base
				    preencherdoce(doce);
				    preenchercabeca(minhoca);
    				mostramatrizcampo(matrizcampo,minhoca,doce,tam,pont); 
    				cont++;
    				break; 
    			case 2:
					system("cls");
    				FILE *load;
					load=fopen("cobra.txt","r");
					if(load==NULL){			//Verifica se há algum arquivo
						puts("Save? Nao Existe.");
						break;
					}
					free(minhoca);    //Limpa a memoria 
					free(save);     
					free(doce);
					fscanf(load,"%d",&tam);
					minhoca =(struct local*) malloc(sizeof(struct local)*tam);		//Aloca denovo
					if(Verifica(minhoca)==0){return 0;};	
					save =(struct local*) malloc(sizeof(struct local)*tam);
					if(Verifica(save)==0){return 0;};
					doce =(struct local*) malloc(sizeof(struct local)*1);
					if(Verifica(doce)==0){return 0;};
					for(int i=0;i<tam;i++){										//Ler os arquivos
						fscanf(load,"%d",&(minhoca+i)->posicx);
						fscanf(load,"%d",&(minhoca+i)->posicy);
					}
					for(int j=0;j<tam;j++){
						fscanf(load,"%d",&(save+j)->posicx);
						fscanf(load,"%d",&(save+j)->posicy);
					}
					fscanf(load,"%d",&time);
					fscanf(load,"%d",&doce->posicx);
					fscanf(load,"%d",&doce->posicy);
					fclose(load);
					mostramatrizcampo(matrizcampo,minhoca,doce,tam,pont); 
					cont++;
					break;
				case 3:			//Ranking
					system("cls");
					FILE *ranking;
					ranking=fopen("ranking.txt","r");
					char frase[1000];
					while(fgets(frase, 1000, ranking) != NULL){
						printf("%s", frase);
					}
					op=getch();
					system("cls");
					break;
    			case 4:
    				system("cls");
					puts("TCHAU!!!");
					return 0;
					break;
			}
		}
		if(cont>0){ 
	       	control=getch();
	       	if((control == 'q')||(control == 'a')||(control == 's')||(control == 'd')||(control == 'w')||(control == 'r')){  
	         	if(time==8){
	              	mudadoce(doce,minhoca,tam);
					if( mudadoce(doce,minhoca,tam)==0){return 0;} 
	              	time=0;     
	         	}
	         	save= (struct local*) realloc(save,sizeof(struct local)*(tam));
	        	if(Verifica(save)==0){return 0;};   
	            for(int i=0;i<tam;i++){
	                salvaposicao((minhoca+i),(save+i));
	            }
	        	switch(control){		//movimento da cabeça
	            	case 's':              
	               		minhoca->posicx = minhoca->posicx+1;                               
	              		break;                                       
	            	case 'w':
	                	minhoca->posicx = minhoca->posicx-1;
	              		break;
	            	case 'd':              
	                	minhoca->posicy = minhoca->posicy+1;   
	              		break;
	            	case 'a':           
	                	minhoca->posicy = minhoca->posicy-1;
	              		break;
	            	case 'q':
	                	cont=0;
	                	system("cls");
	              		break;
	            	case 'r':
	            		FILE *load;				//Colocando as variveis no arquivo
						load=fopen("cobra.txt","w");
						fprintf(load,"%d ",tam);
						for(int i=0;i<tam;i++){
							fprintf(load," %d", (minhoca+i)->posicx);
							fprintf(load," %d", (minhoca+i)->posicy);
						}
						for(int i=0;i<tam;i++){
							fprintf(load," %d", (save+i)->posicx);
							fprintf(load," %d", (save+i)->posicy);
						}
						fprintf(load," %d",time);
						fprintf(load," %d",(doce)->posicx);
						fprintf(load," %d",(doce)->posicy);
						fclose(load);
						system("cls");
			    		mostramatrizcampo(matrizcampo,minhoca,doce,tam,pont);
						puts("Jogo Salvo");
	            		break;
	        	}
	        	if(gameover(minhoca,tam)==0){
	        		system("cls");
	        		printf("Se Lascou!!.\nChama tua mae agora.\n""Digite seu nome: ");
					scanf("%s",nome);
					FILE *ranking=fopen("ranking.txt","a");
					fprintf(ranking,nome,":");
					fprintf(ranking,":");
					fprintf(ranking," %d\n",pont);
					fclose(ranking);
	        		op=getch();
					system("cls");
	           	 	cont=0;
	           	 	pont=0;
	        	};
	        	if((minhoca->posicx == doce->posicx) && (minhoca->posicy == doce->posicy)){  // Se comer o doce
	        		if(time==7){
	        			pont=pont + 5;
					}
					else{
						pont=pont+2;
					}
			    	attposicao(minhoca,save,tam);
			        time=1;
			        tam++;                                                           
			        minhoca = (struct local*) realloc(minhoca,sizeof(struct local)*(tam));    
			        if(Verifica(minhoca)==0){return 0;};                       
			        (minhoca+(tam-1))->posicx = (save+(tam-2))->posicx;
					(minhoca+(tam-1))->posicy = (save+(tam-2))->posicy;                                      
			        mudadoce(doce,minhoca,tam);          
			        system("cls");
			        mostramatrizcampo(matrizcampo,minhoca,doce,tam,pont); 
	    		}                                                               
			    else{		// Se não comer arrasta o corpo
					if((control!='r')&&(control!='q')&&(gameover(minhoca,tam)==1)){
						time++;
			    		attposicao(minhoca,save,tam);
						system("cls");
			    		mostramatrizcampo(matrizcampo,minhoca,doce,tam,pont);
						if(time==7){
	        				puts("Special Candy");
						} 
					}  
			    }
	       }
	       else{
	            system("cls");
	            mostramatrizcampo(matrizcampo,minhoca,doce,tam,pont); 
	            printf("Para mover-se, pressione a,s,d,w.\nPara sair pressione q.\nPara salvar pressione r.");
	       }
	    }
	}
    free(save);
	free(minhoca);
	free(doce);
}
