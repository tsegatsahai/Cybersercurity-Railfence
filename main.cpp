#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream> 

using namespace std;

map<int, char> sub{ {97,'d'}, {98,'k'}, {99,'v'}, {100,'q'}, {101,'f'}, {102,'i'}, {103,'b'}, {104,'j'}, {105,'w'}, {106,'p'}, {107,'e'}, {108,'s'}, {109,'c'}, {110,'x'}, {111,'h'}, {112,'t'}, {113,'m'}, {114,'y'}, {115,'a'}, {116,'u'}, {117,'o'}, {118,'l'}, {119,'r'}, {120,'g'}, {121,'z'}, {122,'n'} };
map<int, char> decSub{ {100,'a'}, {107,'b'}, {118,'c'}, {113,'d'}, {102,'e'}, {105,'f'}, {98,'g'}, {106,'h'}, {119,'i'}, {112,'j'}, {101,'k'}, {115,'l'}, {99,'m'}, {120,'n'}, {104,'o'}, {116,'p'}, {109,'q'}, {121,'r'}, {97,'s'}, {117,'t'}, {111,'u'}, {108,'v'}, {114,'w'}, {103,'x'}, {122,'y'}, {110,'z'} };
char M1(int a);
char M1D(int a);
char M2(int a);
char M2D(int a);
char M3(int a);
char M3D(int a);
int main()
{
	string fileName;
	char letter, answer, cipher;
	int depth = 0;
	vector <int> text;
	ifstream myFile;

	cout << "Please insert a text file to encrypt/decrypt: " ;
	cin >> fileName; 
	myFile.open(fileName);
	if(!myFile){throw runtime_error("Could not open file");}
	while (myFile >> letter) 
		{
			text.push_back(tolower(letter));
		}
	vector<int>::iterator it = text.begin();
	cout << "Please insert 'P' to use the Polyalphabetic Cipher or 'R' for the Rail Fence cipher: ";
	cin >> cipher;
	cout << "Please insert 'E' for encryption or 'D' for decryption: ";
	cin >> answer;
	if(cipher == 'P' || cipher == 'p')
		{
			if(answer == 'E' || answer == 'e')
				{
					while(it != text.end())
						{
							cout << M2(*it);
							++it;
							if(it == text.end()){break;}
							cout << M3(*it);
							++it;
							if(it == text.end()){break;}
							cout << M2(*it);
							++it;
							if(it == text.end()){break;}
							cout << M1(*it);
							++it;
							if(it == text.end()){break;}
							cout << M3(*it);
							++it;
						}	
					cout << endl;
				}
			else if (answer == 'D' || answer == 'd')
				{
					while(it != text.end())
						{
							cout << M2D(*it);
							++it;
							if(it == text.end()){break;}
							cout << M3D(*it);
							++it;
							if(it == text.end()){break;}
							cout << M2D(*it);
							++it;
							if(it == text.end()){break;}
							cout << M1D(*it);
							++it;
							if(it == text.end()){break;}
							cout << M3D(*it);
							++it;
						}	
					cout << endl;
				}
		}
	else if(cipher == 'R' || cipher == 'r')
		{
			cout << "Please insert the depth of the rail fence: ";
			cin >> depth;
			int table[depth][text.size()];
			for(int i =0; i <  depth; i++)
				{
					for(int j =0; j < text.size(); j++)
						{
							//fill every slot in the table with -1 to make it easier to print the cipher/plain text letter on
							table[i][j] = -1;						
						}
				}
			bool up = true; //set the direction to true since we are starting at the top of the table
			int r = 0, c = 0, counter =0;
			if(answer == 'e' || answer == 'E')
				{
				for(int i=0; i < text.size(); i++)
					{
						if(r == 0 || r == depth -1 ) //if r is at the top or bottom, change directions
							{
								//if r==0, then up is false (because we have to go down) and vise versa
								up = !up;  
							}
						table[r][c] = text[i];
						c++;
						if(!up)
							{
								r++;							
							}
						else{r--;}
						
					}
				for(int i = 0; i < depth; i++)
					{
						for(int j =0; j < text.size(); j++)
							{
								if(table[i][j] != -1)
									{
										cout << char( table[i][j]);
									}
							}
					}
					cout << endl;
				}
			else if(answer == 'd' || answer == 'D')
				{
					up = true;
					for(int i=0; i < text.size(); i++)
						{
							if(r == 0 || r == depth -1 ) //if r is at the top or bottom, change directions
								{
									//if r==0, then up is false (because we have to go down) and vise versa
									up = !up;  
								}
							//marking the spots where the cipher text would be with -99	
							table[r][c] = -99; 
							c++;
							if(!up)
								{
									r++;							
								}
							else{r--;}
						}
					for(int i = 0; i < depth; i++)
					{
						for(int j =0; j < text.size(); j++)
							{
								if(table[i][j] == -99)
									{
										table[i][j] = text[counter];
										counter++;
									}
							}
					}
					up = true; 
					r = 0;
					c = 0;
					for(int i=0; i < text.size(); i++)
						{
							if(r == 0 || r == depth -1 ) //if r is at the top or bottom, change directions
								{
									//if r==0, then up is false (because we have to go down) and vise versa
									up = !up;  
								}
							//going through and printing diagonally 
							cout << char(table[r][c] ); 
							c++;
							if(!up)
								{
									r++;							
								}
							else{r--;}
						}
						cout << endl;
				}
		}
}
//left shift three letters
char M1(int a) 
{
	if (a <= 99) { return char((a -3) + 26); }
	else { return (char(a - 3)); }
}

//M1 Decryption
char M1D(int a) 
{
	if (a >= 120) { return char((a + 3) - 26);  }
	else { return char(a + 3); }
}
//sub
char M2(int a) 
{
	return sub[a];
}
//M2 decryption
char M2D(int a) 
{
	return decSub[a];
}

//right shift 5 letters
char M3(int a) 
{
	if (a >= 118) { return char((a + 5) - 26);  }
	else { return char(a + 5); }
}
//M3 decryption
char M3D(int a) 
{
	if (a <= 101) { return char((a -5) + 26); }
	else { return (char(a - 5)); }
}
