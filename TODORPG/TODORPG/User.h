/*@file*/
#pragma once
#include <string>
#include "CycleTask.h"
#include <vector>
#include <cmath>

/**
* Klasa reprezentująca użytkownika
*/
class User
{
public:
	User();
	~User();
	/**
	* Konstruktor wieloargumentowy klasy User
	* @param _username nazwa użytkownika
	* @param _password hasło użytkownika
	* @param _experience doświadczenie użytkownika
	* @param _userTask lista zadań użytkownika
	* @param _userCycleTask lista zadań cyklicznych użytkownika
	*/
	User(std::string _username, std::string _password, int _experience, std::vector<Task*> _userTasks, std::vector<CycleTask*> _userCycleTasks);
	/**
	* Funkcja sprawdza czy podane hasło jest prawidłowe.
	* @param pwd hasło do sprawdzenia
	*/
	bool ValidatePassword(const char * pwd);
	/**
	* Funkcja dodaje zadanie do listy zadań użytkownika.
	* @param t zadanie do dodania
	*/
	void AddTask(Task* t);
	/**
	* Funkcja dodaje zadanie do listy zadań użytkownika przy okazji ustawiając zadany czas.
	* @param t zadanie do dodania
	* @param timeToSet czas na wykonanie zadania
	*/
	void AddTask(Task* t, time_t timeToSet);
	/**
	* Funkcja dodaje zadanie cykliczne do listy zadań cyklicznych użytkownika.
	* @param t zadanie do dodania
	*/
	void AddCycleTask(CycleTask* t);
	/**
	* Funkcja usuwa zadanie z listy zadań użytkownika.
	* @param _id numer id zadania do usunięcia
	*/
	void RemoveTask(int _id);
	/**
	* Funkcja usuwa zadanie cykliczne z listy zadań cyklicznych użytkownika.
	* @param _id numer id zadania do usunięcia
	*/
	void RemoveCycleTask(int _id);
	/**
	* Funkcja usuwa zadanie z listy zadań użytkownika.
	* @param _id numer id zadania do usunięcia
	*/
	void UpdateExperience(TaskDifficulty td, time_t _expDate);
	/**
	* Funkcja zwraca zadanie o podanym id
	* @param _id numer id zadania
	* @return zadanie o podanym numerze id
	*/
	Task* FindTask(int _id);
	/**
	* Funkcja zwraca punkty doświadczenia danego użytkownika 
	* @return punkty doświadczenia danego użytkownika */
	int GetExperience();
	/**
	* Funkcja zwraca poziom danego użytkownika
	* @return poziom danego użytkownika */
	int GetLevel();
	/**
	* Funkcja zwraca liczbę zadań danego użytkownika
	* @return liczba zadań danego użytkownika */
	int GetTasksNumber();
	Task* GetTask(int pos);
	/**
	* Funkcja zwraca json z danego użytkownika. Nie jest to plik, ale obiekt json z biblioteki nlohman json
	* @return json danego użytkownika */
	json ReturnUserJson();
	std::string username; //< nazwa użytkownika
	std::vector<Task*> userTasks; //< vector zadań użytkownika
	std::vector<CycleTask*> userCycleTasks; //< vector zadań cyklicznych użytkownika
private:
	std::string password;//< hasło użytkownika
	int experience;//< doświadczenie użytkownika
	int GetMaxId();
	void CopyTasks(std::vector<Task*> otherTasks);
};

