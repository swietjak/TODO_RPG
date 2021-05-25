/*@file*/
#pragma once
#include <vector>
#include "User.h"
#include <fstream>

using json = nlohmann::json;
/**
* Klasa przechowująca listę użytkowników w programie
*/
class UsersList
{
public:
	/**
	* Funkcja służy do znalezienia użytkownika i sprawdzeniu czy podane hasło jest prawidłowe.
	* @param username nazwa użytkownika
	* @param password hasło podane przy logowaniu
	* @return znaleziony użytkownik
	*/
	User* FindAndVerifyUser(const char* username, const char* password);
	/**
	* Funkcja służy do znalezienia użytkownika.
	* @param username nazwa użytkownika
	* @return znaleziony użytkownik
	*/
	User* FindUser(const char* username);
	/**
	* Funkcja zwraca statystyki wszystkich użytkowników
	*/
	std::multimap<std::string, std::pair<int, int>> GetUsersStats();
	std::string json_text;
	UsersList();
	~UsersList();
	/**
	* Konstruktor jednoargumentowy klasy UsersList
	* @param filename plik tekstowy w formacie jso z którego ma być wczytana lista użytkowników
	*/
	UsersList(const char* filename);
	/**
	* Funkcja dodaje użytkownika do listy
	* @param usr użytkownik, który ma być dodany do listy
	*/
	void AddUser(User* usr);
	/**
	* Funkcja usuwa zadanie z listy zadań użytkownika podanego w parametrze
	* @param username użytkownik, którego zadanie ma być usunięte
	* @param _id numer id zadania
	*/
	void RemoveTask(const char* username, int _id);
	/**
	* Funkcja uaktualnia plik json po wprowadzeniu zmian w użytkownika
	*/
	void UpdateJson();
private:
	json j;
	std::vector<User*> List; //< Lista użytkowników
	std::vector<Task*> FetchTasks(json tasks);
	std::vector<CycleTask*> FetchCycleTasks(json tasks);
	TaskDifficulty ReturnEnumFromJson(std::string difficulty);
};

