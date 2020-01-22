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
            cerr << "Accept: " << n << " ; Flag: BAMBOOFOX{0h!!y0ur_pwn_the_sp3ci@l_jud93}";
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
