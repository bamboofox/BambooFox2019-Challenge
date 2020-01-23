#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

struct note {
    char* ctx;
    size_t sz;
    int in_use;
};

struct note note[8];

int read_int(){
    char buf[8];
    int ret = read(0, buf, 7);
    buf[ret] = 0;
    return atoi(buf);
}

void create(){
    unsigned i = 0, sz = 0;
    for(i=0; i<8 && note[i].in_use ; i++);
    if(i >= 8){
        puts("No empty note");
        return;
    }
    printf("Input size: ");
    sz = read_int();
    if (sz > 0x400){
        puts("Must less than 0x400");
        return;
    }
    note[i].in_use = 1;
    note[i].ctx = calloc(1, sz);
    note[i].sz = sz;
}

void show(){
    unsigned i;
    printf("Input idx: ");
    i = read_int();
    if (i >= 8 || !note[i].in_use){
        puts("Out of bound");
        return;
    }else{
        write(1, note[i].ctx, note[i].sz);
    }
}

void copy(){
    unsigned i,j,k;
    
    printf("Source idx: ");
    i = read_int();
    printf("Destination idx: ");
    j = read_int();
    
    if (i >= 8 || !note[i].in_use || j>=8 || !note[j].in_use ){
        puts("Out of bound or note is not exist");
        return;
    }
    
    k = snprintf(note[j].ctx ,note[j].sz, "%s", note[i].ctx);
    note[j].sz = k;

}

void edit(){
    unsigned i;
    printf("Input idx: ");
    i = read_int();
    if (i >= 8 || !note[i].in_use ){
        puts("Out of bound or note is not exist");
        return;
    }else{
        printf("Your context: ");
        read(0, note[i].ctx, note[i].sz-1);
    }
}

void delete(){
    unsigned i;
    printf("Input idx: ");
    i = read_int();
    if (i >= 8 || !note[i].in_use ){
        puts("Out of bound or note is not exist");
        return;
    }else{
        free(note[i].ctx);
        note[i].ctx = NULL;
        note[i].in_use = 0;
        note[i].sz = 0;
    }

}

void init(){
    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);
    setvbuf(stderr, 0, _IONBF, 0);
}

void menu(){
    puts("*********************");
    puts("* 1. Create note    *");
    puts("* 2. Edit note      *");
    puts("* 3. Show note      *");
    puts("* 4. Copy note      *");
    puts("* 5. Delete note    *");
    puts("* 6. Exit           *");
    printf("Your choice: ");
}

int main(){
    
    init();
    while(1){
        menu();
        switch(read_int()){
        case 1:
            create();
            break;
        case 2:
            edit();
            break;
        case 3:
            show();
            break;
        case 4:
            copy();
            break;
        case 5:
            delete();
            break;
        case 6:
        default:
            exit(0);
        }
    }

}
