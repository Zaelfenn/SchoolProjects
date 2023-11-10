#include "List.h"

int main() {
	List meow;
	meow.prependList("meow");
	meow.prependList("woof");
	meow.appendList("arrwooo");
	meow.prependList("bark bark");
	meow.deleteData("woof");
	meow.prependList("start");
	meow.appendList("end");
	meow.displayListFrwd();
	meow.displayListBckwd();
	List woof;// (meow);
	woof = meow;
	woof.displayListFrwd();
	meow.purgeList();
	woof.displayListBckwd();
	woof.purgeList();
	woof.insertList("c");
	woof.insertList("b");
	woof.insertList("zael");
	woof.insertList("a");
	woof.prependList("start");
	woof.appendList("end");
	woof.displayListFrwd();
	woof.purgeList();
	return 0;
}