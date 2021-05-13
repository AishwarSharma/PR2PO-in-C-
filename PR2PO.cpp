#include<iostream>
#include<conio.h> // getch()
#include<string>
#include<fstream>  // for file handling
#include<ctime>    // for current date and time
#include "windows.h"  // for coor


using namespace std;

// Function definition for setting cursor position int the console window
void gotoxy(int x , int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
// price list of items
// Each array index value is used as an identifier for item codes
float price_list[20] = {865,2.25,44,10,20,7710,33.33,48.97,8,0.5,0.01,88,999,25000,87,4,22,200,20,150};

class po; // Forward declaration of po class needed while using friend function

/* class definition */
class requisition
{
    /* Defining data members for storing requisition details */
    static int req_no;
    int item_code;
    int qty;
    string delivery_date;

public:
    /*class function declaration*/
    void get_data();
    void display();
    friend void generate(requisition,po); // Friend function declaration
};

/*Function for receiving requisition details */

void requisition :: get_data()
{
    system("cls");
    req_no++;
    cout<<"Product Item Code: "<<endl;
    cin>>item_code;
    cout<<"Quantity: "<<endl;
    cin>>qty;
    cout<<"Delivery Date: "<<endl;
    cin>>delivery_date;
} 

int requisition :: req_no;  // static defining

// Function for displaying requisition details
void requisition :: display()
{
    system("cls");
    cout<<"Requisition Number : "<<req_no<<endl;
    cout<<"Product Item Code : "<<item_code<<endl;
    cout<<"Quantity : "<<qty<<endl;
    cout<<"Delivery Date : "<<delivery_date<<endl;
    getch();
}

class po
{
    static int po_no;
    public:
    // constructor is used for incrementing the static variable po_no
    po()
    {
        po_no ++;
    }
    friend void generate(requisition,po); // friend function declaration

};

int po :: po_no;

//defining friend function generate()

void generate(requisition r, po p)
{
    ofstream fout;

    /* Retreiving system date and time */
    
    time_t current = time(0);   // current date/time based on current system
    char* dt = ctime(&current);  // convert now to string form

    //opening the Current_PO.text file in which PO details are stored
    fout.open("Current_PO.txt");
    
    //Generating the PO and storing it in the Current_PO.txt file in a formatted manner
    fout<<"\t\t\t Purchase Order#: "<<p.po_no<<endl;
    fout<<"\t\t\t ________________ \n\n";
    fout<<"Requisition#:"<<r.req_no<<"\t\t\t\tIssue Date:"<<dt<<endl;
    
    if(r.item_code >=1 && r.item_code <= 10)
        fout<<"Supplier: "<<"SKS Inc \n\n";
    else if(r.item_code >=11 && r.item_code <= 20)
        fout<<"Supplier: "<<"KC Spare Parts Ltd. \n\n";
    else
        fout<<"Supplier: "<<"Other(___________________)\n\n";
    
    fout<<"Delivery Date: "<<r.delivery_date<<endl;
    fout<<"---------------------------------------------------------------------------------------------"<<endl;
    fout<<"                                  **Line Items**                                              "<<endl;
    fout<<"---------------------------------------------------------------------------------------------"<<endl;
    fout<<"Item Code \t Quantitiy \t Price \t\t Total "<<endl;
    fout<<"_________ \t _________ \t ______\t\t ______ "<<endl;
    fout<<"  "<<r.item_code<<"\t\t\t\t\t\t "<<r.qty<<"\t\t\t";
    
    if(r.item_code >=1 && r.item_code<=20)
        fout<<"  "<<price_list[r.item_code-1]<<"\t\t\t "<<price_list[r.item_code-1]*r.qty<<endl<<endl<<endl;
    else
        fout<<"_ _ _ \t\t\t _ _ _ \n\n\n\n";
    
    ifstream fin;
    string line;
    //Opening the terms.txt file from where standard terms and conditions are copied into the PO
    fin.open("terms.txt");
   
    while(fin.eof()==0)
    {
        getline(fin,line);
        fout<<line<<endl;
    }
    fin.close();
    fout<<"\n\n\n\n Authorized Signatory: \t\t\t\t\t\t     Total: _ _ _ _";
    fout.close(); 
}

/* Main Function */

int main()
{
    requisition r;
    char flag = 'f';
    char ch;

    //Displaying a menu to accept user commands

    while(1)
    {
        int choice;
        system("cls");
        gotoxy(35,8);
        cout<<"PR2PO";
        gotoxy(35,9);
        cout<<"______";
        gotoxy(22,12);
        cout<<"1 - Create New Requisition";
        gotoxy(22,13);
        cout<<"2 - Display Requisition";
        gotoxy(22,14);
        cout<<"3 - Generate PO";
        gotoxy(22,15);
        cout<<"4 - Exit";
        gotoxy(22,18);
        cout<<"Select an option by typing the numeric code: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
            {
                r.get_data();
                flag = 't';
                break;
            }
            
            case 2:
            {
                if(flag == 'f')
                {
                    gotoxy(22,20);
                    cout<<"Requisition details not yet entered ! Press any key to continue ...";
                    getch();
                }
                else
                    r.display();
                break;
            }
            case 3:
            {
                po p;
                generate(r,p);
                gotoxy(22,20);
                cout<<"PR has been converted into a PO. You can view the current_PO.txt file to view the generated PO and take its print out";
                getch();
                break;
            }

            case 4:
            {
                exit(1);
                break;
            }
            default :
            {
                gotoxy(22,20);
                cout<<"Invalid Choice ! Press any key to continue ..";
                getch();
            }
        }  
    }
    return 0;
}