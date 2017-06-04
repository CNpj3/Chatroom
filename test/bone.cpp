#include <iostream>
#include <string>

using namespace std;

int main()
{
	string name;
	string ans;
	cout << "please input your name to continue" << endl;
    cout << ">>> ";
	cin >> name; 

	if (name != "Jesscia") {
		cout << "Who are you?!! This is for Jesscia!!!! Hey!!!! Are you a Spy?!!!" << endl;
		exit(1);
	}

	cout << endl << "hi! " << name << ", this is MuYu." << endl;
	cout << "Who is your favorite ? (Answer the name without any space)" << endl << ">>> ";

    cin >> ans;
	int courrect = 0;
	while (!courrect) {
		if (ans == "Martin") {
			cout << endl << "oh...I really like Martin, too." << endl 
				 << "but......do you have any other name pop into your mind? " << endl;
		}
		else if (ans == "MuYu") {
			cout << endl << "yeah!! my bone, you are my favorite, too!!!!" << endl;
			break;
		}
		else {
			cout << endl << "oh... really?...QQ" << endl 
				 << "could you please answer again?" << endl;
		}
        cout << ">>> ";
		cin >> ans;
	}

	cout << "bye bye <3" << endl;

	return 0;
}
