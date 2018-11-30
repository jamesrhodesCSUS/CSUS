#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <tuple>
#include <functional>
#include <algorithm>

std::ofstream outfile("output.txt");

//Returns the position in the vector of item search
int Find(std::vector<int> &frames, int search){
    for(int i = 0; i < frames.size(); i++)
        if(search == frames[i])
            return i;
        
    return -1;
}

//Looks into the FUTURE to see what frame to replace
int FindReplacementOpt(const std::vector<int> &input, const std::vector<int> &frames, int starting){
    int max = 0, distance, pos = 0;
    bool unused = false;
    
    for(int i = 0; i < frames.size(); i++){
        distance = 0;
        unused = false;
        for(int j = starting; j < input.size(); j++){
            if(frames[i] != input[j])
                ++distance;
            else{
                unused = true;
                if(distance > max){
                    max = distance;
                    pos = i;
                }
                break;
            }
        }
        if (unused == false)
            return i;
    }
    return pos;
}

//Looks into the past to find the last recently used page for replacement
int FindReplacementLRU(const std::vector<int> &input, const std::vector<int> &frames, int starting){
    int max = 0, distance, pos = 0;
    bool unused = false;
    
    for(int i = 0; i < frames.size(); i++){
        distance = 0;
        unused = false;
        for(int j = starting; j >= 0; j--){
            if(frames[i] != input[j])
                ++distance;
            else{
                unused = true;
                if(distance > max){
                    max = distance;
                    pos = i;
                }
                break;
            }
        }
        if (unused == false)
            return i;
    }
    return pos;
}

//Tuple info
//0 = pages, 1 = frames, 2 = requests
//Replaces pages in First in First Our order
void FIFO(const std::vector<int> &input, const std::tuple<int, int, int> &info){
    std::vector<int> frames;
    int pos = 1;
    int maxf = std::get<1>(info);
    int pagefaults = 1;
    int findpos;
    
    for(int i = 0; i < maxf; i++)
        frames.push_back(-1);
    
    outfile<<"FIFO"<<std::endl;
    
    frames[0] = input[0];
    outfile<<"Page " << input[0] << " loaded into frame 0" << std::endl;
    
    for(int i = 1; i < std::get<2>(info); i++){
        findpos = Find(frames, input[i]);
        if (findpos != -1) {
            outfile<<"Page " << input[i] << " already in frame " << findpos << std::endl;
        }else {
            if(frames[pos] == -1){
                outfile<<"Page "<< input[i] <<" loaded into frame " << pos << std::endl;
                frames[pos++] = input[i];
            }else {
                outfile<<"Page " << frames[pos] << " unloaded from Frame " << pos << ", Page " << input[i] << " loaded into Frame " << pos << std::endl;
                frames[pos++] = input[i];
            }
            ++pagefaults;
        }
        pos %= maxf;//Used to keep the position Between 0 and max frames
        //Ex: maxf = 9, position will go from 0 - 8 ALWAYS
    }
    outfile << pagefaults << " page faults" <<std::endl<<std::endl;
}

void Optimal(const std::vector<int> &input, const std::tuple<int, int, int> &info){
    std::vector<int> frames;
    int pos = 1;
    int maxf = std::get<1>(info);
    int pagefaults = 1;
    int findpos;
    
    for(int i = 0; i < maxf; i++)
        frames.push_back(-1);
    
    outfile<<"Optimal"<<std::endl;
    
    frames[0] = input[0];
    outfile<<"Page " << input[0] << " loaded into frame 0" << std::endl;
    
    for(int i = 1; i < std::get<2>(info); i++){
        findpos = Find(frames, input[i]);
        
        if (findpos != -1) {
            outfile<<"Page " << input[i] << " already in frame " << findpos << std::endl;
        }else {
            if(frames[pos] == -1){
                outfile<<"Page "<< input[i] <<" loaded into frame " << pos << std::endl;
                frames[pos++] = input[i];
            }else {
                //Esentially frames is full in this case
                int replacementpos = FindReplacementOpt(input, frames, i);
                
                outfile<<"Page " << frames[replacementpos] << " unloaded from Frame " << replacementpos << ", Page " << input[i] << " loaded into Frame " << replacementpos << std::endl;
                frames[replacementpos] = input[i];
            }
            ++pagefaults;
        }
        pos %= maxf;
    }
    outfile << pagefaults << " page faults"<<std::endl<<std::endl;
}

void LRU(const std::vector<int> &input, const std::tuple<int, int, int> &info){
    std::vector<int> frames;
    int pos = 1;
    int maxf = std::get<1>(info);
    int pagefaults = 1;
    int findpos;
    
    for(int i = 0; i < maxf; i++)
        frames.push_back(-1);
    
    outfile<<"LRU"<<std::endl;
    
    frames[0] = input[0];
    outfile<<"Page " << input[0] << " loaded into frame 0" << std::endl;
    
    for(int i = 1; i < std::get<2>(info); i++){
        findpos = Find(frames, input[i]);
        
        if (findpos != -1) {
            outfile<<"Page " << input[i] << " already in frame " << findpos << std::endl;
        }else {
            if(frames[pos] == -1){
                outfile<<"Page "<< input[i] <<" loaded into frame " << pos << std::endl;
                frames[pos++] = input[i];
            }else {
                //Esentially frames is full in this case
                int replacementpos = FindReplacementLRU(input, frames, i);
                
                outfile<<"Page " << frames[replacementpos] << " unloaded from Frame " << replacementpos << ", Page " << input[i] << " loaded into Frame " << replacementpos << std::endl;
                frames[replacementpos] = input[i];
            }
            ++pagefaults;
        }
        pos %= maxf;
    }
    outfile << pagefaults << " page faults"<<std::endl<<std::endl;
}

//Reads from file and obtains info and page requests
int main() {
    int pages=0, frames=0, reqs=0;
    std::vector<int> input;
    int collect;
    std::string filename = "input.txt";
    std::ifstream inputfile(filename);
    
    if(inputfile)
    {
        inputfile >> pages;
        inputfile >> frames;
        inputfile >> reqs;
        
        for(int i = 0; i < reqs; i++){
            inputfile >> collect;
            input.push_back(collect);
        }
        
        auto info = std::make_tuple(pages, frames, reqs);
        //3 Calls to the actual functions
        FIFO(input, info);
        Optimal(input, info);
        LRU(input, info);
    }else{
        outfile << "Cannot open file!";
        return -1;
    }
    
    return 0;
}
