import sqlite3
import datetime
from datetime import date

conn = sqlite3.connect('test.db')
print ("Connection to DB Established");
print("\n")
sale_date = None

def create_card_table():
	conn.execute('''CREATE TABLE CARD
	         (ID 			   INT PRIMARY KEY      NOT NULL,
	         NAME              TEXT    				NOT NULL,
	         POINTS            INT     				NOT NULL,
	         IS_ELIGBLE        INT     				NOT NULL,
	         TRASACTION_DATE   DATE     					,
	         DOB   			   DATE     			NOT NULL,
	         AGE   			   DATE     			NOT NULL,
	         ADDRESS           TEXT);''')
	print ("Card Table created successfully");

def create_item_table():
	conn.execute('''CREATE TABLE ITEM
	         (ID 			   INT PRIMARY KEY      NOT NULL,
	         NAME              TEXT    				NOT NULL,
	         CATEGORY          TEXT     			NOT NULL,
	         PRICE             INT     				NOT NULL,
	         QUANTITY          INT 					NOT NULL);''')
	print ("Item Table created successfully");


def add_item():
	item_id = input("Enter Item ID: ")
	item_name = input("Enter Name: ")
	item_category = input("Enter Category (grocery, clothing or electronics: ")
	item_price = input("Enter Price: ")
	item_quantity = input("Enter Quantity: ")
	query = "INSERT INTO ITEM (ID,NAME,CATEGORY,PRICE,QUANTITY) VALUES (?,?,?,?,?);"
	data = (item_id, item_name, item_category, item_price, item_quantity)
	conn.execute(query,data)
	conn.commit()
	print("Item Added Sucessfully")


def add_card():
	card_id = input("Enter Card ID: ")
	customer_name = input("Enter Customer Name: ")
	customer_points = 0
	is_eligble = 0
	dob_year = int(input("Enter Year of Birth: "))
	dob_month = int(input("Enter Month of Birth: "))
	dob_day = int(input("Enter Day of Birth: "))
	customer_dob = datetime.date(dob_year, dob_month, dob_day)
	custome_age = calculateAge(customer_dob)
	customer_adress = input("Enter Customer Address: ")

	query = "INSERT INTO CARD (ID,NAME,POINTS,IS_ELIGBLE,TRASACTION_DATE,DOB,AGE,ADDRESS) VALUES (?,?,?,?,?,?,?,?);"
	data = (card_id, customer_name, customer_points, is_eligble, None,customer_dob, custome_age, customer_adress)
	conn.execute(query, data)
	conn.commit()
	print("New Card Created")


def calculateAge(birthDate):
    today = date.today()
    age = today.year - birthDate.year - ((today.month, today.day) < (birthDate.month, birthDate.day))
    return age

def find_eligblity(user_id):
	search_query = "SELECT * from CARD WHERE ID=?"
	search_data = (user_id,)
	search_result = conn.execute(search_query, search_data)
	rows = search_result.fetchall()
	return (rows[0][3])

def buy_product():
	user_id = input("Enter Card's ID:")
	product_id = input("Enter ID of Product You Want To Buy: ")
	is_eligble = find_eligblity(user_id)
	query = "SELECT * from ITEM WHERE ID=?"
	result = conn.execute(query, product_id)
	rows = result.fetchall()
	product_cat = (rows[0][2])
	product_price = (rows[0][3])
	product_qyt = int(input("Enter Quatity: "))
	total = product_price * product_qyt
	print("Price to be paid: ", total)

	if product_cat == "grocery":
		if is_eligble:
			discount = total/10
			print("Discount of ", discount, " Applied")
			total = total - discount
			print("Price After Discount: ", total)
			points = 1 // (total * 100)
			set_points_zero(user_id)
			update_transaction_date(user_id)
			decrease_quantity(user_id, product_qyt)
		else:
			points = 1 // (total * 100)
			update_points(points, user_id)
			update_transaction_date(user_id)
			decrease_quantity(user_id, product_qyt)
	elif product_cat == "garments":
		if is_eligble:
			discount = total/10
			print("Discount of ", discount, " Applied")
			total = total - discount
			print("Price After Discount: ", total)
			points = 1 // (total * 100)
			set_points_zero(user_id)
			update_transaction_date(user_id)
			decrease_quantity(user_id, product_qyt)
		else:
			points = 1 // (total * 100)
			update_points(points, user_id)
			update_transaction_date(user_id)
			decrease_quantity(user_id, product_qyt)
	else:
		if is_eligble:
			discount = total/10
			print("Discount of ", discount, " Applied")
			total = total - discount
			print("Price After Discount: ", total)
			points = 1 // (total * 100)
			set_points_zero(user_id)
			update_transaction_date(user_id)
			decrease_quantity(user_id, product_qyt)
		else:
			points = 10 / (total * 100)
			update_points(points, user_id)
			update_transaction_date(user_id)
			decrease_quantity(user_id, product_qyt)



def decrease_quantity(product_id, qty):
	search_query = "SELECT * from ITEM WHERE ID=?"
	data = (product_id,)
	result = conn.execute(search_query, data)
	rows = result.fetchall()
	current_qty = (rows[0][4])
	new_qty = current_qty - qty

	update_query = "UPDATE ITEM set QUANTITY = ? where ID = ?"
	data = (new_qty, product_id)
	update_result = conn.execute(update_query,data)
	conn.commit()
	print("Quantity Decreased")


def update_transaction_date(card_id):
	search_query = "SELECT * from CARD WHERE ID=?"
	result = conn.execute(search_query, (card_id,))
	update_query = "UPDATE CARD set TRASACTION_DATE = ? where ID = ?"
	data = (datetime.date.today(), card_id)
	update_result = conn.execute(update_query,data)
	conn.commit()
	print("Date of Transaction Updated")

def set_points_zero(card_id):
	update_query = "UPDATE CARD set POINTS = ? where ID = ?"
	data = (0, card_id)
	update_result = conn.execute(update_query,data)
	conn.commit()
	rows = update_result.fetchall()
	print("Points Updated Sucessfully to 0")

def update_points(points, card_id):
	search_query = "SELECT * from CARD WHERE ID=?"
	result = conn.execute(search_query, (card_id,))
	rows = result.fetchall()
	old_points = rows[0][2]
	new_points = old_points + points

	update_query = "UPDATE CARD set POINTS = ? where ID = ?"
	data = (new_points, card_id)
	update_result = conn.execute(update_query,data)
	conn.commit()
	rows = update_result.fetchall()
	print("Points Updated Sucessfully By ", points)


def db_cleanup():
	search_query = "DELETE FROM CARD WHERE DOB <= date('now', '-365 day')"
	data = (datetime.date.today(),)
	result = conn.execute(search_query)
	conn.commit()
	print("Inactive Cards Deleted Sucessfully")


def display_products():
	query = "SELECT ID, NAME, CATEGORY, PRICE, QUANTITY from ITEM"
	cursor = conn.execute(query)
	for row in cursor:
		print("ID: ", row[0])
		print("Name: ", row[1])
		print("Category: ", row[2])
		print("Price: ", row[3])
		print("Quantity: ", row[4])
		print("\n")

def update_adress():
	card_id = input("Enter Card ID: ")
	new_adress = input("Enter New Aderess: ")
	update_query = "UPDATE CARD set ADDRESS = ? where ID = ?"
	data = (new_adress, card_id)
	conn.execute(update_query, data)
	conn.commit()
	print("Adress Updated")


def update_eligblity(user_id):
	query = "UPDATE CARD set IS_ELIGBLE = 1 WHERE ID=?"
	data = (user_id,)
	conn.execute(query, data)
	conn.commit()
	print("Customer with ID: ", user_id, " is eligble for Discount")


def get_eligble_customers():
	query = "SELECT * from CARD WHERE POINTS >= 1000"
	result = conn.execute(query)
	rows = result.fetchall()
	for row in rows:
		update_eligblity(row[0])

def get_eligble_senior_customers():
	query = "SELECT * from CARD WHERE POINTS >= 1000 and AGE >=60"
	result = conn.execute(query)
	rows = result.fetchall()
	for row in rows:
		update_eligblity(row[0])


def display_cards():
	query = "SELECT ID, NAME, POINTS, ADDRESS from CARD"
	cursor = conn.execute(query)
	for row in cursor:
		print("ID: ", row[0])
		print("Name: ", row[1])
		print("Points: ", row[2])
		print("Address: ", row[3])
		print("\n")

def announce_sale():
	yr = int(input("Enter Year: "))
	mo = int(input("Enter Month: "))
	dy = int(input("Enter Day: "))
	# global sale_date = datetime.date(yr, mo, dy)
	global sale_date
	sale_date = datetime.date(yr, mo, dy)

def get_discount():
	disc_year = int(input("Enter Year of Birth: "))
	disc_month = int(input("Enter Month of Birth: "))
	disc_day = int(input("Enter Day of Birth: "))
	discount_date = datetime.date(disc_year, disc_month, disc_day)


def main_menu():
	while True:
		print("1. Add a Card")
		print("2. Diaplay All Avaliable Cards")
		print("3. Add a item")
		print("4. Display All Avaliable Items")
		print("5. Purchase a Product")
		print("6. Update Aderess")
		print("7. DB Cleanup")
		print("8. Exit")
		print("9. Create Card Table")
		print("10. Create Item Table")
		print("11. Announce Sale")
		print("12. Announce Sale For Senior Citizens")
		choice = int(input("Enter Your Choice: "))

		if choice == 1:
			add_card()
		if choice == 2:
			display_cards()
		if choice == 3:
			add_item()
		if choice == 4:
			display_products()
		if choice == 5:
			if(datetime.date.today() == sale_date):
				print("Its a Sale!!!!!!")
				get_eligble_customers()
			buy_product()
		if choice == 6:
			update_adress()
		if choice == 7:
			db_cleanup()
		if choice == 8:
			conn.close()
			exit()
		if choice == 9:
			create_card_table()
		if choice == 10:
			create_item_table()
		if choice == 11:
			announce_sale()
		if choice == 12:
			announce_sale()
			get_eligble_senior_customers()



main_menu()

conn.close()
