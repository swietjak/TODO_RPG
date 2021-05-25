/*@file*/
#pragma once
#include <string>
#include <ctime>
#include "json.hpp"
#include "TaskDifficulty.h"
#define DAY (24*60*60*1.0)

using json = nlohmann::json;
/**
* Klasa implementująca zadanie
*/
class Task
{
public:
	/**
	* Konstruktor wieloargumentowy klasy Task
	* @param _id id zadania
	* @param _taskTitle tytuł zadania
	* @param _taskDescription opis zadania
	* @param _taskCreatedAt data utworzenia zadania
	* @param _taskExpirationDate data ukończenia zadania
	* @param _td poziom trudności zadania
	*/
	Task(int _id, std::string _taskTitle, std::string _taskDescription, std::time_t _taskCreatedAt, std::time_t _taskExpirationDate, TaskDifficulty _td);
	/**
* Konstruktor wieloargumentowy klasy Task
* @param _id id zadania
* @param _taskTitle tytuł zadania
* @param _taskDescription opis zadania
* @param _taskExpirationDate data ukończenia zadania
* @param _td poziom trudności zadania
*/
	Task(int _id, std::string _taskTitle, std::string _taskDescription, std::time_t _taskExpirationDate, TaskDifficulty _td);
	~Task();
	/**
	* @return id zadania
	*/
	int GetId();
	/**
	* @return tytuł zadania
	*/
	std::string GetTitle();
	/**
	* @return opis zadania
	*/
	std::string GetDescription();
	/**
	* @return data utworzenia zadania
	*/
	std::time_t GetCreatedAt();
	/**
	* @return ukończenia zadania
	*/
	std::time_t GetExpirationDate();
	/**
	* @return poziom trudności zadania
	*/
	TaskDifficulty GetTaskDifficulty();
	/**
	* @return obiekt json z zadania
	*/
	virtual json ReturnTaskJson();
	/**
	* Funkcja ustawia id zadnia
	* @param _id id do ustawienia
	*/
	void SetId(int _id);
	/**
	* Funkcja ustawia datę utworzenia zadnia
	* @param t czas utworzenia do ustawienia
	*/
	void SetCreatedAt(time_t t);
	/**
	* Funkcja ustawia datę utworzenia zadnia
	* @param t datę ukończenia do ustawienia
	*/
	void SetExpirationDate(time_t t);
private:
	int id; //< numer id zadania
	std::string taskTitle; //< tytuł zadania
	std::string taskDescription;//< opis zadania
	std::string GetDifficultyFromEnum();
	std::time_t taskCreatedAt; //< data utworzenia zadania
	std::time_t taskExpirationDate; //< data ukończenia zadania
	std::time_t taskExpirationTime;
	TaskDifficulty td;
};

