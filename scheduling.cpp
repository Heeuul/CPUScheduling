#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

const bool debug = false;

class Prog
{
private:
	int _id;

public:
	string GetName() { return "P" + to_string(_id); }
	int &id;
	int arrivalTime, priority;

	Prog() : id(_id) { _id = -1; }
	Prog(int ID, int arrivalTime, int priority) : id(_id)
	{
		_id = ID;
		this->arrivalTime = arrivalTime;
		this->priority = priority;
	}
};

int main()
{
	bool running = false;
	int no, burst[10], arrival[10], priority[10];
	string name[10];

	initialise(no);

	for (int i = 0; i < no; i++)
		assignDetails(name[i] = "P" + to_string(i), burst[i], arrival[i], priority[i]);

	while (!running)
	{
		displayMenu(no, name, burst, arrival, priority);
		running = performScheduling(name, burst, arrival, priority, no);
	}

	return 0;
}

void initialise(int &no)
{
	do
	{
		cout << "Number of processes(min:3, max:10): ";
		no = getInt();
	} while (no < 3 || no > 10);
	cout << "Processes: " << no << endl
		 << endl;
}
int getInt()
{
	int a;
	while (!(cin >> a))
	{
		cout << "Enter a valid number: ";
		cin.clear();
		cin.ignore(9999, '\n');
	}
	return a;
}

void assignDetails(string &name, int &burst, int &arrival, int &priority)
{
	cout << name << ": Burst time   = ";
	burst = getInt();

	cout << setw(19) << "Arrival time = ";
	arrival = getInt();

	cout << setw(19) << "Priority     = ";
	priority = getInt();

	cout << endl;
}

void displayMenu(int no, string *name, int *burst, int *arrival, int *priority)
{
	cout << endl
		 << setw(15) << "Process" << setw(15) << "Burst time" << setw(15) << "Arrival time" << setw(15) << "Priority" << endl;
	for (int i = 0; i < no; i++)
		cout << setw(15) << name[i] << setw(15) << burst[i] << setw(15) << arrival[i] << setw(15) << priority[i] << endl;

	cout << "\nWhich algorithm would you like to simulate?\n\n"
		 << "1. FCFS(First Come First Served)-based pre-emptive Priority.\n"
		 << "2. Round Robin Scheduling with Priority.\n"
		 << "3. Three-level Queue Scheduling.\n"
		 << "4. Shortest Remaining Time Next (SRTN) Scheduling with Priority.\n\n"
		 << "0. Exit the program.\n\n\n"
		 << "Choice-> ";
}

bool performScheduling(string *name, int *burst, int *arrival, int *priority, int no)
{
	cout << endl
		 << endl;

	switch (getInt())
	{
	case 1:
		fcfs(name, burst, arrival, priority, no);
		break;
	case 2:
		rr(name, burst, arrival, priority, no);
		break;
	case 3:
		tlq(name, burst, arrival, priority, no);
		break;
	case 4:
		srtn(name, burst, arrival, priority, no);
		break;
	case 0:
		return true;

	default:
		cout << "Invalid input! ";
		system("pause");
		break;
	}

	return false;
}

void fcfs(string *name, int *burst, int *arrival, int *priority, int no)
{
	if (debug)
	{
		cout << "Started sorting" << endl;
		cout << "Sorting based on arrival time" << endl;
	}
	for (int i = 0; i < no; i++)
	{
		for (int j = 0; j < no - 1; j++)
		{
			if (arrival[j] > arrival[j + 1])
			{
				swap(name[j], name[j + 1]);
				swap(burst[j], burst[j + 1]);
				swap(arrival[j], arrival[j + 1]);
				swap(priority[j], priority[j + 1]);
			}
		}
	}
	if (debug)
	{
		cout << "Sorting based on priority" << endl;
	}
	for (int i = 0; i < no; i++)
	{
		for (int j = 0; j < no - 1; j++)
		{
			if (arrival[j] == arrival[j + 1])
			{
				if (priority[j] > priority[j + 1])
				{
					swap(name[j], name[j + 1]);
					swap(burst[j], burst[j + 1]);
					swap(arrival[j], arrival[j + 1]);
					swap(priority[j], priority[j + 1]);
				}
			}
		}
	}
	if (debug)
	{
		cout << "Sorting finished" << endl;
	}

	int count = 0;
	for (int i = 0; i <= no; i++)
	{
		if (burst[i] == 0)
		{
			count++;
		}
	}
	int current = -1, before, finished = -1;
	bool running, shown = false, prev = false;
	string output = " ";
	if (debug)
	{
		cout << "0 " << endl;
	}
	for (int time = 0; count < no;)
	{
		running = false;
		before = current;
		for (int i = 0; i < no; i++)
		{
			if (burst[i] > 0 && arrival[i] <= time)
			{
				if (current == -1 || burst[current] == 0 || priority[i] < priority[current] || arrival[current] > time)
				{
					if (debug)
					{
						cout << name[i] << " is suitable." << endl;
					}
					current = i;
				}
			}
		}
		if (arrival[current] <= time && burst[current] > 0)
		{
			burst[current] = burst[current] - 1;
			if (debug)
			{
				cout << name[current] << " running, left: " << burst[current] << endl;
			}
			running = true;
			if (prev == false)
			{
				stringstream ss;
				string t;
				ss << time;
				ss >> t;
				output = output + t;
			}
		}
		if (before != current && before != -1)
		{
			if (debug)
			{
				cout << "Replacing " << name[before] << " with " << name[current] << endl;
			}
			if (shown == false)
			{
				stringstream ss;
				string t;
				ss << time;
				ss >> t;
				output = output + "[" + name[before] + "]" + t;
				shown == false;
			}
		}
		if (burst[current] == 0 && finished != current && running == true)
		{
			finished = current;
			count++;
			if (debug)
			{
				cout << name[current] << " finished, process left: " << no - count << endl;
			}
			stringstream ss;
			string t;
			ss << time + 1;
			ss >> t;
			output = output + "[" + name[finished] + "]" + t;
			shown = true;
			if (count == no)
			{
				if (debug)
				{
					cout << "All process finished" << endl;
				}
			}
		}
		prev = true;
		if (running == false)
		{
			if (debug)
			{
				cout << "Nothing running" << endl;
			}
			output = output + "|";
			prev = false;
		}
		time++;
		if (debug)
		{
			cout << time << "s" << endl;
		}
	}
	if (debug)
	{
		cout << "FCFS simulation finished";
	}
	cout << output << endl;
}

void rr(string *name, int *burst, int *arrival, int *priority, int no)
{
	if (debug)
	{
		cout << "Started sorting" << endl;
		cout << "Sorting based on arrival time" << endl;
	}
	for (int i = 0; i < no; i++)
	{
		for (int j = 0; j < no - 1; j++)
		{
			if (arrival[j] > arrival[j + 1])
			{
				swap(name[j], name[j + 1]);
				swap(burst[j], burst[j + 1]);
				swap(arrival[j], arrival[j + 1]);
				swap(priority[j], priority[j + 1]);
			}
		}
	}
	if (debug)
	{
		cout << "Sorting based on priority" << endl;
	}
	for (int i = 0; i < no; i++)
	{
		for (int j = 0; j < no - 1; j++)
		{
			if (arrival[j] == arrival[j + 1])
			{
				if (priority[j] > priority[j + 1])
				{
					swap(name[j], name[j + 1]);
					swap(burst[j], burst[j + 1]);
					swap(arrival[j], arrival[j + 1]);
					swap(priority[j], priority[j + 1]);
				}
			}
		}
	}
	if (debug)
	{
		cout << "Sorting finished" << endl;
	}

	cout << "Quantum: ";
	int quantum = getInt(), count = 0;
	bool prev = false;
	for (int i = 0; i < no; i++)
	{
		if (burst[i] == 0)
		{
			count++;
		}
	}
	if (debug)
	{
		cout << "0 ";
	}
	int current = -1, before, finished = -1, sTime;
	bool running, ssTime = false;
	string output = " ";
	for (int time = 0; count < no;)
	{
		running = false;
		before = current;
		for (int i = 0; i < no; i++)
		{
			if (burst[i] > 0 && arrival[i] <= time && i != before)
			{
				if (current == -1 || priority[i] <= priority[current] || burst[current] == 0 || arrival[current] > time)
				{
					if (debug)
					{
						cout << name[i] << " is suitable" << endl;
					}
					current = i;
				}
			}
		}
		if (arrival[current] <= time && burst[current] > 0)
		{
			if (prev == false)
			{
				stringstream ss;
				string t;
				ss << time;
				ss >> t;
				output = output + t;
			}
			if (burst[current] >= quantum)
			{
				burst[current] = burst[current] - quantum;
				stringstream ss;
				string t;
				ss << time + quantum;
				ss >> t;
				output = output + "[" + name[current] + "]" + t;
				if (debug)
				{
					cout << name[current] << " running, left: " << burst[current] << endl;
				}
			}
			else
			{
				sTime = burst[current];
				ssTime = true;
				burst[current] = 0;
				stringstream ss;
				string t;
				ss << time + sTime;
				ss >> t;
				output = output + "[" + name[current] + "]" + t;
				if (debug)
				{
					cout << name[current] << " ran and finished" << endl;
				}
			}
			running = true;
		}
		if (burst[current] == 0 && finished != current && running == true)
		{
			count++;
			if (debug)
			{
				cout << name[current] << " finished, process left: " << no - count << endl;
			}
			finished = current;
			if (count == no)
			{
				if (debug)
				{
					cout << "All process finished" << endl;
				}
			}
		}
		prev = true;
		if (running == false)
		{
			if (debug)
			{
				cout << "Nothing running" << endl;
			}
			output = output + "|";
			time++;
			prev = false;
		}
		else if (ssTime == true && running == true)
		{
			time = time + sTime;
			ssTime = false;
		}
		else
		{
			time = time + quantum;
		}
		if (debug)
		{
			cout << time << "s" << endl;
		}
	}
	if (debug)
	{
		cout << "RR simulation finished";
	}
	cout << output << endl;
}

void tlq(string *name, int *burst, int *arrival, int *priority, int no)
{
	if (debug)
	{
		cout << "Start sorting" << endl;
		cout << "Sort based on priority" << endl;
	}
	for (int i = 0; i < no; i++)
	{
		for (int j = 0; j < no - 1; j++)
		{
			if (priority[j] > priority[j + 1])
			{
				swap(name[j], name[j + 1]);
				swap(burst[j], burst[j + 1]);
				swap(arrival[j], arrival[j + 1]);
				swap(priority[j], priority[j + 1]);
			}
		}
	}
	if (debug)
	{
		cout << "Sort based on arrival time" << endl;
	}
	for (int i = 0; i < no; i++)
	{
		for (int j = 0; j < no - 1; j++)
		{
			if (priority[j] == priority[j + 1])
			{
				if (arrival[j] > arrival[j + 1])
				{
					swap(name[j], name[j + 1]);
					swap(burst[j], burst[j + 1]);
					swap(arrival[j], arrival[j + 1]);
					swap(priority[j], priority[j + 1]);
				}
			}
		}
	}
	if (debug)
	{
		cout << "Finished sorting" << endl;
	}

	cout << "Quantum: ";
	int quantum = getInt(), count = 0;
	for (int i = 0; i < no; i++)
	{
		if (burst[i] == 0)
		{
			count++;
		}
	}
	if (debug)
	{
		cout << "0 ";
	}
	int current = -1, before, finished = -1, sTime;
	bool running, ssTime = false, shown = false, prev = false, start1 = false, start2 = false, start3 = false;
	string output = " ", output2 = " ", output3 = " ";
	for (int time = 0; count < no;)
	{
		running = false;
		before = current;
		for (int i = 0; i < no; i++)
		{
			if (priority[i] == 1 || priority[i] == 2)
			{
				if (burst[i] > 0 && arrival[i] <= time && i != before)
				{
					if (current == -1 || priority[i] <= priority[current] || burst[current] == 0 || arrival[current] > time)
					{
						if (debug)
						{
							cout << name[i] << " is suitable" << endl;
						}
						current = i;
					}
				}
			}
			else
			{
				if (burst[i] > 0 && arrival[i] <= time)
				{
					if (current == -1 || burst[current] == 0 || priority[i] < priority[current] || arrival[current] > time)
					{
						if (debug)
						{
							cout << name[i] << " is suitable." << endl;
						}
						current = i;
					}
				}
			}
		}

		if (priority[current] == 1 || priority[current] == 2)
		{
			if (start1 == false)
			{
				if (start2 == true || start3 == true)
				{
					stringstream ss;
					string t;
					ss << time;
					ss >> t;
					output = output + t;
				}
			}
			start1 = true;
			if (arrival[current] <= time && burst[current] > 0)
			{
				if (prev == false)
				{
					stringstream ss;
					string t;
					ss << time;
					ss >> t;
					output = output + t;
				}
				if (burst[current] >= quantum)
				{
					burst[current] = burst[current] - quantum;
					stringstream ss;
					string t;
					ss << time + quantum;
					ss >> t;
					output = output + "[" + name[current] + "]" + t;
					if (debug)
					{
						cout << name[current] << " running, left: " << burst[current] << endl;
					}
				}
				else
				{
					sTime = burst[current];
					ssTime = true;
					burst[current] = 0;
					stringstream ss;
					string t;
					ss << time + sTime;
					ss >> t;
					output = output + "[" + name[current] + "]" + t;
					if (debug)
					{
						cout << name[current] << " ran and finished" << endl;
					}
				}
				running = true;
			}
			if (burst[current] == 0 && finished != current && running == true)
			{
				count++;
				if (debug)
				{
					cout << name[current] << " finished, process left: " << no - count << endl;
				}
				finished = current;
				if (count == no)
				{
					if (debug)
					{
						cout << "All process finished" << endl;
					}
				}
			}
			prev = true;
			if (running == false)
			{
				if (debug)
				{
					cout << "Nothing running" << endl;
				}
				output = output + "|";
				time++;
				prev = false;
			}
			else if (ssTime == true && running == true)
			{
				time = time + sTime;
				ssTime = false;
			}
			else
			{
				time = time + quantum;
			}
			if (debug)
			{
				cout << time << "s" << endl;
			}
		}
		else if (priority[current] == 3 || priority[current] == 4)
		{
			if (start2 == false)
			{
				if (start1 == true || start3 == true)
				{
					stringstream ss;
					string t;
					ss << time;
					ss >> t;
					output2 = output2 + t;
				}
			}
			start2 = true;
			if (arrival[current] <= time && burst[current] > 0)
			{
				burst[current] = burst[current] - 1;
				if (debug)
				{
					cout << name[current] << " running, left: " << burst[current] << endl;
				}
				running = true;
				if (prev == false)
				{
					stringstream ss;
					string t;
					ss << time;
					ss >> t;
					output2 = output2 + t;
				}
			}
			if (before != current && before != -1)
			{
				if (debug)
				{
					cout << "Replacing " << name[before] << " with " << name[current] << endl;
				}
				if (shown == false)
				{
					stringstream ss;
					string t;
					ss << time;
					ss >> t;
					output2 = output2 + "[" + name[current] + "]" + t;
					shown == false;
				}
			}
			if (burst[current] == 0 && finished != current && running == true)
			{
				finished = current;
				count++;
				if (debug)
				{
					cout << name[current] << " finished, process left: " << no - count << endl;
				}
				stringstream ss;
				string t;
				ss << time + 1;
				ss >> t;
				output2 = output2 + "[" + name[finished] + "]" + t;
				shown = true;
				if (count == no)
				{
					if (debug)
					{
						cout << "All process finished" << endl;
					}
				}
			}
			prev = true;
			if (running == false)
			{
				if (debug)
				{
					cout << "Nothing running" << endl;
				}
				output2 = output2 + "|";
				prev = false;
			}
			time++;
			if (debug)
			{
				cout << time << "s" << endl;
			}
		}
		else
		{
			if (start3 == false)
			{
				if (start1 == true || start2 == true)
				{
					stringstream ss;
					string t;
					ss << time;
					ss >> t;
					output3 = output3 + t;
				}
			}
			start3 = true;
			if (arrival[current] <= time && burst[current] > 0)
			{
				burst[current] = burst[current] - 1;
				if (debug)
				{
					cout << name[current] << " running, left: " << burst[current] << endl;
				}
				running = true;
				if (prev == false)
				{
					stringstream ss;
					string t;
					ss << time;
					ss >> t;
					output3 = output3 + t;
				}
			}
			if (before != current && before != -1)
			{
				if (debug)
				{
					cout << "Replacing " << name[before] << " with " << name[current] << endl;
				}
				if (shown == false)
				{
					stringstream ss;
					string t;
					ss << time;
					ss >> t;
					output3 = output3 + "[" + name[before] + "]" + t;
					shown == false;
				}
			}
			if (burst[current] == 0 && finished != current && running == true)
			{
				finished = current;
				count++;
				if (debug)
				{
					cout << name[current] << " finished, process left: " << no - count << endl;
				}
				stringstream ss;
				string t;
				ss << time + 1;
				ss >> t;
				output3 = output3 + "[" + name[finished] + "]" + t;
				shown = true;
				if (count == no)
				{
					if (debug)
					{
						cout << "All process finished" << endl;
					}
				}
			}
			prev = true;
			if (running == false)
			{
				if (debug)
				{
					cout << "Nothing running" << endl;
				}
				output3 = output3 + "|";
				prev = false;
			}
			time++;
			if (debug)
			{
				cout << time << "s" << endl;
			}
		}
	}
	cout << output << endl;
	cout << output2 << endl;
	cout << output3 << endl;
}

void srtn(string *name, int *burst, int *arrival, int *priority, int no)
{
	if (debug)
	{
		cout << "Start sorting" << endl;
		cout << "Sorting based on arrival time" << endl;
	}
	for (int i = 0; i < no; i++)
	{
		for (int j = 0; j < no - 1; j++)
		{
			if (arrival[j] > arrival[j + 1])
			{
				swap(name[j], name[j + 1]);
				swap(burst[j], burst[j + 1]);
				swap(arrival[j], arrival[j + 1]);
				swap(priority[j], priority[j + 1]);
			}
		}
	}
	if (debug)
	{
		cout << "Sorting based on burst time" << endl;
	}
	for (int i = 0; i < no; i++)
	{
		for (int j = 0; j < no - 1; j++)
		{
			if (arrival[j] == arrival[j + 1])
			{
				if (burst[j] > burst[j + 1])
				{
					swap(name[j], name[j + 1]);
					swap(burst[j], burst[j + 1]);
					swap(arrival[j], arrival[j + 1]);
					swap(priority[j], priority[j + 1]);
				}
			}
		}
	}
	if (debug)
	{
		cout << "Sorting based on priority" << endl;
	}
	for (int i = 0; i < no; i++)
	{
		for (int j = 0; j < no - 1; j++)
		{
			if (arrival[j] == arrival[j + 1])
			{
				if (burst[j] == burst[j + 1])
				{
					if (priority[j] > priority[j + 1])
					{
						swap(name[j], name[j + 1]);
						swap(burst[j], burst[j + 1]);
						swap(arrival[j], arrival[j + 1]);
						swap(priority[j], priority[j + 1]);
					}
				}
			}
		}
	}
	if (debug)
	{
		cout << "Sorting finished" << endl;
	}

	int count = 0;
	for (int i = 0; i < no; i++)
	{
		if (burst[i] == 0)
		{
			count++;
		}
	}

	int current = -1, before, finished = -1;
	bool running, prev = false, shown = false;
	string output = " ";
	if (debug)
	{
		cout << "0 ";
	}
	for (int time = 0; count < no;)
	{
		running = false;
		before = current;
		for (int i = 0; i < no; i++)
		{
			if (burst[i] > 0 && arrival[i] <= time)
			{
				if (current == -1 || burst[i] < burst[current] || burst[current] == 0 || arrival[current] > time)
				{
					if (debug)
					{
						cout << name[i] << " is suitable" << endl;
					}
					current = i;
				}
				else if (burst[i] == burst[current])
				{
					if (priority[i] < priority[current])
					{
						if (debug)
						{
							cout << name[i] << " is suitable" << endl;
						}
						current = i;
					}
				}
			}
		}
		if (arrival[current] <= time && burst[current] > 0)
		{
			burst[current] = burst[current] - 1;
			if (debug)
			{
				cout << name[current] << " running, left: " << burst[current] << endl;
			}
			running = true;
			if (prev == false)
			{
				stringstream ss;
				string t;
				ss << time;
				ss >> t;
				output = output + t;
			}
		}
		if (before != current && before != -1)
		{
			if (debug)
			{
				cout << "Replacing " << name[before] << " with " << name[current] << endl;
			}
			if (shown == false)
			{
				stringstream ss;
				string t;
				ss << time;
				ss >> t;
				output = output + "[" + name[before] + "]" + t;
				shown == false;
			}
		}
		if (burst[current] == 0 && finished != current && running == true)
		{
			finished = current;
			count++;
			if (debug)
			{
				cout << name[current] << " finished, process left: " << no - count << endl;
			}
			stringstream ss;
			string t;
			ss << time + 1;
			ss >> t;
			output = output + "[" + name[finished] + "]" + t;
			shown = true;
			if (count == no)
			{
				if (debug)
				{
					cout << "All process finished" << endl;
				}
			}
		}
		prev = true;
		if (running == false)
		{
			if (debug)
			{
				cout << "Nothing running" << endl;
			}
			output = output + "|";
			prev = false;
		}
		time++;
		if (debug)
		{
			cout << time << "s" << endl;
		}
	}
	if (debug)
	{
		cout << "SRTN simulation finished";
	}
	cout << output << endl;
}