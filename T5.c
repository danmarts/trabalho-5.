#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define reset "\e[0m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGHB "\e[0;105m"
#include<time.h>


typedef struct Cell
{
        char piece;
        int colour;
        int activate;
}Cell;

typedef struct jogadores
{
        char *nome;
        int cores[8];
        char forma[8];
        int score;
}jogadores;
void LimpaBuffer()//Função para evitar problema de leitura de dados
{
        char c;
        while((c = getchar()) != '\n' && c != EOF);//Entra em um laço até que não possui nenhum residuo na area temporaria
}
void show_board(Cell **board, int LINES, int COLUMNS)
{
        for (int i = 0; i < LINES; ++i)
        {
                for (int j = 0; j < COLUMNS; ++j)
                {
                        if (i==0 && j==0)
                        {
                                printf("  ");
                        }
                        else if (i==0)
                        {
                                printf("   %i ", j);
                        }else if(j==0)
                        {
                                printf(" %i ", i);
                        }else{
                                if (board[i][j].activate)
                                {
                                        switch(board[i][j].colour)
                                        {
                                                case 0:
                                                printf(" "); 
                                                printf(REDHB"%c%d",board[i][j].piece, board[i][j].colour);
                                                printf(reset);
                                                printf(" |");
                                                break;

                                                case 1:
                                                printf(" "); 
                                                printf(GRNHB"%c%d",board[i][j].piece, board[i][j].colour);
                                                printf(reset);
                                                printf(" |");
                                                break;

                                                case 2:
                                                printf(" "); 
                                                printf(YELHB"%c%d",board[i][j].piece, board[i][j].colour);
                                                printf(reset);
                                                printf(" |");
                                                break;

                                                case 3:
                                                printf(" "); 
                                                printf(YELB"%c%d",board[i][j].piece, board[i][j].colour);
                                                printf(reset);
                                                printf(" |");
                                                break;

                                                case 4:
                                                printf(" "); 
                                                printf(BLUB"%c%d",board[i][j].piece, board[i][j].colour);
                                                printf(reset);
                                                printf(" |");
                                                break;

                                                case 5:
                                                printf(" "); 
                                                printf(MAGHB"%c%d",board[i][j].piece, board[i][j].colour);
                                                printf(reset);
                                                printf(" |");
                                                break;
                                        }
                                }else{
                                        printf("    |");
                                }
                        }
                }
                printf("\n");
                printf("   ");
                for (int k = 0; k < COLUMNS-1; ++k)
                {
                        printf("-----");
                }
                printf("\n");
        }
}
int check_hand(jogadores jogador,char x, int y){
  for(int i=0;i<6;i++){
    if(jogador.forma[i]==x){
      if(jogador.cores[i]==y){
        
        return i;
      }
    }
  }

return 10;
}
int valid_move(Cell **board, int x, int y, char forma, int cor, int ROW, int COL)
{
	if(board[x][y].activate==1)
	{
		return 0;
	}
	if(ROW==2 && COL==2)
	{
		if(x==1 && y==1)
		{
			return 1;
		}else{
			return 0;
		}
	}
	if((x==1 && y==1) || (x==COL-1 && y==ROW-1)||(x==1 &&y==ROW-1)||(x==COL-1 && y==ROW-1) )
	{
		return 0;
	}
	int i = y+1;
	while(board[x][i].activate!=0)
	{
		if(board[x][i].piece == forma && board[x][i].colour == cor)
		{
			return 0;
		}
		i++;
	}
	i = y-1;
	while(board[x][i].activate!=0)
	{
		if(board[x][i].piece == forma && board[x][i].colour == cor)
		{
			return 0;
		}
		i--;
	}
	i = x-1;
	while(board[i][y].activate!=0)
	{
		if(board[i][y].piece == forma && board[i][y].colour == cor)
		{
			return 0;
		}
		i--;
	}
	i = x+1;
	while(board[i][y].activate!=0)
	{
		if(board[i][y].piece == forma && board[i][y].colour == cor)
		{
			return 0;
		}
		i++;
	}
	if(board[x][y+1].activate==1 && board[x+1][y].activate==1)
	{
		if((board[x][y+1].piece == forma && board[x+1][y].piece == forma)||(board[x][y+1].colour == cor && board[x+1][y].colour == cor)||(board[x][y+1].piece == forma  && board[x+1][y].colour == cor)||(board[x+1][y].colour == cor  && board[x][y+1].piece == forma))
		{
			return 1;	
		}else{
			return 0;
		}
	}
	if(board[x][y-1].activate==1 && board[x-1][y].activate==1)
	{
		if((board[x][y-1].piece == forma && board[x-1][y].piece == forma)||(board[x][y-1].colour == cor && board[x-1][y].colour == cor)||(board[x][y-1].piece == forma  && board[x-1][y].colour == cor)||(board[x-1][y].colour == cor  && board[x][y-1].piece == forma))
		{
			return 1;	
		}else{
			return 0;
		}
	}
	if(board[x][y-1].activate==1 && board[x+1][y].activate==1)
	{
		if((board[x][y-1].piece == forma && board[x+1][y].piece == forma)||(board[x][y-1].colour == cor && board[x+1][y].colour == cor)||(board[x][y-1].piece == forma  && board[x+1][y].colour == cor)||(board[x+1][y].colour == cor  && board[x][y-1].piece == forma))
		{
			return 1;	
		}else{
			return 0;
		}
	}
	if(board[x][y+1].activate==1 && board[x-1][y].activate==1)
	{
		if((board[x][y+1].piece == forma && board[x-1][y].piece == forma)||(board[x][y+1].colour == cor && board[x-1][y].colour == cor)||(board[x][y+1].piece == forma  && board[x-1][y].colour == cor)||(board[x-1][y].colour == cor  && board[x][y+1].piece == forma))
		{
			return 1;	
		}else{
			return 0;
		}
	}
	if(board[x][y+1].piece==forma)
	{
		return 1;
	}else if(board[x][y-1].piece==forma)
	{
		return 1;
	}else if(board[x+1][y].piece==forma)
	{
		return 1;
	}else if(board[x-1][y].piece==forma)
	{
		return 1;
	}else if(board[x][y-1].colour==cor)
	{
		return 1;
	}else if(board[x][y+1].colour==cor)
	{
		return 1;
	}else if(board[x+1][y].colour==cor)
	{
		return 1;
	}else if(board[x-1][y].colour==cor)
	{
		return 1;
	}
	return 0;
}

int score(Cell **board,int x,int y){
   int score_shape=0;
   int score_color=0;
   int score_total=0;
   int i;
   i=0;
   while(board[x][y+i].activate!=0){
         
        if(board[x][y].piece==board[x][y+i].piece){
          score_shape++;
        }
        if(board[x][y].colour==board[x][y+i].colour){
          score_color++;
        }
        y++;
   }
   i=0;
  while(board[x][y-i].activate!=0){
         
        if(board[x][y].piece==board[x][y-i].piece){
          score_shape++;
        }
        if(board[x][y].colour==board[x][y-i].colour){
          score_color++;
        }
        i++;
   }
   i=0;
   while(board[x+i][y].activate!=0){
         
        if(board[x][y].piece==board[x+i][y].piece){
          score_shape++;
        }
        if(board[x][y].colour==board[x+i][y].colour){
          score_color++;
        }
        x++;
   }
 
 i=0;
  while(board[x-i][y].activate!=0){
      
        if(board[x][y].piece==board[x-i][y].piece){
          score_shape++;
        }
        if(board[x][y].colour==board[x-i][y].colour){
          score_color++;
        }
        x--;
   }
 if(score_shape!=0){
   score_shape++;
 }
 if(score_color!=0){
   score_color++;
 }
 if(score_color==6){
   score_color=score_color+6;
 }
 if(score_shape==6){
   score_shape=score_shape+6;
 }
 score_total= score_shape+score_color;
 return score_total;
}






int make_move(Cell ***board, int *ROWS, int *COL, jogadores *jogador)
{
	int x, y, color;
        char forma;
	int cor;
        printf("Digite a coordenada em que deseja jogar X Y\n");
        scanf("%i %i", &x,&y);
        printf("Digite a peca (A B)\n");
        scanf (" %c", &forma);
        getchar();
        scanf ("%i",&cor);
        getchar();
	while( check_hand(*jogador, forma, cor)==10 || valid_move(*board,x,y, forma, cor,*ROWS, *COL)==0)
	{
		printf("\n#INVALID MOVEMENT#\n");
		printf("Digite a coordenada em que deseja jogar X Y\n");
		scanf("%i %i", &x,&y);
		printf("Digite a peca (A B)\n");
		scanf (" %c", &forma);
		getchar();
		scanf ("%i",&cor);
		getchar();
	}
		(*board)[x][y].colour = cor;
		(*board)[x][y].piece = forma;
		(*board)[x][y].activate = 1;
		(*jogador).score += score(*board,x,y);
		if(*ROWS==2 && *COL==2)
		{
			*ROWS+=2;
			Cell **tmp = (Cell**) realloc((*board), (*ROWS)*sizeof(Cell*));
			if(tmp){
				(*board) = tmp;
			}
			*COL+=2;
			for(int i = 0; i<*ROWS; i++)
			{
				if(i<=1){
					Cell *tmp = (Cell*) realloc((*board)[i], (*COL)*sizeof(Cell));
					if(tmp)
					{
						(*board)[i] = tmp;	
					}
				}else{
					Cell *tmp = (Cell*) malloc((*COL)*sizeof(Cell));
					if(tmp)
					{
						(*board)[i] = tmp;	
					}
				}
			}
			for (int i = *COL-2; i >= 1; --i)
			{
				for (int j = *ROWS-2; j >= 1; --j)
				{
					(*board)[j+1][i+1].piece = (*board)[j][i].piece;
					(*board)[j+1][i+1].colour = (*board)[j][i].colour;
					(*board)[j+1][i+1].activate= (*board)[j][i].activate;
				}
			}
		}else if(x==1 && y==1)
		{
			*COL+=1;
			for(int i = 0; i<*ROWS; i++)
			{
				Cell *tmp = (Cell*) realloc((*board)[i], (*COL)*sizeof(Cell));
				if(tmp)
				{
					(*board)[i] = tmp;	
				}
			}
			*ROWS+=1;
			Cell **tmp = (Cell**) realloc((*board), (*ROWS)*sizeof(Cell*));
			(*board) = tmp;
			for(int i = *ROWS-1; i<*ROWS; i++)
			{

				Cell *tmp = (Cell*) malloc((*COL)*sizeof(Cell));
				if(tmp)
				{
					(*board)[i]=tmp;
				}
			
			}
			for (int i = *COL-2; i >= 1; --i)
			{
				for (int j = *ROWS-2; j >= 1; --j)
				{
					(*board)[j+1][i+1].piece = (*board)[j][i].piece;
					(*board)[j+1][i+1].colour = (*board)[j][i].colour;
					(*board)[j+1][i+1].activate= (*board)[j][i].activate;
				}
			}
		}else if(x==*COL-1 && y==1)
		{
			*COL+=1;
			for(int i = 0; i<*ROWS; i++)
			{
				Cell *tmp = (Cell*) realloc((*board)[i], (*COL)*sizeof(Cell));
				if(tmp)
				{
					(*board)[i] = tmp;	
				}
			}

			*ROWS+=1;
			Cell **tmp = (Cell**) realloc((*board), (*ROWS)*sizeof(Cell*));
			(*board) = tmp;
			for(int i = *ROWS-1; i<*ROWS; i++)
			{

				Cell *tmp = (Cell*) malloc((*COL)*sizeof(Cell));
				if(tmp)
				{
					(*board)[i]=tmp;
				}
			
			}
			for (int i = *COL-2; i >= 1; --i)
			{
				for (int j = *ROWS-2; j >= 1; --j)
				{
					(*board)[j][i+1].piece = (*board)[j][i].piece;
					(*board)[j][i+1].colour = (*board)[j][i].colour;
					(*board)[j][i+1].activate= (*board)[j][i].activate;
				}
			}
		}else if(x==*COL-1 && y==*ROWS-1)
		{
			*COL+=1;
			for(int i = 0; i<*ROWS; i++)
			{
				Cell *tmp = (Cell*) realloc((*board)[i], (*COL)*sizeof(Cell));
				if(tmp)
				{
					(*board)[i] = tmp;	
				}
			}

			*ROWS+=1;
			Cell **tmp = (Cell**) realloc((*board), (*ROWS)*sizeof(Cell*));
			(*board) = tmp;
			for(int i = *ROWS-1; i<*ROWS; i++)
			{

				Cell *tmp = (Cell*) malloc((*COL)*sizeof(Cell));
				if(tmp)
				{
					(*board)[i]=tmp;
				}
			
			}
		}else if(x==1 && y==*ROWS-1)
		{
			*COL+=1;
			for(int i = 0; i<*ROWS; i++)
			{
				Cell *tmp = (Cell*) realloc((*board)[i], (*COL)*sizeof(Cell));
				if(tmp)
				{
					(*board)[i] = tmp;	
				}
			}

			*ROWS+=1;
			Cell **tmp = (Cell**) realloc((*board), (*ROWS)*sizeof(Cell*));
			(*board) = tmp;
			for(int i = *ROWS-1; i<*ROWS; i++)
			{

				Cell *tmp = (Cell*) malloc((*COL)*sizeof(Cell));
				if(tmp)
				{
					(*board)[i]=tmp;
				}
			
			}
			for (int i = *COL-2; i >= 1 ; --i)
			{
				for (int j = *ROWS-2; j >= 1; --j)
				{
					(*board)[j][i].piece = (*board)[j-1][i].piece;
					(*board)[j][i].colour = (*board)[j-1][i].colour;
					(*board)[j][i].activate= (*board)[j-1][i].activate;
				}
			}

		}else if(x == *ROWS-1)
		{
			*ROWS+=1;
			Cell **tmp = (Cell**) realloc((*board), (*ROWS)*sizeof(Cell*));
			*board = tmp;
			(*board)[*ROWS-1] = (Cell*) malloc((*COL)*sizeof(Cell));
		}else if(x==1)
		{
			*ROWS+=1;
			Cell **tmp = (Cell**) realloc((*board), (*ROWS)*sizeof(Cell*));
			*board = tmp;
			(*board)[*ROWS-1] = (Cell*) malloc((*COL)*sizeof(Cell));
			for (int i = *COL-2; i >= 1 ; --i)
			{
				for (int j = *ROWS-2; j >= 1; --j)
				{
					(*board)[j][i].piece = (*board)[j-1][i].piece;
					(*board)[j][i].colour = (*board)[j-1][i].colour;
					(*board)[j][i].activate= (*board)[j-1][i].activate;
				}
			}
		}else if(y==*COL-1)
		{
			*COL+=1;
			for(int i = 0; i<*ROWS; i++)
			{
				Cell *tmp = (Cell*) realloc((*board)[i], (*COL)*sizeof(Cell));
				if(tmp)
				{
					(*board)[i] = tmp;	
				}
			}
		}else if(y==1)
		{
			*COL+=1;
			for(int i = 0; i<*ROWS; i++)
			{
				Cell *tmp = (Cell*) realloc((*board)[i], (*COL)*sizeof(Cell));
				if(tmp)
				{
					(*board)[i] = tmp;	
				}
			}
			for (int i = *COL-2; i >= 1; --i)
			{
				for (int j = *ROWS-2; j >= 1; --j)
				{
					(*board)[j][i+1].piece = (*board)[j][i].piece;
					(*board)[j][i+1].colour = (*board)[j][i].colour;
					(*board)[j][i+1].activate= (*board)[j][i].activate;
				}
			}
		}
		for (int i = 0; i < *COL; ++i)
		{
			for (int j = 0; j < *ROWS; ++j)
			{
				if(i==1 || j==1 ||i==*COL-1||j==*ROWS-1|| i==0 || j==0)
				{
					(*board)[j][i].activate = 0;
				}
			}
		}
  int l =check_hand(*jogador, forma, cor);
  return l;  
}

void colorir(jogadores jogador){
  for(int i=0;i<6;i++){
      switch(jogador.cores[i]){
             case 0:
             printf(REDHB"%c%d",jogador.forma[i],jogador.cores[i]);
             printf(reset);
             break;

             case 1:
             printf(GRNHB"%c%d",jogador.forma[i],jogador.cores[i]);
             printf(reset);
             break;

             case 2:
             printf(YELHB"%c%d",jogador.forma[i],jogador.cores[i]);
             printf(reset);
             break;

             case 3:
             printf(YELB"%c%d",jogador.forma[i],jogador.cores[i]);
             printf(reset);
             break;

             case 4:
             printf(BLUB"%c%d",jogador.forma[i],jogador.cores[i]);
             printf(reset);
             break;

             case 5: 
             printf(MAGHB"%c%d",jogador.forma[i],jogador.cores[i]);
             printf(reset);
             break;
     }
     printf(" ");
  }
}

int  check(int color, char Lsize){
      FILE *arq;
      arq=fopen("peca.txt","r");

      int c;
      char comp;
      int quant;
      while(fscanf(arq,"%c %d %d\n", &comp, &c, &quant )!=EOF){
            if (c==color){
                  if(Lsize==comp){
                        if (quant==3){
                               fclose(arq);
                               return 2;
                       }
                       fclose(arq);
                       return 1;

               }
       }}
       fclose(arq); 
       return 0;

}

void erase(int line){

        FILE *file1 = fopen("peca.txt", "r");
        FILE *file2 = fopen("temp.txt", "w");
        
        int contador = 0;
        char leitor[1000];

        while(fgets(leitor,1000,file1) != NULL){
                contador++;

                if(contador != line){
                        fputs(leitor,file2);
                }
        }

        fclose(file1);
        fclose(file2);
        remove("peca.txt");
        rename("temp.txt", "peca.txt");
}

void change_piece(int color,char Lsize,int n){
     FILE *change;
     change=fopen("peca.txt","r+");
     char comp;
     int c;
     int quant;
     int line=0;
     while(fscanf(change,"%c %d %d\n", &comp, &c, &quant )!=EOF){
           line++;
           if (c==color){
                  if(Lsize==comp){
                        if(n==1){
                                quant++;}
                                if(n==2){
                                        quant--;
                                }


                                erase(line);
                                fclose(change);        
                                change = fopen("peca.txt", "a");
                                fprintf(change, "%c %d %d\n", comp, c, quant);       


                        }
                }
        }
        fclose(change);

}

void add_piece(int color, char Lsize){
      FILE *add;
      add= fopen("peca.txt","a");

      fprintf(add,"%c %d 1\n",Lsize ,color);
      fclose(add);
}





void pecas(int n, jogadores *jogador){
        FILE *beggin;
        beggin=fopen("peca.txt","a");
        fclose(beggin);
        int color;
        char Lsize;

        int i;
        int a;

                color=rand()%6;
                Lsize=rand()%6+65;
                a =check(color,Lsize);
                while(a==2){
                    color=rand()%6;
                    Lsize=rand()%6+65;


                   a=check(color,Lsize);
                } 
                if(a==0){
                      add_piece(color,Lsize);
                }
                if(a==1){
                      change_piece(color,Lsize,1);
                }
                jogador->forma[n]=Lsize;
                jogador->cores[n]=color;
                printf(" ");
                
      
}


int troca(jogadores jogador){
        
        int a;
        char b;
        int i;
        scanf("%c",&b);
        getchar();
        scanf("%d",&a);
        getchar();
        int tem=check_hand(jogador,b,a);
        if (tem!=10){
        
        change_piece(a,b,2);
        
              
              }
              
      

 return tem;    
}

/////////////////////////////////////////////////
   

////////////////////////////////////////////////////


int main(int argc, char const *argv[])
{
	int ROWS = 2, COL=2;
	Cell **board = (Cell**) malloc(sizeof(Cell*)*ROWS);
	for (int i = 0; i < ROWS; i++) {
    		board[i] = (Cell*) malloc(sizeof(Cell)*COL);
	}
	for (int i = 0; i < COL; ++i)
        {
                for (int j = 0; j < ROWS; ++j)
                {
                        if(i==1 || j==1 || i==COL-1 || j==ROWS-1 || i==0 || j==0)
                        {
                                board[i][j].activate = 0;
                        }
                }
        }
        printf("#################\n");
        printf("##             ##\n");
        printf("##   QWIRKLE   ##\n");
        printf("##             ##\n");
        printf("#################\n\n\n");
        int num_jogadores;
        printf("Digite o numero de jogadores:\n");
        scanf("%i", &num_jogadores);

        jogadores *jogador = (jogadores *) malloc(num_jogadores*sizeof(jogadores));
        char nome[100];

        LimpaBuffer();
        for (int i = 0; i < num_jogadores; ++i) {
                printf("Nome do jogador #%i\n", i+1);
                fgets(nome, 100, stdin);
                int l = strlen(nome);
                jogador[i].nome = (char* ) malloc(sizeof(char)*(l+1));
                strcpy(jogador[i].nome, nome);   
		jogador[i].score = 0;
        }
        int j;
        int cont=0;
        for (int i = 0; i < num_jogadores; ++i)
        {
          for(j=0;j<6;j++){
                pecas(j, &jogador[i]);
                cont=cont+1;
         }
          }
        printf("\n");
        int jogou=1;
        int escolha;
        while(cont<108){
                for (int i = 0; i < num_jogadores; ++i)
                {
			int flag = 0;
			while(flag ==0){
		         for(int l = 0;l< num_jogadores;l++){
                          printf("\nPecas de %s  ",jogador[l].nome);
			  printf("Pontuacao: %i\n", jogador[l].score);
                          colorir(jogador[l]);
                                      }
                       printf("\n--------------------------\n\n");
                        show_board(board, ROWS, COL);
                        printf("Vez de %s",jogador[i].nome);
                        printf("Suas pecas : ");
                        colorir(jogador[i]);
                        printf("\n");

                        printf("(1) - jogar\n(2) - trocar\n(3) - passar\n------------------------------\n opcao: ");
                        scanf("%d" ,&escolha);
                        if (escolha==1){
                        int k =make_move(&board, &ROWS, &COL, &jogador[i]);
                        pecas(k,&jogador[i]);
                        cont=cont+1;   
                        }
                        if (escolha==2 && jogou==1){
                          int Ntroca;
                          printf("quantas peças deseja trocar? ");
                          scanf("%d",&Ntroca);
                          getchar();
                          for(int l=1;l<=Ntroca;l++){
                            printf("Qual a %d peca? ",l);
                            int trade=troca(jogador[i]);
                              pecas(trade,&jogador[i]);
                           
                              
                        } 
                         
                        }
                        system("clear");
			if(escolha == 2 || escolha ==3)
			{
				flag =1;
			}
			} 
                        if (cont==108)
                        {
                                break;
                        }
                }
        }

        free(board);
        return 0;
}

