#include "String.h"
#include <iostream>
using std::cout;
using std::endl;
//memory leaks...
#define _CRT_DBG_MAP_ALLOC 

#include<crtdbg.h>





int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //memory leaks...


	String meow("meow");
	meow += " grrrrr";
	if (meow == "meow grrrrr")
		cout << meow << endl;
	String woof("awroooo");
	if (woof != meow)
		cout << woof << ' ' << meow << endl;
	woof++;
	String cat = woof + " " + meow;
	cout << cat << endl;

	--woof;

	if (cat <= meow)
		cout << "hihi" << endl;
	else
		cout << "nono" << endl;

	if (meow == meow)
		cout << "arf arf arf" << endl;
	else
		cout << "grr grr grr" << endl;
	cout << meow[-1] << endl;
	cout << meow.getLength();

	return 0;
}