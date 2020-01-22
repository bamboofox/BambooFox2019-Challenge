#include "Land.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define SECRET_KEY 394286451

static const int _MAX_C = 1000000000;
static const int _MAX_NUM_QUERY = 128;
static char c[62];
static int VM[0x80];
static int *xddddd;
static char Trash[123];
static int *_d;
static char Trash1[87];
static int *_count;
static char Trash2[63];
static int *_a;
static char Trash3[55];
static int *_c;
static char Trash4[113];
static int *_b;
static char tmp[62];
static int _valid(int x){
	if(x<0||x>_MAX_C) return 0;
	return 1;
}
static int _max(int a,int b){
	if(a>b) return a;
	return b;
}
static int _min(int a,int b){
	if(a<b) return a;
	return b;
}
static void _wrong_answer(const char *MSG) {
	printf("Judge_For_Checking_Egg_Is_WA: %s\n", MSG);
	exit(0);
}
static void _Accepted(const int c){
	printf("Judge_For_Checking_Egg_Is_AC: %d\n",c);
}

static void init(){
    int randNum = 0,rt;
    int fd = open("/dev/urandom", O_RDONLY);
    if(fd < 0)
    {
        _wrong_answer("something error, please call admin.");
    }
    rt = read(fd, (char *)&randNum, sizeof(int));
    rt = close(fd);
    srand(randNum);
    for(int i=1;i<=6;i++)VM[i]=i;
    for(int i=0;i<10000;i++){
        int a,b;
        a = rand()%0x80;
        b = rand()%0x80;
        if(a==b)continue;
        int ta=VM[a];
        VM[a] = VM[b];
        VM[b] = ta;
    }
    for(int i=0;i<0x80;i++){
        switch(VM[i]){
            case 1:
                _count = (VM+i);
                break;
            case 2:
                _a = (VM+i);
                break;
            case 3:
                _b = (VM+i);
                break;
            case 4:
                _c = (VM+i);
                break;
            case 5:
                _d = (VM+i);
                break;
            case 6:
                xddddd = (VM+i);
                break;
        }
    }
}

static void _input(int *x){
	int i, rt, inp;
	rt = scanf("%d",&inp);
    *x = inp^SECRET_KEY;
}
//long long area_4b82677b6c1408df4be21ada9a584fde(int x1, int y1, int x2, int y2){
long long you_cant_call_me(int x1, int y1, int x2, int y2){
	++*_count;
	if(*_count>_MAX_NUM_QUERY)
		_wrong_answer("too many queries");
	if(!_valid(x1)||!_valid(x2)||!_valid(y1)||!_valid(y2))
		_wrong_answer("invalid query");
	if(!(x1<x2&&y1<y2))
		_wrong_answer("invalid query");
	int ml=_max(x1,*_a),mr=_min(x2,*_c);
	int md=_max(y1,*_b),mu=_min(y2,*_d);
	if(ml>=mr||md>=mu) return 0;
	return (long long)(mr-ml)*(long long)(mu-md); 
}

static void fillVM(){
    int *p=VM;
    for(int i=0;i<0x80;i++,p++){
        if(p==xddddd || p==_a || p==_b || p==_c || p==_d || p==_count){
            continue;
        }
        *p = rand()%1000000000;
    }
}

int main() {
    init();
	int t,mx=0;
	rectangle tmp;
	_input(&t);
	while(t--){
        if(t%10==0)init();
		*_count=rand()%8787,*xddddd=1;
		_input(_a),_input(_b),_input(_c),_input(_d);
        fillVM();
        //fprintf(stderr,"%d %d %d %d\n",*_a,*_b,*_c,*_d);
		tmp=find_rectangle();
		if(tmp.a!=*_a||tmp.b!=*_b||tmp.c!=*_c||tmp.d!=*_d)
			_wrong_answer("incorrect place");
		else
			mx=_max(mx,*_count);
	}
	_Accepted(mx);
}
#undef SECRET_KEY