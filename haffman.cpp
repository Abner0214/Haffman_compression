#include<bits/stdc++.h>

using namespace std;

// Huffman tree node
struct HuffmanNode{
    unsigned char data;
    int freq;

    HuffmanNode *left, *right;

    HuffmanNode(unsigned char data, int freq){
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
        this->smallestChild = this;
    }
    HuffmanNode(HuffmanNode* smallestChild, unsigned char data, int freq){
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
        this->smallestChild = smallestChild;
    }
};
// For comparison of two nodes's frequency
bool cmpFrq(HuffmanNode *l, HuffmanNode *r){
    return (l->freq > r->freq);
}
// For comparison of two nodes's alphabetical order
bool cmpAlpha(HuffmanNode *l, HuffmanNode *r){
    return (l->smallestChild->data < r->smallestChild->data);
}
// sort by string's first letter
bool sortLetter(string a, string b){
    return (a < b);
}
// Print Huffman Codes
void printCodeTable(struct HuffmanNode* root, string str, vector<string>& CodeTable){
    // If root is Null then return.
    if (!root) return;
    // If the node's smallestChild is itself that means it's not an internal node and print the string.
    if (root->smallestChild == root){
        //cout << root->data << ": " << str << endl;
        string oneCode;
        oneCode += char(root->data);
        oneCode += " =";
        oneCode += str;
        CodeTable.push_back(oneCode);
    }
    printCodeTable(root->left, str + "0", CodeTable);
    printCodeTable(root->right, str + "1", CodeTable);
}

// Build Huffman Tree
void HuffmanCodes(unsigned char data[], int freq[], int size, vector<string>& CodeTable){

    struct HuffmanNode *left,*right,*top;

    // create a min heap.
    vector<HuffmanNode*> minHeap;
    // For each character create a leaf node and insert each leaf node in the heap.
    for (int i = 0;  i < size;  i++){    
        minHeap.push_back(new HuffmanNode(data[i], freq[i]));
    }
    sort(minHeap.begin(), minHeap.end(), cmpFrq);
    // Iterate while size of min heap doesn't become 1
    while (minHeap.size() > 1){
        
        // Extract two nodes from the heap.
        struct HuffmanNode *tail;
        vector<HuffmanNode*> sameFrq1;  // storage all the same frequency nodes from tail
        tail = minHeap.back();
        sameFrq1.push_back(tail);
        minHeap.pop_back();
        // last one has same frequency
        while (minHeap.size()  &&  minHeap.back()->freq == tail->freq){  // minHeap is not empty  &&  pop all the same frequency nodes
            sameFrq1.push_back(minHeap.back());
            minHeap.pop_back();
        }
        if (sameFrq1.size() > 1){  // there are some the same frequency nodes
            sort(sameFrq1.begin(), sameFrq1.end(), cmpAlpha);
            left = sameFrq1[0];
            right = sameFrq1[1];
            sameFrq1.erase(sameFrq1.begin());  // delete two smallest alphabetical order nodes
            sameFrq1.erase(sameFrq1.begin());
            for (int i = 0;  i < sameFrq1.size();  i++){  // push other nodes back to the minHeap
                minHeap.push_back(sameFrq1[i]);
            }
        }
        else if (minHeap.size() >= 2 && minHeap.back()->freq == minHeap[minHeap.size()-2]->freq){  // second last has the same frequency nodes
            left = tail;  // the smallest frequency node
            vector<HuffmanNode*> sameFrq2;  // storage all the same frequency nodes from tail
            tail = minHeap.back();
            sameFrq2.push_back(tail);
            minHeap.pop_back();
            // second last one has same frequency
            while (minHeap.size()  &&  minHeap.back()->freq == tail->freq){  // minHeap is not empty  &&  pop all the same frequency nodes
                sameFrq2.push_back(minHeap.back());
                minHeap.pop_back();
            }
            if (sameFrq2.size() > 1){  // there are some the same frequency nodes
                sort(sameFrq2.begin(), sameFrq2.end(), cmpAlpha);
                right = sameFrq2[0];
                sameFrq2.erase(sameFrq2.begin());  // delete two smallest alphabetical order nodes
                for (int i = 0;  i < sameFrq2.size();  i++){  // push other nodes back to the minHeap
                    minHeap.push_back(sameFrq2[i]);
                }
            }
        }
        else {  // last and second last has no the same frequency node push tail back
            minHeap.push_back(sameFrq1[0]);
            left = minHeap.back();  // the least two heapNode's frequencies are different
            minHeap.pop_back();
            right = minHeap.back();
            minHeap.pop_back();
        }
        if (left->smallestChild->data > right->smallestChild->data){  // check if leftNode is smaller in alphabetical order
            struct HuffmanNode *temp = left;
            left = right;
            right = temp;
        }
        // cout << "===================" << endl;///////////////////////
        // cout << "left " << left->data << " " << left->smallestChild->data << " " << left->freq << endl;///////////////////
        // cout << "right " << right->data << " " << right->smallestChild->data << " " << right->freq << endl;////////////////
        
        // Create a new internal node having frequency equal to the sum of 
        // two extracted nodes.Assign '$' to this node and make the two extracted 
        // node as left and right children of this new node.Add this node to the 
        // heap.
        top = new HuffmanNode(left->smallestChild, '$', left->freq+right->freq);
        top->left = left;
        top->right = right;
        // cout << "merge :" << top->data << " " << top->smallestChild->data << " " << top->freq << endl;///////////////////
        // arrange the new heapNode
        for (int i = minHeap.size()-1;  i >= 0;  i--){
            if (minHeap[i]->freq >= top->freq){
                minHeap.insert(minHeap.begin()+i+1, top);
                break;
            }
            else if (i == 0  &&  minHeap[i]->freq < top->freq){  // no frequency is bigger but it has gone through all the minheap
                minHeap.insert(minHeap.begin(), top);
            }
        }
        if (minHeap.size() == 0){  // the last heapNode (root)
            minHeap.insert(minHeap.begin(), top);
        }
    }
    // Calling function to print the codes.
    printCodeTable(minHeap[0], " ", CodeTable);
}
void bitToByte(vector<unsigned char>& res, vector<bool> bits){
    long long int byteNumber = bits.size() / 8;
    int extraBitNumber = bits.size() % 8;
    
    // cout << "Haffman code 1: " << endl;////////////////////////////
    // for (auto bit : bits){  // compression haffman code
    //     cout << bit;///////////////////////////
    // }
    // cout << endl;/////////////////////////////////
    for (int i = 0;  i < byteNumber;  i++){
        unsigned char byte = 0;
        for (int j = 7;  j >= 0;  j--){  // 1 byte 8 bits
            if (bits[i*8 + j])  // boolen bit == true assign the bit to 1
                byte |= 1 << 7-j;
            //cout << (int)byte << endl << endl;//////////////////////////
            //cout << bits[i*8 + j];/////////////////////////////////
        }
        res.push_back(byte);
        //cout << endl;///////////////////////////////////////////
    }
    if (extraBitNumber){  // there are some eaxtra bits (less than 8)
        bool extra[8] = {0, 0, 0, 0, 0, 0, 0 ,0};
        for (int i = 0;  i < extraBitNumber;  i++){
            extra[8-extraBitNumber+i] = bits[byteNumber*8 + i];
        }
        unsigned char byte = 0;
        for (int i = 7;  i >= 0;  i--){
            if (extra[i])  // boolen bit == true assign the bit to 1
                byte |= 1 << 7-i;
            //cout << (int)byte << endl << endl;//////////////////////////
            //cout << bits[byteNumber*8 + i];/////////////////////////////////
        }
        res.push_back(byte);
    }
    // ofstream ooooo("whatTheFuck.txt");/////////////////////////////////////////////
    // for (auto r : res){  // output compressed data
    //     ooooo << r;/////////////////////////////////////////////
    // }
    // ooooo.close();
    // for (int r : res){
    //     cout << r << " ";/////////////////////////////////
    // }
    // cout << endl;////////////////////////////////
}
void byteToBit(vector<unsigned char>& res, vector<unsigned char> byteStream, vector<string> codeTable, int usefulBitNumber){
    vector<bool> bitStream;
    //ofstream ooooo("whatTheFuck.txt");////////////////////////////////////////
    for (int i = 0;  i < byteStream.size();  i++){  // transform each bit
        //ooooo << byteStream[i];////////////////////////////////////////
        bool Onebit[8];
        for (int j = 7;  j >= 0;  --j){
            Onebit[j] = (byteStream[i] & (1 << 7-j)) != 0;
        }
        for (int k = 0;  k < 8;  k++){
            bitStream.push_back(Onebit[k]);
        }
    }
    //ooooo.close();//////////////////////////////
    //cout << endl;//////////////////////////////
    if (usefulBitNumber){  // there are some extra bits
        vector<bool> temp;
        for (int i = 0;  i < usefulBitNumber;  i++){  // get the useful bit
            temp.push_back(bitStream.back());
            bitStream.pop_back();
        }
        for (int i = usefulBitNumber;  i < 8;  i++){  // pop the other useless bit
            bitStream.pop_back();
        }
        for (int i = 0;  i < usefulBitNumber;  i++){  // push the useful bit back
            bitStream.push_back(temp.back());
            temp.pop_back();
        }
    }
    // cout << endl << bitStream.size() << endl;////////////////////////////////
    // cout << "Haffman code 2: " << endl;////////////////////////////
    // for (auto bit : bitStream){  // compression haffman code
    //     cout << bit;///////////////////////////
    // }
    // cout << endl;////////////////////////////////
    // int count = 0;////////////////////////////////////////
    for (int currChar = 0;  currChar < codeTable.size();  currChar++){  // find the match code by the code table
        string decode;  // haffman code
        for (int i = 4;  i < codeTable[currChar].size();  i++){   //  line[4:] are haffman code
            decode += codeTable[currChar][i];
        }
        int haffmanLen = codeTable[currChar].size() - 4;
        bool match[haffmanLen];  // transform char haffman code to bool
        for (int i = 0;  i < haffmanLen;  i++){  // build a bool array to compare
            if (decode[i] == '1') match[i] = true;  // this bit is 1 (true) or 0 (false)
            else match[i] = false;
        }
        // for (int i = 0;  i < haffmanLen;  i++){
        //     cout << match[i];/////////////////////////////
        // }
        // cout << endl;////////////////////////////////
        
        bool doneDecoding = true;
        for (int i = 0; i < haffmanLen;  i++){
            if (bitStream[i] != match[i]){
                doneDecoding = false;
                break;
            }
        }
        if (!doneDecoding){
            // cout << "no this one" << endl;////////////////////////////
            continue;  // current haffman code does not match find the new haffman code
        }
        else {  // done decoding
            for (int i = 0;  i < haffmanLen;  i++){
                bitStream.erase(bitStream.begin());
            }
            res.push_back(codeTable[currChar][0]);  // decoding complete
            // cout << codeTable[currChar][0];////////////////////////
            // cout << "======" << count << "=======>" << codeTable[currChar][0] << endl;////////////////////////
            if (bitStream.size() == 0) break;  // complete transform
            currChar = -1;  // restart to find haffman code
            continue;  // deal with next bits decoding
        }
    }
}
int main(int argc, char* argv[]){  // the entry point of a program

    
    string mode = argv[1];  // mode (compression or uncompression)
    string infile = argv[3];  // input file's name
    string infileExtension;
    for (int i = 0;  i < infile.size();  i++){
        if (infile[i] == '.'){
            for (int j = i;  j < infile.size();  j++){
                infileExtension += infile[j];
            }
            break;
        }
    }
    string outfile = argv[5];  // output file's name
    if (mode == "-c"){  // compression
        ifstream inputFile(infile, ios::in | ios::binary);  // open infile
        vector<long long int> appear;  // record ASII code appeared frequency
        appear.assign(256, 0);
        unsigned char c;
        while (inputFile >> c){  // count each code appeared times
            appear[c]++;
        }
        inputFile.close();
        vector<unsigned char> data;  // record appeared code
        for (int i = 0;  i < 256;  i++){  // form ASCII 0-255
            data.push_back((unsigned char)(i));
        }
        for (int i = 0;  i < appear.size();  i++){  // delete appeared frequency == 0
            if (appear[i] == 0){
                appear.erase(appear.begin() + i);
                data.erase(data.begin() + i);
                i--;
            }
        }
        int leftCount = appear.size();  // left code's number
        unsigned char arr[leftCount];
        int freq[leftCount];
        for (int i = 0;  i < leftCount;  i++){
            arr[i] = data[i];
            freq[i] = appear[i];
            // cout << arr[i] << " " << freq[i] << endl;///////////////////////////////////
        }
        vector<string> CodeTable;
        HuffmanCodes(arr, freq, leftCount, CodeTable);
        sort(CodeTable.begin(), CodeTable.end(), sortLetter);
        outfile += ".haffman";  // file extension
        ofstream outputFile(outfile);
        if (outputFile.is_open()){  // open outfile successfully
            ifstream getFile(infile, ios::in | ios::binary);  // open infile
            unsigned char match;
            vector<bool> compress;  // the data output to outfile after compressed
            long long int compressByte = 0;  // byte numbers after compressed
            long long int orgByte = 0;  // original byte numbers
            double compressRate;  // compression rate
            while (getFile >> match){  // count each code appeared times
                for (auto data : CodeTable){  // look for match char
                    if (match == data[0]){  // find the match char
                        vector<bool> currBits;
                        for (int i = data.size()-1;  data[i] != ' ';  i--){
                            if (data[i] == '1') currBits.push_back(true);
                            else currBits.push_back(false);
                        }
                        int pushTimes = currBits.size();
                        for (int i = 0;  i < pushTimes-1;  i++){
                            compress.push_back(currBits.back());
                            currBits.pop_back();
                        }
                        compress.push_back(currBits.back());
                    }
                }
                orgByte += 1;  // 1 char 1 byte
            }
            getFile.close();
            // output to the outfile
            // header
            // 1.haffuman code table, 2.original byte numbers, 
            // 3.byte numbers after compressed, 4.compresstion rate
            // compressed data
            long long int compressedByteNumber = 0;
            int compressedBitNumber = 0;
            compressedByteNumber = compress.size() / 8;
            compressedBitNumber = compress.size() % 8;
            if (compressedBitNumber) compressedByteNumber += 1;  // there are some exta bits can make a byte
            // for (auto data : CodeTable){  // the byte number of haffman table 
            //     compressedByteNumber += (data.size() + 2);
            // }
            // compressedByteNumber += (11 + infileExtension.size() + 2);  // the byte number of record the file's type
            // compressedByteNumber += (10 +  + 9);
            compressRate = double(compressedByteNumber) / double(orgByte);
            for (auto data : CodeTable){  // output Haffman code table
                outputFile << data << endl;
                cout << data << endl;
            }
            outputFile << "File type: " << infileExtension << endl;  // record the file's type
            outputFile << "Original: " << orgByte << " byte(s)" << endl;  // output original byte numbers
            int currFileSize = outputFile.tellp();
            compressedByteNumber += currFileSize;  // the byte number of above data
            compressedByteNumber += (18 + 11 + 3);  // the byte number of Compression
            compressedByteNumber += (13 + 9 + 51);  // the byte number of Compression rate
            outputFile << "Compression: " << compressedByteNumber << " byte(s)."  << " The number of significant bits in the last byte: " << compressedBitNumber << endl;  // output byte and bit number after compressed and extra bit number after compressed
            outputFile << "Compression rate: " << fixed << setprecision(10) << compressRate * 100 << " %" << endl;  // output compresstion rate
            vector<unsigned char> outputByte;
            bitToByte(outputByte, compress);  // transform boolen 8 bits to 1 btye
            //ofstream ooooo("whatTheFuck.txt");/////////////////////////////////////////////
            for (auto byte : outputByte){  // output compressed data
                outputFile << byte;
                //ooooo << byte;/////////////////////////////////////////////
            }
            //ooooo.close();
            // for (auto data : CodeTable){  // print Haffman code table
            //     cout << data << endl;
            // }
            outputFile.close();
            cout << "File type: " << infileExtension << endl;
            cout << "Original: " << orgByte << " byte(s)" << endl;  // print original byte numbers
            cout << "Compression: " << compressedByteNumber << " byte(s)."  << " The number of significant bits in the last byte: " << compressedBitNumber << endl;  // print byte numbers after compressed
            cout << "Compression rate: " << fixed << setprecision(10) << compressRate * 100 << " %" << endl;  // print compresstion rate

        }
        else cout << "Unable to open " << outfile << endl;
    }
    else if (mode == "-u"){  // uncompression
        ifstream inputFile(infile, ios::in);  // open infile
        string line;
        vector<string> codeTable;
        while (getline(inputFile, line)){
            codeTable.push_back(line);
            //cout << line << endl;//////////////////////////////////////
            if (line[line.size()-1] == '%'){  // find the header's tail
                break;
            }
        }
        codeTable.pop_back();  // pop Compression rate
        int usefulBitNumber;
        usefulBitNumber = codeTable.back()[codeTable.back().size()-1];
        usefulBitNumber -= 48;
        codeTable.pop_back();  // pop Compression
        codeTable.pop_back();  // pop Original
        string outfileExtension;
        for (int i = 0;  i < codeTable.back().size();  i++){  // spilt the original file extension
            if (codeTable.back()[i] == '.'){
                for (int j = i;  j < codeTable.back().size();  j++){
                    outfileExtension += codeTable.back()[j];
                }
                break;
            }
        }
        codeTable.pop_back();  // pop File type
        vector<unsigned char> byteStream;
        char Onebyte;
        while (inputFile.get(Onebyte)){
            // ooooo << Onebyte;///////////////////////////////////////
            byteStream.push_back(Onebyte);
        }
        // ofstream binGood("_THIS_FILE_IS_USED_TO_DECODE_.bin", ios::out | ios::binary);
        // // ofstream ooooo("whatTheFuck.txt");///////////////////////////
        // while (inputFile.get(Onebyte)){
        //     // ooooo << Onebyte;///////////////////////////////////////
        //     binGood << (unsigned char)Onebyte;
        // }
        // binGood.close();
        // ifstream decodeBin("_THIS_FILE_IS_USED_TO_DECODE_.bin", ios::in | ios::binary);
        // while (decodeBin.get(Onebyte)){
        //     // ooooo << Onebyte;///////////////////////////////////////
        //     byteStream.push_back(Onebyte);
        // }
        // decodeBin.close();
        // ooooo.close();/////////////////////////////////
        vector<unsigned char> uncompress;
        byteToBit(uncompress, byteStream, codeTable, usefulBitNumber);
        outfile += outfileExtension;
        ofstream outputFile(outfile, ios_base::binary);
        // cout << "*_*" << endl;////////////////////////////////////////
        for (auto data : uncompress){
            outputFile << data;
        }
        outputFile.close();
        cout << "Uncompression completed!" << endl;///////////////////////
    }
    else {  // wrong command
        cout << "[ERROR]: invalid command!" << endl;
    }
    return 0;
}