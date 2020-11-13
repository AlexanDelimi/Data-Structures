

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

bool linearsearch(int noumero)//ορισμα ο κατα αναζητηση ακεραιος
{

    for(int c=0; c<(int)vec.size(); c++)//για ολο το βεκτορα με τους ακεραιους
        {
        if (vec.at(c)==noumero)//αν στην θεση c ειναι ο κατα αναζητηση ακεραιος
       {
    cout<<"The number "<< noumero<<" exist at position "<<c+1<<endl;

        return true;// επεστρεψε αληθες
        }
    }
         cout<<"The number was not found"<< endl;

    return false;// αν δεν βρεθει θα επιστρεψει ψευδες

}
bool binarysearch(vector<int>& input_vector, int element_for_search,int left_border,int right_border)
{
	bool found = false;// αρικα δεν εχει βρει τον ακεραιο
	int middle = floor((left_border + right_border) / 2);// μεση= δεξι οριο + αριστερο δια 2
	if (right_border < left_border)//αν το δεξι οριο ειναι μικροτερο απο το αριστερο σημαινει οτι δεν το βρηκε
	{
		cout << "The number " << element_for_search << " wasn't found." << endl;
	}
	else//αλλιως
	{
		if (element_for_search == input_vector[middle])//αν το στοιχειο προς αναζητηση ειναι ισο με το στοιχειο που λεμε μεσο του βεκτορα
		{
			cout << "The number " << element_for_search << " was found at the position " << middle++ <<endl;
			found = true;// το στοιχειο βρεθηκε
		}
		else
		{
			if (element_for_search > input_vector[middle])//αλλιως αν το στοιχειο ειναι μεγαλυτερο απο το στοιχειο στην μεση του βεκτορα
			{
				middle++;//αυξησε την μεση κατα ενα
				binarysearch(input_vector, element_for_search, middle, right_border);// συνεχισε την αναζητηση στο βετορα απο την νεα μεση και μετα
			}
			else// αλλιως αν ειναι μικροτερο
			{
				middle--;// μειωσε την μεση κατα ενα
				binarysearch(input_vector, element_for_search, left_border, middle);//συνεχισε την αναζητηση απο την νεα μεση και πισω
			}
		}
	}
	return found;// επεστρεψε αν βρεθηκε το στοιχειο
}


bool interpolationsearch(int noumero)
{

    int left=0;//αριστερο οριο =0
    int right=(int)vec.size()-1;// δεξι οριο μεγεθος του πινακα -1
    int next= ((noumero-vec.at(left))/(vec.at(right)-vec.at(left)))*(right-left) +left;// επομενο στοιχειο = τυπος
    while (left<right&& noumero>vec[left]&&noumero<vec[right])// οσο το αριστερο οριο δεν ειναι μικροτερο η ισο απο το δεξι και το νουμερο δεν ειναι μικροτερο απο αυτο στην αριστερη θεση και δεν ειναι μεγαλυτερο απο αυτη στην δεξια
    {
        if(noumero<=vec.at(next))// αν το νουμερο προς αναζητηση ειναι μικροτερο απο τον στοιχειο του τυπου
            {
                right=next-1;//δεξι οριο =τυπος-1
            }
        else//αλλιως
            {
            left=next+1;//αριστερο οριο =τυπος+1
            }
        next=((noumero-vec.at(left))/(vec.at(right)-vec.at(left)))*(right-left) +left;// υπολογισμος του τυπου με τα νεα ορια
    }
    if(noumero==vec.at(next))//αν βρεθει ο αριθμος προς αναζητηση
    {
       cout<<"The number "<< noumero<<" exists at position "<<next+1<<endl;

        return true;//επεστρεψε αληθες
    }
    else//αλλιως
    {
      cout<<"The number was not found"<< endl;

        return false; //επεστρεψε ψευδες
    }
}

typedef struct rbnode//κομβος για red black tree
{
	string colour;//χρωμα
	struct rbnode *right, *left, *parent;//δεικτες προς δεξι, αριστερο παιδι και γονεα
    int value;//τιμη
}node;


void leftrot(node* &root, node* x, node* &nil)//αριστερη περιστροφη
{
	node* y=x->right;//δεικτης προς το δεξι παιδι του κομβου στον οποιο θα κανουμε την περιστροφη
	x->right = y->left;//το δεξι παιδι του κομβου που καλουμε δειχνει στο αριστερο παιδι του καινουργιου δεικτη

	if(y->left!=nil)//αν το αριστερο παιδι του καινουριου δεικτη δεν ειναι φυλλο
	{
		y->left->parent = x;//ο πατερας του αριστερου παιδιου του y δειχνει στο x
	}

	y->parent=x->parent; // ο πατερας του κανουριου δεικτη δειχνει στο πατερα του κομβου προς περιστροφξ

	if(x->parent==nil)//αν ο πατερας του x ειναι φυλλο
		root=y;//η νεα ριζα ειναι ο y
	else if(x==x->parent->left)//αλλιως αν το x ειναι το αριστερο παιδι του πατερα του x
		x->parent->left = y;//τοτε το αριστερο παιδι του πατερα του χ δειχνει στο y
	else//αλλιως
		x->parent->right = y;// το δεξι παιδι του πατερα του χ δειχνει στο y

	y->left = x;//το αριστερο παιδι του y δειχνει στο x
	x->parent = y;//ο πατερας του x δειχνει στο y
}

void rightrot(node* &root, node* y, node* &nil)//δεξια περιστροφη
{
	node* x=y->left;//καινουριος δεικτης σε κομβο (x) που δειχνει στο αριστερο παιδι του κομβου προς περιστροφη y
	y->left = x->right; //το αριστερο παιδι του του y δειχνει στο δεξι παιδι του x

	if(x->right!=nil)//Αν το δεξι παιδι του x δεν ειναι φυλλο
	{
		x->right->parent = y;//ο γονεας του δεξιου παιδιου του x δειχνει στο y
	}

	x->parent=y->parent; //ο γονεας του x δειχνει στον γονεα του y

	if(y->parent==nil)//αν ο γονεας του y ειναι φυλλο
		root=x;//η ριζα ειναι ο x
	else if(y==y->parent->left) //αλλιως αν το y ειναι το αριστερο παιδι του πατερα του y
		y->parent->left = x; //τοτε το x δειχνει στο  αριστερο παιδι του πατερα του y
	else//αλλιως
		y->parent->right = x;//το x δειχνει στο  δεξι παιδι του πατερα του y

	x->right = y;//το δεξι παιδι του x ειναι το y
	y->parent = x;//o γονιος του y ειναι ο x
}

node* rbsearch(node* &root, int searchitem, node* &leaf)//αναζητηση στο red black tree
{
	node* rightnow=root;//δεικτης στον κομβο που βρισκομαστε αυτη την στιγμη, ξεκιναμε απο την ριζα
	while(rightnow!=leaf)//οσο ο δεικτης αυτος δεν ειναι φυλλο
	{
		if(rightnow->value==searchitem)//αν η τιμη του κομβου που δειχνει ο δεικτης αυτος ειναι ισος με το αντικειμονο προς αναζητηση
		{
        cout<< "The number was found"<<endl;
		return rightnow;// επεστρεψε τον δεικτη σε αυτο τον κομβο
		}
		else if(searchitem < rightnow->value)//αλλιως αν ειναι μικροτερο
		rightnow=rightnow->left; //ο δεικτης αυτος δειχνει στο αριστερο παιδι του κομβου που εδειχνε πριν
		else if(searchitem > rightnow->value)// αλλιως αν ειναι μεγλαυτερο
		rightnow=rightnow->right;//ο δεικτης δειχνει στο δεξι παιδι του κομβου που εδειχνε πριν
	}
        cout << "The number wasn't found\n";
	rightnow=leaf;//αν δεν βρεθει μετα την αναζητηση ο δεικτης δειχνει φυλλο
	return 0;
}

void insertfix(node* &root, node* z, node* &nil)// διορθωση δενδρου
{
	while(z->parent->colour=="red")//οσο το χρωμα του γονεα του κομβου του ορισματος ειναι κοκκινος
	{
		if(z->parent==z->parent->parent->left)//αν ο γονεας του κομβου ειναι το αριστερο παιδι του γονεα του
		{
			node* y=z->parent->parent->right;//φτιαχνουμε ενα δεικτη σε κομβο και διεχνει το δεξι παιδι του 'παππου' του z
			if(y->colour=="red") // αν το χρωμα του κομβου που δειχνει ο καινουριος δεικτης ειναι κοκκινο
			{
				z->parent->colour="black";//κανουμε το χρωμα του γονιου του z μαυρο
				y->colour="black";//και το χρωμα του κομβου που δειχνει ο καινουριος δεικτης μαυρο
				z->parent->parent->colour="red";//χρωματιζουμε το παππου του z κοκκινο
				z=z->parent->parent;// και βαζουμε τον δεικτη z να δεινει τον παππου του ωστε να συνεχισει ο ελεγχος στους πιο πανω κομβους
			}
			else if(z==z->parent->right)// αλλιως αν το z ειναι δεξι παιδι
			{
				z=z->parent;// το  βαζουμε το z να δειχνει στον γονιο του
				leftrot(root,z,nil);//κανουμε αριστερη περιστροφη στο καινουριο z

				z->parent->colour="black"; //χρωματιζουμε τον γονιο του καινουριου z μαυρο
				z->parent->parent->colour="red"; //και τον παπποου του κοκκινο
				rightrot(root,z->parent->parent,nil);//κανουμε δεξια περιστροφη στον παππου του καινουριου z
			}
			else//αλλιως
			{
				z->parent->colour="black";//χρωματιζουμε τον γονιο του
				z->parent->parent->colour="red";//χρωματιζουμε τον παππου του z κοκκινο
				rightrot(root,z->parent->parent,nil);//κανουμε δεξια περιστροφη στον αππου του z
			}
		}
		else
		{
			node* y=z->parent->parent->left;//δημιουργουμε δεικτη σε κομβο και δειχνει τοαριστερο παιδι του παππου του z
			if(y->colour=="red")//αν το χρωμα του κομβου που δειχνει ο δεικτης ειναι κοκκινο
			{
				z->parent->colour="black";//χρωματιζουμε τον γονιο του z μαυρο
				y->colour="black";//και το κομβο που δειχνει ο y μαυρο
				z->parent->parent->colour="red";// χρωματιζουμε τον παππου κοκκινο
				z=z->parent->parent;//και βαζουμε τον δεικτη z να δεινει τον παππου του ωστε να συνεχισει ο ελεγχος στους πιο πανω κομβους
			}
			else if(z==z->parent->left)//αλλιως αν το z ειναι αριστερο παιδι
			{
				z=z->parent;//βαζουμε το z να δειχνει τον γονιο του
				rightrot(root,z,nil);//κανουμε αριστερη περιστροφη στο καινουριο z
				z->parent->colour="black";// χρωματζιουμε το καινουριο z μαυρο
				z->parent->parent->colour="red"; //και τον παππου του καινουριου z κοκκινο
				leftrot(root,z->parent->parent,nil);//και κανουμε αριστερη περιστροφη στον παππου του καινουριου z
			}
			else// αλλιως
			{
				z->parent->colour="black";//χρωματιζουμε τον γονιο του z μαυρο
				z->parent->parent->colour="red";//και τον παππου του κοκκινο
				leftrot(root,z->parent->parent,nil);// και κανουμε αριστερη περιστροφη στον παππου του z
			}
		}
	}
	root->colour="black";//οταν τελειωνουμε παντα βαζουμε την ριζα να εχει χρωμα μαυρο
}

void insert(node* &root, node* z, node* &nil)//εισαγωγη κομβου z στο δενδρο
{
	node* y=nil;// το y ειναι δεικτης σε φυλλο δλδ κενο κομβο
	node* x=root;// το x ειναι δεικτης στη ριζα
	while(x!=nil)//οσο το x δεν ειναι φυλλο
	{
		y=x;//το y δειχνει στο x
		if(z->value<y->value)//αν η τιμη του z ειναι μικροτερη της τιμης του y
			x=x->left; // το x δειχνει στο αριστερο παιδι του x
		else
			x=x->right;//αλλιως το x δειχνει στο δεξι παιδι του x
	}
	z->parent=y; //βαζουμε τον γονεα του z να δειχνει στο καινουριο y

	if(y==nil)// αν το y ειναι φυλλο
		root=z;//βαζουμε το z να ειναι ριζα
	else if(z->value < y->value)// αλλιως αν η τιμη του z ειναι μικροτερη της τιμης του y
		y->left=z; //βαλε το z αριστερο παιδι του κομβου που δειχνει ο y
	else//αλλιως
		y->right=z;// βαλε το z δεξι παιδι του κομβου που δειχνει ο y

	z->left=nil;//βαλε το αριστερο παιδι του z φυλλο
	z->right=nil;//βαλε το δεξι παιδι του z φυλλο
	z->colour="red";//βαλε το χρωμα του z κοκκινο
	insertfix(root,z,nil);//καλεσε την επιδιορθωση της εισαγωγης στο z
}


void MyMerge(int array0[], int prwto_stoixeio, int mesaio_stoixeio , int teleutaio_stoixeio)//συμπτυξη των υποπινακων
{

	int *array1 = new int[teleutaio_stoixeio - prwto_stoixeio + 1];//φτιαχνει εναν δεικτη σε πινακα μεγεθους οσο τα στοιχεια
	int i = prwto_stoixeio, j = mesaio_stoixeio + 1, k = 0;
	while (i <= mesaio_stoixeio && j <= teleutaio_stoixeio)//οσο το i ειναι μικροτερο η ισο του μεσαιου στοιχειου και το j μικροτερο η ισο του τελευταιου
	{

		if (array0[i] <= array0[j])//αν το στοιχειο του αρχικου πινακα στη  θεση i ειναι μικροτερο η ισο του αρχικου πινακα στην θεση j
		{
			array1[k] = array0[i];//βαζω στην θεση k του προσωρινου πινακα το στοιχειο στη θεση i του αρχικου πινακα
			k++;//αυξανω το i κ το k κατα ενα
			i++;
		}
		else//αλλιως
		{
			array1[k] = array0[j];//βαζω στην θεση k του προσωρινου πινακα το στοιχειο στη θεση j του αρχικου πινακα
			k++;//αυξανω το j κ το k κατα ενα
			j++;
		}
	}
	while (i <= mesaio_stoixeio)//οσο το i ειναι μικροτερο η ισο του μεσαιου στοιχειου
	{
		array1[k] = array0[i];//βαζω στην θεση k του προσωρινου πινακα το στοιχειο στη θεση i του αρχικου πινακα
		k++;//αυξανω το i κ το k κατα ενα
		i++;
	}
	while (j <= teleutaio_stoixeio)
	{
		array1[k] = array0[j];//βαζω στην θεση k του προσωρινου πινακα το στοιχειο στη θεση j του αρχικου πινακα
		k++;//αυξανω το j κ το k κατα ενα
		j++;
	}
	for (i = prwto_stoixeio; i <= teleutaio_stoixeio; i++)//αντιγραφω τον ταξινομημενο πινακα στον αρχικο
	{
		array0[i] = array1[i - prwto_stoixeio];
	}
	delete[] array1;//διαγραφω τον βοηθητικο πινακα
}

void MyMergeSort(int array0[], int prwto_stoixeio, int teleutaio_stoixeio)
{
	int mesaio_stoixeio;//μεσαια θεση

	if (prwto_stoixeio < teleutaio_stoixeio) //αν η πρωτη θεση ειναι μικροτερη της τελευταιας
        {
		mesaio_stoixeio = (prwto_stoixeio + teleutaio_stoixeio) / 2;//μεσαια θεση = πρωτη κ τελευταια θεση δια δυο

		MyMergeSort(array0, prwto_stoixeio, mesaio_stoixeio);//καλω την mergesort για το κομματι πρωτης θεσης εως και την μεσαια
		MyMergeSort(array0, mesaio_stoixeio + 1, teleutaio_stoixeio);//ομιως για την επομενη απο την μεσαια θεση μεχρι την τελευταια
		MyMerge(array0, prwto_stoixeio, mesaio_stoixeio, teleutaio_stoixeio);//ενωνω τους υποπινακες
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
nil->colour="black";//φτιαχνω μια κενη ριζα για το red black tree
node* root = nil;//
int temp=0;

MyMergeSort(mypointer, 0, vec.size() - 1);


for(int j=0; j<(int)vec.size(); j++)//αρχικοποιω το redblack tree
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

//για να μετρησω τον χρονο και για το csv και txt αρχειο:
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

