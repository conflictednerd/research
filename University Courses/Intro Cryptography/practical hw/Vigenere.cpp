#ifndef _STAT_H_
#define _STAT_H_


#include <string>
#include <map>
#include <stdexcept>
#include <utility>
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <utility>
#include <ctype.h>
#include <cmath>
#include <iterator>
#include <vector>
#include <fstream>

using namespace std;

using std::map;
using std::string;
using std::pair;

typedef map<string, float> Frequency;


class EnglishStat {
    public:
	EnglishStat(const char* text);
	EnglishStat(string &text);
	~EnglishStat();

	// Get Frequency of order 'order'
	Frequency* GetFrequency(int order) throw(std::out_of_range);

	void ComputeFrequency();

	float GetNorm() const { return _norm; }

    private:
	void Preprocess();

    private:

	Frequency **_stats;
	string _text;
	float _norm;
};

#endif/*_STAT_H_*/

class ToLower{
    public:
	char operator() (char c) { return tolower(c); };
};

class IsWhiteSpace {
    public:
	bool operator() (char c) { return isspace(c); };
};

class IsNotAlpha {
    public:
	bool operator() (char c) { return !isalpha(c); };
};


class AddPair {
    public:
	float operator()(Frequency::value_type &t1, Frequency::value_type &t2){
	    return t1.second + t2.second;
	}
};


//char ToLower(char c) { return toupper(c); }

EnglishStat::EnglishStat (const char *text):_text(text)
{
    Preprocess();
}

EnglishStat::EnglishStat (string &text):_text(text)
{
    Preprocess();
}

EnglishStat::~EnglishStat()
{
    delete _stats[0];
    delete _stats[1];
    delete _stats[2];
    delete[] _stats;
}

void
EnglishStat::ComputeFrequency()
{
    int len=_text.size();

    string s[3];
    float percent= 1.f/(len-2);
    for(int i=0; i<len-2; ++i) {
	for(int j=0; j<3; ++j) {
	    s[j]=_text.substr(i,j+1);

	    if(!_stats[j]->count(s[j])){
		_stats[j]->insert(make_pair(s[j], percent));
	    }else {
		(*_stats[j])[s[j]]=(*_stats[j])[s[j]]+percent;
	    }
	}

    }

    _norm = 0.f;
    for(int j=0; j<3; ++j) {
	Frequency::iterator its=_stats[j]->begin();
	Frequency::iterator ite=_stats[j]->end();
	while(its != ite) {
	    _norm += (its->second * its->second);
	    ++its;
	}

    }
}

void
EnglishStat::Preprocess()
{
    //preprocess the string: strip white spaces and turn into lower case
    string::iterator f=std::remove_if(_text.begin(), _text.end(), IsNotAlpha());
    _text.erase(f, _text.end());

    std::transform(_text.begin(), _text.end(), _text.begin(), ToLower());

    _norm = 0.f;

    _stats = new Frequency*[3];
    _stats[0] = new Frequency;
    _stats[1] = new Frequency;
    _stats[2] = new Frequency;

}

Frequency*
EnglishStat::GetFrequency(int order) throw(std::out_of_range)
{
    if(order<=0 || order>3)
	throw std::out_of_range("Must be in [1,3]");

    return _stats[order-1];
}

typedef struct {
    char* s;
    float freq;
}Reference;

Reference ref_order1[] = {"a", 0.082, "b", 0.015, "c", 0.028, "d", 0.043,
			  "e", 0.127, "f", 0.022, "g", 0.020, "h", 0.061,
			  "i", 0.070, "j", 0.002, "k", 0.008, "l", 0.040,
			  "m", 0.024, "n", 0.067, "o", 0.075, "p", 0.019,
			  "q", 0.001, "r", 0.060, "s", 0.063, "t", 0.091,
			  "u", 0.028, "v", 0.010, "w", 0.023, "x", 0.001,
			  "y", 0.020, "z", 0.001};

Reference ref_order2[] = {"th", 0.0263, "in", 0.0208, "he", 0.0175,
	    	 	  "er", 0.0167, "re", 0.0152, "on", 0.0133,
			  "es", 0.0132, "an", 0.0129, "at", 0.0128,
			  "ti", 0.0126, "nt", 0.0116, "ou", 0.0116,
			  "to", 0.0113, "st", 0.0112, "ha", 0.0105,
			  "or", 0.0105, "et", 0.0103, "en", 0.0101,
			  "te", 0.0101, "is", 0.0098, "it", 0.0097,
			  "ea", 0.0093, "se", 0.0090, "al", 0.0089,
			  "ng", 0.0089, "nd", 0.0081, "ed", 0.0076,
			  "hi", 0.0075, "le", 0.0075, "ar", 0.0074,
			  "si", 0.0073, "me", 0.0073, "so", 0.0071,
			  "of", 0.0070, "ve", 0.0068, "ri", 0.0064,
			  "as", 0.0064, "om", 0.0064, "ra", 0.0061,
			  "no", 0.0061, "ne", 0.0060, "co", 0.0060};


Reference ref_order3[] = {"the", 0.0149, "ing", 0.0077, "tha", 0.0052,
    			  "and", 0.0050, "hat", 0.0047, "ion", 0.0045,
			  "ent", 0.0043, "you", 0.0041, "thi", 0.0038,
			  "for", 0.0038, "ati", 0.0038, "tio", 0.0038,
			  "her", 0.0035, "ere", 0.0035, "eth", 0.0034,
			  "int", 0.0032, "our", 0.0028, "tth", 0.0027,
			  "all", 0.0027, "rea", 0.0026, "ter", 0.0026,
			  "nth", 0.0026, "ome", 0.0025, "hin", 0.0025,
			  "ver", 0.0025, "not", 0.0024, "res", 0.0023,
			  "est", 0.0022, "oul", 0.0022, "ont", 0.0022,
			  "ate", 0.0021, "uld", 0.0021, "ers", 0.0021,
			  "tin", 0.0021, "oth", 0.0020, "pro", 0.0020};

/**
*
* @fn float EnglishLike(string &text)
* @brief Compute the likelihood of text being plain English
* @param text Input text.
*
* @return The likelihood
*
*/
float EnglishLike(string &text)
{
    float like = 0.f;
    float norm = 0.f;

    /* Build reference statistics */
    Frequency *ref1 = new Frequency;
    int size = sizeof(ref_order1)/sizeof(Reference);
    for(int i=0; i<size; ++i){
	ref1->insert(std::make_pair(ref_order1[i].s, ref_order1[i].freq));
	norm += ref_order1[i].freq * ref_order1[i].freq;
    }
    Frequency *ref2 = new Frequency;
    size = sizeof(ref_order2)/sizeof(Reference);
    for(int i=0; i<size; ++i){
	ref2->insert(std::make_pair(ref_order2[i].s, ref_order2[i].freq));
	norm += ref_order2[i].freq * ref_order2[i].freq;
    }
    Frequency *ref3 = new Frequency;
    size = sizeof(ref_order3)/sizeof(Reference);
    for(int i=0; i<size; ++i){
	ref3->insert(std::make_pair(ref_order3[i].s, ref_order3[i].freq));
	norm += ref_order3[i].freq * ref_order3[i].freq;
    }

    /* Get the statistics of the text */
    EnglishStat engs(text);
    engs.ComputeFrequency();
    Frequency *s1 = engs.GetFrequency(1);
    Frequency::iterator its=ref1->begin(), ite=ref1->end();
    while(its != ite) {
	if(s1->count(its->first) != 0) {
	    like += ((*s1)[its->first]*its->second);
	    //cout << its->first << " " << its->second << " " <<(*s1)[its->first]<<endl;
	}
	++its;
    }

    s1 = engs.GetFrequency(2);
    its=ref2->begin(); ite=ref2->end();
    while(its != ite) {
	if(s1->count(its->first) != 0) {
	    like += ((*s1)[its->first]*its->second);
	    //cout << its->first << " " << its->second << " " <<(*s1)[its->first]<<endl;
	}
	++its;
    }

    s1 = engs.GetFrequency(3);
    its=ref2->begin(); ite=ref2->end();
    while(its != ite) {
	if(s1->count(its->first) != 0) {
	    like += ((*s1)[its->first]*its->second);
	    //cout << its->first << " " << its->second << " " <<(*s1)[its->first]<<endl;
	}
	++its;
    }

    like = like/(sqrt(norm)*sqrt(engs.GetNorm()));

    return like;
}

//str must be all lower case letters
vector<int> countLetters(string str){
    vector<int> v;
    v.resize(26);
    for(char c: str){
        v[c-'a']++;
    }
    return v;
}

vector<double> freq;

void init(){
    freq.push_back(8.167);
    freq.push_back(1.492);
    freq.push_back(2.202);
    freq.push_back(4.253);
    freq.push_back(12.702);
    freq.push_back(2.228);
    freq.push_back(2.015);
    freq.push_back(6.094);
    freq.push_back(6.966);
    freq.push_back(0.153);
    freq.push_back(1.292);
    freq.push_back(4.025);
    freq.push_back(2.406);
    freq.push_back(6.749);
    freq.push_back(7.507);
    freq.push_back(1.929);
    freq.push_back(0.095);
    freq.push_back(5.987);
    freq.push_back(6.327);
    freq.push_back(9.356);
    freq.push_back(2.758);
    freq.push_back(0.978);
    freq.push_back(2.560);
    freq.push_back(0.15);
    freq.push_back(1.994);
    freq.push_back(0.077);
    for(int i = 0; i<26; i++){
        freq[i] /= 100;
    }
}

int main(){
    init();
    ofstream os;
    os.open("results3.txt");
    string str = "ALLHESHCQAEXSMTGRPPAQXSUSFEEUOFATXLJMDQUHEYPLAZPAUL XSQTJYPYESRTZGGJTFSUVPQDOISALVXSQSWXCGTZWEABWWPXFWZ TPEFXETALEWXMWRLDEUVPMTWHPCUSPTTANILPRWEXFHSXZZEVEJ ANLLPDEVLTXLKSQSEGVRUALLPEOFWZRFGVXQRKPLHEKEYPTZIDA NKSQROJQPDSDEGQOORPDSOMWXBWEMXELSDUTVSHZTGKPFHWVLFT ZIEMBDIZRBJSETEJLZAD";
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    for(int i = 0; i<str.length(); i++) str[i] = tolower(str[i]);
    auto mono = countLetters(str);
    double f2 = 0;
    for(int i: mono){
        f2 += (double(i)/str.length())*(double(i)/str.length());
    }
    cout<<"For english texts, sum(freq_i^2) is roughly 0.065. But for this text, it is "<<f2<< ". So this cannot be a substitution cipher" <<endl;
    for(int d = 2; d<10; d++){
        string keyString = "";
        //each 'part' is a cesar cipher.
        vector<string> parts;
        parts.resize(d);
        for(int i = 0; i<str.length();i++){
            parts[i%d]+=str[i];
        }
        for(string &s: parts){
            auto v = countLetters(s);
            double xi2 = 1000;
            int key;
            for(int i = 0; i<26; i++){
                double temp = 0;
                for(int j = 0;j <26; j++){
                    temp += (v[(i+j)%26] - str.length()*freq[j])*(v[(i+j)%26] - str.length()*freq[j])/(str.length()*freq[j]);
                }
                if(temp<xi2){
                    xi2 = temp;
                    key = i;
                }
            }
            for(int i = 0; i<s.length(); i++){
                s[i]  = (s[i]-'a' - key+26)%26+'a';
            }
            keyString += char(key+'a');
        }
        cout<<"Best key of length " << d << " is \"" << keyString << "\"." <<endl;
        string plainText = "";
        for(int i = 0; i<str.length(); i++){
            plainText += parts[i%d][i/d];
        }
        cout<<plainText<<endl<<endl;
        os << plainText <<endl<<endl;
    }
    os.close();
}
