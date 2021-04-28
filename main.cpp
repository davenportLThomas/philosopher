#include<iostream>
#include<string>
#include<random>
#include<thread>
#include<unistd.h>//for sleep
#include<functional>

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
	//the status of how hungry dude is, at 10 hungry he dies, is death in the requirements
	int hungry = 0;//I should randomize

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

	//pickUp is what is to be used to pick up chopsticks. It needs to return 0 
	bool pickUp()
	{
		//try to pick up
		if(left->state == left->UNUSED)//can be picked up
		{
			if(right->state == right->UNUSED)//picked up both!
			{
				left->state = left->USED;
				right->state = right->USED;
				return 1;
			}
			else
				return 0;//failed to pick up

		}
		else return 0;//more failure

	}

	void release()//I suppose all releases should be successful
	{
		left->state = left->UNUSED;
		right->state = right->UNUSED;
		return;
	}

	void whileHungry()
	{
		if(pickUp())//returns true if it can be picked up
		{
			this->state = EATING;
		}
		else//pickup did not happen
		{
			cout << this->name << " was DENIED" << endl;
			this->state = HUNGRY;
		}

		return;
	}
	
	void whileEating()
	{
		release();//pretty straight forward
		this->state = THINKING;
		return;
	}

	void whileThinking()
	{
		this->state = HUNGRY;
		return;
	}

	void print()
	{
		cout << this->name << "  State: ";
		if(this->state == HUNGRY)
			cout << "HUNGRY" << endl;
		if(this->state == EATING)
			cout << "EATING" << endl;
		if(this->state == THINKING)
			cout << "THINKING" << endl;
		return;
	}

	int run()//this is going to be the philosophical loop if you will
	{
		do
		{
			print();
			//wait a random amount if time
			int n;
			if(this->state == HUNGRY)
				n = 1;
			else
				n = rand() % 5; //currently 1 to 10 seconds
			sleep(n);
			if(this->state == HUNGRY)
				whileHungry();
			else if(this->state == EATING)
				whileEating();
			else if(this->state == THINKING)
				whileThinking();
		}while(1);
		return 0;
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

	//where threading must begin
	thread thread1(&Philosopher::run, Plato);
	thread thread2(&Philosopher::run, Socrates);
	thread thread3(&Philosopher::run, Confucius);

	thread1.join();


	return 0;
}
