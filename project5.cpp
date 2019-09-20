#include <iostream>
#include <fstream>
#include "AVLTreeCopy2.cpp"
#include <string>
#include <time.h>
#include <ctime>


using namespace std;

int main(int argc, char* argv[]){
  // implement this missing part
  // make the array size inside the hash table is 10007
	
	clock_t start, end;
    double duration;
    start = clock();
    
	AVLTree *table = new AVLTree();
    
	int searches = 0;
	int removals = 0;
	int insertions = 0;
	int duplicates = 0;
	int fails = 0;

	//set up file
	ifstream in;
	string file = argv[1];
	in.open(file);
	string frstNm, lstNm, name, SS;
	char frstChr;
	//read file
	
	while(true) {
		in >> frstChr;
		in >> SS; 
		in >> frstNm;
		in >> lstNm;
		name = frstNm + " " + lstNm;
		if(in.eof())
			break;
		//cout << SS << endl;
		//handles the adding
		if(frstChr == 'i') {
			if(table->insert(SS, name) == true) {
				insertions++;
			}
			/*
			else {
				duplicates++;
			}
			*/
		}
		//handles the deleting
		
		if(frstChr == 'd') {
			if(table->deleteNode(SS) == true) {
				removals++;
			}
		}
		
		//handles the retrieving
		if(frstChr == 'r') {
			if(table->find(SS) == true) {
				searches++;
			}
			/*
			else {
				fails++;
			}
			*/
		}
	}

	end = clock();
    duration = ( end - start ) / (double) CLOCKS_PER_SEC;
    cout << "The Number of Valid Insertations: " << insertions << endl;
    //cout << "The Number of Duplicates: " << duplicates << endl;
    cout << "The Number of Valid Deletion : " << removals << endl;
    cout << "The Number of Valid Retrieval: " << searches << endl;
    //cout << "The Number of Failed Retrieval: " << fails << endl;
    cout << "Height of the AVL Tree: " << table->height(table->getRoot()) << endl;
    cout<<"Elapsed time: "<< duration <<'\n';
    table->levelOrder();

    //table->print();
}
