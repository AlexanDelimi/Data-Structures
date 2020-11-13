

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <locale>
#include <time.h>
#include <ctime>
#include <math.h>


using namespace std;


vector <int> vec;

bool linearsearch(int noumero)//������ � ���� ��������� ��������
{

    for(int c=0; c<(int)vec.size(); c++)//��� ��� �� ������� �� ���� ���������
        {
        if (vec.at(c)==noumero)//�� ���� ���� c ����� � ���� ��������� ��������
       {
    cout<<"The number "<< noumero<<" exist at position "<<c+1<<endl;

        return true;// ��������� ������
        }
    }
         cout<<"The number was not found"<< endl;

    return false;// �� ��� ������ �� ���������� ������

}
bool binarysearch(vector<int>& input_vector, int element_for_search,int left_border,int right_border)
{
	bool found = false;// ����� ��� ���� ���� ��� �������
	int middle = floor((left_border + right_border) / 2);// ����= ���� ���� + �������� ��� 2
	if (right_border < left_border)//�� �� ���� ���� ����� ��������� ��� �� �������� �������� ��� ��� �� �����
	{
		cout << "The number " << element_for_search << " wasn't found." << endl;
	}
	else//������
	{
		if (element_for_search == input_vector[middle])//�� �� �������� ���� ��������� ����� ��� �� �� �������� ��� ���� ���� ��� �������
		{
			cout << "The number " << element_for_search << " was found at the position " << middle++ <<endl;
			found = true;// �� �������� �������
		}
		else
		{
			if (element_for_search > input_vector[middle])//������ �� �� �������� ����� ���������� ��� �� �������� ���� ���� ��� �������
			{
				middle++;//������ ��� ���� ���� ���
				binarysearch(input_vector, element_for_search, middle, right_border);// �������� ��� ��������� ��� ������ ��� ��� ��� ���� ��� ����
			}
			else// ������ �� ����� ���������
			{
				middle--;// ������ ��� ���� ���� ���
				binarysearch(input_vector, element_for_search, left_border, middle);//�������� ��� ��������� ��� ��� ��� ���� ��� ����
			}
		}
	}
	return found;// ��������� �� ������� �� ��������
}


bool interpolationsearch(int noumero)
{

    int left=0;//�������� ���� =0
    int right=(int)vec.size()-1;// ���� ���� ������� ��� ������ -1
    int next= ((noumero-vec.at(left))/(vec.at(right)-vec.at(left)))*(right-left) +left;// ������� �������� = �����
    while (left<right&& noumero>vec[left]&&noumero<vec[right])// ��� �� �������� ���� ��� ����� ��������� � ��� ��� �� ���� ��� �� ������� ��� ����� ��������� ��� ���� ���� �������� ���� ��� ��� ����� ���������� ��� ���� ���� �����
    {
        if(noumero<=vec.at(next))// �� �� ������� ���� ��������� ����� ��������� ��� ��� �������� ��� �����
            {
                right=next-1;//���� ���� =�����-1
            }
        else//������
            {
            left=next+1;//�������� ���� =�����+1
            }
        next=((noumero-vec.at(left))/(vec.at(right)-vec.at(left)))*(right-left) +left;// ����������� ��� ����� �� �� ��� ����
    }
    if(noumero==vec.at(next))//�� ������ � ������� ���� ���������
    {
       cout<<"The number "<< noumero<<" exists at position "<<next+1<<endl;

        return true;//��������� ������
    }
    else//������
    {
      cout<<"The number was not found"<< endl;

        return false; //��������� ������
    }
}

typedef struct rbnode//������ ��� red black tree
{
	string colour;//�����
	struct rbnode *right, *left, *parent;//������� ���� ����, �������� ����� ��� �����
    int value;//����
}node;


void leftrot(node* &root, node* x, node* &nil)//�������� ����������
{
	node* y=x->right;//������� ���� �� ���� ����� ��� ������ ���� ����� �� ������� ��� ����������
	x->right = y->left;//�� ���� ����� ��� ������ ��� ������� ������� ��� �������� ����� ��� ����������� ������

	if(y->left!=nil)//�� �� �������� ����� ��� ���������� ������ ��� ����� �����
	{
		y->left->parent = x;//� ������� ��� ��������� ������� ��� y ������� ��� x
	}

	y->parent=x->parent; // � ������� ��� ��������� ������ ������� ��� ������ ��� ������ ���� ����������

	if(x->parent==nil)//�� � ������� ��� x ����� �����
		root=y;//� ��� ���� ����� � y
	else if(x==x->parent->left)//������ �� �� x ����� �� �������� ����� ��� ������ ��� x
		x->parent->left = y;//���� �� �������� ����� ��� ������ ��� � ������� ��� y
	else//������
		x->parent->right = y;// �� ���� ����� ��� ������ ��� � ������� ��� y

	y->left = x;//�� �������� ����� ��� y ������� ��� x
	x->parent = y;//� ������� ��� x ������� ��� y
}

void rightrot(node* &root, node* y, node* &nil)//����� ����������
{
	node* x=y->left;//���������� ������� �� ����� (x) ��� ������� ��� �������� ����� ��� ������ ���� ���������� y
	y->left = x->right; //�� �������� ����� ��� ��� y ������� ��� ���� ����� ��� x

	if(x->right!=nil)//�� �� ���� ����� ��� x ��� ����� �����
	{
		x->right->parent = y;//� ������ ��� ������ ������� ��� x ������� ��� y
	}

	x->parent=y->parent; //� ������ ��� x ������� ���� ����� ��� y

	if(y->parent==nil)//�� � ������ ��� y ����� �����
		root=x;//� ���� ����� � x
	else if(y==y->parent->left) //������ �� �� y ����� �� �������� ����� ��� ������ ��� y
		y->parent->left = x; //���� �� x ������� ���  �������� ����� ��� ������ ��� y
	else//������
		y->parent->right = x;//�� x ������� ���  ���� ����� ��� ������ ��� y

	x->right = y;//�� ���� ����� ��� x ����� �� y
	y->parent = x;//o ������ ��� y ����� � x
}

node* rbsearch(node* &root, int searchitem, node* &leaf)//��������� ��� red black tree
{
	node* rightnow=root;//������� ���� ����� ��� ����������� ���� ��� ������, �������� ��� ��� ����
	while(rightnow!=leaf)//��� � ������� ����� ��� ����� �����
	{
		if(rightnow->value==searchitem)//�� � ���� ��� ������ ��� ������� � ������� ����� ����� ���� �� �� ����������� ���� ���������
		{
        cout<< "The number was found"<<endl;
		return rightnow;// ��������� ��� ������ �� ���� ��� �����
		}
		else if(searchitem < rightnow->value)//������ �� ����� ���������
		rightnow=rightnow->left; //� ������� ����� ������� ��� �������� ����� ��� ������ ��� ������� ����
		else if(searchitem > rightnow->value)// ������ �� ����� ����������
		rightnow=rightnow->right;//� ������� ������� ��� ���� ����� ��� ������ ��� ������� ����
	}
        cout << "The number wasn't found\n";
	rightnow=leaf;//�� ��� ������ ���� ��� ��������� � ������� ������� �����
	return 0;
}

void insertfix(node* &root, node* z, node* &nil)// �������� �������
{
	while(z->parent->colour=="red")//��� �� ����� ��� ����� ��� ������ ��� ��������� ����� ��������
	{
		if(z->parent==z->parent->parent->left)//�� � ������ ��� ������ ����� �� �������� ����� ��� ����� ���
		{
			node* y=z->parent->parent->right;//���������� ��� ������ �� ����� ��� ������� �� ���� ����� ��� '������' ��� z
			if(y->colour=="red") // �� �� ����� ��� ������ ��� ������� � ���������� ������� ����� �������
			{
				z->parent->colour="black";//������� �� ����� ��� ������ ��� z �����
				y->colour="black";//��� �� ����� ��� ������ ��� ������� � ���������� ������� �����
				z->parent->parent->colour="red";//������������ �� ������ ��� z �������
				z=z->parent->parent;// ��� ������� ��� ������ z �� ������ ��� ������ ��� ���� �� ��������� � ������� ����� ��� ���� �������
			}
			else if(z==z->parent->right)// ������ �� �� z ����� ���� �����
			{
				z=z->parent;// ��  ������� �� z �� ������� ���� ����� ���
				leftrot(root,z,nil);//������� �������� ���������� ��� ��������� z

				z->parent->colour="black"; //������������ ��� ����� ��� ���������� z �����
				z->parent->parent->colour="red"; //��� ��� ������� ��� �������
				rightrot(root,z->parent->parent,nil);//������� ����� ���������� ���� ������ ��� ���������� z
			}
			else//������
			{
				z->parent->colour="black";//������������ ��� ����� ���
				z->parent->parent->colour="red";//������������ ��� ������ ��� z �������
				rightrot(root,z->parent->parent,nil);//������� ����� ���������� ���� ����� ��� z
			}
		}
		else
		{
			node* y=z->parent->parent->left;//������������ ������ �� ����� ��� ������� ���������� ����� ��� ������ ��� z
			if(y->colour=="red")//�� �� ����� ��� ������ ��� ������� � ������� ����� �������
			{
				z->parent->colour="black";//������������ ��� ����� ��� z �����
				y->colour="black";//��� �� ����� ��� ������� � y �����
				z->parent->parent->colour="red";// ������������ ��� ������ �������
				z=z->parent->parent;//��� ������� ��� ������ z �� ������ ��� ������ ��� ���� �� ��������� � ������� ����� ��� ���� �������
			}
			else if(z==z->parent->left)//������ �� �� z ����� �������� �����
			{
				z=z->parent;//������� �� z �� ������� ��� ����� ���
				rightrot(root,z,nil);//������� �������� ���������� ��� ��������� z
				z->parent->colour="black";// ������������ �� ��������� z �����
				z->parent->parent->colour="red"; //��� ��� ������ ��� ���������� z �������
				leftrot(root,z->parent->parent,nil);//��� ������� �������� ���������� ���� ������ ��� ���������� z
			}
			else// ������
			{
				z->parent->colour="black";//������������ ��� ����� ��� z �����
				z->parent->parent->colour="red";//��� ��� ������ ��� �������
				leftrot(root,z->parent->parent,nil);// ��� ������� �������� ���������� ���� ������ ��� z
			}
		}
	}
	root->colour="black";//���� ����������� ����� ������� ��� ���� �� ���� ����� �����
}

void insert(node* &root, node* z, node* &nil)//�������� ������ z ��� ������
{
	node* y=nil;// �� y ����� ������� �� ����� ��� ���� �����
	node* x=root;// �� x ����� ������� ��� ����
	while(x!=nil)//��� �� x ��� ����� �����
	{
		y=x;//�� y ������� ��� x
		if(z->value<y->value)//�� � ���� ��� z ����� ��������� ��� ����� ��� y
			x=x->left; // �� x ������� ��� �������� ����� ��� x
		else
			x=x->right;//������ �� x ������� ��� ���� ����� ��� x
	}
	z->parent=y; //������� ��� ����� ��� z �� ������� ��� ��������� y

	if(y==nil)// �� �� y ����� �����
		root=z;//������� �� z �� ����� ����
	else if(z->value < y->value)// ������ �� � ���� ��� z ����� ��������� ��� ����� ��� y
		y->left=z; //���� �� z �������� ����� ��� ������ ��� ������� � y
	else//������
		y->right=z;// ���� �� z ���� ����� ��� ������ ��� ������� � y

	z->left=nil;//���� �� �������� ����� ��� z �����
	z->right=nil;//���� �� ���� ����� ��� z �����
	z->colour="red";//���� �� ����� ��� z �������
	insertfix(root,z,nil);//������ ��� ����������� ��� ��������� ��� z
}


void MyMerge(int array0[], int prwto_stoixeio, int mesaio_stoixeio , int teleutaio_stoixeio)//�������� ��� ����������
{

	int *array1 = new int[teleutaio_stoixeio - prwto_stoixeio + 1];//�������� ���� ������ �� ������ �������� ��� �� ��������
	int i = prwto_stoixeio, j = mesaio_stoixeio + 1, k = 0;
	while (i <= mesaio_stoixeio && j <= teleutaio_stoixeio)//��� �� i ����� ��������� � ��� ��� ������� ��������� ��� �� j ��������� � ��� ��� ����������
	{

		if (array0[i] <= array0[j])//�� �� �������� ��� ������� ������ ���  ���� i ����� ��������� � ��� ��� ������� ������ ���� ���� j
		{
			array1[k] = array0[i];//���� ���� ���� k ��� ���������� ������ �� �������� ��� ���� i ��� ������� ������
			k++;//������ �� i � �� k ���� ���
			i++;
		}
		else//������
		{
			array1[k] = array0[j];//���� ���� ���� k ��� ���������� ������ �� �������� ��� ���� j ��� ������� ������
			k++;//������ �� j � �� k ���� ���
			j++;
		}
	}
	while (i <= mesaio_stoixeio)//��� �� i ����� ��������� � ��� ��� ������� ���������
	{
		array1[k] = array0[i];//���� ���� ���� k ��� ���������� ������ �� �������� ��� ���� i ��� ������� ������
		k++;//������ �� i � �� k ���� ���
		i++;
	}
	while (j <= teleutaio_stoixeio)
	{
		array1[k] = array0[j];//���� ���� ���� k ��� ���������� ������ �� �������� ��� ���� j ��� ������� ������
		k++;//������ �� j � �� k ���� ���
		j++;
	}
	for (i = prwto_stoixeio; i <= teleutaio_stoixeio; i++)//��������� ��� ������������ ������ ���� ������
	{
		array0[i] = array1[i - prwto_stoixeio];
	}
	delete[] array1;//�������� ��� ��������� ������
}

void MyMergeSort(int array0[], int prwto_stoixeio, int teleutaio_stoixeio)
{
	int mesaio_stoixeio;//������ ����

	if (prwto_stoixeio < teleutaio_stoixeio) //�� � ����� ���� ����� ��������� ��� ����������
        {
		mesaio_stoixeio = (prwto_stoixeio + teleutaio_stoixeio) / 2;//������ ���� = ����� � ��������� ���� ��� ���

		MyMergeSort(array0, prwto_stoixeio, mesaio_stoixeio);//���� ��� mergesort ��� �� ������� ������ ����� ��� ��� ��� ������
		MyMergeSort(array0, mesaio_stoixeio + 1, teleutaio_stoixeio);//����� ��� ��� ������� ��� ��� ������ ���� ����� ��� ���������
		MyMerge(array0, prwto_stoixeio, mesaio_stoixeio, teleutaio_stoixeio);//����� ���� ����������
	}
}


void load()
{

   ifstream myfile("integers.txt");

   if(myfile.is_open()){
    string line;
    while(getline(myfile,line)){
        vec.push_back(atoi(line.c_str()));
        }
        myfile.close();
        cout<<"The file was opened successfully\n";
   }
   else
    cout<<"Error"<<endl;
}

void printtxt(double time[][4],int times)
{
int ans;
double sum[]={0.0, 0.0, 0.0, 0.0};
double worst[] ={0.0, 0.0, 0.0, 0.0};
	cout << "are you sure you would like to overwrite the txt file?(1 for yes)\n";
	cin >> ans;
	string words[]={"linear","binary","interpolation","rbsearch"};
	if (ans==1)
	{
		ofstream myfil;
		myfil.open ("output.txt");
		for(int k=0; k<4; k++){
                myfil<<words[k]<<"  ";
        for(int l=1;l<times+1;l++){
        if(worst[k]<time[l-1][k])
         {worst[k]=time[l-1][k];}
        sum[k]=sum[k]+time[l-1][k];}
        myfil<<" The worst time is "<<worst[k]<<" and the average time is "<<sum[k]/(double)times<<" milliseconds"<<endl;;
		}
	myfil.close();
	}

}

void printarray(double time[][4],int times)
{
int ans;
	cout << "are you sure you would like to overwrite the csv file?(1 for yes)\n";
	cin >> ans;
	string words[]={"linear","binary","interpolation","rbsearch"};
	if (ans==1)
	{
		ofstream myfil;
		myfil.open ("output.csv");
		for(int k=0; k<4; k++){
                myfil<<words[k]<<";";
		for(int l=1;l<times+1;l++)

			myfil << time[l-1][k]<< ";";

			myfil << "\n";

		}
	myfil.close();
	}

}
int main()
{
srand(time(NULL));
load();
int *mypointer = &vec[0];
node* nil= new node;//
nil->colour="black";//������� ��� ���� ���� ��� �� red black tree
node* root = nil;//
int temp=0;

MyMergeSort(mypointer, 0, vec.size() - 1);


for(int j=0; j<(int)vec.size(); j++)//���������� �� redblack tree
    {
        node* z=new node;
        z->left=nil;
        z->right=nil;
        z->parent=nil;
        z->colour="red";
       	z->value=vec[j];
        insert(root,z,nil);
    }
   int mode=0;
while(mode <5){
   cout<<"Give a number to find in the file please"<<endl;
   cin>>temp;

    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"~                       Press 1 for linear search                                      ~"<<endl;
    cout<<"~                       Press 2 for binary search                                      ~"<<endl;
    cout<<"~                       Press 3 for interpolation search                               ~"<<endl;
    cout<<"~                       Press 4 for red black tree search                              ~"<<endl;
    cout<<"~                       Press 5 or higher to exit                                      ~"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cin>>mode;

    switch(mode){
    case 1:
        linearsearch(temp);
    break;
    case 2:
	binarysearch(vec,temp,0,(int)vec.size());

	break;
	case 3:
	interpolationsearch(temp);

	break;
	case 4:
        rbsearch(root,temp, nil);

        break;

    }
}

//��� �� ������� ��� ����� ��� ��� �� csv ��� txt ������:
    /*int times=1000;
    double time[times][4];
int start_s,stop_s=0;
   for (int p=0; p<times; p ++){
    for (int mode=0; mode<4; mode++ )
        { time[p][mode]=0.0;}}

    for (int p=0; p<times; p ++){
    for (int mode=0; mode<4; mode++ )
        {

        temp = rand() %1000000 ;

    switch(mode){
    case 0:
        {
        start_s=clock();
        for(int d=0; d<10; d++)
        {
        linearsearch(temp);}
        stop_s=clock();
         time[p][mode]=((stop_s-start_s)/ (double)(CLOCKS_PER_SEC)* 1000.0)*100.0;
        }
    break;
    case 1:
    {
    start_s=clock();
    for(int d=0; d<1000; d++)
    {binarysearch(vec,temp,0,(int)vec.size()-1);}
    stop_s=clock();
      time[p][mode]=((stop_s-start_s)/ (double)(CLOCKS_PER_SEC)* 1000.0);
    }
	break;
	case 2:
    {
    start_s=clock();
    for(int d=0; d<10; d++)
	{
	interpolationsearch(temp);}
    stop_s=clock();
     time[p][mode]=((stop_s-start_s)/ (double)(CLOCKS_PER_SEC)* 1000.0)*100.0;  }
	break;
	case 3:
    {
    start_s=clock();
    for(int d=0; d<10000; d++)
    {rbsearch(root,temp, nil);}
    stop_s=clock();
     time[p][mode]=((stop_s-start_s)/ (double)(CLOCKS_PER_SEC) * 1000.0)/10.0;
    }
        break;
    }






}}
    printarray(time,times);
    printtxt(time,times);*/
    return 0;}

