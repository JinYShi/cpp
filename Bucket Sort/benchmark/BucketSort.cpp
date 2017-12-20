#include "BucketSort.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <math.h>

unsigned int size(unsigned int num){
    return log10(num) + 1;
}

int findNumber(unsigned int number,unsigned int index){
    if(index > 0){
        return fmod(number/(std::pow(10,size(number)-1-index)),10);
    }else{
        while(number/10 > 0){
            number /= 10;
        }
        return number;
    }
}




std::vector<unsigned int> BucketSort::radix_sort(std::vector<unsigned int> numbers, unsigned index){
    if(numbers.size() <= 1) return numbers;
    std::vector<unsigned int> result{};
    std::vector<std::vector<unsigned int>> string_bu{10};
    for(auto item: numbers){
        if(index >= size(item)){
            result.push_back(item);
        }else{
            int a = findNumber(item,index);
            string_bu[a].push_back(item);
        }
    }

    for(auto i : string_bu){
        i = radix_sort(i,index+1);
        for(auto j: i){
            result.push_back(j);
        }

    }
    // for(auto i: result){
    //     std::cout<<i<<std::endl;
    // }

    return result;
}

// TODO: replace this with a parallel version. 
void BucketSort::sort(unsigned int numCores) {

    // for(auto i: numbersToSort){
    //     size(i);
    //     for(int j = 0;j < size(i);j++){
    //         findNumber(i,j);
    //     }
    // }

    // std::vector<unsigned int> a = radix_sort(numbersToSort,0);
    // numbersToSort.clear();
    // numbersToSort = a;

    // std::vector<std::string> a = changeToString(numbersToSort);
    std::vector<std::vector<unsigned int>> buck{10};
    std::vector<std::vector<unsigned int>> out_buck{10};
    // std::vector<std::string> result_string;

    for(auto i: numbersToSort){
        // int index = int(i[0])-'0';
        int index = findNumber(i,0);
        buck[index].push_back(i);   
    }

    std::vector<std::thread> threads;
    int check = 0;
    std::mutex buMut;
    auto sortBucket = [&](std::vector<std::vector<unsigned int>> buck){
        int i;
        while(true){
            {
                std::lock_guard<std::mutex> guard(buMut);
                if(buck.size() != unsigned (check)){
                    i = check;
                    ++check;
                }else
                    return;
            }
            out_buck[i] = radix_sort(buck[i],1);
        }
        

    };

    for(unsigned int i = 0;i < (numCores-1);++i){

        threads.push_back(std::thread(sortBucket,buck));
    } 
    // std::cout<<"check"<<out_buck.size()<<"\n";
    threads.push_back(std::thread(sortBucket,buck));

    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    numbersToSort.clear();
    for(auto i: out_buck){
        for(unsigned int j=0;j < i.size();j++){
           numbersToSort.push_back(i[j]);
        }
        // std::cout<<"\n";
    }


}






























