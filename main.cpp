#include<iostream>
#include<string>

using namespace std;

//GLOBALS
int chopstickCount = 0;
int philosopherCount = 0;


//Chopstick has id set by chopStickCount
class Chopstick
{
	public:
	int id;		// number of chopstick
	enum States{UNUSED, USED}state;

	Chopstick()
	{
		//set id and increment chopstick
		this->id = chopstickCount;
		chopstickCount++;
		//set state to 0
		this->state = UNUSED;		
	}
};

//philosopher has id set by philosopherCount, name set in contruction, chopsticks set in construction as well
class Philosopher
{
	public:
	enum States{THINKING, EATING, HUNGRY}state;
	int id;
	string name;
	Chopstick *left, *right;

	Philosopher(string _name, Chopstick *_left, Chopstick *_right)
	{
		//set id and increment
		this->id = philosopherCount;
		philosopherCount++;
		//set the name
		this->name = _name;
		//set the state
		state = THINKING;
		//set some chopsticks, gotta eat
		this->left = _left;
		this->right = _right;
	}	

	
};


int main()
{
	//the number of chopsticks MUST equal the number of philosophers
	//creating chopsticks, perhaps these should be an array
	Chopstick *zero = new Chopstick();
	Chopstick *one = new Chopstick();
	Chopstick *two = new Chopstick();
	//creating an equal number of philosophers
	Philosopher *Plato = new Philosopher("Plato", zero, one);
	Philosopher *Socrates = new Philosopher("Socrates", one, two);
	Philosopher *Confucius = new Philosopher("Confucius", two, zero);

	//test prints
	cout << Plato->name << " " << Plato->left->id << " " <<  Plato->right->id << endl;
	cout << Socrates->name << " " << Socrates->left->id << " " <<  Socrates->right->id << endl;
	cout << Confucius->name << " " << Confucius->left->id << " " <<  Confucius->right->id << endl;




	return 0;
}
