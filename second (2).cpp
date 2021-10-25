#include <bits/stdc++.h>
using namespace std;

class ShoppingCard
{
	public:
	int Card_ID;
	string Customer_Name;
	int Points;
	int DOB_Date;
	int DOB_Month;
	int DOB_Year;
	int Lasttransaction_Date;
	int Lasttransaction_Month;
	int Lasttransaction_Year;
	string Address;
	ShoppingCard * nextCard;
};

class Item
{
	public:
		int Item_ID;
	string Item_Name;
	float Price;
	int Quantity;
	Item * nextItem;
};

ShoppingCard *Shopping_head = NULL;
Item *Item_head = NULL;

void AddCustomer(int CardID, string CustomerName, int Points, int DDate, int DMonth int DYear, int LTDDate, int LTDMonth, int LTDYear, string address)
{
	ShoppingCard *t = new ShoppingCard();
	t->Card_ID = CardID;
	t->Customer_Name = CustomerName;
	t->Points = Points;
	t->DOB_Date = DDate;
	t->DOB_Month = DMonth;
	t->DOB_Year = DYear;
	t->Lasttransaction_Date = LTDDate;
	t->Lasttransaction_Month = LTDMonth;
	t->Lasttransaction_Year = LTDYear;
	t->Address = address;
	if (Shopping_head == NULL) Shopping_head = t;
	else
	{
		t->nextCard = Shopping_head;
		Shopping_head = t;
	}
}

void AddItems(int ItemID, string ItemName, float price, int quantity)
{
	Item *t = new Item();
	t->Item_ID = ItemId;
	t->Item_Name = ItemName;
	t->Price = price;
	t->Quantity = quantity;
	if (Item_head == NULL) Item_head = t;
	else
	{
		t->nextItem = Item_head;
		Item_head = t;
	}
}

void UpdateAddress()
{
	int CID;
	cout << "Enter the Card ID of the Customer: ";
	cin >> CID;
	ShoppingCard *t = new ShoppingCard();
	while (t != NULL)
	{
		if (t->Card_ID == CID)
		{
			string new_address;
			cout << "Please update the address: ";
			cin >> new_address;
			t->Address = new_address;
			cout << "Congratulations! Address updated successfully."
			return;
		}
		t = t->nextCard;
	}
	cout << "There is no Customer with that ID. Please try again." << endl;
	return;
}

void DisplayContents()
{
	int CID;
	cout << "Enter the Card ID of the Customer: ";
	cin >> CID;
	ShoppingCard *t = new ShoppingCard();
	t = Shopping_head;
	while (t != NULL)
	{
		cout << "The ID of the Shopping Card: " << t->Card_ID << endl;
		cout << "Name of the customer: " << t->Customer_Name << endl;
		cout << "Total Points accumulated by the Customer: " << t->Points << endl;
		cout << "Customer Date of Birth: " << t->DOB_Date << " / "
		t->DOB_Month << " / " << t->DOB_Year << endl;
		cout << "Customer Date of Transaction: " << t->Lasttransaction_Date << " / "
		t->Lasttransaction_Month << " / " << t->Lasttransaction_Year << endl;
		cout << "Address of the Customer: " << t->Address << endl;
		t = t->nextCard;
	}
	Item *s = new Item();
	s = Item_head;
	while (s != NULL)
	{
		cout << "ID of the item: " << s->Item_ID;
		cout << "Name of the item: " << s->Item_Name;
		cout << "Price of the item: " << s->Price;
		cout << "Quantity of the item: " << s->Quantity;
		s = s->nextItem;
	}
	return;
}
