#include"Assignment.h"

////////////////////////////////////////////Tim sach

int getbook(Book& book,fstream& outfile, int row) {
	if (!outfile.eof()) {
		row = row - row % 8;
		for (int i = 0; i < row; i++) {
			string line;
			getline(outfile, line);
		}
		string ISBN;
		getline(outfile,ISBN);
		if (book.ISBN == ISBN)
			return 0;
		else {
			book.ISBN = ISBN;
			getline(outfile, book.name);
			getline(outfile, book.author);
			getline(outfile, book.category);
			getline(outfile, book.publisher);
			string temp;
			getline(outfile, temp);
			stringstream ss1(temp);
			ss1 >> book.year;
			getline(outfile, temp);
			stringstream ss2(temp);
			ss2 >> book.amount;
			getline(outfile, temp);
			stringstream ss3(temp);
			ss3 >> book.price;
			return 1;
		}

	} else
		return 0;
}

void printline() {
	for (int i = 0; i < 132; i++)
		cout << "-";
	cout << endl;
}

void printtitle() {
	printline();
	cout << "| STT |     ISBN       |                      Ten sach               |        Tac gia        |         NXB         |  Nam |So luong|\n";
	printline();
}



void showbookinfo(Book& book,int count) {
	cout << "|" << setw(4) << count << " |" << right << setw(15) << book.ISBN << " | " << left << setw(44) << book.name << "| " << setw(21) << book.author << " | " << setw(19) << book.publisher << " | " << right << setw(4) << book.year << " |" << setw(7) << book.amount << " |\n";
}

void show_all_book() {
	fstream outfile;
	outfile.open("book.txt", ios::in);
	Book book;
	int count = 0;
	printtitle();
	while (1) {
		if (getbook(book,outfile,0) == 1) {
			count++;
			showbookinfo(book, count);
		} else {
			break;
		}
	}
	printline();
	outfile.close();
}

void putinfo(Book& book,string& info) {
	stringstream ss;
	string year, amount;
	ss << book.year << book.amount;
	ss >> year >> amount;
	info += book.ISBN + " " + book.name + " " + book.author + " " + book.publisher + " " + year + " " + amount;
}

void setbookinfo(string& info, Book book,int key) {
	string line;
	stringstream ss(info);
	for (int i = 0; i <= key; i++)
		getline(ss, line);
	stringstream ss2(line);
	ss2 >> book.ISBN >> book.name >> book.author >> book.publisher >> book.year >> book.amount;
}


//Tim kiem theo tung loai:
//0-ISBN
//1-Ten sach
//2-Tac gia
//3-NXB
//4-Nam XB
void find_key(string str, int selection) {
	Book book;
	fstream outfile;
	fstream outfile2;
	string line;
	string temp;
	int curline = 0;
	int count = 0;

	outfile.open("book.txt", ios::in);
	if (outfile.is_open()) {
		for (int i = 0; i < selection; i++) {
			getline(outfile, line);
			curline++;
		}
		printtitle();
		while (getline(outfile, line)) {
			curline++;
			if (line.find(str, 0) != -1) {
				outfile2.open("book.txt", ios::in);
				getbook(book, outfile2, curline);
				count++;
				showbookinfo(book, count);
				putinfo(book, temp);
				outfile2.close();
			}
			for (int i = 0; i < 5; i++) {
				getline(outfile, line);
				curline++;
				if (outfile.eof())
					break;
			}
		}
		printline();
	} else
		cout << "Khong co file";
	if (count == 0)
		cout << "Khong co ket qua phu hop voi tu khoa!";
	outfile.close();
}

void search_key(string str) {
	fstream outfile;
	fstream outfile2;
	string line;
	string temp;
	outfile.open("book.txt", ios::in);
	Book book;
	printtitle();
	int curline = 0;
	int count = 0;
	if (outfile.is_open()) {
		while (getline(outfile, line)) {
			curline++;
			if (line.find(str, 0) != -1) {
				outfile2.open("book.txt", ios::in);
				getbook(book, outfile2, curline);
				count++;
				showbookinfo(book, count);
				putinfo(book, temp);
				outfile2.close();
			}
		}
		printline();
	} else
		cout << "Khong co file";

	if (count == 0)
		cout << "Khong co ket qua phu hop voi tu khoa!";


	outfile.close();
}

void search_name(string str) {
	fstream outfile;
	fstream outfile2;
	string line;

}

//////////////////////////////////////////////////////////////////////////////////////////////////
//Cart

void delete_entire_cart(account *acc) {
	string filename="cart_"+acc->getUsername()+".txt";
	ofstream outfile;
	outfile.open(filename.c_str(), ofstream::out | ofstream::trunc);
	outfile.close();
}

void delete_single_book_cart_function(account *acc, string ISBN) {
	fstream outfile;
	string filename="cart_"+acc->getUsername()+".txt";
	outfile.open(filename.c_str(), ios::in);
	fstream temp;
	temp.open("temp.txt", ios::out);
	string datatemp;
	Book *tempbook=new Book();
	string date, numberofdate;
	int flag=0;
	while (getline(outfile, datatemp)) {
		tempbook->ISBN=datatemp;
		getline(outfile, datatemp);
		tempbook->name=datatemp;
		getline(outfile, datatemp);
		tempbook->author=datatemp;
		getline(outfile, datatemp);
		tempbook->category=datatemp;
		getline(outfile, datatemp);
		tempbook->publisher=datatemp;
		getline(outfile, datatemp);
		tempbook->year=atoi(datatemp.c_str());
		getline(outfile, datatemp);
		tempbook->price=atoi(datatemp.c_str());
		getline(outfile, datatemp);
		date=datatemp;
		getline(outfile, datatemp);
		numberofdate=datatemp;

		if (ISBN != tempbook->ISBN) {
			temp << tempbook->ISBN << '\n' << tempbook->name << '\n' << tempbook->author << '\n' << tempbook->publisher << '\n' << tempbook->year <<'\n' << tempbook->price <<'\n'<<date <<'\n' << numberofdate << endl;
		}

	}
	temp.close();
	outfile.close();
	remove(filename.c_str());
	rename("temp.txt", filename.c_str());
}

void delete_in_cart();
////////////test

void show_cart(account *acc);//TO DOOOOOOOOOOOOOOOOOOOo
////////////test

int get_price(account *acc) {
	fstream outfile;
	string filename="cart_"+acc->getUsername()+".txt";
	outfile.open(filename.c_str(), ios::in);
	string datatemp;
	Book *tempbook=new Book();
	string date, numberofdate;
	int dateint,numberofdateint;
	int totalprice=0;
	while (getline(outfile, datatemp)) {
		tempbook->ISBN=datatemp;
		getline(outfile, datatemp);
		tempbook->name=datatemp;
		getline(outfile, datatemp);
		tempbook->author=datatemp;
		getline(outfile, datatemp);
		tempbook->category=datatemp;
		getline(outfile, datatemp);
		tempbook->publisher=datatemp;
		getline(outfile, datatemp);
		tempbook->year=atoi(datatemp.c_str());
		getline(outfile, datatemp);
		tempbook->price=atoi(datatemp.c_str());
		getline(outfile, datatemp);
		date=datatemp;
		getline(outfile, datatemp);
		numberofdate=datatemp;
		numberofdateint=atoi(datatemp.c_str());
		totalprice=totalprice+numberofdateint*tempbook->price;
	}
	outfile.close();
	return totalprice;
}

void add_to_cart_function(account *acc,string ISBN) {

}
void add_to_cart();
//{
//	check role role ko thi return to reader();
//	getline book ISBn
//	check book exist
//	check active
//	add_to_cart_function
//	}
////////////test

void pay();
void cart();
/////////////////////////////////////////////////////////////////////////////
//Doc thong bao


/// chua xong
void show_all_announcement(account *acc) {
	fstream outfile;
	string filename="announcement_"+acc->getUsername()+".txt";
	outfile.open(filename.c_str(), ios::in);
	string datatemp;
//	cout << " __________________________________________________________________________________________"<<endl;
	cout << "| ID thong bao |             Thong bao                 |        Ngay        |   Da doc ?   |\n";
	cout << " __________________________________________________________________________________________"<<endl;
	cout<<endl;
	announcement *temp=new announcement();
	while (getline(outfile,datatemp)) {
		temp->setID(datatemp);
		getline(outfile, datatemp);
		temp->setAnnounce(datatemp);
		getline(outfile, datatemp);
		temp->setDate(datatemp);
		getline(outfile, datatemp);
		temp->setSeen(datatemp);
		cout<<"|"<<setw(14)<<left<<temp->getID()<<"|";
		if(temp->getAnnounce().length()<40) cout<<setw(39)<<left<<temp->getAnnounce();
		else {
			for(int i=0; i<36; i++) cout<<left<<temp->getAnnounce()[i];
			cout<<"...";
		}
		cout<<"|"<<setw(20)<<temp->getDate()<<"|";
		if(temp->getSeen()=="0") cout<<setw(14)<<left<<"Chua doc"<<endl;
		else cout<<setw(14)<<left<<"Da doc"<<endl;
	}
	outfile.close();
}

void delete_entire_announcement(account *acc) {
	system("cls");
	cout<<"Ban co chac muon xoa toan bo thong bao hay khong? "<<endl;
	cout<<"1. Co"<<endl<<"2. Khong"<<endl;
	char choice;
	do {
		fflush(stdin);
		choice=_getch();
		fflush(stdin);
		if(choice!='1'&&choice!='2') cout<<"Lua chon khong dung. Ban hay nhap lai:"<<endl;
	} while(choice!='1'&&choice!='2');
	if(choice=='1') {
		string filename="announcement_"+acc->getUsername()+".txt";
		ofstream outfile;
		outfile.open(filename.c_str(), ofstream::out | ofstream::trunc);
		outfile.close();
		cout<<"Da xoa."<<endl;
		cout<<"Nhan bat ky de tro ve. "<<endl;
		fflush(stdin);
		choice=_getch();
		fflush(stdin);
		read_announcement(acc);
	}
	if(choice=='2') {
		read_announcement(acc);
	}
}

void delete_already_seen_announcement(account *acc) {
	system("cls");
	cout<<"Ban co chac muon xoa thong bao chua doc hay khong? "<<endl;
	cout<<"1. Co"<<endl<<"2. Khong"<<endl;
	char choice;
	do {
		fflush(stdin);
		choice=_getch();
		fflush(stdin);
		if(choice!='1'&&choice!='2') cout<<"Lua chon khong dung. Ban hay nhap lai:"<<endl;
	} while(choice!='1'&&choice!='2');
	if(choice=='1') {
		fstream outfile;
		string filename="announcement_"+acc->getUsername()+".txt";
		outfile.open(filename.c_str(), ios::in);
		fstream temp1;
		temp1.open("temp.txt", ios::out);
		string datatemp;
		announcement *temp=new announcement();
		string date, numberofdate;
		int flag=0;
		while (getline(outfile, datatemp)) {
			temp->setID(datatemp);
			getline(outfile, datatemp);
			temp->setAnnounce(datatemp);
			getline(outfile, datatemp);
			temp->setDate(datatemp);
			getline(outfile, datatemp);
			temp->setSeen(datatemp);
			if (temp->getSeen()=="0") {
				temp1 << temp->getID() << '\n' << temp->getAnnounce() << '\n' << temp->getDate() << '\n' << temp->getSeen() <<endl;
			}
		}
		temp1.close();
		outfile.close();
		remove(filename.c_str());
		rename("temp.txt", filename.c_str());
		cout<<"Da xoa."<<endl;
		cout<<"Nhan bat ky de tro ve. "<<endl;
		fflush(stdin);
		choice=_getch();
		fflush(stdin);
		read_announcement(acc);
	}
	if(choice=='2') read_announcement(acc);
}

	void set_announcement_already_seen(string ID, account *acc) {
		fstream outfile;
		string filename="announcement_"+acc->getUsername()+".txt";
		outfile.open(filename.c_str(), ios::in);
		fstream temp1;
		temp1.open("temp.txt", ios::out);
		string datatemp;
		announcement *temp=new announcement();
		while (getline(outfile,datatemp)) {
			temp->setID(datatemp);
			getline(outfile, datatemp);
			temp->setAnnounce(datatemp);
			getline(outfile, datatemp);
			temp->setDate(datatemp);
			getline(outfile, datatemp);
			temp->setSeen(datatemp);
			if (ID != temp->getID()) {
				temp1 << temp->getID() << '\n' << temp->getAnnounce() << '\n' << temp->getDate() << '\n' << temp->getSeen() <<endl;
			}
			if (ID == temp->getID()) {
				temp->setSeen("1");
				temp1 << temp->getID() << '\n' << temp->getAnnounce() << '\n' << temp->getDate() << '\n' <<  "1" <<endl;
			}
		}
		outfile.close();
		temp1.close();
		remove(filename.c_str());
		rename("temp.txt",filename.c_str());
	}
	void read_announcement_with_ID_function(account *acc, string ID) {
		system("cls");
		fstream outfile;
		string filename="announcement_"+acc->getUsername()+".txt";
		outfile.open(filename.c_str(), ios::in);
		string datatemp;
		announcement *temp=new announcement();
		while (getline(outfile, datatemp)) {
			temp->setID(datatemp);
			getline(outfile, datatemp);
			temp->setAnnounce(datatemp);
			getline(outfile, datatemp);
			temp->setDate(datatemp);
			getline(outfile, datatemp);
			temp->setSeen(datatemp);
			if(ID==temp->getID()) {
				cout<<"Ngay gui: "<<temp->getDate()<<endl; //Check lai ngay gui
				cout<<"Noi dung thong bao:"<<endl;
				cout<<temp->getAnnounce();
			}
		}
		outfile.close();
		set_announcement_already_seen(ID, acc);
		cout<<endl<<"Nhap bat ky de tro ve:"<<endl;
		fflush(stdin);
		char choice;
		choice=_getch();
		fflush(stdin);
		read_announcement(acc);
	}

	void read_announcement_with_ID(account *acc) {
		string ID;
		cout<<"Nhap ma thong bao ban muon doc: "<<endl;
		fflush(stdin);
		getline(cin, ID);
		if(check_ID_Announcement_in_file(acc,ID)==1) read_announcement_with_ID_function(acc,ID);
		else {
			cout<<"Ma thong bao khong dung."<<endl;
			cout<<"Nhan 1 de nhap ma khac."<<endl;
			cout<<"Nhan bat ky (khac so 1) de tro ve."<<endl;
			char choice;
			fflush(stdin);
			choice=_getch();
			fflush(stdin);
			if(choice=='1') read_announcement_with_ID(acc);
			else read_announcement(acc);
		}
	}

	void read_announcement(account *acc) {
		system("cls");
		cout<<"BANG THONG BAO CUA USER "<<acc->getUsername()<<endl<<endl;
		show_all_announcement(acc);
		cout<<endl<<endl;
		cout<<"1. Doc thong bao theo ma so."<<endl;
		cout<<"2. Xoa toan bo thong bao."<<endl;
		cout<<"3. Xoa thong bao da doc."<<endl;
		cout<<"4. Tro ve."<<endl;
		fflush(stdin);
		char choice;
		do {
			fflush(stdin);
			choice=_getch();
			fflush(stdin);
			if(choice!='1'&&choice!='2'&&choice!='3'&&choice!='4') cout<<"Lua chon khong dung. Ban hay nhap lai:"<<endl;
		} while(choice!='1'&&choice!='2'&&choice!='3'&&choice!='4');
		if(choice=='1') read_announcement_with_ID(acc);
		if(choice=='2') delete_entire_announcement(acc);
		if(choice=='3') delete_already_seen_announcement(acc);
	//	if(choice=='4')  //TO DOOOOOOOOO

	}


