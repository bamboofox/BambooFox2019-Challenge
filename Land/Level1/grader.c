#include "Land.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

static const int _MAX_C = 1000000000;
static const int _MAX_NUM_QUERY = 128;
static char c[62];
static int VM[0x80];
static int *xddddd,*_d;
static int *_count;
static int *_c,*_a;
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

static void init(){
    srand(clock());
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
	int i, sz, rt, inp;
	rt = scanf("%d",&inp);
    *x = inp^394286451;
}
static void _wrong_answer(const char *MSG) {
	printf("Judge_For_Checking_Egg_Is_WA: %s\n", MSG);
	exit(0);
}
static void _Accepted(const int c){
	printf("Judge_For_Checking_Egg_Is_AC: %d\n",c);
}

long long area(int x1, int y1, int x2, int y2){
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

int main() {
    init();
	int t,mx=0;
	rectangle tmp;
	_input(&t);
	while(t--){
        if(t%10==0)init();
		*_count=0,*xddddd=1;
		_input(_a),_input(_b),_input(_c),_input(_d);
        //fprintf(stderr,"%d %d %d %d\n",*_a,*_b,*_c,*_d);
		tmp=find_rectangle();
		if(tmp.a!=*_a||tmp.b!=*_b||tmp.c!=*_c||tmp.d!=*_d)
			_wrong_answer("incorrect place");
		else
			mx=_max(mx,*_count);
	}
	_Accepted(mx);
}
