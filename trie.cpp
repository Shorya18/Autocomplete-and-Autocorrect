#include <bits/stdc++.h>
using namespace std;


class WhiteSpaceDetection
{
	set<string> words;
	string s;

public:
	vector<string> parsedWords;
	vector<bool> dp;
	vector<int> dp1;
	WhiteSpaceDetection(string word)
	{
		this->s = word;
		for (int i = 0; i < word.size() + 1; i++)
		{
			dp.push_back(0);
		}
		for (int i = 0; i < word.size() + 1; i++)
		{
			dp1.push_back(-1);
		}
	}
	
	void addMatchingWord(string word)
	{
		words.insert(word);
	}
	bool isWordPresent(string s);
	bool whitespaceDetectionDP();
	void printWord(int i)
	{
		if (i == 0)
			return;
		printWord(dp1[i]);
		parsedWords.push_back(s.substr(dp1[i], i - dp1[i]));
	}
};

bool WhiteSpaceDetection::isWordPresent(string s)
{
	return (words.find(s) != words.end());
}
bool WhiteSpaceDetection::whitespaceDetectionDP()
{
	int n = s.size();
	dp[0] = 1;
	vector<vector<string>> preSubString;
	for (int i = 0; i < n; i++) {
		vector<string> pre; 
        string sub;
        for (int j = i; j < n; j++) {
            sub += s[j];
			pre.push_back(sub);
        }
		preSubString.push_back(pre);
    }
	for (int i = 1; i < n + 1; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (dp[j] && isWordPresent(preSubString[j][i-j-1]))
			{
				dp[i] = 1;
				dp1[i] = j;
			}
		}
	}
	return dp[n];
}
//n^2*log(number of words);
 class Trie{
	 public:
	Trie *base[26];
	bool isWordEnd;
};

 Trie *getNode(void){
	 Trie *pNode = new Trie;
	pNode->isWordEnd = false;

	for (int i = 0; i < 26; i++){
		pNode->base[i] = NULL;}

	return pNode;
}

void insert(struct Trie *root,const string key){
	struct Trie *node = root;
	for (int i = 0; i < key.length(); i++){
		int index = key[i]-'a';
		if (!node->base[index]){
			node->base[index] = getNode();}

		node = node->base[index];
	}
	node->isWordEnd = true;
}

bool search(struct Trie *root,const string key){
	int length = key.length();
	struct Trie *node = root;
	for (int i = 0; i < length; i++){
		int index = key[i]-'a';

		if (!node->base[index]){
			return false;}

		node = node->base[index];
	}

	return (node != NULL && node->isWordEnd);
}

bool isLastNode(struct Trie *root){
	for (int i = 0; i < 26; i++){
		if (root->base[i]){
			return 0;}
	}
	return 1;
}

void allSuggestions(struct Trie *root,string &word,vector<string> &words){
	if (root->isWordEnd){
		words.push_back(word);
	}
	if (isLastNode(root)){
		word.pop_back();
		return;
	}

	for (int i = 0; i < 26; i++){
			if (root->base[i])	{
			word.push_back(97 + i);
			allSuggestions(root->base[i], word,words);
		}
	}
	word.pop_back();
}


vector<string> printsuggestions(Trie *root,const string word){
	struct Trie *node = root;

	int i;
	int n = word.length();
	vector<string> words;
	for (i = 0; i < n; i++){
		int index =word[i]-'a';
		if (!node->base[index]){
			return words;}
		node = node->base[index];
	}
	bool isWord = (node->isWordEnd == true);
	bool isLast = isLastNode(node);
	
	if (isWord && isLast){
		return words;}
	if (!isLast){
			string prefix = word;
		
		allSuggestions(node, prefix,words);
		return words;
	}
}
//(number of words)*maxword len

int main()
{
	printf("Enter word to be autocorrected and autocompleted\n");
	struct Trie *root = getNode();
	string word;
	cin >> word;
	WhiteSpaceDetection s1(word);
	fstream ff("words2.txt");
	string w1;
	while (ff >> w1)
	{
		insert(root, w1);
		s1.addMatchingWord(w1);
	}
	bool f = 0;
	if (s1.whitespaceDetectionDP())
	{
		s1.printWord(word.size());
	}
	else
	{
		f = 1;
		for (int i = word.size(); i >= 0; i--)
		{
			if (s1.dp[i])
			{
				s1.printWord(i);
				s1.parsedWords.push_back(word.substr(i, word.size() - i));
				break;
			}
		}
	}
	
	if (f)
	{
		const string si = s1.parsedWords[s1.parsedWords.size() - 1];
		vector<string> vec = printsuggestions(root, si);
		if(!vec.size() && s1.parsedWords.size()==1){
			printf("No results found for: ");
			for(int i=0;i<s1.parsedWords.size();i++){
				cout<<s1.parsedWords[i]<<" ";
			}
			return 0;
		}
		if(!vec.size()>0 &&s1.parsedWords.size()>1){
			printf("Did you mean?\n");
			for(int i=0;i<s1.parsedWords.size();i++){
				cout<<s1.parsedWords[i]<<" ";
			}
			return 0;
		}
		cout<<"Suggested Option:\n";
		for(int i=0;i<vec.size();i++){
			cout<<i+1<<" ";
			for(int j=0;j<s1.parsedWords.size()-1;j++){
				cout<<s1.parsedWords[j]<<" ";
			}
			cout<<vec[i]<<"\n";
		}
		int option;
		cin>>option;
		if(option>vec.size()){
			option=vec.size();
		}
		if(option<1){
			option=1;
		}
		option--;
		printf("Selected option is: \n");
		for(int i=0;i<s1.parsedWords.size()-1;i++){
			cout<<s1.parsedWords[i]<<" ";
		}
		cout<<vec[option]<<"\n";
	}
	else{
		cout<<"Did you Mean?\n";
		for (int i = 0; i < s1.parsedWords.size(); i++)
		{
			cout << s1.parsedWords[i] << " ";
		}
	}
	return 0;
}