#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>

#define ALPHABETS 26
#define CASE 'a'

using namespace std;

typedef struct TrieNode//������
{
    bool end_of_word;//��������� �� ����� ����� �����
	 TrieNode* letters[ALPHABETS];//������� �� ������ 26 ������ ���� � ��������� ���

}Node;


Node* CreateNode()//���������� ������
{
	Node *DTNode = new Node;//���������� ������ �� �����

	DTNode->end_of_word = false;//����� ��� ��������� �� ����� ��������� ������� ��� ����� �����

	for (int counter = 0; counter < ALPHABETS; counter++)//����� �� ����������� ��� ������ ��������� ����
	{
		DTNode->letters[counter] = NULL;
	}

	return DTNode;// ���������� ������ ���� ����� ��� �������
}

void DTInsert(Node* root,string word)// �������� �����
{
	Node* next_node = root;// ������� �� ����� ������ ������� ��� ����

	for (int counter = 0; counter < (int)word.length(); counter++)// ��� ���� ������ ��� �����
	{
		int letter_position=tolower(word[counter]) - CASE;//���� ��� ��������� ���� ������ ��������� = ASCII ��� ��������� - '�'
		if (next_node->letters[letter_position] == NULL)//�� � ���� ���� ��� ������ ��������� ����� ����
		{
			next_node->letters[letter_position] = CreateNode();//������������ ����� �� ����
		}
		next_node = next_node->letters[letter_position];//� ������� ����� ������� ���� �������� �����
	}
	next_node->end_of_word = true;// ��� ����� ������� ��� ��������� ��� ����� ����� �����
}

void DTSearch(Node* root, string word)// ���������
{
	Node* next_node = root;//������� �� ����� ������ ������� ��� ����

	for (int counter = 0; counter < (int) word.length(); counter++)//��� ���� ������ ��� ����� ���� ���������
	{
		int letter_position = tolower(word[counter]) - CASE;//���� ��� ��������� ���� ������ ��������� = ASCII ��� ��������� - '�'
		if (next_node->letters[letter_position] != NULL)//�� � ���� ���� ��� ������ ��������� ��� ����� ����
		{
			next_node=next_node->letters[letter_position];//� ������� ����� ������� ���� �������� �����
		}
		else// ������
		{
			cout << "The word " << word << " wasn't found." << endl;//� ���� ��� �������
            return;
		}
	}
	if (next_node->end_of_word)//�� ����� ����� �����
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

bool Is_Leaf_Node(Node* node)//������� �� ����� �����
{
	int counter;
	for (counter = 0; counter < ALPHABETS; counter++)//���� ����� ��� ��������� ������� �� ���� ������ ���� ������ ���� ��� ������ ��� ���������
	{
		if (node->letters[counter])
			return false;// �� ���� �������� ��� ��� ����� ����� ��� ���������� ������
	}
	return true;//������ ���������� ������
}
void Node_Delete(Node* node, int current_letter_position,string word)//��������� ��� ����� ��� ��������� ��� ���� ��������
{
	if(current_letter_position < (int)word.length())//�� � ���� ��� ������ ����� ��������� ��� �� ������� ��� �����
	{
		int letter_position = tolower(word[current_letter_position]) - CASE;//���������� ��� ���� ��� ������ ���������
		node = node->letters[letter_position];//� ������� ��� ��������� ���� ������� ��� ������� ������
		current_letter_position++;// ��������� ��� ���� ���� 1
		Node_Delete(node, current_letter_position, word); // ������� ��� ��������� ���� ���������� ��� �� �������� ����
		delete node;//����������� ��� ������
		node = NULL;//��� ��� ������� �� ������� ����

	}

}


int Times_Used_Elsewere_Node(Node* node)//���������� ���� ����� ��������������� � ������ �� ����� ������
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

	Node* next = root;//������� ��� �������� ��� ��� ����
	int letter_position, previous_word_letter_position = 0;// ������������ ����������
	Node* temp = CreateNode();//���������� ��������� ������ �� �����
	for (int counter = 0; counter <(int) word.length(); counter++)//��� ��� ��� ������ ��� �����
	{
		letter_position = tolower(word[counter]) - CASE;//���������� ��� ���� ��� ������ ���������
		if (next->letters[letter_position] != NULL)//�� � �������� ������ ��� ��� ������ ��������� ��� ����� �����
		{
			if(Times_Used_Elsewere_Node(next)>0)// �� ��������������� �������� � ������ ����� ��� ���� ����, ����� �� ����� � ���������
			{
				previous_word_letter_position = counter;//������� �� ��� ��������� ��� ������ ��� ���������
				temp = next;//��� ������� ��� ��������� ������ �� ������� ���� ����� ����
			}
			next = next->letters[letter_position];//� ������� ���� ��� ������� ������ ��� �����
		}
		else//������
		{
			cout << "The word " << word << " wasn't found." << endl;// � ���� ��� �������
			return ;
		}
	}
	if (next->end_of_word )// �� � ������ ����� ����� �����
	{
		if (!Is_Leaf_Node(next))// �� ��� ����� �����, ��� ������� ���� ��� ����� ������ �� ������ ���� �� ���� ��������, ���� �����������
		{

			next->end_of_word = false;//������� ��� ������� ����� ����� �����
			cout << "The word " << word << " was deleted. " <<endl;// � ���� ����������
		}
		else
		{
			if (previous_word_letter_position == 0)//�� ��� ������ ���� ���� �� �� ���� ��������
			{
				Node_Delete(root, 0, word);//�������� ��� ������ ��� �����
				letter_position = tolower(word[0]) - CASE;//���������� ��� ���� ��� ������ ���������
				root->letters[letter_position] = NULL;//�� ������ ��� ��� ���� �������� �����
			}
			else //������
			{
				Node_Delete(temp, previous_word_letter_position, word);//��������� ���� ������ ���� ��� ��� overlapping ������
				letter_position = tolower(word[previous_word_letter_position]) - CASE;//���������� ��� ���� ��� ������ ���������
				temp->letters[letter_position] = NULL;//�� ������ ��� �� ������ ���� �������� �����
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
