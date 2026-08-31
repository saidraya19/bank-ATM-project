#include <iostream>
#include <string>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
struct info {
	string acauntcode = "", name = "", codepine = "", phone = "";
	double acauntbalance = 0;
};
struct lol { 
	string username = "";
	string password = "";
	string permition = "";
};
info  converttostruct( string &line);
string  convertline( info &data)
{
	string s = "";
	string  sep =  "#//#";
	s += data.acauntcode + sep;
	s += data.name + sep;
	s += data.codepine + sep;
	s += to_string(data.acauntbalance) + sep;
	s += data.phone;
	return s;
}
string  convertlolline( lol &data)
{
        string s = "";
        string  sep =  "#//#";
        s += data.username + sep;
        s += data.password + sep;
        s += data.permition;
        return s;
}
int count_lines(string s)
{
        fstream in(s);
        string line;
        int c = 0;

        while (getline(in, line))
                c++;

        return c;
}
bool	find(string s, char l)
{
	int i = 0;
	while( i != s.length())
	{
		if(s[i] == l)
		{
			return true;
		}
		i++;
	}
	return false;
}
lol  convertloltostruct( string &line)
{
	lol data;
        string temp = "";
        int i = 0;
        int fd = 0;
        while( i < line.length())
        {
                if(  i + 3 < line.length() && line[i] == '#' && line[i + 1] == '/' && line[i + 2] == '/' &&  line[i + 3] == '#')
                {
                        if ( fd == 0 )
                        { data.username = temp;
                        }
                        else if( fd == 1)
                        {
                                data.password = temp;
                        }
                        else if( fd == 2)
                        {
                                data.permition = temp;
                        }
                        temp = "";
                        fd++;
                        i += 4;
                }
                else
                {
                        temp += line[i];
                        i++;
                }

        }
	if (fd == 0)
        data.username = temp;
    else if (fd == 1)
        data.password = temp;
    else if (fd == 2)
        data.permition = temp;

    return data;
}
void admin(lol &data)
{
    fstream file("data.txt", ios::in);
    bool exists = false;
    string line;
    if(file.is_open())
    {
        while(getline(file, line))
        {
            lol tmp = convertloltostruct(line);
            if(tmp.username == "admin")
            {
                exists = true;
                break;
            }
        }
        file.close();
    }

    if(!exists)
    {
        data.username = "admin";
        data.password = "1111";
        data.permition = "1234567";
        ofstream fout("data.txt", ios::app);
        fout << convertlolline(data) << endl;
        fout.close();
    }
}
lol	permitions(lol &data)
{
	char a, b, c, d, e, f, j, h;
	cout << "do you want to give this user full access y/n : ";
                        cin >> a;
                        if (a == 'y' || a == 'Y')
                        {
                                data.permition = "1234567";
                        }
                        else
                        {
                                cout << "do you want to give access to" << "\n\n";
                                cout << " access to show client list y/n : ";
                                cin >> b;
                                if(b == 'y' || b == 'Y')
                                {
                                        data.permition += '1';
                                }
                                cout <<"\n";
                                cout << "access to add new client y/n : "; 
                                cin >> c;
                                if(c == 'y' || c == 'Y')
                                {
                                        data.permition += '2';
                                }
                                cout <<"\n";
                                cout << "access to delet client y/n : ";
                                cin >> d;
                                if(d == 'y' || d == 'Y')
                                {
                                        data.permition += '3';
                                }
                                cout <<"\n";
                                cout << "access to update client y/n : "; 
                                cin >> e;
                                if(e == 'y' || e == 'Y')
                                {
                                        data.permition += '4';
                                }
                                cout <<"\n";
                                cout << "access to find client y/n : "; 
                                cin >> f;
                                if(f == 'y' || f == 'Y')
                                {
                                        data.permition += '5';
                                }
                                cout <<"\n";
                                cout << "access to transaction y/n : ";
                                cin >> j;
                                if(j == 'y' || j == 'Y')
                                {
                                        data.permition += '6';
                                }
				cout <<"\n";
                                cout << "access to manage users y/n : ";
                                cin >> h;
                                if(h == 'y' || h == 'Y')
                                {
                                        data.permition += '7';
                                }
                        }
			return data;
}
void addUsers()
{
	string line = "";
        cout << "---------------------------------------------------------------" << "\n";
        cout << "---------------------------------------------------------------" << "\n\n";
        cout << "                          ADD NEW USER                         " << "\n\n";
        cout << "---------------------------------------------------------------" << "\n";
        cout << "---------------------------------------------------------------" << "\n\n\n";
        string res = "";
         lol add;
	 char a, b, c, d, e, f, J, H;
	 lol bigdata;
        string w = "y";
        do
        {
                bool find = false;
		cout << "enter username :";
                 getline(cin >> ws, bigdata.username);
		 cout <<"\n";
		 cout << "enter password : ";
		 cin >> bigdata.password;
                ifstream file("data.txt");
                if (!file.is_open())
                {
			cout << "this file not exist " ;
			cout << endl;
                        return;
                }
                while(getline(file, line))
                {
                        add = convertloltostruct(line);
                        if(bigdata.password == add.password && bigdata.username == add.username)
                        {
                                find = true;
                                break;
                        }
                }
                file.close();
                if(find)
                {
                        cout << "\n";
                        cout << "This client already exists";
                        continue;
                }
                else
                {
			bigdata = permitions(bigdata);
                        ofstream fout("data.txt", ios::app);
                        fout << convertlolline(bigdata) << endl;
                        fout.close();
                        cout << "user added successfully " << "\n\n\n";
                        cout << "do you want to add more users Y/N " << endl;
                        cin >> w;
                }
        }while( w == "y" || w == "Y" );
        cout << " evry user you added saved successfully " << endl;
}
void	Updateusers()
{
	cout << "---------------------------------------------------------------" << "\n";
    cout << "---------------------------------------------------------------" << "\n\n";
        cout << "                     UPDATE USERS                              " << "\n\n";
        cout << "---------------------------------------------------------------" << "\n";
        cout << "---------------------------------------------------------------" << "\n\n\n";
	lol data;
	lol bigdata;
        string line = "";
	 cout << "enter username :  ";
        cin >> data.username;
        cout << "enter password : ";
        cin >> data.password;
        fstream in("data.txt");
        ofstream out("temp.txt");
        if (!in.is_open())
        {
		 cout << "this file not exist " ;
                        cout << endl;
                return;
        }
        bool found = false;
        while(getline(in, line))
        {
                bigdata = convertloltostruct(line);
                string inswer = "n";
                if( data.password == bigdata.password)
                {
                        found = true;
			cout << " username " << bigdata.username;
                        cout << "do you want to edit this client y/n : ";
                        cin >> inswer;
                        if (inswer == "y" || inswer == "Y")
                        {
                                cout << "enter username :  ";
				cin >> data.username;
				cout << "enter password : ";
				data = permitions(data);
                                cout << "\n\n\n";
                                out << convertlolline(bigdata) << endl;
                                continue;
                        }
                }
                out << convertlolline(bigdata) << endl;
        }
        in.close();
        out.close();
        if(!found)
        {
                cout << "the client not exist" << endl;
                remove("temp.txt");
        }
        else {
                remove("data.txt");
                if(rename("temp.txt", "data.txt") != 0)
                {
                        cout << "there is problem check you code ";
                }
                else
                {
                        cout << " file updated successfully " << endl;
                }
        }
}
void    removeuser()
{
	lol data, bigdata;
        cout << "---------------------------------------------------------------" << "\n";
        cout << "---------------------------------------------------------------" << "\n\n";
        cout << "                     DELET USERS FROM FILE                     " << "\n\n";
        cout << "---------------------------------------------------------------" << "\n";
        cout << "---------------------------------------------------------------" << "\n\n\n";
        cout << "enter username :  ";
        cin >> data.username;
	cout << "enter password : ";
	cin >> data.password;
        string line = "";
        fstream in("data.txt");
        ofstream out("temp.txt");
        if (!in.is_open())
        {
                 cout << "this file not exist " ;
                        cout << endl;
                return;
        }
        bool check = true;
        bool found = false;
        while(getline(in, line))
        {
                bigdata = convertloltostruct(line);
                if ( data.password == bigdata.password )
                {
			 if ( data.password == "1111" && data.username == "admin")
			{
				cout << " you cannot delet admin " << endl;
				return;
			}
                        found = true;
                        cout << " uesername : " << data.username << endl;
			cout << " password  : " << data.password;
			cout << endl;
                        string letter = "y";
                        cout << "do you want to delet this user y/n " << endl;
                        cin >> letter;
                        if(letter == "y" || letter == "Y")
                        {
                                check = false;

                        }
                }
                if (check)
                {
                        out << line << endl;
                }
        }
        in.close();
        out.close();
        if(!found)
        {
                cout << "user wiirh password " << data.password << " not found" << endl;
                remove("temp.txt");
        }
        else
        {
                remove("data.txt");
                if ( rename("temp.txt", "data.txt") != 0)
                {
                        cout << "error" << endl;
                }
                else
                {
                        cout <<"file updated successfuly " << endl;
                }
        }
}
void 	addclient()
{
	info bigdata;
	string line = "";
	cout << "---------------------------------------------------------------" << "\n";
	cout << "---------------------------------------------------------------" << "\n\n";
	cout << "                     ADD NEW CLIENTS SCREEN                    " << "\n\n";
	cout << "---------------------------------------------------------------" << "\n";
	cout << "---------------------------------------------------------------" << "\n\n\n";
	string res = "";
	info lol;
	string w = "y";
	do
	{
		bool find = false;
		cout << "adding new clients" << "\n\n";
		cout << "Your account number   :";
		cin >> lol.acauntcode;
		ifstream file("myfile.txt");
		if (!file.is_open())
		{
			cout << "file myfile.txt not found" << endl;
			return;
		}
		while(getline(file, line))
		{
			bigdata = converttostruct(line);
			if(lol.acauntcode == bigdata.acauntcode)
			{
				find = true;
				break;
			}
		}
		file.close();
		if(find) 
		{
			cout << "\n";
			cout << "This client already exists";
			continue;
		}
		else
		{
			cout << "your name             :";
			getline(cin >> ws, lol.name);
			cout << "Your codepin is:       ";
			cin >> lol.codepine;
			cout << "Your phone number is  :";
			cin >> lol.phone;
			cout << "Your acount balance   :";
			cin >> lol.acauntbalance;
			ofstream fout("myfile.txt", ios::app);
			fout << convertline(lol) << endl;
			fout.close();
			cout << "client added successfully " << "\n\n\n";
			cout << "do you want to add more clients Y/N " << endl;
			cin >> w;
		}
	}while( w == "y" || w == "Y" );
	cout << " evry client you added saved successfully " << endl;
}
info  converttostruct( string &line)
{
	info data;
	string temp = "";
	int i = 0;
	int fd = 0;
	while( i < line.length())
	{
		if(  i + 3 < line.length() && line[i] == '#' && line[i + 1] == '/' && line[i + 2] == '/' &&  line[i + 3] == '#')
		{
			if ( fd == 0 )
			{ data.acauntcode = temp;
			}
			else if( fd == 1)
			{
				data.name = temp;
			}
			else if( fd == 2)
			{
				data.codepine = temp;
			}
			else if( fd == 3)
			{
				data.acauntbalance = stod(temp);
			}
			temp = "";
			fd++;
			i += 4;
		}
		else
		{
			temp += line[i];
			i++;
		}

	}
	data.phone = temp;
	return data;
}
void    updateclient( info &forma)
{
	cout << "---------------------------------------------------------------" << "\n";
	cout << "---------------------------------------------------------------" << "\n\n";
	cout << "                     UPDATE CLIENTS                              " << "\n\n";
	cout << "---------------------------------------------------------------" << "\n";
	cout << "---------------------------------------------------------------" << "\n\n\n";
	string nbaccount;
	string line = "";
	cout << "enter your account number ";
	cin >> nbaccount;
	string result = "";
	fstream in("myfile.txt");
	ofstream out("temp.txt");
	if (!in.is_open())
	{
		cout << "File myfile.txt not found!" << endl;
		return;
	}
	bool found = false;
	while(getline(in, line))
	{
		forma = converttostruct(line);
		string inswer = "n";
		if( nbaccount == forma.acauntcode)
		{
			found = true;
			cout << "\nRecord of data:\n";
			cout << "Acaunt number:        " << forma.acauntcode << endl;
			cout << "Your name is:         " << forma.name << endl;
			cout << "Your codepin is:      " << forma.codepine << endl;
			cout << "Your phone number is: " << forma.phone << endl;
			cout << "Your acount balance:  " << forma.acauntbalance << endl;
			cout << "\n\n\n";
			cout << "do you want to edit this client y/n : ";
			cin >> inswer;
			if (inswer == "y" || inswer == "Y")
			{
				cout << "Your name is:         ";
				cin >> forma.name;
				cout << "Your codepin is:      ";
				cin >> forma.codepine;
				cout << "Your phone number is: ";
				cin >> forma.phone;
				cout << "Your acount balance:  ";
				cin >> forma.acauntbalance;
				cout << "\n\n\n";
				result = convertline(forma);
				out << result << endl;
				continue;
			}
		}
		result = convertline(forma);
		out << result << endl;
	}
	in.close();
	out.close();
	if(!found)
	{
		cout << "the client not exist" << endl;
		remove("temp.txt");
	}
	else {
		remove("myfile.txt");
		if(rename("temp.txt", "myfile.txt") != 0)
		{
			cout << "there is problem check you code ";
		}
		else
		{
			cout << " file updated successfully " << endl;
		}
	}
}
void	removeclients()
{
	cout << "---------------------------------------------------------------" << "\n";
	cout << "---------------------------------------------------------------" << "\n\n";
	cout << "                     DELET CLIENTS FROM FILE                    " << "\n\n";
	cout << "---------------------------------------------------------------" << "\n";
	cout << "---------------------------------------------------------------" << "\n\n\n";
	info car;
	string nbaccount;
	cout << "enter your account number ";
	cin >> nbaccount;
	string line = "";
	fstream in("myfile.txt");
	ofstream out("temp.txt");
	if (!in.is_open())
	{
		cout << "File myfile.txt not found!" << endl;
		return;
	}
	bool check = true;
	bool found = false;
	while(getline(in, line))
	{
		car = converttostruct(line);
		if (car.acauntcode == nbaccount)
		{
			found = true;
			cout << " record of data " << "\n\n";
			cout << " acount number :         " << car.acauntcode << endl;
			cout << " your name is :          " << car.name << endl;
			cout << " your codepin is :       " << car.codepine << endl;
			cout << " your phone number is :  " << car.phone << endl;
			cout << " your acount balance is :" << car.acauntbalance  << endl;
			string letter = "y";
			cout << "do you want to delet this client y/n " << endl;
			cin >> letter;
			string test = convertline(car);
			if(letter == "y" || letter == "Y")
			{
				check = false;

			}
		}
		if (check)
		{
			out << line << endl;
		}
	}
	in.close();
	out.close();
	if(!found)
	{
		cout << "client with number account " << nbaccount << " not found" << endl;
		remove("temp.txt");
	}
	else
	{
		remove("myfile.txt");
		if ( rename("temp.txt", "myfile.txt") != 0)
		{
			cout << "error" << endl;
		}
		else
		{
			cout <<"file updated successfuly " << endl;
		}
	}
}
void    searshuser()
{
	lol data, bigdata;
        cout << "---------------------------------------------------------------" << "\n";
        cout << "---------------------------------------------------------------" << "\n\n";
        cout << "                     SEARSH FOR USER                        " << "\n\n";
        cout << "---------------------------------------------------------------" << "\n";
        cout << "---------------------------------------------------------------" << "\n\n\n";
        string nbaccount;
        string line = "";
        cout << "enter username ";
        cin >> data.username;
	cout << endl;
	cout << "enter passwrd : ";
	cin >> data.password;
	cout << endl;
        fstream in("data.txt");
        if (!in.is_open())
        {
                 cout << "this file not exist " ;
                        cout << endl;
                return;
        }
        bool found = false;
        while(getline(in, line))
        {
                string tmp = "";
                bigdata = convertloltostruct(line);
                string inswer = "n";
                if( data.password == bigdata.password)
                {
                        found = true;
                        cout << "Record of data:" << "\n";
                        cout << "username : " << data.username << endl;
                        cout << "password : " << data.password << endl;
                        cout << "\n\n\n";
                }
        }
        in.close();
}
void    listofusers()
{
        lol data;
string line = "";

ifstream in("data.txt");
if (!in.is_open())
{
	cout << "this file not exist";
	cout << endl;
    return;
}
cout << "--------------------------------------"<< "number of users is" << "[" << count_lines("data.txt")  << "]" << "-----------------------------------------" << "\n\n";

        cout << "-----------------------------------------------------------------------------------------------------" << "\n\n";
        cout << left << "|" << setw (30) << "username";
        cout << left << "|" << setw(30) << "password";
        cout << left << "|" << setw(30) << "permission" ;
        cout << "\n\n";
        cout << "-----------------------------------------------------------------------------------------------------" << "\n\n";
while (getline(in, line))
{
    data = convertloltostruct(line);

    cout << "|" << left << setw(30) << data.username;
    cout << "|" << left << setw(30) << data.password;
    cout << "|" << left << setw(30) << data.permition;
    cout << endl;
}
 cout << "\n\n";
        cout << "----------------------------------------------------------------------------------------------------" << "\n\n";
in.close();
}
int count_lines()
{
        fstream in("myfile.txt");
        string line;
        int c = 0;

        while (getline(in, line))
                c++;

        return c;
}
void    searshclients(info &forma)
{
	cout << "---------------------------------------------------------------" << "\n";
	cout << "---------------------------------------------------------------" << "\n\n";
	cout << "                     SEARSH FOR CLIENTS                        " << "\n\n";
	cout << "---------------------------------------------------------------" << "\n";
	cout << "---------------------------------------------------------------" << "\n\n\n";
	string nbaccount;
	string line = "";
	cout << "enter your account number ";
	cin >> nbaccount;
	string result = "";
	fstream in("myfile.txt");
	if (!in.is_open())
	{
		cout << "File myfile.txt not found!" << endl;
		return;
	}
	bool found = false;
	while(getline(in, line))
	{
		string tmp = "";
		forma = converttostruct(line);
		string inswer = "n";
		if( nbaccount == forma.acauntcode)
		{
			found = true;
			cout << "Record of data:" << "\n";
			cout << "Acaunt number:        " << forma.acauntcode << endl;
			cout << "Your name is:         " << forma.name << endl;
			cout << "Your codepin is:      " << forma.codepine << endl;
			cout << "Your acount balance:  " << forma.acauntbalance << endl;
			cout << "Your phone number is: " << forma.phone << endl;
			cout << "\n\n\n";
		}
	}
	in.close();
}
void    convert()
{
	info zios;
	string line = "";
	ifstream in("myfile.txt");
	if (!in.is_open())
	{
		cout << "File myfile.txt not found!" << endl;
		return;
	}
	while(getline(in, line))
	{
		zios = converttostruct(line);
		cout << "|" << left << setw(20) << zios.acauntcode;
		cout << "|" << left << setw(20) << zios.name;
		cout << "|" << left << setw(20) << zios.codepine;
		cout << "|" << left << setw(20) << zios.acauntbalance;
		cout << "|" << left << setw(20) << zios.phone;
		cout << endl;
	}
	in.close();
}
void	deposit()
{
	cout << "---------------------------------------------------------------" << "\n\n";
        cout << "                        deposit screen                          " << "\n\n";
        cout << "---------------------------------------------------------------" << "\n\n";
	info forma;
	string nbaccount;
	string line = "";
	cout << "enter your account number ";
	cin >> nbaccount;
	string result = "";
	fstream in("myfile.txt");
	ofstream out("temp.txt");
	if (!in.is_open())
	{
		cout << "File myfile.txt not found!" << endl;
		return;
	}
	bool found = false;
	string letter = "";
	while(getline(in, line))
	{
		forma = converttostruct(line);
		double inswer = 0;
		if( nbaccount == forma.acauntcode)
		{
			found = true;
			cout << "\nRecord of data:\n";
			cout << "Acaunt number:        " << forma.acauntcode << endl;
			cout << "Your name is:         " << forma.name << endl;
			cout << "Your codepin is:      " << forma.codepine << endl;
			cout << "Your phone number is: " << forma.phone << endl;
			cout << "Your acount balance:  " << forma.acauntbalance << endl;
			cout << "\n\n\n";
			cout << "please enter deposit amount  : ";
			cin >> inswer;
			while (inswer <= 0)
			{
				cout << "invalid amount, enter a positive number: ";
				cin >> inswer;
			}
			cout << "\n\n";
			cout << " ar you sure you want perform this transaction ? y/n : ";
			cin >> letter;
			if (letter == "y" || letter == "Y")
			{
				forma.acauntbalance += inswer;
				result = convertline(forma);
				out << result << endl;
				continue;
			}
		}
		result = convertline(forma);
		out << result << endl;
	}
	in.close();
	out.close();
	while(!found)
	{
		cout << "this account not exist try again : ";
                cin >> nbaccount;
		remove("temp.txt");
	}
	if(found)
	{
		remove("myfile.txt");
		if(rename("temp.txt", "myfile.txt") != 0)
		{
			cout << "there is problem check you code ";
		}
		else
		{
			cout << " file updated successfully " << endl;
		}
	}
}
void    withdraw()
{
	cout << "---------------------------------------------------------------" << "\n\n";
        cout << "                       withdraw screen                         " << "\n\n";
        cout << "---------------------------------------------------------------" << "\n\n";
	info forma;
	string nbaccount;
	string line = "";
	cout << "enter your account number ";
	cin >> nbaccount;
	string result = "";
	fstream in("myfile.txt");
	ofstream out("temp.txt");
	if (!in.is_open())
	{
		cout << "File myfile.txt not found!" << endl;
		return;
	}
	bool found = false;
	string letter = "";
	while(getline(in, line))
	{
		forma = converttostruct(line);
		double inswer = 0;
		if( nbaccount == forma.acauntcode)
		{
			found = true;
			cout << "\nRecord of data:\n";
			cout << "Acaunt number:        " << forma.acauntcode << endl;
			cout << "Your name is:         " << forma.name << endl;
			cout << "Your codepin is:      " << forma.codepine << endl;
			cout << "Your phone number is: " << forma.phone << endl;
			cout << "Your acount balance:  " << forma.acauntbalance << endl;
			cout << "\n\n\n";
			cout << "please enter withdraw amount  : ";
			cin >> inswer;
			cout << "\n\n";
			while(forma.acauntbalance < inswer)
			{
				cout << "amount exceeds the balance, you can withdraw up to :" << forma.acauntbalance << endl;
				cout << "please enter withdraw amount  : ";
				cin >> inswer;
			}
			cout << " ar you sure you want perform this transaction ? y/n : ";
			cin >> letter;
			if (letter == "y" || letter == "Y")
			{
				forma.acauntbalance -= inswer;
				result = convertline(forma);
				out << result << endl;
				continue;
			}
		}
		result = convertline(forma);
		out << result << endl;
		}

	in.close();
	out.close();
	while(!found)
	{
		cout << "this account not exist try again : ";
		cin >> nbaccount;
		remove("temp.txt");
	}
	if(found)
	{
		remove("myfile.txt");
		if(rename("temp.txt", "myfile.txt") != 0)
		{
			cout << "there is problem check you code ";
		}
		else
		{
			cout << " file updated successfully " << endl;
		}
	}
}
	
double	totalbalances()
{
	double total = 0;
	info forma;
	string line = "";
	fstream in("myfile.txt");
	if(!in.is_open())
	{
		cout << "File myfile.txt not found!" << endl;
		return -1;
	}
	bool found = false;
	while(getline(in, line))
	{
		forma = converttostruct(line);
		total += forma.acauntbalance;
	}
	in.close();
	return total;
}
void	printclient()
{
	cout << "---------------------------------------------------------------" << "\n";
	cout << "---------------------------------------------------------------" << "\n\n";
	cout << "                          CLIENT LIST                              " << "\n\n";
	cout << "---------------------------------------------------------------" << "\n";
	cout << "---------------------------------------------------------------" << "\n\n\n";
	cout << "--------------------------------------"<< "number of client is" << "[" << count_lines("myfile.txt")  << "]" << "-------------------------------------------" << "\n\n";

	cout << "--------------------------------------------------------------------------------------------------------" << "\n\n";
	cout << left << "|" << setw (20) << "acount number";
	cout << left << "|" << setw(20) << "client name";
	cout << left << "|" << setw(20) << "codepin";
	cout << left << "|" << setw(20) << "acountbalance";
	cout << left << "|" << setw(20) << "phone";
	cout << "\n\n";
	cout << "--------------------------------------------------------------------------------------------------------" << "\n\n";
	convert();
	cout << "\n\n";
	cout << "-------------------------------------------------------------------------------------------------------" << endl;
}
void	transactions()
{
	info zios;
string line = "";

ifstream in("myfile.txt");
if (!in.is_open())
{
    cout << "File myfile.txt not found!" << endl;
    return;
}
cout << "--------------------------------------"<< "number of client is" << "[" << count_lines()  << "]" << "-----------------------------------------" << "\n\n";

        cout << "-----------------------------------------------------------------------------------------------------" << "\n\n";
        cout << left << "|" << setw (30) << "acount number";
        cout << left << "|" << setw(30) << "client name";
        cout << left << "|" << setw(30) << "acountbalance" ;
        cout << "\n\n";
        cout << "-----------------------------------------------------------------------------------------------------" << "\n\n";
while (getline(in, line))
{
    zios = converttostruct(line);

    cout << "|" << left << setw(30) << zios.acauntcode;
    cout << "|" << left << setw(30) << zios.name;
    cout << "|" << left << setw(30) << zios.acauntbalance;
    cout << endl;
}
 cout << "\n\n";
        cout << "----------------------------------------------------------------------------------------------------" << "\n\n";
	cout <<"                             "<< "TOTAL BALANCES : " << totalbalances() << "                            ";
in.close();
}
lol 	login(lol &data)
{
	cout << "enter username :  ";
        cin >> data.username;
        cout << "enter password : ";
        cin >> data.password;
	return data;
}
void	checkpermitions(lol data, char c)
{
        if(!find(data.permition, c))
        {
		system("clear");
		cout << "\a";
                cout << "-----------------------------------" << endl;
                cout << "         access denied              " << endl;
                cout << "you don't have permission to do this    " << endl;
                cout << " please contact your admin.         " << endl;
                cout << "------------------------------------" << endl;
        }
	
}
void    project(info &strix)
{
        system("clear");
        cout << "------------------------------------------" << endl;
        cout << "|                                        |" << endl;
        cout << "|              login screen              |" << endl;
        cout << "|                                        |" << endl;
        cout << "------------------------------------------" << endl;
        cout << endl;
        lol data;
        lol bigdata;
        string line = "";
        bool found = false;
        while(!found)
        {
        lol temp = login(data);
        fstream in("data.txt");
        if (!in.is_open())
        {
                cout << "File not found!\n";
                return;
        }
        while(getline(in, line))
        {
                bigdata = convertloltostruct(line);
                if( temp.password == bigdata.password && bigdata.username == temp.username)
                {
			data = bigdata;
                        found = true;
                        break;
                }
        }
                 in.close();
    if(!found)
    {
         system("clear");
         cout << "------------------------------------------" << endl;
        cout << "|                                        |" << endl;
        cout << "|              login screen              |" << endl;
        cout << "|                                        |" << endl;
        cout << "------------------------------------------" << endl;
        cout << "\a";
        cout << "This user does not exist, please try again :)\n\n";
    }
        }
        enum listofclients {list = 1, add = 2, delet = 3, searsh = 4, update = 5, transactions2 = 6, manage_users = 7, Exit = 8};
        system("clear");
        do {
		system("clear");

                cout << "---------------------------------------------------------------" << "\n";
                cout << "---------------------------------------------------------------" << "\n\n";
                cout << "                       MAIN MINU SCREEN                       " << "\n\n";
                cout << "---------------------------------------------------------------" << "\n";
                cout << "---------------------------------------------------------------" << "\n\n";
                cout << "[1] " << "show client list. " << endl;
                cout << "[2] " << "add new client." << endl;
                cout << "[3] " << "delete client." << endl;
                cout << "[4] " << "find client info." << endl;
                cout << "[5] " << "update client." << endl;
                cout << "[6] " << "transactions." << "\n";
                cout << "[7] " << "manage users." << endl;
                cout << "[8] " << "exit." << "\n\n";
                int input = 0;
                cout << "choose what do you want to do? from[1 to 8] : ";
                int choice;
                while(!(cin >> input) || input < 1 || input > 8)
                {
                        system("beep -f 750 -l 300");
                         system("beep -f 1000 -l 300");
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "invalid choice enter number between 1 and 7 : ";
                }
                listofclients choices = static_cast<listofclients>(input);
                if ( input == list )
                {
                        if(!find(data.permition, '1'))
                        {
				system("clear");
                                checkpermitions(data, '1');
				cout << "\nPress Enter to restart...";
				cin.ignore();
				cin.get();
                                continue;
                        }
                        system("clear");
			printclient();
		}
		else if ( input == add)
		{
			if(!find(data.permition, '2'))
                        {
                                checkpermitions(data, '2');
				cout << "\nPress Enter to restart...";
                                cin.ignore();
                                cin.get();
                                continue;
                        }
			system("clear");
			addclient();
		}
		else if ( input == delet)
		{
			if(!find(data.permition, '3'))
                        {
                                checkpermitions(data, '3');
				cout << "\nPress Enter to restart...";
                                cin.ignore();
                                cin.get();
                                continue;
                        }
			system("clear");
			removeclients();
		}
		else if ( input == searsh)
		{
			if(!find(data.permition, '4'))
                        {
                                checkpermitions(data, '4');
				cout << "\nPress Enter to restart...";
                                cin.ignore();
                                cin.get();
                                continue;
                        }
			system("clear");
			searshclients((strix));
		}
		else if( input == update)
		{
			if(!find(data.permition, '5'))
                        {
                                checkpermitions(data, '5');
				cout << "\nPress Enter to restart...";
                                cin.ignore();
                                cin.get();
                                continue;
                        }
			system("clear");
			updateclient(strix);
		}
		else if(input == transactions2)
		{
			if(!find(data.permition, '6'))
                        {
                                checkpermitions(data, '6');
				cout << "\nPress Enter to restart...";
                                cin.ignore();
                                cin.get();
                                continue;
                        }
			system("clear");
			do
			{
			system("clear");
			enum ranc{ deposit2 = 1, withdraw2 = 2, totalbalances2 = 3, minu = 4};
			int temp = 0;
		cout << "---------------------------------------------------------------" << "\n";
                cout << "---------------------------------------------------------------" << "\n\n";
                cout << "                     TRANSACTIONS MINU SCREEN                  " << "\n\n";
                cout << "---------------------------------------------------------------" << "\n";
                cout << "---------------------------------------------------------------" << "\n\n";
		cout << "[1] " << "deposit. " << endl;
                cout << "[2] " << "withdraw." << endl;
                cout << "[3] " << "total balances." << endl;
                cout << "[4] " << "menu." << endl;
		 cout << "choose what do you want to do? from[1 to 4] : ";
		 int choice;
		 while(!(cin >> temp) || temp < 1 || temp > 4)
		 {
			 system("beep -f 750 -l 300");
			 system("beep -f 1000 -l 300");
			 cin.clear();
			 cin.ignore(10000, '\n');
			 cout << "invalid choice enter number between 1 and 7 : ";
		 }
		  ranc cloc = static_cast<ranc>(temp);
		  if(temp == deposit2)
		  {
			  system("clear");
			  deposit();
		  }
		  else if ( temp == withdraw2) 
		  {
			  system("clear");
			  withdraw();
		  }
		  else if ( temp == totalbalances2)
		  {
			  system("clear");
			  transactions();
		  }
		  else if(temp == minu)
		  {
			  break;
		  }
		  cout << "\nPress Enter to restart...";
                cin.ignore();
                cin.get();
			}while(true);
		}
		else if ( input == manage_users )
		{
			if(!find(data.permition, '7'))
                        {
                                checkpermitions(data, '7');
				cout << "\nPress Enter to restart...";
                                cin.ignore();
                                cin.get();
                                continue;
                        }
			system("clear");
			enum listinfousers{ listusers = 1, adddusers = 2, deletusers = 3, upddateusers = 4,  findusers = 5, mainminu = 6};
			cout << "---------------------------------------------------------------" << "\n";
                cout << "---------------------------------------------------------------" << "\n\n";
                cout << "                      MANAGE USERS SCREEN                      " << "\n\n";
                cout << "---------------------------------------------------------------" << "\n";
                cout << "---------------------------------------------------------------" << "\n\n";
                cout << "[1] " << "show users list. " << endl;
                cout << "[2] " << "add new user." << endl;
                cout << "[3] " << "delete users." << endl;
                cout << "[4] " << "update users." << endl;
                cout << "[5] " << "find users info." << endl;
                cout << "[6] " << "main minu." << "\n\n";
		cout << "choose what do you want to do? from[1 to 6] : ";
		int choice;
		while(!(cin >> choice) || choice < 1 || choice > 6)
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "invalid choice enter number between 1 and 6 : ";
		}
		listinfousers list = static_cast<listinfousers>(choice);
		if(list == listusers)
		{
			system("clear");
			listofusers();
		}
		else if(list == adddusers)
		{
			system("clear");
			addUsers();
		}
		else if( list == upddateusers)
		{
			system("clear");
			Updateusers();
		}
		else if(list == deletusers)
		{
			system("clear");
			removeuser();
		}
		else if(list == findusers)
                {
                        system("clear");
			searshuser();
		}
		else if(list == mainminu)
                {
                        system("clear");
		
		}
		}
		else if( input == Exit)
		{
			system("clear");
			return;
		}
		cout << "\nPress Enter to restart..." ;
		cin.ignore();
		cin.get();
		system("clear");
	}while(true);
}
int main()
{
	info said;
	project(said);
	return 0;
}
