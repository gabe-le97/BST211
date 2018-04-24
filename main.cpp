// Necessary Libraries
#include "bst.h"
#include "dna.h"
#include <iostream>

/*
------------------------------
integer comparison
------------------------------
*/
bool intLT(int &x, int &y) {
	return x < y;
}

/*
------------------------------
Double Comparison
------------------------------
*/
bool doubleComp(double &x, double &y) {
	return x < y;
}

/*
------------------------------
String Comparison
------------------------------
*/
bool stringComp(std::string &x, std::string &y) { 
	return x < y;
}

/*
------------------------------
DNA comparison
------------------------------
*/
bool seqLenLessThan(DNA& item1, DNA& item2) {
	// compares the two dna objects and returns a bool value
	return item1.getSequence().length() < item2.getSequence().length();
}

// ran through gradescope --- it asks to use header
bool headerLessThan(DNA& item1, DNA& item2) {
	// compares the two dna object headers
	return item1.getHeader() < item2.getHeader();
}

/*
------------------------------
Main function
------------------------------
*/
int main() {
	// integer template being tested
	std::vector<int> v = {1, 5, 9, 2, 17, 392, 27, 346};
	BST<int> b(v, &intLT);
	int z = b.find(1, &intLT);
	std::cout << z << std::endl;


	// double template being tested
	std::vector<double> d = {2.3, 10.3, 21.2, 9.7, 3.1};
	BST<double> alpha(d, &doubleComp);
	// should return 10.3
	double look = alpha.find(10.3, &doubleComp);
	std::cout << look << std::endl;


	// string template being tested
	std::vector<std::string> s = {"Computer", "CSC211", "Duck", "Weight", "iPhone"};
	BST<std::string> st(s, &stringComp);
	std::string found = st.find("Computer", &stringComp);
	std::cout << found << std::endl;

	// DNA class template being tested
	// Creating different dna objects
	DNA::DNA dna1 = DNA::DNA(">Header 1", "GATTACA");
	DNA::DNA dna2 = DNA::DNA(">Header 2", "ATANNAT");
	DNA::DNA dna3 = DNA::DNA(">Header 3", "ANT");
	DNA::DNA dna4 = DNA::DNA(">Header 4", "GATTATAN");
	DNA::DNA dna5 = DNA::DNA(">Header 5", "NACT");
	DNA::DNA dna6 = DNA::DNA(">Header 6", "AGNTA");

	// objects are placed into a vector
	std::vector<DNA> DNAobjects = {dna1, dna2, dna3, dna4, dna5};
	// can use either sequence or header sort (gradescope asks for header)
	BST<DNA> dna(DNAobjects, &seqLenLessThan);
	DNA::DNA found1 = dna.find(dna4, &seqLenLessThan);
	std::cout << found1.getHeader() << " -> " << found1.getSequence() << std::endl;

	// testing string if not found
	std::vector<std::string> p = {"Computer", "CSC211", "Lenovo", "Acer", "iPhone"};
	BST<std::string> ps(p, &stringComp);
	// should throw a runtime error
	std::string foundIt = ps.find("iMac", &stringComp);
	std::cout << foundIt << std::endl;
}
