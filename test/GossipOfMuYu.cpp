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

	cout << endl << "hi, " << name << " !" << endl
		 << "Do you want to know the secert of Mu Yu?" << endl
		 << "Let's guess who is the person that Mu Yu is favorite!!!" << endl
		 << "(Answer the name without any space)" << endl
		 << "如果不知道那個人的英文怎麼表示，也可以用中文噢" << endl <<  ">>> ";

    cin >> ans;
	while (ans != "quit") {
		if (ans == "Jessica" || ans == "潔心") {
			cout << endl << "yeah!! Jesscia, my bone, my favorite!!!!" << endl
				 << ans << " Let's be LOSERS and stay in pot!!!" << endl;
			break;
		}
		else if (ans == "Martin") 
			cout << endl << "oh...I really like " << ans << ", but...he is OCCUPIED!!!" << endl;

		else if (ans == "二宮和也" || ans == "nino" || ans == "NINO")
			cout << endl << "oh...I really like " << ans << ", but there is someone I love more..." << endl;

		else if (ans == "Po An" || ans == "Po-An" || ans == "柏安" || ans == "林柏安")
			cout << endl << "oh...I really like " << ans << ", but...she is OCCUPIED!!!" << endl;

		else if (ans == "本恩" || ans == "廖本恩")
			cout << endl << "un...do you sure that you want to answer this name...?" << endl
				 << "I thought someone may kill us......" << endl;

		else if (ans == "Peter" || ans == "彼得靠" || ans == "彼得")
			cout << endl << "well... "<< ans << " has his GODDESS now. And we're 屁話 friends" << endl;

		else if (ans == "柏柏" || ans == "柏辰")
			cout << endl << "un...you really think I will fall in love with a GOLDEN FISH like " << ans << "?!" << endl;

		else if (ans == "李綠")
			cout << endl << "well... " << ans << " has his GODDESS now. And I really don't like his...hair...." << endl;

		else if (ans == "心怡姐" || ans == "女神姐姐" || ans == "心怡" || ans == "Jenny")
			cout << endl << "yeah! " << ans << " is my goddess, but just only goddess..." << endl;

		else if (ans == "黃義")
			cout << endl << "un...do you know that " << ans << " is only an acquaintance..." << endl
				 << "and " << ans << " is OCCUPIED by 大溶解" << endl;

		else if (ans == "大溶解")
			cout << endl << "un...do you know that " << ans << " is only an acquaintance..." << endl
				 << "and " << ans << " is OCCUPIED by 黃義" << endl;

		else if (ans == "榮恩" || ans == "ㄇㄌ")
			cout << endl << "HOW DARE AM I!!!!!! just forget it, please." << endl;	

		else if (ans == "華恩" || ans == "于華恩")
			cout << endl << "oh...I really like " << ans << "and she is so funny. but......" << endl;

		else 
			cout << endl << "Wrong Answer!! and you guess the one I even prepare no response for ......" << endl;

        cout << "Do you have any else name to answer? " << endl
        	 << "or if you don't want to guess anymore, input \"quit\"" << endl
        	 << ">>> ";
		cin >> ans;
	}

	cout << "bye bye <3" << endl << endl << endl;

	return 0;
}
