#include<iostream>
#include<string>
#include<vector>
template<typename T>
int findCompleteTags(std::vector<T> allTags){
	int complete = 0;
	for(int i = 0; i < allTags.size(); i++){
		if(allTags[i].complete()){
			complete++;
		}
	}

	return complete;
}
	
void output(std::string input, std::string end="\n"){
	struct tag{
		int start[2] = {-1, -1};
		int end[2] = {-1, -1};
		bool startOpen = true;
		bool endOpen = true;
		std::string startInfo;
		std::string endInfo;
		bool complete(){
			if(start[0] == -1 && start[1] == -1){
				startOpen = true;
			}
			if(end[0] == -1 && end[1] == -1){
				endOpen = true;
			}
			return !(startOpen or endOpen);
		}
	};
	std::vector<tag> allTags; 

	for(int i = 0; i < input.size(); i++){
		if(input[i] == '<'){
			if(findCompleteTags(allTags) == allTags.size()){
				tag newTag;
				newTag.start[0] = i;
				allTags.push_back(newTag);
			}else{
				allTags[findCompleteTags(allTags)].end[0] = i;
			}
		}
		else if(input[i] == '>'){
			if(allTags[findCompleteTags(allTags)].start[1] == -1){
				allTags[findCompleteTags(allTags)].start[1] = i;
			}
			else if(allTags[findCompleteTags(allTags)].end[1] == -1){
				allTags[findCompleteTags(allTags)].end[1] = i;
			}
		}
		
	}
	std::string openingContents = "";
	for(int i = allTags[0].start[0] + 1; i < allTags[0].start[1]; i++){
		openingContents += input[i];
	}
	std::string closingContents = "";
	for(int i = allTags[0].end[0]+1; i < allTags[0].end[1]; i++){
		closingContents += input[i];
	}


	for(int i = allTags[0].start[1] + 1; i < allTags[0].end[0]; i++){
		std::cout << input[i];
	}
	std::cout << end;

}
int main(){
	output("<bold color-blue>Hello World</>");

	return 0;
}
