#include <sys/ioctl.h>
#include<iostream>
#include<string>
#include<vector>
#include <unistd.h>

bool isPresent(std::string target, std::vector<std::string> data){
	for(int i = 0; i < data.size(); i++){
		if(data[i] == target) return true;
	}
	return false;
}

void output(std::string styles_string, std::string content = " "){
	std::vector<std::string> styles;
	std::string style_buffer = "";
	for(int i = 0; i < styles_string.size(); i++){
			if ((styles_string[i] == ',') && (style_buffer != "")){
				styles.push_back(style_buffer);
				style_buffer = "";
			}
			else if(styles_string[i] != ' '){
				style_buffer += styles_string[i];
			}
	}
	styles.push_back(style_buffer);//break up input string into array. Could be improved using iterator
	
	if(isPresent("red", styles)){
		system("printf $(tput setaf 1);");
	}else if(isPresent("green", styles)){
		system("printf $(tput setaf 2);");
	}else if(isPresent("yellow", styles)){
		system("printf $(tput setaf 3);");
	}else if(isPresent("blue", styles)){
		system("printf $(tput setaf 4);");
	}else if(isPresent("magenta", styles)){
		system("printf $(tput setaf 5);");
	}
	
	if(isPresent("background-red", styles)){
		system("printf $(tput setab 1);");
	}else if(isPresent("background-green", styles)){
		system("printf $(tput setab 2);");
	}else if(isPresent("background-yellow", styles)){
		system("printf $(tput setab 3);");
	}else if(isPresent("background-blue", styles)){
		system("printf $(tput setab 4);");
	}else if(isPresent("background-magenta", styles)){
		system("printf $(tput setab 5);");
	}
	
	if(isPresent("bold", styles)){
		system("printf $(tput bold)");
	}
	if(isPresent("underline", styles)){
		system("printf $(tput smul)");
	}
	if(isPresent("reverse", styles)){
		system("printf $(tput rev)");
	}
	if(isPresent("standout", styles)){
		system("printf $(tput smso)");
	}
	
	struct winsize size;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);
	int consoleWidth = size.ws_col;
	
	if(isPresent("center", styles)){
		int padding = (consoleWidth-content.size())/2;
		if (padding > 1){
			for(int i = 0; i < padding; i++){
				std::cout << " ";
			}
			std::cout << content;
			for(int i = 0; i < padding; i++){
				std::cout << " ";
			}
		}
		else{
			std::cout << content;
		}
		std::cout << std::endl;
		
	}
	else if(isPresent("line-break", styles)){
		for(int i = 0; i < consoleWidth; i++){
			std::cout << content.at(0);
		}
		std::cout << std::endl;
	}
	else{
		std::cout << content << std::endl;
	}
	system("printf $(tput sgr0);");
}
int main(){
	output("center, bold, fill-line,  background-magenta","Terminal Beauty Version 0.1");
	std::cout << "\n";
	output("center", "This allows styling of the console by using tput to set colors and styles.");
	std::cout << "\n";
	output("underline, bold", "Supported Colors:");
	output("red", "Red");
	output("blue", "Blue");
	output("green", "Green");
	output("yellow", "Yellow");
	output("magenta", "Magenta");
	std::cout << "\n";
	output("underline, bold", "Supported Formats:");
	output("underline", "Underlined");
	output("bold", "Bold");
	output("center", "Centered");
	
	std::cout << "\n";
	output("underline, bold", "Line Breaks:");
	output("background-blue, line-break", " ");
	output("background-yellow, line-break", " ");
	output("magenta, line-break", "_");
	
	std::cout << "\n";
	output("center", "Styles can be combined like so: ");
	output("bold, center, underline, background-yellow", "bold, center, underline, background-yellow");
	
	return 0;
}
