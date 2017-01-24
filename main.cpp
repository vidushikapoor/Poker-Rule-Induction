/*
 * main.cpp
 *
 *  Created on: Nov 27, 2016
 *      Author: vidushikapoor
 */


#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <iterator>
#include <forward_list>
#include <typeinfo>
using namespace std;

namespace B{
    // Used to represent a row in the CSV input file
	class CsvRow
	{
		public:
			std::string const& operator[](std::size_t index) const
			{
				return m_data[index];
			}
			std::size_t size() const
			{
				return m_data.size();
			}
			void readNextRow(std::istream& str)
			{
				std::string line;
				std::getline(str, line);
		
				std::stringstream lineStream(line);
				std::string         cell;
		
				m_data.clear();
				while(std::getline(lineStream, cell, ','))
				{
					m_data.push_back(cell);
				}
			}
		private:
			std::vector<std::string> m_data;
	};
	
	/**
		Overloades the '>>' operator for the CsvRow class
		
		@param str istream object used for concatenation of the string content
		@param data reference to a CsvRow object used for concatenation
		@return Joined string that can accept for CsvRow object references
	*/
	std::istream& operator>>(std::istream& str, CsvRow& data)
	{
		data.readNextRow(str);
		return str;
	}
} // namespace B

// Used to represent the two properties of a card i.e. Suit and Rank
class Card{
	public:
		// Initialization Constructor 
		Card(){
			suit=0;
			rank=0;
		}
		// Initialization Constructor with parameters
		Card(int suit, int rank){
			this->suit=suit;
			this->rank=rank;
		}
		int getSuit(){
			return suit;
		}
	
		int getRank(){
			return rank;
		}
	
		void setSuit(int suit){
			this->suit=suit;
		}
	
		void setRank(int rank){
			this->rank=rank;
		}
	
		void printCard() {
			cout << suit << "," << rank << endl;
		}	
		
	private:
		int suit;
		int rank;
};

/**
    Helper function to compare the suits of 2 input cards. This is used for sorting.
    
    @param c1 First card to be compared
    @param c2 Second card to be compared
    @return True or False if the suit of first card is smaller than the second card
*/
bool suitComparator(Card c1, Card c2) 
{ 
	return (c1.getSuit() < c2.getSuit()); 
}

/**
    Helper function to compare 2 input cards. This is used for sorting
    
    @param c1 First card to be compared
    @param c2 Second card to be compared
    @return True or false if the suit or rank of the first card is smaller than that of the second card
*/
bool cardComparator(Card c1, Card c2) {
	if(c1.getSuit() == c2.getSuit()){
		return (c1.getRank() < c2.getRank());
	}
	return false;
}

// Used to represent a hand consisting of 5 cards
class Hand{
	public:
		Hand(){
		}
		void sort(){
			std::sort(Cards.begin(),Cards.end(), suitComparator);
			std::sort(Cards.begin(),Cards.end(), cardComparator);
		}
		void addCard(Card c){
			Cards.push_back(c);
		}
		void printHand(){
			for (std::vector<Card>::iterator it=Cards.begin(); it!=Cards.end(); ++it){
				(*it).printCard();
			}
		}
		vector<Card> Cards;
};

// Class to couple a hand to its playable decision using the probability of winning
class PokerDecision{
public:
	PokerDecision(){
	}
	PokerDecision(int dec, Hand temp){
		decision=dec;
		h=temp;
	}
	void printPokerDecision(){
		cout << "Hand: "<<endl;
		h.printHand();
		cout << "Decision" ;
		cout<<":"<<decision<<endl;
	}

	int decision;
	Hand h;
};

namespace A{
	class OneCard  {
		public:
			virtual ~OneCard() { };
			void setSuit(int w) {
				setSuitNew = w;
			}
		
			void setRank(int h) {
				setRankNew = h;
			}
			void typeInfo(){
				cout<<"Name of template "<<typeid(*this).name()<<endl;
			}
			int setSuitNew;
			int setRankNew;
	}; // class OneCard
} // namespace A 

// Derived class
class RankSuit: public A::OneCard{
public:
	int sort() {
		if(setSuitNew>setRankNew)
			return setSuitNew;
		else{
			return setRankNew;
		}
	}
};

namespace A{
	void cast_function(OneCard& a){
		try {
			RankSuit& b = dynamic_cast<RankSuit&>(a);
			b.sort();
		}
		catch (const std::bad_cast& e) {
			std::cerr << "  Exception " << e.what() << " thrown." << std::endl;
			std::cerr << "  Object is not of type RankSuit" << std::endl;
		}
	}
} // namespace A

// Class created to handle nodes in a linked list
class node{
	public:
		node(){
			next=NULL;
			prev=NULL;
		}
		node(PokerDecision dec){
			d=dec;
			next=NULL;
			prev=NULL;
		}
		node* next;
		node* prev;
		PokerDecision d;
};

// Class created to store the list of records to their corresponding playable decisions in a linked list
class linkedList{
	public:
		linkedList(){
			head=NULL;
			tail=NULL;
		}
		void appendEnd(PokerDecision data){
			node* ptr;
			if(!head){
				head=tail=new node();
				head->prev=nullptr;
				head->next=nullptr;
				head->d=data;
			}
			else{
				ptr=new node();
				tail->next=ptr;
				ptr->prev=tail;
				ptr->d=data;
				tail=tail->next;
			}
		}
		
		void printList(){
			node* trav=head;
			while(trav != NULL){
				PokerDecision temp = trav->d;
				temp.printPokerDecision();
				trav=trav->next;
			}
		}
	
		node* head;
		node* tail;
};

// Exception class defined to handle cases where file is absent
class FileMissingException
{
	public:
		void printError(char* f)
		{
			cout << "File \"" << f << "\" is missing" << endl;
		}
};

// Exception class defined to handle issues with file reading issues
class FileReadingException
{
	public:
		void printError(char* f)
		{
			cout << "Error in reading file \"" << f << "\"" << endl;
		}
	};
	template <typename T>
	inline T const& Max (T const& a, T const& b)  {
		return a < b ? b:a;
	}
	
	template <typename T>
	inline T const& Min (T const& a, T const& b)  {
		return a > b ? b:a;
}

int main()
{
	vector<int> gamerInput;
	int j;
	int k;
	Max(j,k);
	Min(j,k);

	// Reading in the hand detail from the user
	cout<<"Enter the cards detail:"<<endl;
	Card currentCard;
	Hand userHand;
	for(int i=1;i<6;i++){
		cout<<i<<"card Suit: "<<endl;
		cin>>j;
		cout<<i<<"card rank: "<<endl;
		cin>>k;
		currentCard.setSuit(j);
		currentCard.setRank(k);
		userHand.addCard(currentCard);
	}
	userHand.printHand();
	cout << "Sorting: " << endl;
	userHand.sort();
	userHand.printHand();
	cout << "Sorted" << endl;
	std::ifstream file("labels.csv");
	B::CsvRow row;

	int size=11; // Defines the size of array which corresponds to number of columns in file
	std::unique_ptr<int[]> trainArr(new int[size]);
	vector<int> trainArray;
	bool header_row = true;
	while(file >> row)
	{
		// skip header line
		if (header_row == true) {
			header_row = false;
			continue;
		}

		for (int i=0; i<=10;i++){
			long a=stol(row[i]);
			trainArray.push_back(a);
		}
	}
	linkedList ll;
	PokerDecision dec;

	int count=0;
	int NUM_RECORDS = 1176;
	cout << "Reading records ... " << endl;
	// *********** LOGIC TO BE WRITTEN ************
	while(count<NUM_RECORDS){
		cout << "Count: " << count << endl;
		Hand tempHand;
		for(unsigned i=count;i<=count+10;i+=2){
			Card tempCard;
			if(i!=count+10){
				tempCard.setSuit(trainArray.at(i));
				tempCard.setRank(trainArray.at(i+1));
				tempHand.addCard(tempCard);
			}
			if(i==count+10){
				dec.decision=trainArray.at(i);
				tempHand.sort();
				dec.h=tempHand;
				break;
			}
		}
		ll.appendEnd(dec);
		count=count+11;

		node* search=ll.head;
		vector<int>test;
		for(int i=0;i<userHand.Cards.size();i++){
			Card tempUserCard=userHand.Cards.at(i);
			test.push_back(tempUserCard.getSuit());
			test.push_back(tempUserCard.getRank());
		}

		// Search for the user's hand in the linked list
		while(search!=NULL){
			PokerDecision temp=search->d;
			Hand tempHand=temp.h;
			vector<int>train;
			for(int i=0;i<tempHand.Cards.size();i++){
				Card tempCard=tempHand.Cards.at(i);
				train.push_back(tempCard.getSuit());
				train.push_back(tempCard.getRank());
			}

			if(equal(train.begin(),train.end(),test.begin())){
				cout<<"Decision factor:"<<endl;
				PokerDecision found=search->d;
				found.printPokerDecision();
				cout<<"Go ahead and play, you have a good probability to win. Cheers !!"<<endl;
				break;
			}
			else{
				continue;
			}
		}
	}
}

