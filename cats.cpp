#include <iostream>
#include <fstream>
using namespace std;


// struct for cat variables  
struct Cat{
  enum {MAX_CHAR_LEN = 100};
  char name[MAX_CHAR_LEN]; 
  double minLifeSpan;
  double maxLifeSpan;
  double minWeight;
  double maxWeight;
  char temperament[100];
  char Origin[100];
  Cat();
};

void printExample(ostream &out, Cat Cats);
const int MAX_CATS = 100;
// default constructor for cat 
Cat::Cat(){
  for(int index = 0; index > MAX_CHAR_LEN; index ++) {
    name[index] = '\0';
    temperament[index] = '\0';
    Origin[index] = '\0';
  }
  minLifeSpan = 0.0;
  maxLifeSpan = 0.0;
  minWeight = 0.0;
  maxWeight = 0.0;
}
// prints cat data
void printExample(ostream &out, Cat Cats) {
  out << Cats.name << ";";
  out << Cats.minLifeSpan << ";";
  out << Cats.maxLifeSpan << ";";
  out << Cats.minWeight << ";";
  out << Cats.maxWeight << ";";
  out << Cats.temperament << ";";
  out << Cats.Origin << endl;
}

// Validates the double values entered by the user are actually doubles
double readDouble(const char prompt[]) {
  double temp = 0;
  cout << prompt;
  cin >> temp;
  while (!cin) {
    cin.clear();
    cin.ignore(1000,'\n');
    cout << "Invalid Data!" << endl;
    cout << prompt;
    cin >> temp;
  }
  return temp;
}

// adds cat 
void AddCat(Cat cats[], int index)
{
      
  cout << "\nCat Breed: ";
      
  cin.getline(cats[index].name, MAX_CATS);
  cats[index].minLifeSpan = readDouble("Enter the cats minimum life span: ");
  cats[index].maxLifeSpan = readDouble("Enter the max life span: ");
  cats[index].minWeight = readDouble("Enter the minimum weight(lbs): ");
  cats[index].maxWeight = readDouble("Enter the max weight(lbs): ");
      
  cout << "Enter the Origin: ";
  cin >> cats[index].Origin;
  
  cout << "Enter the Temperament: ";
  cin >> cats[index].temperament;
  
  cin.ignore(100,'\n');

}


// removes cat
void removeCat(Cat cats[], int size, int index)
{
  cout << "Enter index of cat to delete: " << endl;
  int delIndex;
  cin >> delIndex;
  for(int index = delIndex; index < size; index ++){
    
    cats[index] = cats[index + 1];
    
  }
  
}
// prints cats of the origin entered by the user
void PrintCatsByOrigin(Cat Cats[])
{
  string CatOrigin = "";
  cout << "Enter Cat Origin: ";
  cin >> CatOrigin;
  for(int index = 0; index < MAX_CATS; index ++){
    if (Cats[index].Origin == CatOrigin){
      cout << "index" << index << ": ";
      printExample(cout, Cats[index]);
      cout << endl;
    }

  }
}
// displays cat list 
void printArrayToScreen(Cat examples[], int numExamples) {
  for (int index = 0; index < numExamples; index++) {
    cout << "Index " << index << ": ";
    printExample(cout, examples[index]);
  }
}
// prints a new cat database
void printArrayToFile(const char fileName[], Cat examples[], int numExamples) {
  ofstream outFile(fileName);
  for (int index = 0; index < numExamples; index++) {
    printExample(outFile, examples[index]);
  }
}
// reads the cats from the file 
Cat readcat(ifstream &inFile){
    Cat Cats; 
    inFile.get(Cats.name, Cat::MAX_CHAR_LEN, ';');
    inFile.ignore(100,';');
    inFile >> Cats.minLifeSpan;
    inFile.ignore(100,';');
    inFile >> Cats.maxLifeSpan;
    inFile.ignore(100,';');
    inFile >> Cats.minWeight;
    inFile.ignore(100,';');
    inFile >> Cats.maxWeight;
    inFile.ignore(100,';');
    inFile >> Cats.temperament;
    inFile.ignore(100,';');
    inFile >> Cats.Origin;
    inFile.ignore(100,'\n');
    // If we reached the end of the file while reading, then the entry is not valid
  
    return Cats;
}
// reads every cat in file 
int readCats(Cat Cats[]) {
  ifstream catFile("cats.txt");
  int numCats = 0;
  while(catFile.peek() != EOF && numCats < MAX_CATS) {
    Cats[numCats] = readcat(catFile);
    numCats++;
  }
  return numCats;
}
// main function with the display menu 
int main() {
  Cat cats[MAX_CATS]; 
  int num = readCats(cats);
  cout << "Cats: " << num << endl;
  printArrayToScreen(cats, num);
    
  
  
  int indX = 0;
  while (indX != 7){
    cout << "\n";
    cout << "Enter 1 to display the cat list" << endl;
    cout << "Enter 2 to add a cat to the list" << endl;
    cout << "Enter 3 to display cats by origin" << endl;
    cout << "Enter 4 to Remove a cat from the list" << endl;
    cout << "Enter 5 to Reload database from the file" << endl;
    cout << "Enter 6 to print database" << endl; 
    cout << "Enter 7 to Exit" << endl;
    indX = readDouble("What would you like to do: ");
     
    cin.ignore(100,'\n');

      
      if(indX == 6){
        printArrayToFile("cats1.txt", cats, num);
      }
    
      if(indX == 5){
        num = readCats(cats);
      }

      if(indX == 4){
       if (num < MAX_CATS){
          removeCat(cats, num, indX);
          num--;
        }
      }

      if(indX == 3){
        PrintCatsByOrigin(cats);
      }
    
      if(indX == 2){
        if (num < MAX_CATS){
          AddCat(cats, num);
          num++;
        }
      }
       
      if(indX == 1){
        printArrayToScreen(cats, num);
      }
        
  
   
  }
}


