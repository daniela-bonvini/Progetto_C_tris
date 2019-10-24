/****************************/
/* PROGRAMMA GIOCO DEL TRIS */
/****************************/


/*****************************/
/* inclusione delle librerie */
/*****************************/
#include <stdio.h>
#include <stdbool.h>


/********************************/
/* dichiarazione delle funzioni */
/********************************/
void stampa_matrice(char[][3]);


/************************/
/* definizione funzioni */
/************************/

/* definizione funzione main */
int main(void)
{
    /* dichiarazione delle variabili locali alla funzione */
    char matrice[3][3] = {                  /* output: matrice di gioco 3x3 */
                            {'1', '2', '3'},
                            {'4', '5', '6'},
                            {'7', '8', '9'}
                         };
    int coordinate[9][2] = {                /* lavoro: array per conversione input utente in coordinate della matrice */
                            {0,0}, {0,1}, {0,2},
                            {1,0}, {1,1}, {1,2},
                            {2,0}, {2,1}, {2,2}
                         };
    int turno = 0;                          /* lavoro: segna il turno corrente della partita */
    int vittoria = 0;                       /* lavoro: indica se c'è una condizione per la vittoria */
    int input_posizione;                    /* input: salva la posizione in cui l'utente desidera mettere il simbolo */
    int posizioneX = 0,                     /* lavoro: salva le coordinate x e y convertite dall'input dell'utente */
        posizioneY = 0;
    int esito_lettura;                      /* lavoro: salva il valore della funzione scanf() */
    int i;                                  /* lavoro: indicizza i cicli di controllo della vittoria */
    char simbolo;                           /* lavoro: segna il simbolo corrente da inserire nella matrice di gioco */
    char carattere_rimosso;                 /* lavoro: salva il valore della funzione getchar() */
    bool validazione_positiva;              /* lavoro: salva l'esito del ciclo di valutazione dell'input */


    /* stampa la matrice iniziale */
    stampa_matrice(matrice);

    while (turno < 9 && vittoria == 0)
    {
        /* aggiorna il simbolo da inserire nella matrice con X se il turno è pari e con Y se il turno è dispari */
        simbolo = (turno % 2 == 0? 'X': 'O');

        /* effettua una validazione stretta dell'input */
        do
        {
            printf("Indica dove vuoi inserire %c: \n",
                   simbolo);
            esito_lettura = scanf("%d",
                                  &input_posizione);

            /* se l'input inserito è un carattere o un numero minore di 1 o un numero maggiore di 9 */
            if (esito_lettura != 1 || input_posizione < 1 || input_posizione > 9)
            {
                validazione_positiva = false;
                printf("Input inserito non valido, inserisci un numero intero compreso tra 1 e 9.\n");
            }
            else
            {
                /* converte l'input dell'utente in coordinate x e y */
                posizioneX = coordinate[input_posizione-1][0];
                posizioneY = coordinate[input_posizione-1][1];

                /* controlla che la posizione inserita non sia già occupata */
                if (matrice[posizioneX][posizioneY] == 'X' || matrice[posizioneX][posizioneY] == 'O')
                {
                    validazione_positiva = false;
                    printf("Quella posizione è già occupata, inserisci nuovamente le coordinate.\n");
                }
                else
                {
                    validazione_positiva = true;
                }
            }
            /* svuota il buffer dagli input precedenti */
            do
            {
                carattere_rimosso = getchar();
            } while (carattere_rimosso != '\n');

        } while (!validazione_positiva);

        /* aggiorna la matrice di gioco in base all'input ricevuto */
        matrice[posizioneX][posizioneY] = simbolo;

        /* stampa a schermo la matrice aggiornata */
        stampa_matrice(matrice);

        /* inizia a eseguire il controllo per l'eventuale vittoria dal turno 5 in poi */
        if (turno > 3)
        {
            /* controllo vittoria sulle righe */
            for(i = 0; i < 3; i++)
            {
                if (matrice[i][0] == matrice[i][1] && matrice[i][1] == matrice[i][2])
                {
                    printf("C'e' un tris sulla riga. Vince il giocatore col simbolo %c!\n", simbolo);
                    vittoria = 1;
                }
            }

            /* controllo vittoria sulle colonne */
            for(i = 0; i < 3; i++)
            {
                if (matrice[0][i] == matrice[1][i] && matrice[1][i] == matrice[2][i])
                {
                    printf("C'e' un tris sulla colonna. Vince il giocatore col simbolo %c!\n", simbolo);
                    vittoria = 1;
                }
            }

            /* controllo vittoria sulle diagonali */
            {
                if ( (matrice[0][0] == matrice[1][1] && matrice[1][1] == matrice[2][2]) ||
                     (matrice[0][2] == matrice[1][1] && matrice[1][1] == matrice[2][0]) )
                {
                    printf("C'e' un tris sulla diagonale. Vince il giocatore col simbolo %c!\n", simbolo);
                    vittoria = 1;
                }
            }
        }
    turno++;
    }

    /* in caso di parità */
    if (turno == 9 && vittoria == 0)
    {
        printf("La partita è finita in parità.\n");
    }
return(0);
}

/* definizione della funzione per stampare a schermo la matrice di gioco */
void stampa_matrice(char matrice_temp[][3])
{
    /* dichiarazione delle variabili locali alla funzione */
    int i, j;

    /* ciclo per stampare le righe */
    for (i = 0; i < 3; i++)
    {
        /* ciclo per stampare le colonne */
        for(j = 0; j < 3; j++)
        {
            printf("%c ", matrice_temp[i][j]);
            if (j == 0 || j == 1)
            {
                printf("| ");
            }
        }
    printf("\n");
    }
}