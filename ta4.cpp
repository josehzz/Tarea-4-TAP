#include <iostream>
#include <string>
#include <vector>
#include <cmath>

/*
    Integrantes:
    Jose Hernandez
    Luis Caceres
*/

using namespace std;

void appendZeros(string &n, int total){
    while(total > 0){
        n = n + '0';
        total--;
    }
}

void addLeading(string &n1, string &n2) {
    int len1 = n1.size();
    int len2 = n2.size();

    //cout << "added0: " << n1 << " " << n2 << "sizes: " << n1.size() << " " << n2.size() <<endl;

    if (len1 < len2){
        for (int i = 0; i < len2 - len1; i++)
            n1 = '0' + n1;
    }
    else if (len1 > len2){
        for (int i = 0; i < len1 - len2; i++)
            n2 = '0' + n2;
    }

    //cout << "added1: " << n1 << " " << n2 <<endl;
}

string addString(string n1, string n2){ //Assuming both string have same size
    addLeading(n1, n2);
    //cout << "to add: " << n1 << " " << n2 <<endl;

    string res = "";
    bool carry = false;
    int sum = 0;
    for(int i = n1.size() -1; i > -1; i--){
        if(n1[i] == '0'){ //Add n2 if n1 is '0'
            sum = (int)(n2[i] - '0');

            if(carry){ //Check if there's carry over
                carry = false;
                sum += 1;
            }

            if(sum > 9){//Check if carry over onto next digit
                carry = true;
                sum = sum%10;
            }

            res = (char)(sum + (int)'0') + res;
        }
        else if(n2[i] == '0'){ //Add n1 if n2 is '0'
            sum = (int)(n1[i] - '0');

            if(carry){ //Check if there's carry over
                carry = false;
                sum += 1;
            }

            if(sum > 9){//Check if carry over onto next digit
                carry = true;
                sum = sum%10;
            }

            res = (char)(sum + (int)'0') + res;
        }
        else {
            sum = (int)(n1[i] + n2[i] - '0' - '0'); //Add numbers as integers

            if(carry){ //Check if there's carry over
                carry = false;
                sum += 1;
            }

            if(sum > 9){ //Check if carry over
                carry = true;
                sum = sum%10;
            }

            res = (char)(sum + '0') + res;
        }
    }

    if(carry){ //Carry over was left
        res = '1' + res;
    }

    return res;
}

void resString1(string &n1){ //Only reduces n1 by 1
    if(n1.size() == 1 && n1[0] == '0') return; //Do nothing

    int sus = 0;
    bool lend = false;

    for(int i = n1.size() -1; i > -1; i--){
        if(n1[i] == '0' && !lend){ //Has to lend from next digit
            n1[i] = '9';
            lend = true; continue;
        }
        else if(n1[i] != '0' && !lend){ //No need for lending
            n1[i] = (char)((int)n1[i] - 1); break;
        }

        if(n1[i] == '0' && lend){ //This digit can't lend
            n1[i] = '9';
        }
        else if(n1[i] != '0' && lend) {//A lending digit was found
            n1[i] = (char)((int)n1[i] - 1);

            if(n1[i] == '0' && i == 0){ //Erase leading '0'
                n1.erase(0, 1);
            }
            break;
        }
    }
}

string resta(string n1, string n2){
    int ind = 0;
    while(n2[ind] == '0'){
        n2.erase(0, 1);
        if(n2.size() < 1) return n1;
    }

    string res; res.assign(n1);
    //resString1(n2); //Padding

    while(n2.size() > 1 || n2[0] != '0'){ //While there's multiplication to be done
        resString1(res);
        //addLeading(n1, res);
        resString1(n2);
    }

    return res;
}

int isStringBigger(string n1, string n2){
    int len1 = n1.size(), len2 = n2.size();

    //if(len2 == 4) cout << "size 4: " << n2[0] << " " << n2[3] <<endl;

    if(len1 > len2){
        return 1;
    }
    else if(len1 < len2){
        return -1;
    }
    else { //Equal size
        for(int i = 0; i < len1; i++){
            if(n1[i] - '0' > n2[i] - '0'){ //Leading digits are bigger that n2's
                return 1;
            }
            else if(n1[i] - '0' < n2[i] - '0'){
                return -1;
            }
        }
    }

    return 0; //Two string are the same
}

string resString(string n1, string n2){
    addLeading(n1, n2);
    //cout << "res st: " << n1 << " " << n2 <<endl;

    //Decide which string is bigger and put that on n1
    int isBigger = isStringBigger(n1, n2);
    if(isBigger == 0){ //Equal
        return "0";
    }
    else if(isBigger == -1){ //Swap - n2 is bigger
        string au; au.assign(n1);
        n1.assign(n2);
        n2.assign(au);
    }//If equals 1, no need to swap

    //Do subtraction

    //Success

    int sus = 0;
    bool lend = false;

    for(int i = n1.size() -1; i > -1; i--){
        if((int)(n1[i] - '0') - (int)(n2[i] - '0') < 0 && !lend){ //Has to lend from next digit
            sus = 10 + (int)(n1[i] - '0') - (n2[i] - '0');
            n1[i] = (char)sus + '0';
            lend = true;
        }
        else if((int)(n1[i] - '0') - (int)(n2[i] - '0') >= 0 && !lend){ //No need for lending
            n1[i] = n1[i] - (n2[i] - '0');
        }

        int j = i - 1;
        while(lend){ //Search for a lending digit
            if(n1[j] == '0'){ //This digit can't lend
                n1[j] = '9';
            }
            else if(n1[j] != '0') {//A lending digit was found
                n1[j] = (char)((int)n1[j] - 1);
                lend = false;

    //            if(n1[i] == '0' && i == 0){ //Erase leading '0'
    //                n1.erase(0, 1);
    //            }
            }
            j--;
        }

        //if(n1[i] < '0') cout << "S: " << n1 << " I: " << i << endl;
    }

    //Erase leading zeros
    for(int i = 0; i < n1.size(); ){
        if(n1[i] == '0'){ //Delete leading zero
            n1.erase(0, 1);
        }
        else if(n1[i] != '0'){ //Valid digit found
            break;
        }
    }

    //cout << "res en: " << n1 << " " << n2 <<endl;

    return n1;
}

string multiply(string num1, string num2){
    int len1 = num1.size();
    int len2 = num2.size();
    if (len1 == 0 || len2 == 0)
       return "0";

    vector<int> result(len1 + len2, 0);

    int i_n1 = 0; //Indexes
    int i_n2 = 0;

    for (int i = len1 - 1; i >= 0; i--){
        int carry = 0;
        int n1 = num1[i] - '0';

        i_n2 = 0;

        // Go from right to left in num2
        for (int j = len2 - 1; j >= 0; j--){
            int n2 = num2[j] - '0';
            int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

            carry = sum / 10; //Next carry

            result[i_n1 + i_n2] = sum % 10;

            i_n2++;
        }

        if (carry > 0) //next carry
            result[i_n1 + i_n2] += carry;

        i_n1++;
    }

    // ignore '0's from the right
    int i = result.size() - 1;
    while (i >= 0 && result[i] == 0)
       i--;

    if (i == -1) //shouldn't happen
       return "0";

    string s = "";
    while (i >= 0)
        s += (char)result[i--] + '0';

    return s;
}

string divCon(string n1, string n2){
    addLeading(n1, n2);
    int _n = n1.size();

    //if(_n == 1) cout << "_" << n1 << " " << n2 <<endl;

    if(_n == 0) return 0;
    if(_n == 1) return multiply(n1, n2);

    int _h1 = (int)floor(_n / 2.0); //Set halves ID
    int _h2 = (int)ceil(_n - _h1);

    string x1 = n1.substr(0, _h1); //Divide strings
    string y1 = n1.substr(_h1, _h2);

    string x2 = n2.substr(0, _h1);
    string y2 = n2.substr(_h1, _h2);

    //cout << "na: " << x1 << " " << y1 << " ni: " << x2 << " " << y2 <<endl;

    string z2 = divCon(x1, x2);
    string z0 = divCon(y1, y2);
    string z1 = resString(resString(divCon(addString(x1, y1), addString(x2, y2)), z2), z0);

    //cout << "z2: " << z2 << " z1: " << z1 << " z0: " << z0 <<endl;

    appendZeros(z2, _h2 * 2); //Add '0's from decimal base
    appendZeros(z1, _h2);

    string to = addString(addString(z2, z1), z0);
    return to;
}

int main(){
    string all, num1, num2;
    getline(cin, all);

    num1 = all.substr(0, all.find(" "));
    all.erase(0, all.find(" ") + 1);
    num2 = all.substr(0, all.find(" "));

    addLeading(num1, num2); //Add '0' if strings are not equal in length
    //cout << num1 << endl << num2 <<endl;

    //cout << "sum: " << addString("0222", "5000") <<endl;

    //resString1(num1); cout << "res: " << num1 <<endl;
    //resString1(num1); cout << "res: " << num1 <<endl;
    //resString1(num1); cout << "res: " << num1 <<endl;

//    cout << "mult: " << multiply(num1, num2) <<endl;
//    cout << "divC: " << divCon(num1, num2) <<endl;
//    cout << "resS: " << resString(num1, num2) <<endl;

    string result = divCon(num1, num2);

    //Erase leading zeros
    for(int i = 0; i < result.size(); ){
        if(result[i] == '0'){ //Delete leading zero
            result.erase(0, 1);
        }
        else if(result[i] != '0'){ //Valid digit found
            break;
        }
    }

    cout << result <<endl;

    return 0;
}
