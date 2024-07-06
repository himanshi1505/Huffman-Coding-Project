#include <bits/stdc++.h>

using namespace std;
const int map_size = 27 ;

class HuffmanNode{
    public :
        int freq ; 
        char data ; 
        HuffmanNode * left ; 
        HuffmanNode * right ; 

    HuffmanNode( int f , char ch ) : freq(f) , data(ch) ,left(nullptr),right(nullptr) {}
};

class Cmp{
    public :
        bool operator()(HuffmanNode * left , HuffmanNode* right){
            if(left->freq == right->freq) return left->data > right->data ;
            return left->freq > right->freq ;
        } 

};

class HuffmanCoding{
    private:
        map<char,int> FrequencyMap ; 
        HuffmanNode * root ;

        char characters[map_size] = {'k', 'j', 'p', 'x', 'K', '.', 'h', 'c', 'e', 'd', 'y', 'C', 'o', 'n', 'a', 'w', ' ', 'g', 't', 'r', 'u', 'l', 'i', 's', 'I', 'f', ','};
        int frequencies[map_size] = {2, 1, 8, 1, 1, 3, 7, 4, 17, 7, 2, 1, 16, 8, 6, 1, 29, 6, 14, 7, 6, 4, 5, 5, 1, 2, 1};

    public : 
        void buildHuffmanTree(){
            priority_queue<HuffmanNode* , vector<HuffmanNode*> , Cmp > minHeap ; 

            for(int itr = 0 ; itr < map_size ; itr++ ){
                minHeap.push( new HuffmanNode(frequencies[itr] , characters[itr] )) ;
            }

            while(minHeap.size() != 1){
                HuffmanNode * left = minHeap.top() ; minHeap.pop() ;
                HuffmanNode * right = minHeap.top() ; minHeap.pop() ;

                int sum = left->freq + right->freq ;
                HuffmanNode * sum_node = new HuffmanNode(sum , '\0') ;

                sum_node->left = left ; 
                sum_node->right = right ;

                minHeap.push(sum_node) ;
            }

            root = minHeap.top() ;
            cout<<root->freq<<endl ;
        }

        void writeOutput(string output ){
            ofstream DecodedFile("output.txt"  , ios::out) ;

            if(!DecodedFile.is_open()){
                cerr<<"Error opening the output file!"<<endl ;
            }
            DecodedFile<<output ;

            cout<<"Filel decoded successfully and out written to output.txt"<<endl ;
        }

        string decode(){
            buildHuffmanTree() ;

            string InputFIleName = "compressed.txt" ;

            ifstream inputFile(InputFIleName , ios::in) ;

            if(!inputFile.is_open()){
                cerr<<"Error opening the input file!"<<endl ;
                return "";
            }

            string encoded_data((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
            string output ;

            HuffmanNode * curr = root ;
            //Traversal inside tree ;
            for( char ch : encoded_data){
                if(ch == '0') curr = curr->left ;
                if(ch == '1') curr = curr->right ;


                if(curr->right == nullptr && curr->left == nullptr){
                    output += curr->data ; 
                    curr = root ;
                    continue ; 
                }
            }

            return output ; 
        }
        

};

int main() {
    
    HuffmanCoding Decompressor ; 
    string decoded_string =Decompressor.decode() ;
    Decompressor.writeOutput(decoded_string) ;

    return 0;
}
