#include "pch.h"
#include <iostream>
#include <string>

class PersonData
{
private:
	std::string m_firstName;
	std::string m_lastName;
	std::string m_address;
	std::string m_city;
	std::string m_state;
	int m_zip;
	int m_phone;
public:
	PersonData(std::string first, std::string last, std::string address
		, std::string city, std::string state, int zip, int phone)
	{
		m_firstName = first;
		m_lastName = last;
		m_address = address;
		m_city = city;
		m_state = state;
		m_zip = zip;
		m_phone = phone;
	}
	PersonData() { PersonData("", "", "", "", "", 0, 0); }
	virtual ~PersonData() {}
	void setFirstName(std::string first) { m_firstName = first; }
	void setLastName(std::string last) { m_lastName = last; }
	void setAddress(std::string address) { m_address = address; }
	void setCity(std::string city) { m_city = city; }
	void setState(std::string state) { m_state = state; }
	void setZip(int zip) { m_zip = zip; }
	void setPhone(int phone) { m_phone = phone; }
	std::string getFirstName() { return m_firstName; }
	std::string getLastName() { return m_lastName; }
	std::string getAddress() { return m_address; }
	std::string getCity() { return m_city; }
	std::string getState() { return m_state; }
	int getZip() { return m_zip; }
	int getPhone() { return m_phone; }
};

class CustomerData : public PersonData
{
private:
	int m_customerNumber;
	bool m_mailingList;
public:
	CustomerData(int customerNum, bool mailList) : PersonData()
	{
		m_customerNumber = customerNum;
		m_mailingList = mailList;
	}
	CustomerData() : PersonData()
	{
		m_customerNumber = 0;
		m_mailingList = false;
	}
	virtual ~CustomerData() {}
	void setCustomerNum(int customerNum)
	{
		m_customerNumber = customerNum;
	}
	void setMailingList(bool mailList) 
	{
		m_mailingList = mailList; 
	}
	int getCustomerNum() { return m_customerNumber; }
	int getMailingList() { return m_mailingList; }
};

class PreferredCustomer : public CustomerData
{
private:
	double m_purchasesAmount;
	double m_discountLevel;
	void adjustDiscount()
	{
		if (m_purchasesAmount < 500)
			m_discountLevel = 0;
		else if (m_purchasesAmount >= 500 && m_purchasesAmount < 1000)
			m_discountLevel = .05;
		else if (m_purchasesAmount >= 1000 && m_purchasesAmount < 1500)
			m_discountLevel = .06;
		else if (m_purchasesAmount >= 1500 && m_purchasesAmount < 2000)
			m_discountLevel = .07;
		else
			m_discountLevel = .1;
	}
	double validatePurchase(double purchases)
	{
		while (purchases < 0)
		{
			std::cout << "Purchase cannot be a negative value. "
				<< "Input purchase again: ";
			std::cin >> purchases;
			std::cout << std::endl;
		}
		return purchases;
	}
public:
	PreferredCustomer(double purchases, int customerNum, bool mailList) :
		CustomerData(customerNum, mailList)
	{
		m_purchasesAmount = validatePurchase(purchases);
		adjustDiscount();
	}
	PreferredCustomer(double purchases) : CustomerData()
	{
		m_purchasesAmount = validatePurchase(purchases);
		adjustDiscount();
	}
	PreferredCustomer() : CustomerData()
	{
		m_purchasesAmount = 0;
		m_discountLevel = 0;
	}
	void addPurchasesAmount(double purchases)
	{
		m_purchasesAmount += validatePurchase(purchases);
		adjustDiscount();
	}
	double getPurchasesAmount() { return m_purchasesAmount; }
	double getDiscountLevel() { return m_discountLevel; }
};

int main()
{
	PreferredCustomer billy(0, 12345, false);
	billy.setFirstName("Billy");
	billy.setLastName("Bronco");
	billy.setAddress("3801 West Temple Ave");
	billy.setCity("Pomona");
	billy.setState("CA");
	billy.setZip(91768);
	billy.setPhone(8697659);
	std::string mail;

	if (billy.getMailingList())
		mail = "Yes";
	else
		mail = "No";
	
	std::cout << "Customer Name: " << billy.getFirstName()
		<< " " << billy.getLastName() << "\n"
		<< "Address: " << billy.getAddress() << " "
		<< billy.getCity() << " " << billy.getState()
		<< " " << billy.getZip() << "\n" << "Phone number: "
		<< billy.getPhone() << "\nCustomer Number: "
		<< billy.getCustomerNum() << "\nIs the customer on the mail List?"
		<< " " << mail << std::endl;

	std::cout << "Adding $700 of purchases: \n";
	billy.addPurchasesAmount(700);
	std::cout << "Current discount level: " << billy.getDiscountLevel()
		<< "\nAdding $800 of purchases: \n";
	billy.addPurchasesAmount(800);
	std::cout << "Current discount level: "
		<< billy.getDiscountLevel() << "\nTesting input validation: "
		<< "Adding -$300 of purchases" << std::endl;
	billy.addPurchasesAmount(-300);
	return 0;
}