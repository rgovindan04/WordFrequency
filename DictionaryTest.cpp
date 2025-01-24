//Rishi Govindan
//rigovind
//pa8

#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

	 string S[] =   { // words to insert
                     "plaices",
                     "ambusher",
                     "crosby",
                     "wattles",
                     "pardoner",
                     "pythons",
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",
                     "dissocialised",
                     "cohabit",
                     "hemiolia",
                     "cantling",
                     "glamorized",
                     "millesimal",
                     "glagolitic"
                  };

	string T[] =   { // words to delete
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",      
                  };

	Dictionary A;
   	Dictionary B;

   	cout << endl;

	for(int i=0; i<26; i++){
      		A.setValue(S[i], i+1);
   	}

	B = A;

   	B.setValue("deschooler", 101);
   	B.setValue("reinsurer", 102);
   	B.setValue("glagolitic", 103);
   	B.setValue("cul", 104);
   	B.setValue("ambusher", 105);

	Dictionary C = B;

   	cout << "A.size() = " << A.size() << endl  << A << endl;
   	cout << "B.size() = " << B.size() << endl  << B << endl;
   	cout << "C.size() = " << C.size() << endl  << C << endl;

	cout << "copy constructor creates identical trees: " << endl;
   	cout << ((C.pre_string()==B.pre_string())?"true":"false") << endl;
   	cout << endl;

	cout << "A==B is " << (A==B?"true":"false") << endl;
   	cout << "B==C is " << (B==C?"true":"false") << endl;
   	cout << "C==A is " << (C==A?"true":"false") << endl << endl;

	cout << "A.getValue(\"hemiolia\") = " << A.getValue("hemiolia") << endl;
   	A.getValue("hemiolia") *= 10; // change the value associated with "hemiolia"
   	cout << "A.getValue(\"hemiolia\") = " << A.getValue("hemiolia") << endl << endl;

	cout << "A.size() = " << A.size() << endl  << A << endl;
   	cout << "A pre-order: " << endl << A.pre_string() << endl;

	for(int i=0; i<13; i++){ 
      		A.remove(T[i]);
   	}

	cout << "A.size() = " << A.size() << endl  << A << endl;
   	cout << "A pre-order: " << endl << A.pre_string() << endl;

	cout << "forward iteration on B, changing values:" << endl;
   	for(B.begin(); B.hasCurrent(); B.next()){
      		cout << "("+B.currentKey()+", " << B.currentVal() << ") ";
      		B.currentVal()++;  // change value
      		cout << "("+B.currentKey()+", " << B.currentVal() << ")\n";
   	}
   	cout << endl;

	cout << "reverse iteration on C, changing values" << endl;
   	for(C.end(); C.hasCurrent(); C.prev()){
      		cout << "("+C.currentKey()+", " << C.currentVal() << ") ";
      		C.currentVal()++;  // change value
      		cout << "("+C.currentKey()+", " << C.currentVal() << ")\n";
   	}
   	cout << endl;

	cout << "test pre-condition errors:" << endl;
   	try{
      		A.getValue("blah");
   	}catch(logic_error& e){
      		cout << e.what() << endl;
      		cout << "   continuing without interruption" << endl;
   	}
   	try{
      		A.remove("blah");
   	}catch(logic_error& e){
      		cout << e.what() << endl;
      		cout << "   continuing without interruption" << endl;
   	}
   	try{
      		A.currentKey();
   	}catch(logic_error& e){
      		cout << e.what() << endl;
      		cout << "   continuing without interruption" << endl;
   	}
   	try{
      		A.currentVal();
   	}catch(logic_error& e){
      		cout << e.what() << endl;
      		cout << "   continuing without interruption" << endl;
   	}  
   	try{
      		A.next();
   	}catch(logic_error& e){
      		cout << e.what() << endl;
      		cout << "   continuing without interruption" << endl;
   	}
   	try{
      		A.prev();
   	}catch(logic_error& e){
      		cout << e.what() << endl;
      		cout << "   continuing without interruption" << endl;
   	}
   	cout << endl;  

   return(0);
}
