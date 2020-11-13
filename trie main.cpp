#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>

#define ALPHABETS 26
#define CASE 'a'

using namespace std;

typedef struct TrieNode//κομβος
{
    bool end_of_word;//μεταβλητη αν ειναι τελος λεξης
	 TrieNode* letters[ALPHABETS];//δεικτης σε πινακα 26 θεσεων οσες η αλφαβητος μας

}Node;


Node* CreateNode()//δημιουργια κομβου
{
	Node *DTNode = new Node;//δημιουργει δεικτη σε κομβο

	DTNode->end_of_word = false;//θετει την μεταβλητη αν ειναι τελευταιο γραμμμα της λεξης ψευδη

	for (int counter = 0; counter < ALPHABETS; counter++)//βαζει τα περιεχομενα του πινακα γραμματων κενο
	{
		DTNode->letters[counter] = NULL;
	}

	return DTNode;// επιστρεφει δεικτη στον κομβο που εφτιαξε
}

void DTInsert(Node* root,string word)// εισαγωγη λεξης
{
	Node* next_node = root;// δεικτης σε κομβο αρχικα δειχνει την ριζα

	for (int counter = 0; counter < (int)word.length(); counter++)// για καθε γραμμα της λεξης
	{
		int letter_position=tolower(word[counter]) - CASE;//θεση του γραμματος στον πινακα αλφαβητου = ASCII του γραμματος - 'α'
		if (next_node->letters[letter_position] == NULL)//αν η θεση αυτη του πινακα αλφαβητου ειναι κενη
		{
			next_node->letters[letter_position] = CreateNode();//δημιουργουμε κομβο σε αυτη
		}
		next_node = next_node->letters[letter_position];//ο δεικτης πλεον δειχνει στον παρακατω κομβο
	}
	next_node->end_of_word = true;// στο τελος θετουμε την μεταβλητη για τελος λεξης αληθη
}

void DTSearch(Node* root, string word)// αναζητηση
{
	Node* next_node = root;//δεικτης σε κομβο αρχικα δειχνει στη ριζα

	for (int counter = 0; counter < (int) word.length(); counter++)//για καθε γραμμα της λεξης προς αναζητηση
	{
		int letter_position = tolower(word[counter]) - CASE;//θεση του γραμματος στον πινακα αλφαβητου = ASCII του γραμματος - 'α'
		if (next_node->letters[letter_position] != NULL)//αν η θεση αυτη του πινακα αλφαβητου δεν ειναι κενη
		{
			next_node=next_node->letters[letter_position];//ο δεικτης πλεον δειχνει στον παρακατω κομβο
		}
		else// αλλιως
		{
			cout << "The word " << word << " wasn't found." << endl;//η λεξη δεν βρεθηκε
            return;
		}
	}
	if (next_node->end_of_word)//αν ειναι τελος λεξης
	{
		cout << "The word " << word << " was found." << endl;
    return;
	}
	else
	{
		cout << "The word " << word << " wasn't found." << endl;
        return;
	}
}

bool Is_Leaf_Node(Node* node)//ελεγχει αν ειναι φυλλο
{
	int counter;
	for (counter = 0; counter < ALPHABETS; counter++)//στον κομβο του ορισματος ελεγχει αν εχει δεικτη προς καποιο κελι του πινακα της αλφαβητου
	{
		if (node->letters[counter])
			return false;// αν εχει σημαινει οτι δεν ειναι φυλλο και επιστρεφει ψευδες
	}
	return true;//αλλιως επιστρεφει αληθες
}
void Node_Delete(Node* node, int current_letter_position,string word)//διαγραφει τον κομβο του ορισματος και τους παρακατω
{
	if(current_letter_position < (int)word.length())//αν η θεση στο ορισμα ειανι μικροτερη απο το μεγεθος της λεξης
	{
		int letter_position = tolower(word[current_letter_position]) - CASE;//υπολογιζει την θεση στο πινακα αλφαβητου
		node = node->letters[letter_position];//ο δεικτης του ορισματος τωρα δειχνει στο επομενο γραμμα
		current_letter_position++;// αυξανουμε την θεση κατα 1
		Node_Delete(node, current_letter_position, word); // καλουμε την συναρτηση αυτη αναδρομικα για τα δεδομενα αυτα
		delete node;//διαγραφουμε τον δεικτη
		node = NULL;//και τον βαζουμε να δειχνει κενο

	}

}


int Times_Used_Elsewere_Node(Node* node)//υπολογιζει ποσε φορες χρησιμοποιειται ο κομβος σε αλλες λεξεις
{
	int counter=0;
	for (int c = 0; c < ALPHABETS; c++)
	{
		if (node->letters[c] == NULL)
		{
			counter++;
		}
	}
	if (counter > 1)
	{
		return counter;
	}
	else
	{
		return counter;
	}
}



void Delete(Node* root, string word)
{

	Node* next = root;//δεικτης που ξεικναει απο την ριζα
	int letter_position, previous_word_letter_position = 0;// αρχικοποιηση μεταβλητων
	Node* temp = CreateNode();//δημιουργει προσωρινο δεικτη σε κομβο
	for (int counter = 0; counter <(int) word.length(); counter++)//για ολη την εκταση της λεξης
	{
		letter_position = tolower(word[counter]) - CASE;//υπολογιζει την θεση στο πινακα αλφαβητου
		if (next->letters[letter_position] != NULL)//αν ο επομενος κομβος απο τον πινακα αλφαβητου δεν ειναι κενος
		{
			if(Times_Used_Elsewere_Node(next)>0)// αν χρησιμοποιειται παρακατω ο κομβος αυτος για αλλη λεξη, χωρις να ειναι η τελευταια
			{
				previous_word_letter_position = counter;//κραταμε σε μια μεταβλητη τον αριθμο του γραμματος
				temp = next;//και βαζουμε τον προσωρινο δεικτη να δειχνει στον κομβο αυτο
			}
			next = next->letters[letter_position];//ο δεικτης παει στο επομενο γραμμα της λεξης
		}
		else//αλλιως
		{
			cout << "The word " << word << " wasn't found." << endl;// η λεξη δεν βρεθηκε
			return ;
		}
	}
	if (next->end_of_word )// αν ο κομβος ειναι τελος λεξης
	{
		if (!Is_Leaf_Node(next))// αν δεν ειναι φυλλο, δλδ υπαρχει λεξη που μεχρι εκεινο το σημειο εχει τα ιδια γραμματα, αλλα συνεχιζεται
		{

			next->end_of_word = false;//βαζουμε την ταμπελα τελος λεξης ψευδη
			cout << "The word " << word << " was deleted. " <<endl;// η λεξη διαγραφηκε
		}
		else
		{
			if (previous_word_letter_position == 0)//αν δεν εχουμε βρει λεξη με τα ιδια γραμματα
			{
				Node_Delete(root, 0, word);//διαγραφη των κομβων της λεξης
				letter_position = tolower(word[0]) - CASE;//υπολογιζει την θεση στο πινακα αλφαβητου
				root->letters[letter_position] = NULL;//οι κομβοι απο την ριζα γινονται κενοι
			}
			else //αλλιως
			{
				Node_Delete(temp, previous_word_letter_position, word);//διαγραφει τους κοβους κατω απο τις overlapping λεξεις
				letter_position = tolower(word[previous_word_letter_position]) - CASE;//υπολογιζει την θεση στο πινακα αλφαβητου
				temp->letters[letter_position] = NULL;//οι κομβοι απο το σημειο αυτο γινονται κενοι
			}
			cout << "The word " << word << " was deleted." << endl;
			return ;
		}
	}

}

void menu()
{
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"~                            Press 1 to search a word                                            ~"<<endl;
    cout<<"~                            Press 2 to delete a word                                            ~"<<endl;
    cout<<"~                            Press 3 to insert a word                                            ~"<<endl;
    cout<<"~                            Press 3 or higher to exit                                           ~"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

}

int main()
{
	vector <string> words;
	int counter;
	string word;
	Node *DTRoot = CreateNode();
	fstream maifile;
	maifile.open("words.txt");
	if (maifile.is_open())
	{
		cout << "Words loaded " << endl;
		string line;
		while (getline(maifile, line))
		{
			words.push_back(line);
		}
		maifile.close();
	}
	else
	{
		cout << "words.txt file not found." << endl;
	}
	for (counter = 0; counter <(int) words.size(); counter++)
	{
		DTInsert(DTRoot,words[counter]);
	}
	int triemode=0;
	while (triemode<3){
	menu();
	cin>>triemode;
	switch(triemode){
	case 1:
	cout << "Enter a word to search for in the Digital Tree." << endl;
	cin >> word;
	DTSearch(DTRoot, word);
	break;
	case 2:
    cout << "Enter a word to delete in the Digital Tree." << endl;
	cin >> word;
    Delete(DTRoot,word);
        break;}}
	return 0;
}
