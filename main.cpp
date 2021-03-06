#include<iostream>
#include<string>
#include<random>
#include<thread>
#include<functional>
#include<chrono>

using namespace std;

#define MAXTIME 1200 
#define EATERS 20 

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
	//keeping track of states
	int thinkingStat = 0;
	int eatingStat = 0;
	int hungryStat = 0;
	int allTime = 0;
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
		// umm what if 
		if(left->state == left->UNUSED)//can be picked up
		{
			if(right->state == right->UNUSED)//picked up both!
			{
				//coin flip
				int flip = rand() % 2;
				if(flip)
				{
					left->state = left->USED;
					right->state = right->USED;
					return 1;
				}
				else return 0;
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
	//		cout << this->name + " was DENIED\n";
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
		string output = "";

		output += " " + this->name;
		if(this->state == HUNGRY){
			output += "     HUNGRY   Total: ";
			output += to_string(hungryStat);
		}
		if(this->state == EATING){
			output += "	EATING Total: ";
			output += to_string(eatingStat);
		}
		if(this->state == THINKING){
			output += "	THINKING Total: ";
			output += to_string(thinkingStat);
		}
		output += "\n";
		cout << output;
		return;
	}

	int run()//this is going to be the philosophical loop if you will
	{
		do
		{
			//wait a random amount if time
			//an end condition
			if(allTime > MAXTIME) 
				break;
			int n;
			if(this->state == HUNGRY)
				n = 1;
			else
				n = rand() % 20 + 1; //currently 1 to 10 seconds
			this_thread::sleep_for(chrono::seconds(n));
			allTime += n;
			print();
			if(this->state == HUNGRY)
			{	
				this->hungryStat += n;
				whileHungry();
			}
			else if(this->state == EATING)
			{
				this->eatingStat += n;
				whileEating();
			}
			else if(this->state == THINKING)
			{
				this->thinkingStat += n;
				whileThinking();
			}
		}while(1);
		return 0;
	}	
};




int main()
{

#if 1
	int size = EATERS;
	Chopstick **chopsticks = new Chopstick* [size];
	for (int i = 0; i < size; i++){
		chopsticks[i] = new Chopstick(); 
	}
	vector<string> names;
       	names.push_back("Plato");
	names.push_back("Confucius");
        names.push_back("Socrates");
       	names.push_back("Kant");
       	names.push_back("Locke");
	names.push_back("Mario");
	names.push_back("Thomas");
	names.push_back("Jacob");
	names.push_back("Sun Tzu");	
	names.push_back("DesCartes");
	names.push_back("Nietzsche");
	names.push_back("St. Aquinas");
	names.push_back("Marx");
	names.push_back("Spinoza");
	names.push_back("Satre");
	names.push_back("Beavoir");
	names.push_back("Russell");
	names.push_back("Voltaire");
	names.push_back("Heidegger");
	names.push_back("Bacon");
	names.push_back("Kierkegaard");
	Philosopher **philosophers = new Philosopher* [size];

	for (int i = 0; i < size; i++){
		if(i == names.size())
		{
			string randoName = "philosopher_";
			randoName += to_string(i);
			cout << randoName;
			names.push_back(randoName);
		}		
		if( i < size - 1){
			philosophers[i] = new Philosopher(names[i], chopsticks[i], chopsticks[i+1]);
		}
		else{ // must use last chopstick and the first chopstick
			philosophers[i] = new Philosopher(names[i], chopsticks[i], chopsticks[0]);
		}
	}

	// creating threads
	thread * threads = new thread [size];
	for (int i = 0; i < size; i++){
		threads[i] = thread(&Philosopher::run, philosophers[i]);
	}
	

	for(int i = 0; i < size; i++)
		threads[i].join();


        cout << endl << endl << "====================Program finished==========================" << endl << endl;	

	for(int i = 0; i < size; i++)
		cout << philosophers[i]->name << "---  Eating: " << philosophers[i]->eatingStat << " Thinking: " << philosophers[i]->thinkingStat << " Hungry: " << philosophers[i]->hungryStat << endl;
	
	//cleaning pointers
	for(int i =0; i < size; i++){
		delete philosophers[i];
		delete chopsticks[i];
	}
	delete [] philosophers;
	delete [] chopsticks;
	delete [] threads;

#else

	//the number of chopsticks MUST equal the number of philosophers
	//creating chopsticks, perhaps these should be an array
	Chopstick *zero = new Chopstick();
	Chopstick *one = new Chopstick();
	Chopstick *two = new Chopstick();

	//Chopstick *three = new Chopstick();

	//creating an equal number of philosophers
	Philosopher *Plato = new Philosopher("Plato", zero, one);
	Philosopher *Socrates = new Philosopher("Socrates", one, two);
	Philosopher *Confucius = new Philosopher("Confucius", two, zero);

	//Philosopher *lambo = new Philosopher("lambo", three, zero);

	//test prints
	cout << Plato->name << " " << Plato->left->id << " " <<  Plato->right->id << endl;
	cout << Socrates->name << " " << Socrates->left->id << " " <<  Socrates->right->id << endl;
	cout << Confucius->name << " " << Confucius->left->id << " " <<  Confucius->right->id << endl;

	//where threading must begin
	thread thread1(&Philosopher::run, Plato);
	thread thread2(&Philosopher::run, Socrates);
	thread thread3(&Philosopher::run, Confucius);
	//thread thread4(&Philosopher::run, lambo);
	thread1.join();
#endif 


	return 0;
}
