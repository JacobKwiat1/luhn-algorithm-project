#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum CrdCard{
    AmEx, Visa, MasterCard, Discover, ALL
};

void genCC(CrdCard, char[]);
void flipDig(char[]);
bool validCC(char[]);
void Luhn(char ccc[]);
int main()
{
    srand(time(0));
    //what kind of card to generate. options are Amex, Visa, MasterCard, Discover, and All
    CrdCard type = Discover;
    int countP = 0;
    int countN = 0;
    char tester[17];
    for(int i = 0; i < 10000; i++) {
        genCC(type, tester);
        Luhn(tester);
        flipDig(tester);
        if(validCC(tester)) {
            cout << tester << " 1" << endl;
            countP++;
        }
        else {
            cout << tester << " 0" << endl;
            countN++;
        }
    }
    cout << "invalid: " << countN << ", valid: " << countP;
    return 0;
}

void Luhn(char card[]){
    int final = 0;
    int calculatedDigit;
    //size is either 15 or 16 digits depending on when the first '\0' shows up
    int size = (card[14] != '\0') ? 15 : 14;
    for(int i = 1; i <= size; i++) {
        //-48 because digits are stored as characters
        calculatedDigit = (card[size-i]-48)*(1+i%2);
        final += (calculatedDigit < 10) ? calculatedDigit : calculatedDigit-9;
        //final += ((card[size-i]-48)*(1+i%2) < 10) ? (card[size-i]-48)*(1+i%2) : (card[size-i]-48)*(1+i%2)-9;
    }
    final *= 9;
    final %= 10;
    card[size] = final + '0';
    cout << endl << '\0' << endl;
    return;
}

void genCC(CrdCard kind, char card[]) {
    int size = (kind == AmEx) ? 16 : 17;
    //beginnings for cards
    //9 = random, 8 used as place holder for random 4 or 7
    char begin[5][4] = {{'3', '8', '9', '9'}, //AmEx
        {'4','9','9','9'}, //Visa
        {'5', (rand()%5+1)+'0','9','9'}, //MasterCard
        {'6','0','1','1'}, //Discover
        {'0','0','0','0'}}; //all
        for(int i = 0; i < size-1; i++)   {
            while(i < 4)    {
                if(begin[kind][i] == '8')   {
                    card[i] = (rand()%2 == 1) ? '4' : '7';
                }
                else if(begin[kind][i] == '9')  {
                    card[i] = rand()%10 + '0';
                }
                else    {
                    card[i] = begin[kind][i];
                }
                i++;
            }
            card[i] = rand()%10 + '0';
        }
        for(int i = size; i <= size; i++)    {
            card[i] = '\0';
        }
        return;
}

//change a random digit in the number to a random value from 1-9
void flipDig(char card[])    {
    int size = (card[15] != '\0') ? 16 : 15;
    card[rand()%size] = rand()%10 + '0';
}

bool validCC(char card[])    {
    int final = 0;
    int calculatedDigit;
    //size is either 15 or 16 digits depending on when the first '\0' shows up
    int size = (card[15] != '\0') ? 15 : 14;
    for(int i = 1; i <= size; i++) {
        //-48 because digits are stored as characters
        calculatedDigit = (card[size-i]-48)*(1+i%2);
        final += (calculatedDigit < 10) ? calculatedDigit : calculatedDigit-9;
    }
    final *= 9;
    final %= 10;
    return ((final + '0') == card[size]);
}
