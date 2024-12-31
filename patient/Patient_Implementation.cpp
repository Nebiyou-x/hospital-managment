#include "Patient.h"

#include <string>

using namespace std;

// default Patient constructor
Patient::Patient(int patientId, const string& firstName, const string& lastName,
	int age, char sex, const string& date,
	const string& medicalHistory, const string& familyDisease) : id(patientId), age(age), sex(sex)
{
	setFirstName(firstName);
	setLastName(lastName);
	setDate(date);
	setMedicalHistory(medicalHistory),
		setFamilyDisease(familyDisease);
}

// set patient id 
void Patient::setId(int patientId) {
	id = patientId;
}

// get patient id
int Patient::getId() const { return id; }

// set patient first name
void Patient::setFirstName(const string& fname)
{
	// copy at most 30 characters from string to firstName
	size_t length{ fname.size() };
	length = (length < 30 ? length : 29);
	fname.copy(firstName, length);
	firstName[length] = '\0'; // append null character to firstName
}

// get patient first name
string Patient::getFirstName() const { return firstName; }

// set patient last name
void Patient::setLastName(const string& lname)
{
	// copy at most 30 character from string to last name
	size_t length{ lname.size() };
	length = (length < 30 ? length : 29);
	lname.copy(lastName, length);
	lastName[length] = '\0'; // append null charachter to lastName
}

// get patient last name
string Patient::getLastName() const { return lastName; }

// set patient age
void Patient::setAge(int patientAge)
{
	age = patientAge;
}

// get patient age
int Patient::getAge() const { return age; }

// set patient sex
void Patient::setSex(char patientSex)
{
	sex = patientSex;
}

// get patient sex
char Patient::getSex() const { return sex; }

// set patient registration date
void Patient::setDate(const string& dateOfRegistration)
{
	date = dateOfRegistration;
}

// get patient registration date
string Patient::getDate() const { return date; }

// set patient past medical history 
void Patient::setMedicalHistory(const string& medicalHistory)
{
	// copy at most 70 characters from string to past medical history
	size_t length{ medicalHistory.size() };
	length = (length < 70 ? length : 69);
	medicalHistory.copy(pastMedicalHistory, length);
	pastMedicalHistory[length] = '\0'; // append null character to past medical history
}

// get patient past medical history
string Patient::getMedicalHistory() const { return pastMedicalHistory; }

// set patient's family disease
void Patient::setFamilyDisease(const string& fDisease)
{
	// copy at most 50 characters from string to family disease
	size_t length{ fDisease.size() };
	length = (length < 50 ? length : 49);
	fDisease.copy(pastMedicalHistory, length);
	pastMedicalHistory[length] = '\0'; // append null character to past Medical History
}
