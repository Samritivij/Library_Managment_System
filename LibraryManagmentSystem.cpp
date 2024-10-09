#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<iostream>
 
using namespace std;
 
class book
{
          char book_number[30];
          char book_name[50];
          char author_name[20];
          int num_copies;
 
  public:
          void get_book_details()											// to get data from the user//
          {
          			cout<<"\nENTER DETAILS ABOUT BOOK U WANT TO DONATE\n";
                    cout<<"\nEnter The Book Number: ";
                    cin>>book_number;
                    cout<<"\nEnter The Name of The Book: ";
                     cin.ignore();
                    cin.getline(book_name,50);
                    cout<<"\nEnter The Author's Name: ";
                    cin.ignore();
                    cin.getline(author_name,50);
                    fflush(stdin);
           			cout<<"\nEnter No. Of Copies : ";
    				cin>>num_copies;
          }
 
          void show_book()														// to display the data from the library//
          {
                    cout<<"\nBook Number: "<<book_number;
                    cout<<"\nBook Name: "<<book_name;
                    cout<<"\nAuthor's Name: "<<author_name;
                    cout<<"\nCOPIES : "<<num_copies;
          }
          void modify_book()													// to modify the data from the Library//
          {
                    cout<<"\n The Book number : "<<book_number;
                    cout<<"\n To Modify Book Name : ";
                    cin.ignore();
                    cin.getline(book_name,50);
                    cout<<"\n To Modify Author's Name: ";
                    cin.ignore();
                    cin.getline(author_name,50);
                    fflush(stdin);
       				cout<<"\nEnter The Number Of Copies : ";
    				cin>>num_copies;
          }
          char* getbooknumber()													// member function defined in the function//
          {
                    return book_number;
          }
          void report()                                                          // member function added in the function//
          {cout<<book_number<<setw(30)<<book_name<<setw(30)<<author_name<<setw(30)<<num_copies<<endl;}
 
};        
 
       
 
 
 
 
void design()																	// to provide The design to the programme//
{
     system("cls");
  cout<<"\t\t\t\t####\t####";
  cout<<"\t\t\t\t#####\t#####";
   cout<<"\t\t\t\t######\t######";
   cout<<"\t\t\t\t#######\t#######";
   cout<<"\t\t\t\t########\t########";
	cout<<"\t\t\t\t############\t##########";
   cout<<"\t\t\t\t##########\t##########";
   cout<<"\t\t\t\t##########\t##########";
   cout<<"\t\t\t\t########\t##########";
   cout<<"\t\t\t\t############\t##########";
   cout<<"\t\t\t\t#######\t#######";
   cout<<"\t\t\t\t######\t######";
   cout<<"\t\t\t\t####\t#####";
   cout<<"\t\t\t\t##\t##";
}
fstream fp;
book bk;
void write_book()																	//case1 to add the data in the files of person donated books//
{
          system("cls");
          int more_or_main;
          fp.open("book.dat",ios::out|ios::app);
          do
          {
                    bk.get_book_details();
                    fp.write((char*)&bk,sizeof(book));
                    cout<<"\nPress 1 To Add More Books";
                    cout<<"\nPress 2 To Retuen To Menu\n";
                    cout<<"Enter: ";
                    cin>>more_or_main;
          }while(more_or_main == 1);
          fp.close();
}
 void display_allb()																//case2 to show the available data of books in the library//
{
          system("cls");
          fp.open("book.dat",ios::in);
          if(!fp)
          {
                    cout<<"Error file Is Not In The Library";
                    getch();
                    return;
          }
          cout<<"\n\n\t\tList Of the Books In The Library\n\n";
           cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author"<<setw(25)<<"Copies"<<endl;
          while(fp.read((char*)&bk,sizeof(book)))
          {
                    bk.report();
          }
          fp.close();
          getch();
}
void display_a_book(char n[])														// display the data of the book searched by the user //
{
          system("cls");
          cout<<"\nBook Details In The Library:::\n";
          int check=0;
          fp.open("book.dat",ios::in);
          while(fp.read((char*)&bk,sizeof(book)))
          {
                    if(strcmpi(bk.getbooknumber(),n)==0)
                    {
                               bk.show_book();
                              check=1;
                    }
          }
          fp.close();
          if(check==0)
                    cout<<"\n\nBook does not exist";
        getch();
}
void modify_book()																	// to modify the data of the book by the user//
{
          system("cls");
          char n[20];
          int found=0;
          cout<<"\n\n\tTo Modify The Data Of The Book";
          cout<<"\n\n\tEnter The book number As A Character: ";
          cin>>n;
          fp.open("book.dat",ios::in|ios::out);
          while(fp.read((char*)&bk,sizeof(book)) && found==0)
          {
                    if(strcmpi(bk.getbooknumber(),n)==0)
                    {
                               bk.show_book();
                               cout<<"\nEnter The New Details of book"<<endl;
                               bk.modify_book();
                               int pos=-1*sizeof(bk);
                              fp.seekp(pos,ios::cur);
                              fp.write((char*)&bk,sizeof(book));
                              cout<<"\n\n\t Book Updated Successfully";
                              found=1;
                    }
          }
          fp.close();
          if(found==0)
                    cout<<"\n\n Book Not Found In Library ";
          getch();
}
 
void delete_book()																	// to delete the book from the files
{
          system("cls");
          char n[20];
          int flag=0;
          cout<<"\n\n\n\tDelete the book from library";
          cout<<"\n\nEnter The Book's number As A Character You Want To Delete: ";
          cin>>n;
          fp.open("book.dat",ios::in|ios::out);
          fstream fp2;
          fp2.open("Temp.dat",ios::out);
          fp.seekg(0,ios::beg);
          while(fp.read((char*)&bk,sizeof(book)))
          {
                    if(strcmpi(bk.getbooknumber(),n)!=0)  
                    {
                               fp2.write((char*)&bk,sizeof(book));
                    }
                    else
                              flag=1;
          }
          fp2.close();
          fp.close();
          remove("book.dat");
          rename("Temp.dat","book.dat");
          if(flag==1)
                    cout<<"\n\n\tBook Deleted From The Library";
          else
                    cout<<"\n\nBook Not Found In Library";
          getch();
}


 
 
int main()
{
		
          int option = 0;
          for(;;)
          {
              design();
              cout<<"\n\n";
              cout<<"Submitted By Vishal Kathpalia"<<endl;
              cout<<"\nSubmitted To Vipin Kumar\n";
            cout<<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
                cout<<"\n\t\t@@Press 1 To Donate The Book In The Library";
                cout<<"\n\t\t@@Press 2 To Show All The Data Of the books";
                cout<<"\n\t\t@@Press 3 To Check The Availability Of The Books In Library";
                cout<<"\n\t\t@@Press 4 To Modify The Data Of The Books";
                cout<<"\n\t\t@@Press 5 To Delete The Book From The Library";
                cout<<"\n\t\t@@Press 6 TO Exit From The Menu";
 			cout<<"\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
 			cout<<"\n\t\tOption: ";
 			cin>>option;
 			switch(option)
          	{
                    case 1:  system("cls");
                                         write_book();
                                                   break;
                               case 2: display_allb();
                                 break;
                    case 3:
                              char num[20];
                               system("cls");
                              cout<<"\n\n\tPlease Enter The Book Number As A Character Saved in File";
                              cin>>num;
                              display_a_book(num);
                              break;
                    case 4: modify_book();break;
                    case 5: delete_book();break;
                    case 6: exit(0);
                               break;
                    default:cout<<"\a";
          }     
       
      }
  }
