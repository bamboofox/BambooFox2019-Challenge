#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
	if(argc != 4)
		return 0;
	int n;
	fstream in, ans, out;
	string s, r;
	in.open(argv[1], ios::in);
	//ans.open(argv[2], ios::in);
	out.open(argv[3], ios::in);
	out >> s;
	if(s == "Judge_For_Checking_Egg_Is_AC:"){
		out >> n;
		if(n<=59){
            cout<<1.0;
            cerr << "Accept: " << n << " ; Flag: BAMBOOFOX{WTF!!How_d0_y0u_5o1v3_thi5_problem_w1thout_9uery!?}";
        }
        else{
            cout<<0.0;
            cerr << "Too many query: " << n << "";
        }
		return 0;
	}
	if(s == "Judge_For_Checking_Egg_Is_WA:"){
		getline(out, r);
		cout << 0.0;
		cerr << "Wrong Answer: " + r;
		return 0;
	}
	cout << 0.0;
	cerr << "Unexpected Error";
	return 0;
}
