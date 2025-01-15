#include "process.h"
#include "struct.h"
#include "utils.h"

void InizializeCrocodileList(node **list,int stream,int y,int dir,int active){
    for (int i = 1; i <= MAX_N_CROCODILE; i++)
    {
        node *new=(node*)malloc(sizeof(node));
        if ((new==NULL))
        {
            puts("ERRORE:");
            exit(-1);
        }
        new->info.id=(stream*10)+i;
        //new->info.x_entity=dir;
        //new->info.x_bullet
        new->info.dir=dir;
        new->next=NULL;
        new->info.active=0;//non è ancora stato aseegnato a nessun processo

        if (*list==NULL)
        {
            *list=new;
            continue;
        }
        node *current=*list;
        while (current->next!=NULL)
        {
            current=current->next;
        }
        current->next=new;
    }
}

void AssignementProcessToCrocodile(node **list)