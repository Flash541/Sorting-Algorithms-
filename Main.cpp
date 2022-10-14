#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include<thread>
#include <chrono>
#include <functional>
#include<ctime>
#include<ratio>
using namespace std;


const int t = 256;
const int w = 1283;
int m,n,k(0);
bool g(0);
#define d 10
#define NO_OF_CHARS 256

//FSA
int getNextState(char *pat, int M, int state, int x)
{
    // If the character c is same as next character
    // in pattern,then simply increment state
    if (state < M && x == pat[state])
        return state+1;

    // ns stores the result which is next state
    int ns, i;

    // ns finally contains the longest prefix
    // which is also suffix in "pat[0..state-1]c"

    // Start from the largest possible value
    // and stop when you find a prefix which
    // is also suffix
    for (ns = state; ns > 0; ns--)
    {
        if (pat[ns-1] == x)
        {
            for (i = 0; i < ns-1; i++)
                if (pat[i] != pat[state-ns+1+i])
                    break;
            if (i == ns-1)
                return ns;
        }
    }

    return 0;
}

/* This function builds the TF table which represents4
    Finite Automata for a given pattern */
void computeTF(char *pat, int M, int TF[][NO_OF_CHARS])
{
    int state, x;
    for (state = 0; state <= M; ++state)
        for (x = 0; x < NO_OF_CHARS; ++x)
            TF[state][x] = getNextState(pat, M, state, x);
}

/* Prints all occurrences of pat in txt */
void search(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);

    int TF[M+1][NO_OF_CHARS];

    computeTF(pat, M, TF);

    // Process txt over FA.
    int i, state=0;
    for (i = 0; i < N; i++)
    {
        state = TF[state][txt[i]];
        if (state == M)
            ;;//printf ("\n%d\n\t",i-M+1);
    }
}



void SUNDAY(char *text, char *patt)
{

size_t temp[256];
size_t *shift = temp;
size_t i, patt_size = strlen(patt),text_size=strlen(text);
for(i=0;i<256;i++){


    *(shift+i)=patt_size+1;
}

for (i=0;i<patt_size;i++){


    *(shift+(unsigned char)(*(patt+i))) = patt_size-i;
    }

size_t limit = text_size- patt_size +1;
for (i = 0; i<limit; i+=shift[text[i+patt_size]]){

    if(text[i]==*patt){

        char *match_text = text +i+1;
        size_t match_size =1;
        do{

            if(match_size==patt_size){

               ;; //cout<<i<<endl;
            }
        }
        while((*match_text++)==patt[match_size++]);
    }
    //cout<<endl;
}
}


//Robin Karp
void Robinsearch(char pat[], char txt[], int q)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and first
    // window of text
    for (i = 0; i < M; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++)
    {

        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters one by one
        if ( p == t )
        {
            bool flag = true;
            /* Check for characters one by one */
            for (j = 0; j < M; j++)
            {
                if (txt[i+j] != pat[j])
                {
                  flag = false;
                  break;
                }
                  if(flag)
                   ;;//cout<<i<<" ";

            }

            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]

            if (j == M)
                ;;//cout<<"Pattern found at index "<< i<<endl;
        }

        // Calculate hash value for next window of text: Remove
        // leading digit, add trailing digit
        if ( i < N-M )
        {
            t = (d*(t - txt[i]*h) + txt[i+M])%q;

            // We might get negative value of t, converting it
            // to positive
            if (t < 0)
            t = (t + q);
        }
    }
}
void Rabin_Karp_Algorithm(string text,string pattern){

    //Length of text string.
    int tlen = text.length();

    //Length of pattern string.
    int plen = pattern.length();

    int flag;
    int c=1,i=0;

    //Calculate hash_p(hash value of pattern) and hash_0
    int hash_p=0,hash=0;
    while(i<plen){
        hash_p=(hash_p*t + pattern[i])%w;
        hash=(hash*t + text[i])%w;
        i++;
    }

     //Calculate (t^(plen-1))%w
    for(int i=1;i<=plen-1;i++)
        c=(c*t)%w;

    i=0;
    while(i<=tlen-plen){
       if(hash_p==hash){
            flag=1;
            for(int j=0;j<plen;j++){
                if(pattern[j]==text[i+j]){
                    continue;
                }
                else{
                    flag = 0;
                    break;
                }
           }
            if(flag==1){
                    ;;
                    //cout<<i<<" ";
                    }
       }


       //Calculate hash value of next window
       //hash_i+1 = t * {hash_i - text[i] * t^(plen-1)} + text[i+plen]
       if(i<tlen-plen){
           hash=((t*(hash-text[i]*c))+text[i+plen])%w;
            if(hash<0){
                hash = hash + w;
            }
       }
       i++;
    }
}





void Bsearch(char* pat, char* txt)
{
    int M = strlen(pat);
    int N = strlen(txt);

    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++) {
        int j;

        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++)
            if (txt[i + j] != pat[j])
                break;

        if (j == M) // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
            //cout << "\t\t"<< i << endl;
            ;;
    }
}

void BruteForce(string text,string pattern)
{
  //length of text string stored in n
  int n = text.length();
  //length of pattern string stored in m
  int m = pattern.length();
  int i,j;
  //Loop for text
  for (i = 0; i <= n-m; i++)
  {
    //Loop for pattern
    for (j = 0; j < m; j++)
    {
      if (text[i+j]!= pattern[j])
        break;
    }
   //if j==pattern length means pattern found
    if (j == m)
      ;;//cout<<"Found at index "<<i<<endl;
  }
}



//KMP improved version

void lps_func(string txt, vector<int>&Lps){
    Lps[0] = 0;
    int len = 0;
    int i=1;
    while (i<txt.length()){
        if(txt[i]==txt[len]){
            len++;
            Lps[i] = len;
            i++;
            continue;
        }
        else{
            if(len==0){
                Lps[i] = 0;
                i++;
                continue;
            }
            else{
                len = Lps[len-1];
                continue;
            }
        }
    }
}

void KMP(string pattern,string text){
    int n = text.length();
    int m = pattern.length();
    vector<int>Lps(m);

    lps_func(pattern,Lps); // This function constructs the Lps array.

    int i=0,j=0;
    while(i<n){
        if(pattern[j]==text[i]){i++;j++;} // If there is a match continue.
        if (j == m) {
            //cout<<i - m <<' ';    // if j==m it is confirmed that we have found the pattern and we output the index
                                  // and update j as Lps of last matched character.
            j = Lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i]) {  // If there is a mismatch
            if (j == 0)          // if j becomes 0 then simply increment the index i
                i++;
            else
                j = Lps[j - 1];  //Update j as Lps of last matched character
        }
    }
}

// Prints occurrences of txt[] in pat[]
void KMPSearch(char* pat, char* txt)
{
	int M = strlen(pat);
	int N = strlen(txt);

	// create lps[] that will hold the longest prefix suffix
	// values for pattern
	int lps[M];

	// Preprocess the pattern (calculate lps[] array)
	computeLPSArray(pat, M, lps);

	int i = 0; // index for txt[]
	int j = 0; // index for pat[]
	while (i < N) {
		if (pat[j] == txt[i]) {
			j++;
			i++;
		}

		if (j == M) {
			//printf(" %d\n ", i - j);
			j = lps[j - 1];
		}

		// mismatch after j matches
		else if (i < N && pat[j] != txt[i]) {
			// Do not match lps[0..lps[j-1]] characters,
			// they will match anyway
			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}
}

// Fills lps[] for given patttern pat[0..M-1]
void computeLPSArray(char* pat, int M, int* lps)
{
	// length of the previous longest prefix suffix
	int len = 0;

	lps[0] = 0; // lps[0] is always 0

	// the loop calculates lps[i] for i = 1 to M-1
	int i = 1;
	while (i < M) {
		if (pat[i] == pat[len]) {
			len++;
			lps[i] = len;
			i++;
		}
		else // (pat[i] != pat[len])
		{
			// AAACAAAA and i = 7. The idea is similar
			// to search step.
			if (len != 0) {
				len = lps[len - 1];

				// Also, note that we do not increment
				// i here
			}
			else // if (len == 0)
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}
*/





int main() {


    FILE* file;

    file = fopen("book.txt", "r");

    string current = "";

    string book = "";
    string Text = "AABBCCDDAAABBBCCCDDDAAAABBBBCCCCDDDDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDAABBCCDDAABBCCDDAAAAABBBBBCCCCCDDDDDAAAAAAABBBBBBBCCCCCCDDDDDDABCDABCDABCDABCDABCDABCDABCDABCDABCDAAAAAAAABBBBBBBBCCCCCCCDDDDDABCDABCDABCDABCDABCDABCDABCDAAAAABCDABCDABCDABCDAAAAAABBBBCCCCCDDDDDABCDABCDABCDABCDABCDABCDABCDABCDAAAAAABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDAAAAABBBBBABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDABCDCCCCCDDDDAAAAABBBBBCCCCCDDDDDAAAAABBBBBCCCCCDDDDDAAAAABBBBBCCCCCDDDDDAAAAABBBBBCCCCCDDDDD";
    string chappter = "abc";
    string chap2 = "tion";
    string chap3="affid";
    string chap4="affili";
    string chap5 = "af";
    string chap6 = "ac";
    string chap7 = "affect";
    string chap8 ="academical" ;//10 bytes
    string chap9 ="bibliographic";//13 bytes
    string chap10 = "ABCDABCDABCDABCDABCD"; //20 Bytes
    // assigning value to string s

    int n = chap5.length();

    // declaring character array
    char char_pattern[n + 1];


    // copying the contents of the
    // string to char array
    strcpy(char_pattern, chap5.c_str());



    char c;

    do {
        c = fgetc(file);
        if (c == EOF) break;
        book = book + c;
    } while (c != EOF);

int m = book.length();
char target_text[m+1];
strcpy(target_text,book.c_str());
    //Sunday(chappter,book);

printf("Length of Pattern 1:%d\n",chappter.length());
printf("Length of Pattern 2: %d\n ",chap2.length());
printf("Length of Pattern 3: %d\n",chap3.length());
printf("Length of Pattern 4: %d\n",chap4.length());
printf("Length of Pattern 5: %d\n",chap5.length());
printf("Length of Pattern 6: %d\n",chap6.length());
printf("Length of Pattern 7: %d\n",chap7.length());
printf("Length of TEXT: %d\n",Text.length());
printf("Length of Pattern 10: %d\n",chap10.length());
printf("Length of Book.txt file: %d\n",book.length());


for(int i = 1; i<=150; i++){ //Loop used for localization of the CHRONO time measurement variables
high_resolution_clock::time_point start =std::chrono::high_resolution_clock::now();

SUNDAY(target_text,char_pattern);
high_resolution_clock:: time_point finish = std::chrono::high_resolution_clock::now();
cout <<chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << "ns\n";
}
    return 0;
}




