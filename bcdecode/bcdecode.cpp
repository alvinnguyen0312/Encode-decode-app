/*
Name:		Alvin Nguyen
Date:		05 April, 2018
Purpose:	Book cipher decoder
			Takes a book file and a coded file and decodes the coded file to provide a message

*/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
using book_size_type = uintmax_t; 							  
using book_location_type = pair<book_size_type, book_size_type>;
using book_location_list_type = vector<book_location_type>;

int main(int argc, char * argv[])
{
	//1.validate command line input
	if (argc < 4)
	{
		cout << "bcdecode(c) 2009 - 18, Alvin Nguyen" << endl;
		cerr << "Incorrect number of arguments" << endl;
		cout << "Usage: BookCipherDecode bookfile codedfile decodedfile" << endl;
		return EXIT_FAILURE;
	}
	//2. validate coded file and book file
	ifstream in_book(argv[1], ios::in);
	if (!in_book)
	{
		cerr << "Opening book file has failed." << endl;
		return EXIT_FAILURE;
	}

	ifstream in_coded(argv[2], ios::binary);
	if (!in_coded)
	{
		cerr << "Opening coded file has failed." << endl;
		return EXIT_FAILURE;
	}

	//3.Read book file
	vector<string>v_book;
	string line;
	book_location_type loc;
	while (getline(in_book, line))
	{
		line += "\n";
		v_book.push_back(line);
	}
	
	//4.Read the data from binary into char
	ofstream out_msg(argv[3]);
	while (in_coded.read(reinterpret_cast<char*>(&loc), sizeof(book_location_type))) {
		out_msg << v_book[loc.first][loc.second];
	}
	cout << "bcdecode(c) 2009 - 18, Alvin Nguyen" << endl;
}
	
