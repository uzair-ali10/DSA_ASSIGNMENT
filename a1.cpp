#include <bits/stdc++.h>
using namespace std;

class Student {
public:
	string name;
	int rollNO;
	int CGPA;
	int branchID;
	int univID;
	Student* nextStudent;
};

class University{
public:
	int univID;
	string univName;
	string univLocation;
	int foundingYear;
	University *nextUniversity;
};

struct Branch{
public:
	int branchID;
	string branchName;
	int univID;
	Branch* nextBranch;
};

Student *stu_head = NULL;
University *univ_head = NULL;
Branch *branch_head = NULL;

void insertStudent(int roll, string name, int cgpa, int branchID, int universityID)
{
	Student* t = new Student();
	t->rollNO = roll;
	t->name = name;
	t->branchID = branchID;
	t->univID = universityID;

	if(stu_head==NULL)
	{
		stu_head = t;
	}
	else
	{
		t->nextStudent = stu_head;
		stu_head = t;
	}
}

bool isUniqueStu(int in_roll)
{
	Student *temp = new Student();
	temp = stu_head;

	while(temp!=NULL)
	{
		if(temp->rollNO == in_roll)
		{
			return false;
		}
		temp = temp->nextStudent;
	}
	return true;
}

void insertUniversity(int uid, string uname, string uloc, int yr)
{
	University *t = new University();
	t -> univID = uid;
	t -> univName = uname;
	t -> univLocation = uloc;
	t -> foundingYear = yr;

	if(univ_head==NULL)
	{
		univ_head = t;
	}
	else
	{
		t->nextUniversity = univ_head;
		univ_head = t;
	}
}

void insertBranch(int bid, string bname, int uid)
{
	Branch *t = new Branch();
	t -> branchID = bid;
	t -> branchName = bname;
	t -> univID = uid;

	if(branch_head==NULL)
	{
		branch_head = t;
	}
	else
	{
		t->nextBranch = branch_head;
		branch_head = t;
	}
}

int main() {
// #ifndef ONLINE_JUDGE
// 	freopen("input.txt", "r", stdin);
// 	freopen("output.txt", "w", stdout);
// #endif

while(true) 
{
	cout<<"Wlcm to Student Record management!!!\nEnter 1 to create a new Student Record\nEnter 2 to create a new University Record\nEnter 3 to create a new Branch Record\n";
	cout<<"Enter Your Choice"<<endl;
	int choice;

	cin>>choice;

	if(choice==1)
	{
		cout<<"Enter Roll No of Student: "<<endl;
		int roll_num; cin>>roll_num;
		if(isUniqueStu(roll_num)==false)
		{
			cout<<"An Record with the given Roll No Already Exists"<<endl;
			break;
		}

		cout<<"Enter Name of Student: "<<endl;
		string name_stu; cin>>name_stu;

		cout<<"Enter CGPA of Student: "<<endl;
		int cgpa_stu; cin>>cgpa_stu;

		cout<<"Enter Branch ID of Student: "<<endl;
		int bid_stu; cin>>bid_stu;

		cout<<"Enter University ID of Student: "<<endl;
		int uid_stu; cin>>uid_stu;
		insertStudent(roll_num, name_stu, cgpa_stu, bid_stu, uid_stu);
		cout<<"Student Record Created!!"<<endl;
	}
	else if(choice==2)
	{
		cout<<"Enter Name of University: "<<endl;
		string uname; cin>>uname;

		cout<<"Enter University's ID: "<<endl;
		int uid; cin>>uid;

		cout<<"Enter University's Location: "<<endl;
		string loc; cin>>loc;

		cout<<"Enter University's Founding Year: "<<endl;
		int yr; cin>>yr;
		insertUniversity(uid, uname, loc, yr);
		cout<<"University Record Created!!"<<endl;
	}
	else if(choice==3)
	{
		cout<<"Enter Branch ID: ";
		int bid; cin>>bid;

		cout<<"Enter Branch Name: ";
		string bname; cin>>bname;

		cout<<"Enter University ID: ";
		int uid; cin>>uid;

		insertBranch(bid, bname, uid);
		cout<<"Branch Record Created!!"<<endl;
	}
}
return 0;
}
