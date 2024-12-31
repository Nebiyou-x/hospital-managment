
#pragma once
#include <string>



// class Patient definition

class Patient
{
public:
	// default Patient constructor
	Patient(int = 0, const std::string & = "", const std::string & = "",
		int = 0, char = '\0', const std::string & = "",
		const std::string & = "", const std::string & = "");

	// accessor functions for patient Id
	void setId(int);
	int getId() const;

	// accessor functions for patient firstName
	void setFirstName(const std::string&);
	std::string getFirstName() const;

	// accessor functions for patient lastName
	void setLastName(const std::string&);
	std::string getLastName() const;

	// accessor functions for patient age
	void setAge(int);
	int getAge() const;

	// accessor functions for patient sex
	void setSex(char);
	char getSex() const;

	// accessor functions for date
	void setDate(const std::string&);
	std::string getDate() const;

	// accessor functions for past medical history 
	void setMedicalHistory(const std::string&);
	std::string getMedicalHistory() const;

	// accessor functions for family disease
	void setFamilyDisease(const std::string&);
	std::string getFamilyDisease() const;

private:
	int id;
	char firstName[17];
	char lastName[17];
	int age;
	char sex;
	char date[11];
	char pastMedicalHistory[70];
	char familyDisease[50];

};






