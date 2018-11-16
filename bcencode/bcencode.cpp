/*
Name:		Alvin Nguyen
Date:		05 April 2018
Purpose:	Book cipher encoder
Takes a book file and a message file and encodes the message using
line and offset values from the book file and produces a coded file
https://www.ascii-codes.com/cp850.html
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


//data types (aliases) used in this project
//book size
using book_size_type = uintmax_t; //unsigned int max size								 
using book_location_type = pair<book_size_type, book_size_type>;
using book_location_list_type = vector<book_location_type>;
using encoding_book_type = vector<book_location_list_type>;

int main(int argc, char * argv[]) {
	//1.validate command lines args - 4 args
	if (argc < 4 ) 
	{
		cout << "bcencode(c) 2009 - 18, Alvin Nguyen" << endl;
		cerr << "Incorrect number of arguments" << endl;
		cout << "Usage: BookCipherEncode bookfile originalfile codedfile" << endl;
		return EXIT_FAILURE;
	}
	//2. validate message file and book file
	ifstream in_book(argv[1], ios::in);
	if (!in_book)
	{
		cerr << "Opening book file has failed." << endl;
		return EXIT_FAILURE;
	}

	ifstream in_msg(argv[2], ios::in);
	if (!in_msg)
	{
		cerr << "Opening message file has failed." << endl;
		return EXIT_FAILURE;
	}
	
	//3.Read message file
	char ch1;
	vector<char>v_msg;
	while (in_msg.get(ch1))
		v_msg.push_back(ch1);

	//4.Read book file
	vector<string>v_book;
	string line;
	while (getline(in_book, line))
	{
		line += "\n";
		v_book.push_back(line);
	}

	//5. Look up each element of v_msg vector in book v_book vector,
	//then create a vector to store a pair of location (line, column) of the look-up letter in book file
	book_location_list_type loc;
	bool skip = false;
	int lineNum = 0;
	int count = 0;
	vector<char>v_msg1 = v_msg;
	for (int i = 0; i < v_msg.size(); ++i)
	{
		while(lineNum < v_book.size())
		{
			for (int j = 0; j < v_book[lineNum].size(); ++j)
			{
				if (v_msg[i] == v_book[lineNum][j])
				{
					v_msg1.erase(v_msg1.begin()+count);
					loc.push_back(make_pair(lineNum, j));
					skip = true;
					break;
					count++;
				}			
			}
			lineNum++;
			if (skip) {
				skip = false;
				break;
			}		
		}
	}
	
	//The encoder program reports and quits if the message
	//cannot be encoded by the book file - report which character cannot be encoded
	if (loc.size() < v_msg.size())
	{
		cerr << "The message cannot be encoded by the book file." << endl;
		cerr << "The characters cannot be encoded are: ";
		for (auto x : v_msg1)
			cout << x;
		return EXIT_FAILURE;
	}

	//7. Write location (line/column) to binary files
	ofstream out_coded(argv[3], ios::binary);
	for (size_t i = 0; i < loc.size(); ++i)
	{
		out_coded.write((char *)(&loc[i].first), sizeof(loc[i].first));
		out_coded.write((char *)(&loc[i].second), sizeof(loc[i].second));
	}
	cout << "bcencode(c) 2009 - 18, Alvin Nguyen" << endl;

}//end main

 

